#include<stdio.h>
#include<stdlib.h>

// Definition de la structure
typedef struct Liste
{
    int info; 
    struct Liste *suivant; // Pointeur vers l'element suivant
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
Cellule *EmpilerPPile(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    CL->suivant = pile; // Inserer au sommet
    return ((Cellule *)CL);
}
Cellule *DepilerPPile(Cellule *pile, int *val)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); // tester si la pile existe
    Supp = pile;
    *val = pile->info; // recuperer la valeur de l'element depiler
    pile = pile->suivant;
    free(Supp);
    return ((Cellule *)pile);
}
void AfficherPPile(Cellule *pile)
{
    Cellule *pile2 = NULL;
    int val;
    if (!pile) // tester si la pile existe
    {
        printf("\nPile inexiste ou vide!");
        exit(0);
    }
    printf("\nPile : ");
    while (pile) // tant qu'on a un element dans la pile
    {   // Afficher l'element et le depiler
        printf("%d\t",pile->info);
        pile2 = EmpilerPPile(pile2, pile->info);
        pile = DepilerPPile(pile,&val);
    }
    while (pile2)
    {   // Récupperer la pile
        pile = EmpilerPPile(pile, pile2->info);
        pile2 = DepilerPPile(pile2,&val);
    }
}

Cellule *SupprimerPPile(Cellule *pile, int val)
{
    Cellule *tmp = NULL;
    int supp;
    while (pile)
    {
        pile = DepilerPPile(pile,&supp);
        if (supp != val) tmp = EmpilerPPile(tmp,supp);
    }
    while (tmp)
    {
        tmp = DepilerPPile(tmp,&supp);
        pile = EmpilerPPile(pile,supp);
    }
    return ((Cellule *)pile);
}

void main()
{
    Cellule *pile = NULL;
    pile = EmpilerPPile(pile,2);
    pile = EmpilerPPile(pile,2);
    pile = EmpilerPPile(pile,1);
    pile = EmpilerPPile(pile,12);
    pile = EmpilerPPile(pile,2);
    AfficherPPile(pile);
    pile = SupprimerPPile(pile,2);
    AfficherPPile(pile);
}