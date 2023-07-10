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

Cellule *SupprimerPileElem(Cellule *pile, int val)
{
    Cellule *tmp = NULL;
    int rt;
    while (pile)
    {
        if (pile->info != val) tmp = EmpilerPPile(tmp,pile->info);
        pile = DepilerPPile(pile);
    }
    while (tmp)
    {
        pile = EmpilerPPile(pile,tmp->info);
        tmp = DepilerPPile(tmp);
    }
    return ((Cellule *)pile); 
}