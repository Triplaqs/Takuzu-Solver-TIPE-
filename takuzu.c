#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/*/
(c1) : Pas plus de 2 elements identiques adjacents
(c2) : Même nombre de 0 et de 1 par ligne/colonne
(c3) : Aucune ligne/colonne identique
CONVENTION : 
SI CONDITION RESPECTÉE : TRUE
SINON : FALSE
/*/

// AFFICHAGE
void _affiche(int** tab, int n, int p){ //un affichage increvable non-esthétique de secours
    for(int i=0; i < n; i++){ 
        printf("[");
        for(int j = 0; j < p; j++){
            printf("%d ;", tab[i][j]);
        }
        printf("]\n");
    }
}

void affiche(int** tab, int n, int p){ //un affichage plus capricieux mais plus adapté visuellement à l'usage de ce fichier
    for(int i=0; i < n; i++){ 
        printf("[");
        for(int j = 0; j < p-1; j++){
            if(tab[i][j]!=-1){
                printf(" %d ;", tab[i][j]);
            }
            else{
                printf("%d ;", tab[i][j]);
            }
        }
        if(tab[i][p-1]!=-1){
                printf(" %d ]\n", tab[i][p-1]);
            }
            else{
                printf("%d ]\n", tab[i][p-1]);
            }
    }
}

void al(){
    printf("\n");
}

void alt(){
    printf("\n-----\n\n");
}

void tr(){
    printf("\n-----\n");
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

//renvoie le nombre de pertes sur une ligne (l = indice de la ligne sur la matrice)
int cbn_loss_lig(int ** grille, int n, int l){
    int cpt = 0;
    for(int i =0; i<n; i++){
        if( grille[l][i]==-1){
            cpt++;
        }
    }
    return cpt;
}

//renvoie le nombre de pertes sur une colone (c = indice de la colone sur la matrice)
int cbn_loss_col(int ** grille, int n, int c){
    int cpt = 0;
    for(int i =0; i<n; i++){
        if( grille[i][c]==-1){
            cpt++;
        }
    }
    return cpt;
}

int sum_lig(int ** grille, int n, int l){
    int cpt=0;
    for(int i=0; i<n; i++){
        cpt=cpt+grille[l][i];
    }
    return cpt;
}

int sum_lis_ptr(int * l, int n){
    int cpt=0;
    for(int i=0; i<n; i++){
        cpt=cpt+l[i];
    }
    return cpt;
}

int sum_col(int ** grille, int n, int c){
    int cpt=0;
    for(int i=0; i<n; i++){
        cpt=cpt+grille[i][c];
    }
    return cpt;
}

//renvoie false s'il existe, false sinon
bool is_lig_ex(int ** grille, int n, int * lig){
    bool etat=false;
    for(int i= 0; i<n; i++){
        bool exit=true;
        for(int j =0; j<n; j++){
            if(!(grille[i][j]==lig[j])){
                exit=false;
                break;
            }         
        }
        etat=etat||exit;
    }
    return etat;
}

bool is_col_ex(int ** grille, int n, int * lig){
    bool etat=false;
    for(int i= 0; i<n; i++){
        bool exit=true;
        for(int j =0; j<n; j++){
            if(!(grille[j][i]==lig[j])){
                exit=false;
                break;
            }         
        }
        etat=etat||exit;
    }
    return etat;
}

int** association(int ** grille, int n){
    int ** grilleb;
    grilleb=(int**)calloc(n, sizeof(int*));
    for(int i= 0; i<n; i++){
        grilleb[i]=(int*)calloc(n, sizeof(int));
        for(int j =0; j<n; j++){
            grilleb[i][j]=grille[i][j];
        }
    }
    return grilleb;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//================================== TRAITEMENT EN COURS ========================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//VRFC =vérification en cours 
//C2 COLONNE
bool vrfc_col_cpt(int ** grille, int n){
    int cpt0 = 0;
    int cpt1 = 0;
    bool etat = true;
    for(int i=0; i < n; i++){
        cpt0=0;
        cpt1=0;
        for(int j=0; j < n; j++){
            if(grille[j][i]==0){
                cpt0 ++;
            }
            else if(grille[j][i]==1){
                cpt1 ++;
            }
        }
        //printf("1 : %d, 0 : %d", cpt1, cpt0);
        etat=etat&&(cpt1<=(n/2))&&(cpt0<=(n/2));
    }
    return etat;
}

//C2 LIGNE
bool vrfc_lig_cpt(int ** grille, int n){
    int cpt0 = 0;
    int cpt1 = 0;
    bool etat = true;
    for(int i=0; i < n; i++){
        cpt0=0;
        cpt1=0;
        for(int j=0; j < n; j++){
            if(grille[i][j]==0){
                cpt0 ++;
            }
            else if(grille[i][j]==1){
                cpt1 ++;
            }
        }
        //printf("1 : %d, 0 : %d", cpt1, cpt0);
        etat=etat&&(cpt1<=(n/2))&&(cpt0<=(n/2));
    }
    return etat;
}

//C1 LIGNE
bool vrfc_lig_adj(int ** grille, int n){
    bool etat = true;
    for(int i=0; i < n; i++){
        //printf("ligne %d\n", i);
        for(int j=0; j < n-2; j++){
            //printf("ligne %d : %d\n", i, (etat)&&(!((grille[i][j]==grille[i][j+1])&&(grille[i][j+1]==grille[i][j+2]))));
            etat = (etat)&&(!((grille[i][j]==grille[i][j+1])&&(grille[i][j+1]==grille[i][j+2])&&((grille[i][j]==1)||(grille[i][j]==0))));
          //  printf("elt j : %d\n", grille[i][j]);
        }
    }
    return etat;
}

//C1 COLONNE
bool vrfc_col_adj(int ** grille, int n){
    bool etat = true;
    for(int j=0; j < n; j++){
        for(int i=0; i < n-2; i++){
            //printf("colonne %d : %d\n", j, (etat)&&(!((grille[i][j]==grille[i+1][j])&&(grille[i+1][j]==grille[i+2][j]))));
            etat = (etat)&&(!((grille[i][j]==grille[i+1][j])&&(grille[i+1][j]==grille[i+2][j])&&((grille[i][j]==1)||(grille[i][j]==0))));
        }
    }
    return etat;
}



//C3 LIGNE
// renvoie false si 2 colonnes sont identiques (-1 non pris en compte)
// true sinon
bool vrfc_lig_id(int ** grille, int n){
    for(int i=0; i < n; i++){ //parcours première ligne, 1er elt à comparer
        for(int j = i+1; j < n; j++){ //parcours du reste de la ligne depuis l'elt précédent
            if(grille[i][0]==grille[j][0]){ //si 2 premier elt de colonne sont identiques :
                int cpt=1;                   //on parcours les elts de chaque 2 à 2 
                while((cpt<n)&&(grille[i][cpt]==grille[j][cpt])&&(grille[j][cpt]!=-1)){  //tant qu'ils sont égaux
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
bool vrfc_col_id(int ** grille, int n){
    for(int i=0; i < n; i++){ //parcours première colonne, 1er elt à comparer
        for(int j = i+1; j < n; j++){ //parcours du reste de la ligne depuis l'elt précédent
            if(grille[0][i]==grille[0][j]){ //si 2 premier elt de colonne sont identiques :
                int cpt=1;                   //on parcours les elts de chaque 2 à 2 
                while((cpt<n)&&(grille[cpt][i]==grille[cpt][j])&&(grille[cpt][j]!=-1)){  //tant qu'ils sont égaux
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



//renvoie true si la matrice respecte les règles même avec des pertes false sinon
bool is_ok_cours(int ** grille, int n){
    bool res = true;
    res = res&&(vrfc_lig_adj(grille, n));
    res = res&&(vrfc_col_adj(grille, n));
    res = res&&(vrfc_lig_cpt(grille, n));
    res = res&&(vrfc_col_cpt(grille, n));
    res = res&&(vrfc_lig_id(grille, n));
    res = res&&(vrfc_col_id(grille, n));
    return res;
}




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++chap
//======================================= RÉSOLUTION ============================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//     ----> C1 <-------

// ici on renvoie si des modifications ont eu lieu ou non (si oui, true)
bool res_c1_lig(int ** grille, int n){
    bool etat = false;
    for(int i=0; i < n; i++){ //parcours classique par elt
        for(int j = 0; j < n-2; j++){ 
            //cas 2 à coté (avant) 
            if((grille[i][j+1]==grille[i][j+2])&&(grille[i][j]==-1)&&(grille[i][j+1]!=-1)){
                grille[i][j]=1-grille[i][j+1];
                etat=true;
            }
            //cas 2 à coté (après)
            if((grille[i][j]==grille[i][j+1])&&(grille[i][j+2]==-1)&&(grille[i][j]!=-1)){
                grille[i][j+2]=1-grille[i][j];
                etat=true;
            }
            //cas 2 autour 
            if((grille[i][j]==grille[i][j+2])&&(grille[i][j+1]==-1)&&(grille[i][j]!=-1)){
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
            if((grille[i+1][j]==grille[i+2][j])&&(grille[i][j]==-1)&&(grille[i+1][j]!=-1)){
                grille[i][j]=1-grille[i+1][j];
                etat=true;
            }
            //cas 2 à coté (après)
            if((grille[i][j]==grille[i+1][j])&&(grille[i+2][j]==-1)&&(grille[i+1][j]!=-1)){
                grille[i+2][j]=1-grille[i][j];
                etat=true;
            }
            //cas 2 autour 
            if((grille[i][j]==grille[i+2][j])&&(grille[i+1][j]==-1)&&(grille[i][j]!=-1)){
                grille[i+1][j]=1-grille[i][j];
                etat=true;
            }
        }
    }
    return etat;
}


//     ----> C2 <-------


bool res_c2_lig(int ** grille, int n){
    bool etat = false;
    for(int i =0; i<n; i++){
        if (cbn_loss_lig(grille, n, i)==1){
            for(int j=0; j<n; j++){
                if(grille[i][j]==-1){
                    if(sum_lig(grille, n, i)==((n/2)-2)){
                        grille[i][j]=1;
                        etat=true;
                    }
                    if(sum_lig(grille, n, i)==((n/2)-1)){
                        grille[i][j]=0;
                        etat=true;
                    }
                }
            }
        }   
    }
    return etat;
}

bool res_c2_col(int ** grille, int n){
    bool etat = false;
    for(int j =0; j<n; j++){
        if (cbn_loss_col(grille, n, j)==1){
            for(int i=0; i<n; i++){
                if(grille[i][j]==-1){
                    if(sum_col(grille, n, j)==((n/2)-2)){
                        grille[i][j]=1;
                        etat=true;
                    }
                    if(sum_col(grille, n, j)==((n/2)-1)){
                        grille[i][j]=0;
                        etat=true;
                    }
                }
            }
        }   
    }
    return etat;
}

//     ----> C3 <-------

bool res_c3_lig(int ** grille, int n){
    bool etat = false;
    for(int i =0; i<n; i++){
        if (cbn_loss_lig(grille, n, i)==2){ //filtrage des lignes avec uniquement 2 pertes
            //printf("arrive -> ind %d\n", i);
            int * liga=(int*)calloc(n, sizeof(int));
            int * ligb=(int*)calloc(n, sizeof(int));
            int cpt=0;
            int * inda=(int*)calloc(n, sizeof(int));
            int * indb = (int*)calloc(n, sizeof(int));
            for(int j=0; j<n; j++){
                if(grille[i][j]==-1){ //essayage des 2 combinaisons possibles
                    assert(cpt!=2);
                    if(cpt==1){
                        //printf("inda : %d\n", *inda);
                        liga[j]=0;
                        ligb[j]=1;
                        int b = j;
                        *indb=b;
                        cpt++;
                        //printf("assignation b à %d (indb : %d)\n", j, *indb);
                        //printf("inda : %d\n", *inda);
                    }
                    else if(cpt==0){
                        liga[j]=1;
                        ligb[j]=0;
                        int a = j;
                        *inda=a;
                        cpt++;
                        //printf("assignation a à %d (inda : %d)\n", j, *inda);
                    }
                }
                else{
                    liga[j]=grille[i][j];
                    ligb[j]=grille[i][j];
                }
                //printf("inda : %d\nindb : %d\ncpt : %d\n", *inda, *indb, cpt);
            }
            /*int ** mata = (int **)calloc(1, sizeof(int*));
            mata[0]=liga;
            int ** matb = (int **)calloc(1, sizeof(int*));
            matb[0]=ligb;
            affiche(mata, 1, n);
            affiche(matb, 1, n);*/
            //printf("inda : %d\nindb : %d\ncpt : %d\n", *inda, *indb, cpt);
            if(sum_lis_ptr(liga, n)!=n/2){ //verification qu'il manque bien un 1 et un 0, sinon, la C2 fera l'affaire 
                //printf("IF 1\n");
                break;
            }
            if(!(is_lig_ex(grille, n, liga))&&!(is_lig_ex(grille, n, ligb))){ //si les 2 ne sont pas dans la grille, on a pas plus d'Info, on abandonne
                //printf("IF 2\n");
                break;
            }
            assert(is_lig_ex(grille, n, liga)!=is_lig_ex(grille, n, ligb)); //si les 2 sont dans la grille, on a un problème, la bonne solution devrait être parmis les 2.
            
            if((is_lig_ex(grille, n, liga))&&!(is_lig_ex(grille, n, ligb))){  //si la première ligne est déjà dedans et pas la 2ème, alors la 2ème est solution
                grille[i][*inda]=0;
                grille[i][*indb]=1;
                etat=true;
                //printf("ISSUE 1\n");
            }
            if(!(is_lig_ex(grille, n, liga))&&(is_lig_ex(grille, n, ligb))){  //et inversement
                grille[i][*inda]=1;
                grille[i][*indb]=0;
                etat=true;
                //printf("ISSUE 2\n");
            }
        }   
    }
    return etat;
}

