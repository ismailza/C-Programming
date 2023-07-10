#include<stdio.h>
#include<stdlib.h>
#define NbElem 25
// structure du tableau
typedef struct
{
    int info[NbElem]; // tableau d'entiers
    int IdElem; // Indice du dernier element
}TAB;
void Affichage(TAB tab)
{
    if (tab.IdElem == -1) printf("\nTAB vide");
    else
    {
        printf("\nTAB : ");
        for (int i = 0; i <= tab.IdElem; i++) printf("%d\t",tab.info[i]);
    }
}
int InsertionBonnePlace(TAB *tab, int val)
{
    int i;
    if (!tab) return ((int)-1);
    if (tab->IdElem == NbElem-1) return ((int)0);
    i = tab->IdElem;
    while ((i >= 0) && (val < tab->info[i]))
    {
        tab->info[i+1] = tab->info[i];
        i--;
    }
    tab->info[i+1] = val;
    ++tab->IdElem;
    return ((int)1);
}
int Transforme(TAB *tab)
{
    int i,j;
    if (!tab) return ((int)-1);
    if (2*(tab->IdElem) >= NbElem-1) return ((int)0);
    j = tab->IdElem;
    for (i = tab->IdElem; i >= 0; i--)
    {
        tab->info[j+i] = tab->info[i];
        tab->info[j+i+1] = 2*tab->info[i];
        j--;
    }
    tab->IdElem = 2*tab->IdElem +1;
    return ((int)1);
}

void main()
{
    TAB tab;
    tab.IdElem = -1;
    int rt;
    rt = InsertionBonnePlace(&tab,5);
    rt = InsertionBonnePlace(&tab,12);
    rt = InsertionBonnePlace(&tab,8);
    rt = InsertionBonnePlace(&tab,11);
    rt = InsertionBonnePlace(&tab,20);
    rt = InsertionBonnePlace(&tab,6);
    rt = InsertionBonnePlace(&tab,8);
    rt = InsertionBonnePlace(&tab,2);
    rt = InsertionBonnePlace(&tab,9);
    Affichage(tab);
    rt = Transforme(&tab);
    Affichage(tab);
}