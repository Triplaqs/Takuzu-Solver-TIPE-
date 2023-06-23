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
def bis(num):
    return str(bin(num)[2:])

def bii(num):
    return int(bin(num)[2:])


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


#print(sys.path)
#print("chemin : ", os.path.exists("/home/triplaqs/Documents/MP2I/TIPE/Implé/pik10.png"), "\n\n")
#print("chemin : ", os.path.exists("/home/triplaqs/Documents/MP2I/TIPE/Implé"), "\n\n")

img = cv.imread("/home/triplaqs/Documents/MP2I/TIPE/Implé/pik10.jpg")
assert img is not None
#print(img)
temp=[]
temp = img[:2]
#print(temp[0][:2])
car=[[],[]]
car[0] = temp[0][:2]
car[1] = temp[1][:2]  
print("\ngrille de base")
affiche(car)
print("\nessais")
affiche(bin_list(car))