bool res_c3_col(int ** grille, int n){
    bool etat = false;
    for(int i =0; i<n; i++){
        if (cbn_loss_col(grille, n, i)==2){ //filtrage des lignes avec uniquement 2 pertes
            //printf("arrive -> ind %d\n", i);
            int * cola=(int*)calloc(n, sizeof(int));
            int * colb=(int*)calloc(n, sizeof(int));
            int cpt=0;
            int * inda=(int*)calloc(n, sizeof(int));
            int * indb = (int*)calloc(n, sizeof(int));
            for(int j=0; j<n; j++){
                if(grille[j][i]==-1){ //essayage des 2 combinaisons possibles
                    assert(cpt!=2);
                    if(cpt==1){
                        //printf("inda : %d\n", *inda);
                        cola[j]=0;
                        colb[j]=1;
                        int b = j;
                        *indb=b;
                        cpt++;
                        //printf("assignation b à %d (indb : %d)\n", j, *indb);
                        //printf("inda : %d\n", *inda);
                    }
                    else if(cpt==0){
                        cola[j]=1;
                        colb[j]=0;
                        int a = j;
                        *inda=a;
                        cpt++;
                        //printf("assignation a à %d (inda : %d)\n", j, *inda);
                    }
                }
                else{
                    cola[j]=grille[j][i];
                    colb[j]=grille[j][i];
                }
                //printf("inda : %d\nindb : %d\ncpt : %d\n", *inda, *indb, cpt);
            }
            /*int ** mata = (int **)calloc(n, sizeof(int*));
            int ** matb = (int **)calloc(n, sizeof(int*));
            for(int k =0; k<n; k++){
                mata[k]=(int *)calloc(1, sizeof(int));
                matb[k]=(int *)calloc(1, sizeof(int));
                mata[k][0]=cola[k];
                matb[k][0]=colb[k];
            }
            affiche(mata, n, 1);
            affiche(matb, n, 1);*/
            //printf("inda : %d\nindb : %d\ncpt : %d\n", *inda, *indb, cpt);
            if(sum_lis_ptr(cola, n)!=n/2){ //verification qu'il manque bien un 1 et un 0, sinon, la C2 fera l'affaire 
                //printf("IF 1\n");
                break;
            }
            if(!(is_col_ex(grille, n, cola))&&!(is_col_ex(grille, n, colb))){ //si les 2 ne sont pas dans la grille, on a pas plus d'Info, on abandonne
                //printf("IF 2\n");
                break;
            }
            assert(is_col_ex(grille, n, cola)!=is_col_ex(grille, n, colb)); //si les 2 sont dans la grille, on a un problème, la bonne solution devrait être parmis les 2.
            
            if((is_col_ex(grille, n, cola))&&!(is_col_ex(grille, n, colb))){  //si la première ligne est déjà dedans et pas la 2ème, alors la 2ème est solution
                grille[*inda][i]=0;
                grille[*indb][i]=1;
                etat=true;
                //printf("ISSUE 1\n");
            }
            if(!(is_col_ex(grille, n, cola))&&(is_col_ex(grille, n, colb))){  //et inversement
                grille[*inda][i]=1;
                grille[*indb][i]=0;
                etat=true;
                //printf("ISSUE 2\n");
            }
        }   
    }
    return etat;
}


