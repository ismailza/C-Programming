#include<stdio.h>
#include<stdlib.h>

// les structures
typedef struct cell
{
    int info;
    struct cell *suivant;
}Cellule;

typedef struct
{
    Cellule *Tete, *Queue;
}File;

// Prototype
Cellule *Empiler(Cellule *pile,int val);
Cellule *Depiler(Cellule *pile);
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
Cellule *Empiler(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    if (!pile) return ((Cellule *)CL); // tester si la pile existe
    CL->suivant = pile; // Inserer au sommet
    return ((Cellule *)CL);
}
// 3- Supprimer un element au sommet de la pile
Cellule *Depiler(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); // tester si la pile existe
    Supp = pile;
    pile = pile->suivant;
    free(Supp);
    return ((Cellule *)pile);
}

int Enfiler(File *file, int val)
{
    Cellule *CL = NULL;
    if (!file) return -1;
    if (!file->Tete) 
    {
        file->Queue = Empiler(file->Queue,val);
        file->Tete = file->Queue;
    }
    else
    {
        CL = Empiler(CL,val);
        file->Queue->suivant = CL;
        file->Queue = CL;
    }
    return 1;
}
int Defiler(File *file)
{
    if (!file) return ((int)-1);
    file->Tete = Depiler(file->Tete);
    if (!file->Tete) file->Queue = NULL;
    return ((int)1);
}

void main()
{
    File *file = (File *)malloc(sizeof(File));
    file->Tete = file->Queue = NULL;

    int rt;
    rt = Enfiler(file,12);
    rt = Enfiler(file,13);
    rt = Defiler(file);
    printf("\n%d",file->Tete->info);
}