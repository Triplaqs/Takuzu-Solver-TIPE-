#ifndef PREUVE_H
#define PREUVE_H

#include <stdio.h>
#include <stdbool.h>

// MANIPULATION OBJETS

//libère les allocs d'une matrice
void freem(int ** gril, int n);

//Fonction récursive de remplissage 
void remplir(int ** gril, int n, int i, int j, int *cpt);


//calcul des grilles valides parmis les nxn
int cbn_grilles(int n);


//Fonction récursive de remplissage afin de stocker
void remplir_stock(int ** gril, int n, int i, int j, int *cpt, int*** res);

//stocke toutes les grilles valides de Takuzu
int*** stocker_grilles(int n);

//copie une grille
int** copy(int** grille, int n, int p);

//copie tableau
int* copyt(int*tab, int n);

//affiche tableau
void affichet(int*tab, int n);


// PREUVE

//prend une grille, sa taille et un tableau de coordonnées
//renvoie true si la grille sans toutes les cases du tableau admet une solution unique
bool unique(int** gril, int n, int*tab, int k);

//fonction puissance ahah
int pui(int a, int b);


//prend la dim du takuzu et le nombre de cases à indicer
//renvoie un tableau avec les tableaux d'indices de position
//res dim : n^k x 2k
//tab dim : 2k
void exhaustab(int n, int k, int* tab, int i, int**res, int*cpt);

//init exhaustab  
//n : dimension de la grille
//k : nombre de cases à enlever
//renvoie tab [[indices 1][indices 2]]
int** remplir_tab_cns(int n, int k);

//prend une grille, un tableau de tableaux de coordonnées et renvoie si la grille moins
//les coordonnées admet une unique solution
bool is_ok_tab(int**gril, int n, int k, int**tab);


//renvoie true si une grille de dim n est solvable pour toute k pertes
int is_solvable(int n, int k);

//Renvoie le nombre maximal de case possible à cacher avant de perdre l'unicité de la solution
int cns(int n);

// TESTS

//Tests partie manipulation
void test_manipulation();

//Tests partie preuve
void test_preuve();

#endif /* PREUVE_H */
