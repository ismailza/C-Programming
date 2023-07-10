#include<stdio.h>
#include<stdlib.h>

typedef struct cell
{
    int info;
    struct cell *suivant;
}Cellule;

Cellule *CreerCellule(int val)
{
    Cellule *CL;
    CL = (Cellule *)malloc(sizeof(Cellule)); // Allocation de la memoire
    if (!CL) 
    {   // Erreur d'allocation de la memoire
        printf("\nErreur d'allocation de la memoire!");
        exit(0); // Quitter le programme
    }
    CL->info = val; // Affecter la valeur
    CL->suivant = NULL; // Initialiser le pointeur suivant par NULL
    return ((Cellule *)CL); // retourne CL
}
Cellule *InsererPListeFin(Cellule *liste, int val)
{
    Cellule *CL, *courant;
    CL = CreerCellule(val); // Creer l'element
    if (!liste) return ((Cellule *)CL); // tester si la liste existe
    courant = liste; // Initialiser courant a la tete de la liste
    while (courant->suivant) // tant que courant a un suivant
        courant = courant->suivant; // passer a l'element suivant
    courant->suivant = CL; // Inserer l'element
    return ((Cellule *)liste); 
}
void AfficherPListe(Cellule *liste)
{
    Cellule *courant;
    // si la liste est vide
    if (!liste) printf("\nLa liste est vide");
    else
    {
        courant = liste; // initialiser courant par la tete de la liste
        printf("\nListe : ");
        while (courant)
        {   // tant qu'on a un element dans la liste
            printf("%d\t",courant->info); // afficher l'element
            courant = courant->suivant; // passer au suivant
        }
    }
}
Cellule *NetoyerListe(Cellule *liste, int val)
{
    Cellule *courant, *Supp, *ptQueue;
    if (!liste) return ((Cellule *)NULL);
    // Si la valeur est en tete
    while (liste->info == val)
    {
        Supp = liste;
        liste = liste->suivant;
        free(Supp);
    }
    courant = liste;
    while (courant->suivant)
    {
        if (courant->suivant->info == val)
        {
            Supp = courant->suivant;
            courant->suivant = courant->suivant->suivant;
            free(Supp);
            continue;
        }
        courant = courant->suivant;
    }
    ptQueue = courant;
    while (liste != ptQueue)
    {
        courant = liste;
        liste = liste->suivant;
        courant->suivant = ptQueue->suivant;
        ptQueue->suivant = courant;
    }
    return ((Cellule *)liste);
}

void main()
{
    Cellule *liste = NULL;
    liste = InsererPListeFin(liste,10);
    liste = InsererPListeFin(liste,11);
    liste = InsererPListeFin(liste,12);
    liste = InsererPListeFin(liste,12);
    liste = InsererPListeFin(liste,13);
    liste = InsererPListeFin(liste,14);
    liste = InsererPListeFin(liste,12);
    liste = InsererPListeFin(liste,10);
    liste = InsererPListeFin(liste,17);
    liste = InsererPListeFin(liste,19);
    AfficherPListe(liste);
    liste = NetoyerListe(liste,12);
    AfficherPListe(liste);
}