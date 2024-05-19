import numpy as np
import os
import sys
import cv2 as cv
import csv
print(cv.__version__)

"""
image = tableau de pixels (len = dim)
pixel = tableau de RGB    (len = 3)
Doc : https://docs.opencv.org/3.4/d2/de6/tutorial_py_setup_in_ubuntu.html
"""

#print(sys.path)
#print("chemin : ", os.path.exists("/home/triplaqs/Documents/MP2I/TIPE/Implé/pik10.png"), "\n\n")
#print("chemin : ", os.path.exists("/home/triplaqs/Documents/MP2I/TIPE/Implé"), "\n\n")


#########################################################################################
#################################-----TABLEAU/MATRICE-----###############################
#########################################################################################

#duplique un tableau sans pointeur
def copy(T):
    r = []
    for i in range(len(T)):
        r.append(T[i])
    return r

#affichage des matrices
def affiche(grille):
    n = len(grille)
    p = len(grille[0])
    print("[",end="")
    for i in range(n):
        #//estétique
        if (i==0):
            print("[", end="")
        else: 
            print(" [", end="")  
        #//affichage
        for j in range(p):
            print(grille[i][j], "; ", end="")
        #//estétique
        if (i<n-1):
            print("]")
        else: 
            print("]", end="")   
    print("]")

#affichage dédié à la fonction combinaisons()
def affiche_decomposition(R):
    if(len(R)==0):
        print("Image imcompatible")
    else:
        for i in range(len(R)):
            print(R[i])

def affiche_list_tak(L):
    for i in range(len(L)):
        print("[")
        for j in range(len(L[i])):
            affiche(L[i][j])
        print("]")


#########################################################################################
###################################-----TO BIN GRILL-----################################
#########################################################################################

#nombre to binaire (string)
@np.vectorize
def bis(num):
    return bin(num)[2:]

@np.vectorize
def bis8(num):
    res = bin(num)[2:]
    while(len(res)!=8):
        res='0'+res
    return res

#nombre to binaire (int)
def bii(num):
    return int(bin(num)[2:])

#binairise une matrice
def bin_list(grille : np.ndarray):
    return bis(grille)
    # res=grille
    # n=len(grille)
    # p=len(grille[0])
    # c=len(grille[0][0])
    # for i in range(n):
    #     for j in range(p):
    #         for k in range(c):
    #             print("original : ", grille[i][j][k], " ; bin : ", bis(grille[i][j][k]))
    #             print(bis(grille[i][j][k]))#////
    #             res[i][j][k]=bis(grille[i][j][k])
    #             print(type(res))
    #             print("res elt (bin attribué): ", res[i][j][k])
    # print("\ngrille binairisée")
    # return res

def bin_list8(grille : np.ndarray):
    return bis8(grille)

#Liste des carrés des nombres paires ou L[i]= ((i+1)*2)**2
L=[4, 16, 36, 64, 100, 144, 196]

#prend une grille, et renvoie le nombre de bits qu'elle comporte
def gti(grille):
    return len(grille)*len(grille[0])*3*8

#renvoie R liste des listes pour les possibles décompositions en grilles de coté paire
def combinaisons(grille, L):
    n=gti(grille)
    #print("nombre de bits : ", n, "\n") #RÉACTIVER POUR AFFICHAGE
    assert(n>=4)
    R=[]
    i=len(L)-1
    while(n<L[i]):
        i=i-1
    #print("multiple de 4 :", L[i])
    T=[]
    cbn(n, L, R, i, T)
    return R

#décomposition entammée avec le parcours précédent T (à ajouter si ça marche)
def cbn(n, L, R, i, T):
    #print("T (début appel)", T)
    k=n//L[i]
    if((n!=0)and(i>=0)):
        for j in range(k+1):
            Ttemp=copy(T)
            for u in range(j):
                Ttemp.append(L[i])
            #print("append : ", T.append(j))
            #print("temp   : ", Ttemp)
            #print(n,i,k)
            cbn(n-(j*L[i]), L, R, i-1, Ttemp)
    elif(n==0):
        R.append(T)
    else:
        return 0

#########################################################################################
####################################-----TO TAKUZU-----##################################
#########################################################################################
#grille = image
    
#prend une image et renvoie la suite des nombres binaires qui la composent IMG -> STR
def gril_to_str(grille):
    res = ''
    for i in range(len(grille)):
        for j in range(len(grille[0])):
            for k in range(len(grille[0][0])):
                res=res+ str(bis8(grille[i][j][k]))
    return res