bool res_all(int**grille, int n){
    bool res = false;
    res=res||(res_c1_col(grille, n));
    res=res||(res_c1_lig(grille, n));
    res=res||(res_c2_col(grille, n));
    res=res||(res_c2_lig(grille, n));
    res=res||(res_c3_col(grille, n));
    res=res||(res_c3_lig(grille, n));
    return res;
}

void resolve(int ** grille, int n){
    bool is=true;

    while(is){
        is=res_all(grille, n);
    }
}

//RESOUD LORS DE L'EXPLORATION EXHAUSTIVE RENVOIE 
//TRUE SI LE PROBLEME EST LA VALEUR DE BASE
//FALSE SI ON TOMBE DANS UNE IMPASSE 
bool resolve_absurde(int ** grille, int n){
    bool is=true;
    while(is&&(is_ok_cours(grille, n))){
        is=res_all(grille, n);
    }
    if(!is_ok_cours(grille, n)){
        return true;
    }
    else if(!is){
        return false;
    }
    else{
        return false;
        }
}

void reso_exhaust(int ** grille, int n){
    int ** grilleb;
    while(!(vrf_all(grille, n))){  //tant que la grille n'est pas remplie
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(grille[i][j]==-1){     //on recherche les pertes
                    grilleb = association(grille, n);
                    grilleb[i][j]=1;        
                    if(resolve_absurde(grilleb, n)){   //on essaye de developper avec une valeur
                        grille[i][j]=0;
                    }
                    else{
                        grilleb=association(grille, n);
                        grilleb[i][j]=0;
                        if(resolve_absurde(grilleb, n)){   //on essaye de developper avec une valeur
                           grille[i][j]=1;
                        }
                    }
                    resolve(grille, n);
                }
            }
        }
    }
}

