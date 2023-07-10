/*
|   TP2: le probleme du plan de circulation d’automobiles propose par un Ingenieur a
|        la Direction Commerciale.
|       - Determinisation des composates fortement connexes d'un graphe G = (X, U);
|       - Determinisation du graphe reduit de G;
|       - La decision recommandee pour la Direction Commercial.
|   On suppose que les sommets de X sont numérotes de 1 a n, avec n = |X|.
|   Realiser par : Ismail ZAHIR
*/
#include <stdio.h>
#include <stdlib.h>
// les structures de donnees et les fonctions utilisees sont definies dans le ficher "fncts_tps.h"
#include "fncts.h"

/********************************************************************************
| Nom     : CFC_a;
| Entrees : Matrice * : la matrice d'adjacence du graphe initial
|           Cellule * : la liste des sommets qui non pas encore dans une CFC
|           int       : un sommet
| Sorties : Cellule * : la composante fortement connexe contenant a
| la fonction permet la determination de la composante fortement connexe contenant
| un sommet a et la retourne sous une liste
*/
Cellule *CFC_a (Matrice *M, Cellule *X, int a)
{
    Cellule *X_plus = NULL,     // X+ : liste des sommets atteindent par a  
            *X_moins = NULL,    // X- : liste des sommets qui atteindent a
            *X_prime,           // X' : la composante fortement connexe 
            *ptr, *ptrX;        // pointeur pour le parcours des listes
    int i;
    if (!M || !X) // si la matrice n'existe pas ou l'ensemble des sommets est vide
    {   
        printf("\nErreur : matrice n'existe pas !");
        exit(0);
    }
    if (a < 0 || M->n <= a) // si le sommet n'est pas correct
    {
        printf("\nErreur : sommet %d n'existe pas !", a);
        return ((Cellule *)NULL);
    }
    int m[M->n];                            // tableau des sommets marques
    X_plus = Inserer_Fin_Liste(X_plus, a);  // initialiser X+ par 'a'
    for (i = 0; i < M->n; m[i++] = 0);      // initialisation du tableau m
    m[a] = 1;                               // marquer le sommet 'a'
    ptr = X_plus;
    while (ptr)
    {   
        ptrX = X;
        while (ptrX) // pour tout sommet de X
        {   /* s'il existe un arc dont l'extrimite initial est le sommet courant
             et son extrimite terminal n'est pas marquee */
            if (M->matrice[ptr->n][ptrX->n] && !m[ptrX->n])
            {   // on insere l'extrimite terminal dans X_plus
                X_plus = Inserer_Fin_Liste(X_plus, ptrX->n);
                m[ptrX->n] = 1;
            }
            ptrX = ptrX->svt;           // le sommet suivant de X
        }
        ptr = ptr->svt;
    }
    X_moins = Inserer_Fin_Liste(X_moins, a);// initialiser X- par 'a'
    for (i = 0; i < M->n; m[i++] = 0);      // re-initialisation du tableau m
    m[a] = 1;                               // marquer le sommet 'a'
    ptr = X_moins;
    while (ptr) 
    {
        ptrX = X;
        while (ptrX) // pour tout sommet de X
        {   /* s'il existe un arc dont l'extrimite terminal est le sommet courant
             et son extrimite initial n'est pas marquee */
            if (M->matrice[ptrX->n][ptr->n] && !m[ptrX->n])
            {   // on insere l'extrimite initial dans X_plus
                X_moins = Inserer_Fin_Liste(X_moins, ptrX->n);
                m[ptrX->n] = 1;
            }
            ptrX = ptrX->svt;           // le sommet suivant de X
        }
        ptr = ptr->svt;
    }
    X_prime = Intersection_2_Listes(X_plus, X_moins);   // la composante connexe
    return ((Cellule *)Trier_Liste(X_prime));
}
/********************************************************************************
| Nom     : CFC;
| Entrees : Matrice * : la matrice d'adjacence du graphe initial
| Sorties : TableCE * : table des classes d'equivalence
| la fonction permet la determination des composantes fortement connexes 
| d'un graphe et retourne l'ensemble des classes d'equivalence
*/
int CFC (Matrice *M, int tableCFCs[MAX])
{
    Cellule *X = NULL,          // ensembles des sommets
            *X_prime,           // composante fortement connexe
            *ptr;               // pointeur pour le parcour
    int i, nb_cfc = 0;
    if (!M) // si la matrice n'existe pas
    {
        printf("\nErreur : matrice n'existe pas !");
        exit(0);
    }
    // initialisation de l'ensemble des sommets
    for (i = 0; i < M->n; i++) X = Inserer_Fin_Liste(X,i);
    while (X)   // tant qu'on a des sommets non encore dans une CFC
    {
        X_prime = CFC_a(M, X, X->n);    // la CFC contenant le sommet de X
        ptr = X_prime;
        while (ptr)     // construir la classe d'equivalence           
        {   
            tableCFCs[ptr->n] = nb_cfc;
            ptr = ptr->svt;
        }
        nb_cfc++;      // augmenter le nombre de classe d'equivalence
        // eliminer les sommets qui appartient deja a une CFC
        X = Substrct_2_Ordered_Lists(X, X_prime);   
    }
    return ((int )nb_cfc);
}
/********************************************************************************
| Nom     : Graphe_Reduit;
| Entrees : Matrice * : la matrice d'adjacence du graphe initial
|         : TableCE * : table des classes d'equivalence
| Sorties : Matrice * : la matrice d'adjacence du graphe reduit
| la fonction permet la construction de la matrice d'adjacence du graphe reduit 
| d'un graphe a partir de sa matrice d'adjacence et les classes d'equivalence
*/
Matrice *Graphe_Reduit (Matrice *M, int tableCFCs[MAX], int nb_cfc)
{
    if (!M) 
    {
        printf("\nErreur : matrice d'adjacence n'existe pas !");
        exit(0);
    }
    int i, j;
    Matrice *MGR = CreerMatrice(nb_cfc); // creation de la matrice pour le graphe reduit
    // initialisation de la matrice
    for (i = 0; i < nb_cfc; i++) for (j = 0; j < nb_cfc; MGR->matrice[i][j++] = 0);
    // creation des arcs 
    for (i = 0; i < M->n; i++)  
    {
        for (j = 0; j < M->n; j++) 
        {
            if (M->matrice[i][j] && (tableCFCs[i] != tableCFCs[j])) 
                MGR->matrice[tableCFCs[i]][tableCFCs[j]] = 1;
        }
    }
    return ((Matrice *)MGR);
}

void main()
{
    Matrice *M = remplirMatrice("graphe.txt");
    int tableCFCs[MAX];
    int nb_cfc = CFC(M, tableCFCs);
    // AfficherClassesEquivalence(t, M->n);
    for (int i=0; i < M->n; i++) printf("\n\t%d => %d",i+1, tableCFCs[i]+1);
    printf("\nMatrice d'adjacence du graphe reduit : ");
    Matrice *MR = Graphe_Reduit(M, tableCFCs, nb_cfc);
    AfficherMatrice(MR);
    printf("\nLa decision recommandee pour la direction : ");
    if (MR->n > 1) printf("\n==> \tNon faisable.");
    else printf("\n==> \tFaisable.");

}