#include<stdio.h>
#include<stdlib.h>
// Definition de la structure
typedef struct cell
{
    int info;
    struct cell *suivant; 
}Cellule;
typedef struct PL
{
    Cellule *pile;
    struct PL *suivant;
}Liste;

Liste *CreerListe(Cellule *pile)
{
    Liste *liste = (Liste *)malloc(sizeof(Liste));
    if (!liste) 
    {
        printf("\nErreur lors de l'allocation de la memoire pour la liste");
        exit(0);
    }
    liste->pile = pile;
    liste->suivant = NULL;
    return ((Liste *)liste);
}
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
Liste *InsererListe(Liste *liste, Cellule *pile)
{
    Liste *courant, *LST;
    LST = CreerListe(pile);
    if (!liste) return ((Liste *)LST);
    courant = liste;
    while (courant->suivant) courant = courant->suivant;
    courant->suivant = LST;  
    return ((Liste *)liste);
}
// 2- Inserer un element au sommet de la pile
Cellule *EmpilerPPile(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    if (!pile) return ((Cellule *)CL); // tester si la pile existe
    CL->suivant = pile; // Inserer au sommet
    return ((Cellule *)CL);
}
// 3- Supprimer un element au sommet de la pile
Cellule *DepilerPPile(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); // tester si la pile existe
    Supp = pile;
    pile = pile->suivant;
    free(Supp);
    return ((Cellule *)pile);
}

Liste *TrierPile(Cellule *pile)
{
    Liste *liste = NULL, *courant;
    Cellule *PL = NULL;
    int inserted = 0;
    if (!pile) return ((Liste *)NULL);
    while (pile)
    {
        courant = liste;
        while (courant)
        {
            if (pile->info <= courant->pile->info)
            {
                courant->pile = EmpilerPPile(courant->pile,pile->info);
                inserted = 1;
                break;
            }
            courant = courant->suivant;
        }
        if (inserted==0)
        {
            PL = CreerCellule(pile->info);
            liste = InsererListe(liste,PL);
        }
        inserted = 0;
        pile = DepilerPPile(pile);
    }
    return ((Liste *)liste);
}

void Affichage(Liste *liste)
{
    Liste *courant, *ptMin, *pred;
    if (!liste) printf("\nListe vide");
    else
    {
        printf("\nListe : ");
        while (liste)
        {
            courant = liste;
            ptMin = liste;
            while (courant->suivant)
            {
                if (courant->suivant->pile->info < ptMin->pile->info) 
                {
                    ptMin = courant->suivant;
                    pred = courant;
                }
                courant = courant->suivant;
            }
            printf("%d\t",ptMin->pile->info);
            ptMin->pile = DepilerPPile(ptMin->pile);
            if (!ptMin->pile)
            {
                pred->suivant = pred->suivant->suivant;
                free(ptMin);
            }
        }
    }
}


void AfficherPPile(Cellule *pile)
{
    Cellule *pile2 = NULL;
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
        pile = DepilerPPile(pile);
    }
    while (pile2)
    {   // Récupperer la pile
        pile = EmpilerPPile(pile, pile2->info);
        pile2 = DepilerPPile(pile2);
    }
}
void main()
{
    Liste *liste;
    Cellule *pile = NULL;
    pile = EmpilerPPile(pile,12);
    pile = EmpilerPPile(pile,16);
    pile = EmpilerPPile(pile,10);
    pile = EmpilerPPile(pile,13);
    pile = EmpilerPPile(pile,20);

    AfficherPPile(pile);

    liste = TrierPile(pile);
    Affichage(liste);
}