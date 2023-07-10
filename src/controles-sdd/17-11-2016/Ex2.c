#include<stdio.h>
#include<stdlib.h>
// Definition de la structure
typedef struct cell
{
    int info; // variable pour stocker l'entier
    struct cell *suivant; // pointeur vers l'element suivant
}Cellule;

Cellule *CreerCellule(int val)
{
    Cellule *CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL)
    {
        printf("\nErreur d'allocation"); exit(0);
    }
    CL->info = val;
    CL->suivant = NULL;
    return ((Cellule *)CL);
}
// Insertion d'un element en tete de la liste
Cellule *InsererDebut(Cellule *liste, int val)
{
    Cellule *CL = CreerCellule(val);
    CL->suivant = liste;
    return ((Cellule *)CL);
}
Cellule *Construire_3_Listes(Cellule *liste, Cellule *Alst1[1], Cellule *Alst2[1], Cellule *Alst3[1])
{
    Cellule *liste1 = NULL, *liste2 = NULL, *liste3 = NULL;
    Cellule *courant;
    if (!liste) 
    {
        Alst1[0] = NULL;
        Alst2[0] = NULL;
        Alst3[0] = NULL;
        return ((Cellule *)NULL);
    }
    courant = liste;
    while (courant)
    {
        if (courant->info >= 0)
        {
            if (!liste1) liste1 = InsererDebut(liste1,courant->info);
            else if (courant->info < liste1->info) liste1 = InsererDebut(liste1,courant->info);
            else liste3 = InsererDebut(liste3,courant->info);
        }
        else
        {
            if (!liste2) liste2 = InsererDebut(liste2,courant->info);
            else if (courant->info < liste2->info) liste2 = InsererDebut(liste2,courant->info);
            else liste3 = InsererDebut(liste3,courant->info);
        }
        courant = courant->suivant;
    }
    Alst1[0] = liste1;
    Alst2[0] = liste2;
    Alst3[0] = liste3;
    return ((Cellule *)liste);
}
// Recuperer la cellule du minimum
Cellule *RecupererMin(Cellule *liste, Cellule *AddMin[1])
{
    Cellule *courant, *ptMin;
    int min;
    // existance de la liste
    if (!liste)
    {
        AddMin[0] = NULL;
        return ((Cellule *)NULL);
    }
    min = liste->info;
    courant = liste;
    while (courant->suivant)
    {
        if (courant->suivant->info < min)
        {
            ptMin = courant;
            min = courant->suivant->info;
        }
        courant = courant->suivant;
    }
    // le min est en tete
    if (min == liste->info)
    {
        AddMin[0] = liste;
        liste = liste->suivant;
        AddMin[0]->suivant = NULL;
        return ((Cellule *)liste);
    }
    AddMin[0] = ptMin->suivant;
    ptMin->suivant = ptMin->suivant->suivant;
    AddMin[0]->suivant = NULL;
    return ((Cellule *)liste);  
}
void AffichageCroissantListes(Cellule *liste1, Cellule *liste2, Cellule *liste3)
{
    Cellule *courant, *courant3[1], *tmp = NULL;
    int rt, min;
    if (!liste1 && !liste2 && !liste3) printf("\nListes vides");
    else
    {
        printf("\nListe : ");
        courant = liste2;
        liste3 = RecupererMin(liste3,courant3);
        while (courant && courant3[0])
        {
            if (courant->info < courant3[0]->info)
            {
                printf("%d\t",courant->info);
                courant = courant->suivant;
            }else
            {
                printf("%d\t",courant3[0]->info);
                tmp = InsererDebut(tmp,courant3[0]->info);
                liste3 = RecupererMin(liste3,courant3);
            }
        }
        while (courant)
        {
            printf("%d\t",courant->info);
            courant = courant->suivant;
        }
        courant = liste1;
        while (courant && courant3[0])
        {
            if (courant->info < courant3[0]->info)
            {
                printf("%d\t",courant->info);
                courant = courant->suivant;
            }else
            {
                printf("%d\t",courant3[0]->info);
                tmp = InsererDebut(tmp,courant3[0]->info);
                liste3 = RecupererMin(liste3,courant3);
            }
        }
        while (courant)
        {
            printf("%d\t",courant->info);
            courant = courant->suivant;
        }  
        while (courant3[0])
        {
            printf("%d\t",courant3[0]->info);
            tmp = InsererDebut(tmp,courant3[0]->info);
            liste3 = RecupererMin(liste3,courant3);
        }
    }
}

void main()
{
    Cellule *liste = NULL;
    Cellule *liste1[1], *liste2[1], *liste3[1];
    liste = InsererDebut(liste,-6);
    liste = InsererDebut(liste,11);
    liste = InsererDebut(liste,1);
    liste = InsererDebut(liste,5);
    liste = InsererDebut(liste,8);
    liste = InsererDebut(liste,-15);
    liste = InsererDebut(liste,-8);
    liste = InsererDebut(liste,7);
    liste = InsererDebut(liste,12);
    liste = Construire_3_Listes(liste,liste1,liste2,liste3);
    AffichageCroissantListes(liste1[0],liste2[0],liste3[0]);
}