#include<stdio.h>
#include<stdlib.h>
#define NbElem 25
// definition de la structure
typedef struct
{
    int info[NbElem]; // Tableau des entiers
    int IdElem; // indice du dernier element de la liste
}TAB;

int InsererTabOrdonne(TAB *tab, int val)
{
    int i;
    // tester l'existance du tableau
    if (!tab) return ((int)-1);
    // tester la saturation du tableau
    if (tab->IdElem == NbElem-1) return ((int)0);
    // Insertion de l'entier
    i = tab->IdElem;
    while ((i>=0) && (val > tab->info[i]))
    {
        tab->info[i+1] = tab->info[i];
        i--;
    }
    tab->info[i+1] = val;
    tab->IdElem++;
    return ((int)1);    
}