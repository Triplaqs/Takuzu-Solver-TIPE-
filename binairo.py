import numpy as np
import os
import sys
import cv2 as cv
print(cv.__version__)

"""
image = tableau de pixels (len = dim)
pixel = tableau de RGB    (len = 3)
Doc : https://docs.opencv.org/3.4/d2/de6/tutorial_py_setup_in_ubuntu.html
"""

#print(sys.path)
#print("chemin : ", os.path.exists("/home/triplaqs/Documents/MP2I/TIPE/Implé/pik10.png"), "\n\n")
#print("chemin : ", os.path.exists("/home/triplaqs/Documents/MP2I/TIPE/Implé"), "\n\n")



#nombre to binaire (string)
def bis(num):
    return str(bin(num)[2:])

#nombre to binaire (int)
def bii(num):
    return int(bin(num)[2:])

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

#binairise une matrice
def bin_list(grille):
    res=grille
    n=len(grille)
    p=len(grille[0])
    c=len(grille[0][0])
    for i in range(n):
        for j in range(p):
            for k in range(c):
                print("original : ", grille[i][j][k], " ; bin : ", bis(grille[i][j][k]))
                res[i][j][k]=bis(grille[i][j][k])
                # print("res elt (bin attribué): ", res[i][j][k])
    print("\ngrille binairisée")
    return res

#Liste des carrés des nombres paires ou L[i]= ((i+1)*2)**2
L=[4, 16, 36, 64, 100, 144, 196]

#prend une grille, et renvoie le nombre de bits qu'elle comporte
def gti(grille):
    return ((len(grille))**2)*3*8

#renvoie R liste des listes pour les possibles décompositions en grilles de coté paire
def combinaisons(grille, L):
    n=gti(grille)
    print("n : ", n)
    assert(n>=4)
    R=[]
    i=len(L)-1
    while(n<L[i]):
        i=i-1
    print("multiple de 4 :")
    print(L[i])
    T=[]
    cbn(n, L, R, i, T)
    return R

#décomposition entammée avec le parcours précédent T (à ajouter si ça marche)
def cbn(n, L, R, i, T):
    #print("T (début appel)", T)
    if(n<=0):
        return 0
    k=n%L[i]
    if(k!=0):
        for j in range(k):
            Ttemp=T
            Ttemp.append(j)
            #print("append : ", T.append(j))
            #print("temp   : ", Ttemp)
            print(n,i,k)
            cbn(n-(j*L[i]), L, R, i-1, Ttemp)
    else:
        R.append(T)
    

#tronquage de la matrice image initiale
dim=2

#ouverture de l'image sous forme de matrice
img = cv.imread("/home/axel/Documents/TIPE/Implé/ex1.png")
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
print("\ncombinaisons de la grille :\n")
print(combinaisons(car, L))




#PIL 

#IMG -> TAK 
# CNS UNICITE 6X6