#include<stdio.h>
#include<stdlib.h>

typedef struct cell
{
    int info;
    struct cell *suivant;
}Cellule;

Cellule *CreerCellule(int val)
{
    Cellule *CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL)
    {
        printf("\nErreur d'allocation de la memoire pour la cellule!");
        exit(0);
    }
    CL->info = val;
    CL->suivant = NULL;
    return ((Cellule *)CL);
}
Cellule *InsertionBonnePlace(Cellule *liste, int val)
{
    Cellule *courant, *CL;
    CL = CreerCellule(val);
    if (!liste) return ((Cellule *)CL);
    // Insertion en tete
    if (val < liste->info)
    {
        CL->suivant = liste;
        return ((Cellule *)CL);
    }
    courant = liste;
    while (courant->suivant)
    {
        // Insertion en milieu
        if (val < courant->suivant->info)
        {
            CL->suivant = courant->suivant;
            courant->suivant = CL;
            return ((Cellule *)liste);
        }
        courant = courant->suivant;
    }
    // Insertion en queue
    courant->suivant = CL;
    return ((Cellule *)liste);
}
Cellule *Transformer(Cellule *liste)
{
    Cellule *courant, *CL;
    if (!liste) return ((Cellule *)NULL);
    courant = liste;
    while (courant)
    {
        CL = CreerCellule(2*courant->info);
        CL->suivant = courant->suivant;
        courant->suivant = CL;
        courant = courant->suivant->suivant;
    }
    return ((Cellule *)liste);
}

void Affichage(Cellule *liste)
{
    Cellule *courant;
    if (!liste) printf("\nListe vide");
    else
    {
        printf("\nListe :  ");
        courant = liste;
        while (courant)
        {
            printf("%d\t",courant->info);
            courant = courant->suivant;
        }
    }
}

void main()
{
    Cellule *liste = NULL;
    liste = InsertionBonnePlace(liste,5);
    liste = InsertionBonnePlace(liste,7);
    liste = InsertionBonnePlace(liste,4);
    liste = InsertionBonnePlace(liste,9);
    liste = InsertionBonnePlace(liste,2);
    liste = InsertionBonnePlace(liste,12);
    liste = InsertionBonnePlace(liste,20);
    liste = InsertionBonnePlace(liste,15);
    Affichage(liste);
    liste = Transformer(liste);
    Affichage(liste);
}