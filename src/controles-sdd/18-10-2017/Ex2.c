#include<stdio.h>
#include<stdlib.h>
#define NbElem 25
typedef struct 
{
    int info[NbElem];
    int IdElem;
}TAB;

typedef struct cell
{
    int info;
    struct cell *suivant;
}Cellule;

Cellule *TrasfererListeTab(Cellule *liste, TAB *tab)
{
    Cellule *courant;
    int i;
    if (!liste) return ((Cellule *)NULL);
    courant = liste;
    while (courant)
    {
        i = tab->IdElem;
        while ((i>=0) && (courant->info < tab->info[i]))
        {
            tab->info[i+1] = tab->info[i];
            i--;
        }
        tab->info[i+1] = courant->info;
        tab->IdElem++;        
        courant = courant->suivant;
    }
    return ((Cellule *)liste);
}