def sqrt(num):
    for i in range(num):
        if(i**2==num):
            return i

#prend une suite de nombre et une décomposition Takuzu et renvoie la liste des grilles STR + 1 COMPO -> LIST TAK
def str_to_gril(string, T):
    cpt=0
    res=[]
    for k in range(len(T)):
        res.append([])
        dim = sqrt(T[k])
        for i in range(dim):
            res[k].append([])
            for j in range(dim):
                res[k][i].append(int(string[cpt]))
                cpt+=1
    return res

#prend une liste de composition un string et renvoie un tableau de tableau de grille de takuzus STR + COMPOS -> LIST LIST TAK
def compo_to_tak(string, decomposition):
    res = []
    for i in range(len(decomposition)):
        res.append(str_to_gril(string, decomposition[i]))
    return res

#prend la liste des liste de takuzus et les compositions, renvoie que les bonnes compositions
def bonnes_compos(takuzus, compos):
    res = []
    for k in range(len(takuzus)):
        temp=True
        for i in range(len(takuzus[k])):
            temp = temp and is_ok(takuzus[k][i])
        if(temp==True):
            res.append(compos[k])
    return res

#renvoie true si un elt est dans un tableau, faux sinon
def is_in_tab(tab, elt):
    for i in range(len(tab)):
        if(tab[i]==elt):
            return True
    return False

#prend un tableau et renvoie toutes les combinaisons à partir de ces elts
def _mult_comb(temp, res, tab, i, indices):
    if(i==len(tab)):
        if (not(is_in_tab(res, temp))):
            res.append(temp)
    for k in range(len(tab)):
        if (not(is_in_tab(indices, k))):
            indices2=copy(indices)
            indices2.append(k)
            temp2=copy(temp)
            temp2.append(tab[k])
            _mult_comb(temp2, res, tab, i+1, indices2)

#init _mult_comb
def mult_comb(tab):
    res=[]
    _mult_comb([], res, tab, 0, [])
    return res
    
def combinaisons_mult(img):
    all = combinaisons(img, L)
    res=[]
    for i in range(len(all)):
        temp=mult_comb(all[i])
        for j in range(len(temp)):
            res.append(temp[j])
    return res
    

#prend une image et renvoie les bonnes compos possibles pour l'encoder en Takuzu
def gril_to_compo(img):
    compos = combinaisons(img, L)
    string = gril_to_str(img)
    lltak = compo_to_tak(string, compos)
    return bonnes_compos(lltak, compos)


#prend une image et renvoie les bonnes compos possibles pour l'encoder en Takuzu
def gril_to_compo_mult(img):
    compos = combinaisons_mult(img)
    string = gril_to_str(img)
    lltak = compo_to_tak(string, compos)
    return bonnes_compos(lltak, compos)



#########################################################################################
###################################----VERIFICATION----##################################
#########################################################################################
#grille = takuzu

#C1 : pas plus de 2 nombres consécutifs
#C2 : autant de 1 que de 0 sur chaque ligne/colonne
#C3 : unicité de chaque ligne/colonne

#renvoie true si la règle est respectée, false sinon
def c1_lig(grille):
    res = True
    for i in range(len(grille)):
        for j in range(1, len(grille[0])-1):
            res = res and not((grille[i][j-1]==grille[i][j])and(grille[i][j]==grille[i][j+1]))
    return res

def c1_col(grille):
    res = True
    for i in range(1, len(grille)-1):
        for j in range(len(grille[0])):
            res = res and not((grille[i-1][j]==grille[i][j])and(grille[i][j]==grille[i+1][j]))
    return res

def c2_lig(grille):
    res = True
    for i in range(len(grille)):
        cpt1=0
        cpt0=0
        for j in range(len(grille[0])):
            if(grille[i][j]==0):
                cpt0+=1
            elif(grille[i][j]==1):
                cpt1+=1
        res=res and (cpt1==(len(grille))/2) and (cpt1==(len(grille))/2)
    return res 

def c2_col(grille):
    res = True
    for i in range(len(grille)):
        cpt1=0
        cpt0=0
        for j in range(len(grille[0])):
            if(grille[j][i]==0):
                cpt0+=1
            elif(grille[j][i]==1):
                cpt1+=1
        res=res and (cpt1==(len(grille))/2) and (cpt1==(len(grille))/2)
    return res 
            
def c3_col(grille):
    n=len(grille)
    for i in range(len(grille)):
        for j in range(i+1, len(grille[0])):
            if(grille[0][i]==grille[0][j]):
                cpt=1
                while((cpt<n)and(grille[cpt][i]==grille[cpt][j])):
                    cpt+=1
                if(cpt==n):
                    return False
    return True

