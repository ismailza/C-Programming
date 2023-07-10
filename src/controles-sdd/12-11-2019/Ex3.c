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
Cellule *InsererPListeFin(Cellule *liste, Cellule *CL)
{
    Cellule *courant = liste;
    if (!liste) return ((Cellule *)CL);
    while (courant->suivant) courant = courant->suivant;
    courant->suivant = CL;
    return ((Cellule *)liste); 
}
Cellule *EmpilerPPile(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    if (!pile) return ((Cellule *)CL); // tester si la pile existe
    CL->suivant = pile; // Inserer au sommet
    return ((Cellule *)CL);
}
Cellule *DepilerPPile(Cellule *pile, int *val)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); // tester si la pile existe
    Supp = pile;
    *val = pile->info;
    pile = pile->suivant;
    free(Supp);
    return ((Cellule *)pile);
}
// Recuperer la cellule du minimum dans une liste
Cellule *RecupererMinListe(Cellule *liste, Cellule *AddMin[1])
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

Cellule *TransListePile(Cellule *liste)
{
    Cellule *pile = NULL, *courant[1], *tmp = NULL;
    int val;
    if (!liste) return ((Cellule *)NULL);
    while (liste)
    {
        liste = RecupererMinListe(liste,courant);
        tmp = EmpilerPPile(tmp,courant[0]->info);      
    }
    while (tmp)
    {
        pile = EmpilerPPile(pile,tmp->info);
        tmp = DepilerPPile(tmp,&val);
    }
    return ((Cellule *)pile);    
}

// c
// Cellule *RecupererMinPile(Cellule *pile, Cellule *AddMin[1])
// {
//     Cellule *tmp = NULL;
//     int min, rang, i = 1, val;
//     if (!pile)
//     {
//         AddMin[0] = NULL;
//         return ((Cellule *)NULL);
//     }
//     min = pile->info;
//     rang = 1;
//     while (pile->suivant)
//     {
//         pile = DepilerPPile(pile,&val);
//         tmp = EmpilerPPile(tmp, val);
//         i++;
//         if (pile->info < min)
//         {
//             min = pile->info;
//             rang = i;
//         }
//     }
//     while (tmp)
//     {
//         tmp = DepilerPPile(tmp,&val);
//         pile = EmpilerPPile(pile,val);
//     }
//     for (i = 0; i < rang; i++) 
//     {
//         pile = DepilerPPile(pile,&val);
//         tmp = EmpilerPPile(tmp, val);   
//     }
//     AddMin[0] = pile;
//     printf("\n%d",AddMin[0]->info);
//     pile = DepilerPPile(pile,&val);
//     AddMin[0]->suivant = NULL;    
//     while (tmp)
//     {
//         tmp = DepilerPPile(tmp,&val);
//         pile = EmpilerPPile(pile,val);
//     }
    
//     return ((Cellule *)pile);    
// }

// Cellule *TransPileListe(Cellule *pile)
// {
//     Cellule *liste = NULL, *courant[1], *ptMin;
//     int min;
//     while (pile)
//     {
//         pile = RecupererMinPile(pile,courant);
//         liste = InsererPListeFin(liste,courant[0]);
//     }
//     return ((Cellule *)liste); 
// }

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

void main()
{
    Cellule *liste = NULL, *pile = NULL;
    liste = InsererPListeFin(liste,CreerCellule(14));
    liste = InsererPListeFin(liste,CreerCellule(6));
    liste = InsererPListeFin(liste,CreerCellule(13));
    liste = InsererPListeFin(liste,CreerCellule(8));
    pile = TransListePile(liste);
    AfficherPPile(pile);
    printf("\n****************************");
    liste = NULL;
    liste = TransPileListe(pile);
    AfficherPListe(liste);

}