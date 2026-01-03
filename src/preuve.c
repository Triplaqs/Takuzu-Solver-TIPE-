#include "preuve.h"
#include "takuzu.h"
#include <time.h>
#include <stdio.h>

/*unsigned long long int add(unsigned long int n, unsigned long long int sum){
    return (n == 0) ? sum : add(n-1, n+sum); //tail recursion form
}*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//=================================== MANPILULATION =============================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void freem(int ** gril, int n){
    for(int i = 0; i<n; i++){
        free(gril[i]);
    }
    free(gril);
}

//Fonction récursive de remplissage 
void remplir(int ** gril, int n, int i, int j, int *cpt){
    int ** grila = association(gril, n);
    int ** grilb = association(gril, n);
    freem(gril, n);
    grila[i][j]=1;
    grilb[i][j]=0;
    if((i==n-1)&&(j==n-1)){
        if(vrf_all(grila, n)){
            *cpt=(*cpt)+1;
            free(grila);
        }
        if(vrf_all(grilb, n)){
            *cpt=(*cpt)+1;
            free(grilb);
        }
    }
    else{
        if(j==(n-1)){
            remplir(grila, n, (i+1), 0, cpt);
            remplir(grilb, n, (i+1), 0, cpt);
        }
        else{
            remplir(grila, n, i, (j+1), cpt);
            remplir(grilb, n, i, (j+1), cpt);
        }
    }
}

//calcul des grilles valides parmis les nxn
int cbn_grilles(int n){
    int ** grille=(int**)calloc(n, sizeof(int*));
    for(int i=0; i<n; i++){
        grille[i]=(int*)calloc(n, sizeof(int));
    }
    int cpt=0;
    remplir(grille, n, 0, 0, &cpt);
    return cpt;
}



//Fonction récursive de remplissage afin de stocker
void remplir_stock(int ** gril, int n, int i, int j, int *cpt, int*** res){
    int ** grila = association(gril, n);
    int ** grilb = association(gril, n);
    freem(gril, n);
    grila[i][j]=1;
    grilb[i][j]=0;
    if((i==n-1)&&(j==n-1)){
        if(vrf_all(grila, n)){
            res[(*cpt)]=grila;
            *cpt=(*cpt)+1;
        }
        if(vrf_all(grilb, n)){
            res[(*cpt)]=grilb;
            *cpt=(*cpt)+1;
        }
    }
    else{
        if(j==(n-1)){
            remplir_stock(grila, n, (i+1), 0, cpt, res);
            remplir_stock(grilb, n, (i+1), 0, cpt, res);
        }
        else{
            remplir_stock(grila, n, i, (j+1), cpt, res);
            remplir_stock(grilb, n, i, (j+1), cpt, res);
        }
    }
}

//stocke toutes les grilles valides de Takuzu
int*** stocker_grilles(int n){
    int num_mat_val=cbn_grilles(n);           //nombre de grilles valides
    int*** res = calloc(num_mat_val, sizeof(int**));
    int ** grille=(int**)calloc(n, sizeof(int*));
    for(int i=0; i<n; i++){
        grille[i]=(int*)calloc(n, sizeof(int));
    }
    int cpt=0;
    remplir_stock(grille, n, 0, 0, &cpt, res);
    return res;
}

int** copy(int** grille, int n, int p){
    int** res = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n; i++){
        res[i]=(int*)calloc(p, sizeof(int));
        for(int j=0; j<p; j++){
            res[i][j]=grille[i][j];
        }
    }
    return res;
}

int* copyt(int*tab, int n){
    int* res = (int*)calloc(n, sizeof(int));
    for(int i = 0; i<n; i++){
        res[i]=tab[i];
    }
    return res;
}

void affichet(int*tab, int n){
    printf("[ ");
    for(int i = 0; i<n; i++){
        printf("%d, ", tab[i]);
    }
    printf(" ]\n");
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//=====================================  PREUVE  ================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//prend une grille, sa taille et un tableau de coordonnées
//renvoie true si la grille sans toutes les cases du tableau admet une solution unique
bool unique(int** gril, int n, int*tab, int k){
    for(int i = 0; i<k; i++){
        gril[tab[2*i]][tab[2*i+1]]=-1;
    }
    bool res = resolution_pratique(gril, n);
    return res;
}

int pui(int a, int b){
    int res = 1;
    for(int i=0; i<b; i++){
        res= res*a;
    }
    return res;
}



//prend la dim du takuzu et le nombre de cases à indicer
//renvoie un tableau avec les tableaux d'indices de position
//res dim : n^k x 2k
//tab dim : 2k
void exhaustab(int n, int k, int* tab, int i, int**res, int*cpt){
    //n^k x 2k
    if(i==2*k){
        res[*cpt]=tab;
        *cpt=(*cpt)+1;
        return;
    }
    for(int j = 0; j<n; j++){
        int* tab2 = copyt(tab, 2*k);
        tab2[i]=j;
        exhaustab(n, k, tab2, i+1, res, cpt);
    }     
    free(tab);
}

//init exhaustab  
//n : dimension de la grille
//k : nombre de cases à enlever
//renvoie tab [[indices 1][indices 2]]
int** remplir_tab_cns(int n, int k){
    int p = pui(n, 2*k);
    int** res = (int**)calloc(p , sizeof(int*));
    for(int i=0; i<p; i++){
        res[i]=(int*)calloc(2*k, sizeof(int));
    }
    int cpt = 0;
    int*tab=(int*)calloc(2*k, sizeof(int));
    exhaustab(n, k, tab, 0, res , &cpt);
    return res;
}

//prend une grille, un tableau de tableaux de coordonnées et renvoie si la grille moins
//les coordonnées admet une unique solution
bool is_ok_tab(int**gril, int n, int k, int**tab){
    bool res= true;
    int p = pui(n, 2*k);
    for(int i = 0; i<p; i++){
        res=res&&(unique(gril, n, tab[i], k));
    }
    return res;
}


//renvoie true si une grille de dim n est solvable pour toute k pertes
int is_solvable(int n, int k){
    int*** all_grils = stocker_grilles(n);
    int**tab = remplir_tab_cns(n, k);
    int p = cbn_grilles(n);
    bool res=true;
    for(int i = 0; i<p; i++){
        res=res&&(is_ok_tab(all_grils[i], n, k, tab));
    }
    return res;

}

int cns(int n){
    bool res=true;
    for(int i = 0; i<(n*n)+1; i++){
        res=is_solvable(n, i);
        if(!res){
            return (i-1);
        }
    }
    return n*n;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//======================================  TESTS  ================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void test_manipulation(){
    //printf("result : %llu \n", add(1000000, 0));//OK
    printf("nb de grille valide en 2x2 : %d\n", cbn_grilles(2));
    printf("nb de grille valide en 4x4 : %d\n", cbn_grilles(4));
    //printf("nb de grille valide en 6x6 : %d\n", cbn_grilles(6));
    int*** res2 = stocker_grilles(2);
    int*** res4 = stocker_grilles(4);
    //printf("%d\n", res4[0][0][0]);
    //affiche(res4[0], 4, 4);
    //al();
    //affiche(res4[71], 4, 4);
}

void test_preuve(){
    int*** res2 = stocker_grilles(2);
    int*** res4 = stocker_grilles(4);
    int ** tab2 = remplir_tab_cns(2, 3);
    affichet(tab2[0], 6);
    affiche(res2[0], 2, 2);
    printf("%d\n", unique(res2[0], 2, tab2[0], 3));

    int ** tab4 = remplir_tab_cns(4, 3);
    affichet(tab4[4095], 6);
    //printf("is ok tab 2x2 : %d\n", is_ok_tab(res2[0], 2, 3, tab2));
    printf("is ok grille 2x2 pertes de 3 : %d\n", is_solvable(2, 3));
    printf("is ok grille 2x2 pertes de 4 : %d\n", is_solvable(2, 4));
    printf("cns de cases cachées en 2x2 : %d\n", cns(2));
    printf("cns de cases cachées en 4x4 : %d\n", cns(4));
    //printf("cns de cases cachées en 6x6 : %d\n", cns(6));

}

int main(){
    main2();
    //test_manipulation();
    test_preuve();
    return 0;
}




//vrf_all