def c3_lig(grille):
    n=len(grille)
    for i in range(len(grille)):
        for j in range(i+1, len(grille[0])):
            if(grille[i][0]==grille[j][0]):
                cpt=1
                while((cpt<n)and(grille[i][cpt]==grille[j][cpt])):
                    cpt+=1
                if(cpt==n):
                    return False
    return True

def is_ok(grille):
    res = True and c1_col(grille) and c1_lig(grille) and c2_col(grille) and c2_lig(grille) and c3_col(grille) and c3_lig(grille)
    return res

#########################################################################################
#######################################----TEST----######################################
#########################################################################################
print("\nTESTS\n")

MV = [[0, 1, 0, 1],
     [1, 0, 1, 0],
     [0, 1, 1, 0],
     [1, 0, 0, 1]]

MF = [[0, 1, 0, 0],
     [0, 1, 1, 0],
     [1, 1, 0, 1],
     [1, 1, 0, 1]]

MU = [[0, 1],
      [1, 0]]

print("c1 col : MV", c1_col(MV))
print("c1 lig : MV", c1_lig(MV))
print("c2 lig : MV", c2_lig(MV))
print("c2 col : MV", c2_col(MV))
print("c3 col : MV", c3_col(MV))
print("c3 lig : MV", c3_lig(MV))
print("is ok ?  MV", is_ok(MV))
print("")
print("c1 col : MF", c1_col(MF))
print("c1 lig : MF", c1_lig(MF))
print("c2 lig : MF", c2_lig(MF))
print("c2 col : MF", c2_col(MF))
print("c3 col : MF", c3_col(MF))
print("c3 lig : MF", c3_lig(MF))
print("is ok ?  MV", is_ok(MF))
print("")
print("c1 col : MF", c1_col(MU))
print("c1 lig : MF", c1_lig(MU))
print("c2 lig : MF", c2_lig(MU))
print("c2 col : MF", c2_col(MU))
print("c3 col : MF", c3_col(MU))
print("c3 lig : MF", c3_lig(MU))
print("is ok ?  MV", is_ok(MU))




#########################################################################################
#######################################----MAIN----######################################
#########################################################################################
print("\nMAIN\n")



#tronquage de la matrice image initiale
dim=2

#ouverture de l'image sous forme de matrice
img = cv.imread("/home/axel/Documents/TIPE/Implé/ex1.png")
img3 = cv.imread("/home/axel/Documents/TIPE/Implé/img2.png")
assert img is not None #image vide/non trouvée/erreur ?
#print(img)
temp=[]
temp = img[:dim]
#print(temp[0][:2])
car=[]
for i in range(dim):
    car.append([])
    car[i] = temp[i][:dim]
print("\ngrille de base :\n")
affiche(car)
print("\ngrille binairisée :\n")
affiche(bin_list(car))
print("\ngrille binairisée sur 8 bits :\n")
affiche(bin_list8(car))
#print("\ngrille binairisée V2 :\n")
#affiche_bin(bin_list(car))
print("\n\ncombinaisons de la grille :\n")
print("\ndimensions de l'image : 1x1 pixels")
affiche_decomposition(combinaisons([[['1', '1', '1']]], L))
print("\n décomposition complète")
affiche_decomposition(combinaisons_mult([[['1', '1', '1']]]))
print("img1 :")
affiche(car)
print("\ndimensions de l'image : 2x2 pixels")
affiche_decomposition(combinaisons(car, L))
print("\n v2 décomposition")
#affiche_decomposition(combinaisons_mult(car)) #TROP LOURD
print("\nimg1 :\n")
affiche(car)
print("\ntout le code binaire", gril_to_str(car))
print("")
affiche_decomposition(gril_to_compo(car))
img2= [[[60, 90, 150]]]
print("\nimg2 :")
affiche(img2)
print("string : ", gril_to_str(img2))
print("compositions : ")
affiche_decomposition(combinaisons(img2, L))
taks = compo_to_tak(gril_to_str(img2), combinaisons(img2, L))
affiche_list_tak(taks)
print("")
print("is ok toutes les grilles de cla composition")
for j in range(len(taks)):
    for i in range(len(taks[j])):
        print("grille compo ", j, " N°", i, " : ", is_ok(taks[j][i]))
    print("")

affiche_decomposition(gril_to_compo(img2))
print(gti(img3))
print(mult_comb([1,2, 3]))




#PIL 

#IMG -> TAK 
# CNS UNICITE 6X6