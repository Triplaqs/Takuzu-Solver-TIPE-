#include "takuzu.c"

int cpt;

//Fonction récursive de remplissage 
void remplir(int ** gril, int n, int i, int j, int *cpt){
    int ** grila = association(gril, n);
    int ** grilb = association(gril, n);
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






//vrf_all