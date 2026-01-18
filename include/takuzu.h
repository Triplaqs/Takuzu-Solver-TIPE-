#ifndef TAKUZU_H
#define TAKUZU_H

#include <stdio.h>
#include <stdbool.h>

//Affichage

//un affichage increvable non-esthétique de secours
void _affiche(int** tab, int n, int p);

//un affichage plus capricieux mais plus adapté visuellement à l'usage de ce fichier
void affiche(int** tab, int n, int p);

//aller à la ligne
void al();

//aller à la ligne + large espace
void alt();

//aller à la ligne + large espace + saut de ligne
void tr();

//Vérification

//C1 LIGNE
bool vrf_lig_adj(int ** grille, int n);


//C1 COLONNE
bool vrf_col_adj(int ** grille, int n);


//C2 LIGNE
bool vrf_lig_sum(int ** grille, int n);


//C2 COLONNE
bool vrf_col_sum(int ** grille, int n);


//C3 LIGNE
// renvoie false si 2 colonnes sont identiques
// true sinon
bool vrf_lig_id(int ** grille, int n);


//C3 COLONNE
bool vrf_col_id(int ** grille, int n);

//checkup global
bool vrf_all(int ** grille, int n);


//Traitement

//Il y a-t-il des pertes ?
bool is_loss(int ** grille, int n);


//renvoie le nombre de pertes sur une ligne (l = indice de la ligne sur la matrice)
int cbn_loss_lig(int ** grille, int n, int l);


//renvoie le nombre de pertes sur une colone (c = indice de la colone sur la matrice)
int cbn_loss_col(int ** grille, int n, int c);


int sum_lig(int ** grille, int n, int l);

int sum_lis_ptr(int * l, int n);


int sum_col(int ** grille, int n, int c);


//renvoie false s'il existe, false sinon
bool is_lig_ex(int ** grille, int n, int * lig);


bool is_col_ex(int ** grille, int n, int * lig);


int** association(int ** grille, int n);

//Traitement en cours


//VRFC =vérification en cours 
//C2 COLONNE
bool vrfc_col_cpt(int ** grille, int n);


//C2 LIGNE
bool vrfc_lig_cpt(int ** grille, int n);


//C1 LIGNE
bool vrfc_lig_adj(int ** grille, int n);


//C1 COLONNE
bool vrfc_col_adj(int ** grille, int n);


//C3 LIGNE
// renvoie false si 2 colonnes sont identiques (-1 non pris en compte)
// true sinon
bool vrfc_lig_id(int ** grille, int n);


//C3 COLONNE
bool vrfc_col_id(int ** grille, int n);


//renvoie true si la matrice respecte les règles même avec des pertes false sinon
bool is_ok_cours(int ** grille, int n);


//Résolution


//     ----> C1 <-------
// ici on renvoie si des modifications ont eu lieu ou non (si oui, true)
bool res_c1_lig(int ** grille, int n);


bool res_c1_col(int ** grille, int n);


//     ----> C2 <-------


bool res_c2_lig(int ** grille, int n);


bool res_c2_col(int ** grille, int n);

//     ----> C3 <-------

bool res_c3_lig(int ** grille, int n);


bool res_c3_col(int ** grille, int n);


bool res_all(int**grille, int n);


void resolve(int ** grille, int n);

//RESOUD LORS DE L'EXPLORATION EXHAUSTIVE RENVOIE 
//TRUE SI LE PROBLEME EST LA VALEUR DE BASE
//FALSE SI ON TOMBE DANS UNE IMPASSE 
bool resolve_absurde(int ** grille, int n);


void reso_exhaust(int ** grille, int n);


void resolution(int ** grille, int n);


bool resolution_pratique(int ** grille, int n);

//Tests


void test_verif_trait();

void test_traitement();

void test_traitement_cours();

void test_resolution_c1();

void test_resolution_c2();

void test_resolution_c3();

void test_resolution();

void exemple1();

void exemple2();

void exemple3();

void exemple4();

void exemple4();

int main0();

#endif /* TAKUZU_H */
