#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*/
(c1) : Pas plus de 2 elements identiques adjacents
(c2) : Même nombre de 0 et de 1 par ligne/colonne
(c3) : Aucune ligne/colonne identique
CONVENTION : 
SI CONDITION RESPECTÉE : TRUE
SINON : FALSE
/*/

// AFFICHAGE
void affiche(int** tab, int n, int p){
    for(int i=0; i < n; i++){ 
        printf("[");
        for(int j = 0; j < p; j++){
            printf("%d ;", tab[i][j]);
        }
        printf("]\n");
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//===================================== VÉRIFICATION ============================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//C1 LIGNE
bool vrf_lig_adj(int ** grille, int n){
    bool etat = true;
    for(int i=0; i < n; i++){
        //printf("ligne %d\n", i);
        for(int j=0; j < n-2; j++){
            //printf("ligne %d : %d\n", i, (etat)&&(!((grille[i][j]==grille[i][j+1])&&(grille[i][j+1]==grille[i][j+2]))));
            etat = (etat)&&(!((grille[i][j]==grille[i][j+1])&&(grille[i][j+1]==grille[i][j+2])));
          //  printf("elt j : %d\n", grille[i][j]);
        }
    }
    return etat;
}

//C1 COLONNE
bool vrf_col_adj(int ** grille, int n){
    bool etat = true;
    for(int j=0; j < n; j++){
        for(int i=0; i < n-2; i++){
            //printf("colonne %d : %d\n", j, (etat)&&(!((grille[i][j]==grille[i+1][j])&&(grille[i+1][j]==grille[i+2][j]))));
            etat = (etat)&&(!((grille[i][j]==grille[i+1][j])&&(grille[i+1][j]==grille[i+2][j])));
        }
    }
    return etat;
}

//C2 LIGNE
bool vrf_lig_sum(int ** grille, int n){
    int res=0;
    bool etat = true;
    for(int i=0; i < n; i++){
        //printf("ligne %d\n", i);
        for(int j=0; j < n; j++){
            res=res+grille[i][j];
            //printf("elt j : %d\n", grille[i][j]);
        }
        etat=etat&&(res==n/2);
        res=0;
    }
    return etat;
}

//C2 COLONNE
bool vrf_col_sum(int ** grille, int n){
    int res=0;
    bool etat = true;
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            res=res+grille[j][i];
        }
        etat=etat&&(res==n/2);  
        res=0;
    }
    return etat;
}

//C3 LIGNE
// renvoie false si 2 colonnes sont identiques
// true sinon
bool vrf_lig_id(int ** grille, int n){
    for(int i=0; i < n; i++){ //parcours première ligne, 1er elt à comparer
        for(int j = i+1; j < n; j++){ //parcours du reste de la ligne depuis l'elt précédent
            if(grille[i][0]==grille[j][0]){ //si 2 premier elt de colonne sont identiques :
                int cpt=1;                   //on parcours les elts de chaque 2 à 2 
                while((cpt<n)&&(grille[i][cpt]==grille[j][cpt])){  //tant qu'ils sont égaux
                    cpt++;             
                }
                if(cpt==n){   //si on parvient jusqu'au bout de deux colonnes, alors 2 colonnes sont égales
                    return false;
                }
            }
        }
    }
    return true;
}

//C3 COLONNE
bool vrf_col_id(int ** grille, int n){
    for(int i=0; i < n; i++){ //parcours première colonne, 1er elt à comparer
        for(int j = i+1; j < n; j++){ //parcours du reste de la ligne depuis l'elt précédent
            if(grille[0][i]==grille[0][j]){ //si 2 premier elt de colonne sont identiques :
                int cpt=1;                   //on parcours les elts de chaque 2 à 2 
                while((cpt<n)&&(grille[cpt][i]==grille[cpt][j])){  //tant qu'ils sont égaux
                    cpt++;                   
                }
                if(cpt==n){   //si on parvient jusqu'au bout de deux colonnes, alors 2 colonnes sont égales
                    return false;
                }
            }
        }
    }
    return true;

}

//ALL IN ONE
bool vrf_all(int ** grille, int n){
    bool res = true;
    res = res&&(vrf_lig_adj(grille, n));
    res = res&&(vrf_col_adj(grille, n));
    res = res&&(vrf_lig_sum(grille, n));
    res = res&&(vrf_col_sum(grille, n));
    res = res&&(vrf_lig_id(grille, n));
    res = res&&(vrf_col_id(grille, n));
    return res;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//===================================== TRAITEMENT ==============================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool is_loss(int ** grille, int n){
    bool etat = false;
    for(int i=0; i < n; i++){ //parcours classique par elt
        for(int j = 0; j < n; j++){ 
            if (grille[i][j]==-1){
                etat=true;
            } //une donnée = -1 ?
        }
    }
    return etat;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//======================================= RÉSOLUTION ============================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ici on renvoie si des modifications ont eu lieu ou non (si oui, true)
bool res_c1_lig(int ** grille, int n){
    bool etat = false;
    for(int i=0; i < n; i++){ //parcours classique par elt
        for(int j = 0; j < n-2; j++){ 
            //cas 2 à coté (avant) 
            if((grille[i][j+1]==grille[i][j+2])&&(grille[i][j]==-1)){
                grille[i][j]=1-grille[i][j+1];
                etat=true;
            }
            //cas 2 à coté (après)
            if((grille[i][j]==grille[i][j+1])&&(grille[i][j+2]==-1)){
                grille[i][j+2]=1-grille[i][j];
                etat=true;
            }
            //cas 2 autour 
            if((grille[i][j]==grille[i][j+2])&&(grille[i][j+1]==-1)){
                grille[i][j+1]=1-grille[i][j];
                etat=true;
            }
        }
    }
    return etat;
}


bool res_c1_col(int ** grille, int n){
    bool etat = false;
    for(int i=0; i < n-2; i++){ //parcours classique par elt
        for(int j = 0; j < n; j++){ 
            //cas 2 à coté (avant) 
            if((grille[i+1][j]==grille[i+2][j])&&(grille[i][j]==-1)){
                grille[i][j]=1-grille[i+1][j];
                etat=true;
            }
            //cas 2 à coté (après)
            if((grille[i][j]==grille[i+1][j])&&(grille[i+2][j]==-1)){
                grille[i+2][j]=1-grille[i][j];
                etat=true;
            }
            //cas 2 autour 
            if((grille[i][j]==grille[i+2][j])&&(grille[i+1][j]==-1)){
                grille[i+1][j]=1-grille[i][j];
                etat=true;
            }
        }
    }
    return etat;
}




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//========================================= TESTS ===============================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void test_verif_trait(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS VERIFICATION ET TRAITEMENT\n");
    printf("-----\n");
    gril[0][0]=1;
    gril[0][1]=1;
    gril[0][2]=1;
    gril[0][3]=1;
    gril[1][0]=0;
    gril[1][1]=1;
    gril[1][2]=0;
    gril[1][3]=0;
    gril[2][0]=1;
    gril[2][1]=0;
    gril[2][2]=1;
    gril[2][3]=0;
    gril[3][0]=0;
    gril[3][1]=0;
    gril[3][2]=0;
    gril[3][3]=1;
    affiche(gril, n, n);
    printf("-----\n");
    printf("C1 : ligne : %d\n", vrf_lig_adj(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_adj(gril, n));
    printf("C2 : ligne : %d\n", vrf_lig_sum(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_sum(gril, n));
    printf("C3 : ligne : %d\n", vrf_lig_id(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_id(gril, n));
    printf("ALL : %d\n-----\n\n", vrf_all(gril, n));
    gril[0][0]=0;
    gril[0][2]=0;
    gril[1][2]=1;
    gril[3][0]=1;
    gril[3][3]=1;
    affiche(gril, n, n);
    printf("-----\n");
    printf("C1 : ligne : %d\n", vrf_lig_adj(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_adj(gril, n));
    printf("C2 : ligne : %d\n", vrf_lig_sum(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_sum(gril, n));
    printf("C3 : ligne : %d\n", vrf_lig_id(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_id(gril, n));
    printf("ALL : %d\n-----\n\n", vrf_all(gril, n));
    gril[1][0]=1;
    gril[1][1]=0;
    gril[2][0]=1;
    gril[3][3]=1;
    affiche(gril, n, n);
    printf("-----\n");
    printf("C1 : ligne : %d\n", vrf_lig_adj(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_adj(gril, n));
    printf("C2 : ligne : %d\n", vrf_lig_sum(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_sum(gril, n));
    printf("C3 : ligne : %d\n", vrf_lig_id(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_id(gril, n));
    printf("ALL : %d\n-----\n\n", vrf_all(gril, n));
    printf("PERTES : %d\n-----\n\n", is_loss(gril, n));
    gril[2][3]=-1;
    affiche(gril, n, n);
    printf("-----\n");
    printf("C1 : ligne : %d\n", vrf_lig_adj(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_adj(gril, n));
    printf("C2 : ligne : %d\n", vrf_lig_sum(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_sum(gril, n));
    printf("C3 : ligne : %d\n", vrf_lig_id(gril, n));
    printf("     colon : %d\n-----\n", vrf_col_id(gril, n));
    printf("ALL : %d\n-----\n\n", vrf_all(gril, n));
    printf("PERTES : %d\n-----\n", is_loss(gril, n));
}

void test_resolution(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS RÉSOLUTION\n");
    printf("-----\n");
    gril[0][0]=1;
    gril[0][1]=0;
    gril[0][2]=1;
    gril[0][3]=0;
    gril[1][0]=0;
    gril[1][1]=1;
    gril[1][2]=0;
    gril[1][3]=1;
    gril[2][0]=0;
    gril[2][1]=1;
    gril[2][2]=1;
    gril[2][3]=0;
    gril[3][0]=1;
    gril[3][1]=0;
    gril[3][2]=0;
    gril[3][3]=1;
    printf("is ok ? : %d", vrf_all(gril, n));
    affiche(gril, n, n);
    int c1col = res_c1_col(gril, n); //on associe TRUE ou FALSE s'il y a eu du changement 
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt col c1 : %d\n", c1col);
    int c1lig = res_c1_lig(gril, n); //idem
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt lig c1 : %d\n", c1lig);
}



int main(){
    //test_verif_trait();
    test_resolution();
    return 0;
}

