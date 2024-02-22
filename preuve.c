#include "takuzu.c"

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
        }
        if(vrf_all(grilb, n)){
            *cpt=(*cpt)+1;
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

int*** stocker_grilles(int n){
    return NULL;
}

int main(){
    main2();
    //printf("result : %llu \n", add(1000000, 0));//OK
    printf("nb de grille valide en 2x2 : %d\n", cbn_grilles(2));
    printf("nb de grille valide en 4x4 : %d\n", cbn_grilles(4));
    printf("nb de grille valide en 6x6 : %d\n", cbn_grilles(6));
    return 0;
}




//vrf_all