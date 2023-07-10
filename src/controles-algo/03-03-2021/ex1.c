#include<stdio.h>
#include<stdlib.h>
typedef struct CL
{
    int info;
    struct CL *svt;
}Cellule;
typedef struct LP
{
    Cellule *pile;
    struct LP *svt;
}Liste;
Liste *CreerListe(Cellule *pile)
{
    if (!pile) return ((Liste *)NULL);
    Liste *liste = (Liste *)malloc(sizeof(Liste));
    if (!liste) exit(0);
    liste->pile = pile;
    liste->svt = NULL;
    return ((Liste *)liste);
}
Cellule *CreerCellule(int val)
{
    Cellule *CL;
    CL = (Cellule *)malloc(sizeof(Cellule)); 
    if (!CL) exit(0); 
    CL->info = val; 
    CL->svt = NULL; 
    return ((Cellule *)CL); 
}

Liste *Insert_ListePile(Liste *liste, int val)
{
    Liste *courant = liste;
    Cellule *PL = CreerCellule(val);
    if (!liste) return ((Liste *)CreerListe(PL));
    if (val <= liste->pile->info)
    {
        PL->svt = liste->pile;
        liste->pile = PL;
        return ((Liste *)liste);
    }
    while (courant->svt)
    {
       if (val <= courant->svt->pile->info)
       {
            PL->svt = courant->svt->pile;
            courant->svt->pile = PL;
            return ((Liste *)liste);
       }
       courant = courant->svt;
    }
    courant->svt = CreerListe(PL);
    return ((Liste *)liste);
}

Cellule *DepilerPile(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); 
    Supp = pile;
    pile = pile->svt;
    free(Supp);
    return ((Cellule *)pile);
}

void Affichage(Liste *liste)
{
    Liste *courant, *ptMin, *pred = NULL;
    if (!liste) printf("\nListe vide");
    else
    {
        printf("\nListe : ");
        while (liste)
        {
            courant = liste;
            ptMin = liste;
            while (courant->svt)
            {
                if (courant->svt->pile->info < ptMin->pile->info) 
                {
                    ptMin = courant->svt;
                    pred = courant;
                }
                courant = courant->svt;
            }
            printf("%d\t",ptMin->pile->info);
            ptMin->pile = DepilerPile(ptMin->pile);
            if (!ptMin->pile)
            {
                if (!pred) liste = liste->svt;
                else pred->svt = pred->svt->svt;
                free(ptMin);
            }
        }
    }
}

void main()
{
    Liste *liste = NULL;
    int V[14] = {5,4,3,10,9,2,19,16,-1,8,7,13,21,22};
    for (int i = 0; i < 14; i++) liste = Insert_ListePile(liste,V[i]);
    
    Affichage(liste);
}