void resolution(int ** grille, int n){
    resolve(grille, n);
    reso_exhaust(grille, n);
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



void test_traitement(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS TRAITEMENT\n");
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
    affiche(gril, n, n);
    tr();
    printf("is okay ? : %d\n", vrf_all(gril, n));
    printf("is loss ? : %d\n", is_loss(gril, n));
    gril[1][3]=-1;
    gril[2][2]=-1;
    gril[2][3]=-1;
    gril[3][0]=-1;
    alt();
    affiche(gril, n, n);
    tr();
    printf("is okay ? : %d\n", vrf_all(gril, n));
    printf("is loss ? : %d\n", is_loss(gril, n));
    alt();
    for(int i=0; i<4; i++){
        printf("lig %d got %d loss. \n", i, cbn_loss_lig(gril, n, i));
    }
    tr();
    for(int i=0; i<4; i++){
        printf("col %d got %d loss. \n", i, cbn_loss_col(gril, n, i));
    }
    alt();
     for(int i=0; i<n; i++){
        printf("somme lignes %d : %d\n", i, sum_lig(gril, n, i));
    }
    tr();
    for(int i=0; i<n; i++){
        printf("somme colones %d : %d\n", i, sum_col(gril, n, i));
    }
    alt();
    int * l1 = (int *)calloc(4, sizeof(int));
    int * l2 = (int *)calloc(4, sizeof(int));
    l1[0]=1; l1[1]=0; l1[2]=1; l1[3]=0;
    l2[0]=1; l2[1]=0; l2[2]=0; l2[3]=1;
    printf("is lig [1,0,1,0] in ? : %d\n", is_lig_ex(gril, n, l1));
    printf("is lig [1,0,0,1] in ? : %d\n", is_lig_ex(gril, n, l2));
    alt();
    int * c1 = (int *)calloc(4, sizeof(int));
    int * c2 = (int *)calloc(4, sizeof(int));
    c1[0]=0; c1[1]=1; c1[2]=1; c1[3]=0;
    c2[0]=1; c2[1]=0; c2[2]=0; c2[3]=1;
    printf("is col [0,1,1,0] in ? : %d\n", is_lig_ex(gril, n, l1));
    printf("is col [1,0,0,1] in ? : %d\n", is_lig_ex(gril, n, l2));
    alt();
}

void test_traitement_cours(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS TRAITEMENT\n");
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
    affiche(gril, n, n);
    tr();
    printf("is okay ? : %d\n", vrf_all(gril, n));
    printf("is loss ? : %d\n", is_loss(gril, n));
    gril[1][3]=-1;
    gril[2][2]=-1;
    gril[2][3]=-1;
    gril[3][0]=-1;
    alt();
    affiche(gril, n, n);
    tr();
    printf("verif c2 colomne %d\n", vrfc_col_cpt(gril, n));
    printf("verif c2 ligne   %d\n", vrfc_lig_cpt(gril, n));
    gril[3][1]=1;
    gril[3][2]=1;
    gril[1][2]=1;
    alt();
    affiche(gril, n, n);
    tr();
    printf("verif c2 colomne %d\n", vrfc_col_cpt(gril, n));
    printf("verif c2 ligne   %d\n", vrfc_lig_cpt(gril, n));  
    alt();
    gril[3][2]=-1;
    gril[1][2]=-1;
    gril[2][1]=-1;
    affiche(gril, n, n);
    tr();
    printf("verif c1 colomne %d\n", vrfc_col_adj(gril, n));
    printf("verif c1 ligne   %d\n", vrfc_lig_adj(gril, n));
    gril[2][2]=1;
    gril[1][2]=1;
    gril[1][3]=1;
    affiche(gril, n, n);
    tr();
    printf("verif c1 colomne %d\n", vrfc_col_adj(gril, n));
    printf("verif c1 ligne   %d\n", vrfc_lig_adj(gril, n));
    gril[3][2]=-1;
    gril[1][2]=-1;
    gril[2][1]=-1;
    gril[0][1]=1;
    gril[1][1]=-1;
    gril[2][1]=1;
    gril[3][1]=-1;
    gril[3][0]=0;
    affiche(gril, n, n);
    tr();
    printf("verif c3 colomne %d\n", vrfc_col_id(gril, n));
    printf("verif c3 ligne   %d\n", vrfc_lig_id(gril, n));
    gril[1][1]=1;
    gril[1][2]=1;
    gril[3][1]=1;
    gril[3][2]=1;
    affiche(gril, n, n);
    tr();
    printf("verif c3 colomne %d\n", vrfc_col_id(gril, n));
    printf("verif c3 ligne   %d\n", vrfc_lig_id(gril, n));

    //A FAIRE CONTINUE TESTER VRFC LIG/COL ADJ (update : compté sans les -1)
}

void test_resolution_c1(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS RÉSOLUTION C1\n");
    printf("-----\n");
    gril[0][0]=1;
    gril[0][1]=0;
    gril[0][2]=1;
    gril[0][3]=0;
    gril[1][0]=0;
    gril[1][1]=1;
    gril[1][2]=0;
    gril[1][3]=-1;
    gril[2][0]=0;
    gril[2][1]=1;
    gril[2][2]=-1;
    gril[2][3]=-1;
    gril[3][0]=-1;
    gril[3][1]=0;
    gril[3][2]=0;
    gril[3][3]=1;
    printf("is ok ? : %d\n\n", vrf_all(gril, n));
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
    int c1col2 = res_c1_col(gril, n);  
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt col c1 : %d\n", c1col2);
    printf("is ok ? : %d\n", vrf_all(gril, n));
    int c1col3 = res_c1_col(gril, n);  
    int c1lig2 = res_c1_lig(gril, n);
    printf("\nrappel des fonctions : changement ?\ncol c1 : %d\nlig c1 : %d\n\n-----\n", c1col3, c1lig2);
}


void test_resolution_c2(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS RÉSOLUTION C2\n");
    printf("-----\n");
    gril[0][0]=1;
    gril[0][1]=0;
    gril[0][2]=1;
    gril[0][3]=0;
    gril[1][0]=0;
    gril[1][1]=1;
    gril[1][2]=0;
    gril[1][3]=-1;
    gril[2][0]=0;
    gril[2][1]=1;
    gril[2][2]=-1;
    gril[2][3]=-1;
    gril[3][0]=-1;
    gril[3][1]=0;
    gril[3][2]=0;
    gril[3][3]=1;
    printf("is ok ? : %d\n\n", vrf_all(gril, n));
    affiche(gril, n, n);
    int c2col = res_c2_col(gril, n); //on associe TRUE ou FALSE s'il y a eu du changement

    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt col c2 : %d\n", c2col);
    int c2lig = res_c2_lig(gril, n); //idem
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt lig c2 : %d\n", c2lig);
    int c2col2 = res_c2_col(gril, n);  
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt col c2 : %d\n", c2col2);
    printf("is ok ? : %d\n", vrf_all(gril, n));
    int c2col3 = res_c2_col(gril, n);  
    int c2lig2 = res_c2_lig(gril, n);
    printf("\nrappel des fonctions : changement ?\ncol c1 : %d\nlig c1 : %d\n\n-----\n", c2col3, c2lig2);
   
}

void test_resolution_c3(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS RÉSOLUTION C3\n");
    printf("-----\n");
    gril[0][0]=1;
    gril[0][1]=0;
    gril[0][2]=-1;
    gril[0][3]=-1;
    gril[1][0]=0;
    gril[1][1]=1;
    gril[1][2]=1;
    gril[1][3]=0;
    gril[2][0]=1;
    gril[2][1]=0;
    gril[2][2]=0;
    gril[2][3]=1;
    gril[3][0]=-1;
    gril[3][1]=-1;
    gril[3][2]=0;
    gril[3][3]=1;
    affiche(gril, n, n);
    alt();
    int c3lig = res_c3_lig(gril, n); 
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt lig c3 : %d\n", c3lig);
    alt();
    /*int * liga = (int *)calloc(4, sizeof(int));
    liga[0]=1; liga[1]=0; liga[2]=0; liga[3]=1;
    int * ligb = (int *)calloc(4, sizeof(int));
    ligb[0]=1; ligb[1]=0; ligb[2]=1; ligb[3]=0;
    printf("is in test [1, 0, 0, 1] ? %d\n", is_lig_ex(gril, n, liga));
    printf("is in test [1, 0, 1, 0] ? %d\n", is_lig_ex(gril, n, ligb));*/
    gril[1][2]=-1;
    gril[2][2]=-1;
    gril[1][3]=-1;
    gril[2][3]=-1;
    affiche(gril, n, n);
    int c3col = res_c3_col(gril, n); 
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    printf("\nchmt col c3 : %d\n", c3col);
    al();
    printf("is ok ? : %d\n", vrf_all(gril, n));
    alt();
}

void test_resolution(){
    int n=4;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nTESTS RÉSOLUTION\n");
    printf("-----\n");
    al();
    gril[0][0]=1;
    gril[0][1]=0;
    gril[0][2]=-1;
    gril[0][3]=-1;
    gril[1][0]=-1;
    gril[1][1]=1;
    gril[1][2]=-1;
    gril[1][3]=0;
    gril[2][0]=1;
    gril[2][1]=-1;
    gril[2][2]=0;
    gril[2][3]=1;
    gril[3][0]=-1;
    gril[3][1]=-1;
    gril[3][2]=0;
    gril[3][3]=-1;
    affiche(gril, n, n);
    al();
    resolve(gril, n); 
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    al();
    printf("is ok ? : %d\n", vrf_all(gril, n));
    alt();
}

void exemple1(){
    int n=6;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nEXEMPLE\n");
    printf("-----\n");
    al();
    //ligne 1
    gril[0][0]=-1;
    gril[0][1]=1;
    gril[0][2]=-1;
    gril[0][3]=0;
    gril[0][4]=-1;
    gril[0][5]=-1;
    //ligne 2
    gril[1][0]=-1;
    gril[1][1]=-1;
    gril[1][2]=-1;
    gril[1][3]=-1;
    gril[1][4]=-1;
    gril[1][5]=-1;
    //ligne 3
    gril[2][0]=-1;
    gril[2][1]=-1;
    gril[2][2]=-1;
    gril[2][3]=0;
    gril[2][4]=1;
    gril[2][5]=-1;
    //ligne 4
    gril[3][0]=-1;
    gril[3][1]=-1;
    gril[3][2]=-1;
    gril[3][3]=1;
    gril[3][4]=-1;
    gril[3][5]=-1;
    //ligne 5
    gril[4][0]=-1;
    gril[4][1]=0;
    gril[4][2]=1;
    gril[4][3]=-1;
    gril[4][4]=-1;
    gril[4][5]=0;
    //ligne 6
    gril[5][0]=-1;
    gril[5][1]=1;
    gril[5][2]=1;
    gril[5][3]=-1;
    gril[5][4]=-1;
    gril[5][5]=0;
    affiche(gril, n, n);
    resolve(gril, n);
    //|||||||||||||||||||||||||
    //gril[2][2]=0; //FONCTIONNE !!!!
    //gril[0][0]=1;
    //printf("\nresolve absurde : %d\n", resolve_absurde(gril, 6));
    resolution(gril, 6);

    //|||||||||||||||||||||||||
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    al();
    printf("is ok ? : %d\n", vrf_all(gril, n));
    alt();
}

void exemple2(){
    int n=6;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nEXEMPLE FACILE\n");
    printf("-----\n");
    al();
    //ligne 1
    gril[0][0]=1;
    gril[0][1]=-1;
    gril[0][2]=-1;
    gril[0][3]=0;
    gril[0][4]=-1;
    gril[0][5]=-1;
    //ligne 2
    gril[1][0]=-1;
    gril[1][1]=-1;
    gril[1][2]=0;
    gril[1][3]=0;
    gril[1][4]=-1;
    gril[1][5]=1;
    //ligne 3
    gril[2][0]=-1;
    gril[2][1]=0;
    gril[2][2]=0;
    gril[2][3]=-1;
    gril[2][4]=-1;
    gril[2][5]=1;
    //ligne 4
    gril[3][0]=-1;
    gril[3][1]=-1;
    gril[3][2]=-1;
    gril[3][3]=-1;
    gril[3][4]=-1;
    gril[3][5]=-1;
    //ligne 5
    gril[4][0]=0;
    gril[4][1]=0;
    gril[4][2]=-1;
    gril[4][3]=1;
    gril[4][4]=-1;
    gril[4][5]=-1;
    //ligne 6
    gril[5][0]=-1;
    gril[5][1]=1;
    gril[5][2]=-1;
    gril[5][3]=-1;
    gril[5][4]=0;
    gril[5][5]=0;
    affiche(gril, n, n);
    resolution(gril, n);
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    al();
    printf("is ok ? : %d\n", vrf_all(gril, n));
    alt();
}


void exemple3(){
    int n=6;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nEXEMPLE MOYEN\n");
    printf("-----\n");
    al();
    //ligne 1
    gril[0][0]=-1;
    gril[0][1]=0;
    gril[0][2]=-1;
    gril[0][3]=-1;
    gril[0][4]=-1;
    gril[0][5]=-1;
    //ligne 2
    gril[1][0]=0;
    gril[1][1]=0;
    gril[1][2]=-1;
    gril[1][3]=-1;
    gril[1][4]=-1;
    gril[1][5]=-1;
    //ligne 3
    gril[2][0]=-1;
    gril[2][1]=-1;
    gril[2][2]=-1;
    gril[2][3]=0;
    gril[2][4]=-1;
    gril[2][5]=-1;
    //ligne 4
    gril[3][0]=-1;
    gril[3][1]=-1;
    gril[3][2]=-1;
    gril[3][3]=-1;
    gril[3][4]=-1;
    gril[3][5]=-1;
    //ligne 5
    gril[4][0]=1;
    gril[4][1]=-1;
    gril[4][2]=1;
    gril[4][3]=1;
    gril[4][4]=-1;
    gril[4][5]=-1;
    //ligne 6
    gril[5][0]=-1;
    gril[5][1]=-1;
    gril[5][2]=-1;
    gril[5][3]=1;
    gril[5][4]=-1;
    gril[5][5]=-1;
    affiche(gril, n, n);
    resolution(gril, n);
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    al();
    printf("is ok ? : %d\n", vrf_all(gril, n));
    alt();
}

void exemple4(){
    int n=6;
    int ** gril = (int**)calloc(n, sizeof(int*));
    for(int i=0; i<n;i++){
        gril[i]=(int*)calloc(n, sizeof(int));
    }
    printf("\n-----\nEXEMPLE DIFFICILE\n");
    printf("-----\n");
    al();
    //ligne 1
    gril[0][0]=-1;
    gril[0][1]=-1;
    gril[0][2]=0;
    gril[0][3]=-1;
    gril[0][4]=-1;
    gril[0][5]=-1;
    //ligne 2
    gril[1][0]=-1;
    gril[1][1]=-1;
    gril[1][2]=-1;
    gril[1][3]=1;
    gril[1][4]=-1;
    gril[1][5]=-1;
    //ligne 3
    gril[2][0]=-1;
    gril[2][1]=-1;
    gril[2][2]=-1;
    gril[2][3]=-1;
    gril[2][4]=-1;
    gril[2][5]=-1;
    //ligne 4
    gril[3][0]=-1;
    gril[3][1]=0;
    gril[3][2]=-1;
    gril[3][3]=1;
    gril[3][4]=-1;
    gril[3][5]=0;
    //ligne 5
    gril[4][0]=1;
    gril[4][1]=-1;
    gril[4][2]=-1;
    gril[4][3]=-1;
    gril[4][4]=-1;
    gril[4][5]=-1;
    //ligne 6
    gril[5][0]=-1;
    gril[5][1]=-1;
    gril[5][2]=0;
    gril[5][3]=-1;
    gril[5][4]=-1;
    gril[5][5]=0;
    affiche(gril, n, n);
    resolution(gril, n);
    printf("\nI  I  I  I  I\n");
    printf("V  V  V  V  V\n\n");
    affiche(gril, n, n);
    al();
    printf("is ok ? : %d\n", vrf_all(gril, n));
    alt();
}


int main(){
    //test_verif_trait();        //validé
    //test_traitement();        //validé
    //test_traitement_cours(); //validé     
    //test_resolution_c1();   //validé
    //test_resolution_c2();  //validé
    //test_resolution_c3(); //validé
    //test_resolution();   //validé
    //exemple1();         //réussi demande raisonnment non-implémenté (DRNI)
    //exemple2();        //réussi (facile)   
    //exemple3();       //réussi (moyen)
    //exemple4();      //réussi (difficile)
    return 0;
}

/*NOTE :
TESTER RESOLVE ABSURDE L682 a l'air de fonctionner, mais la résolution réécrit sur les valeurs ??
TESTER RESO EXHAUST L698
*/