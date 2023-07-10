#include<stdio.h>
#include<stdlib.h>
#define MaxElem 25
typedef struct
{
    int tab[MaxElem];
    int NbElem; // nombre d'element dans le tableau
    int debut, fin; // indice de debut et de fin
}TAB;

int Empiler(TAB *pile, int val)
{
    if (!pile) return ((int)-1); // pile inexiste
    if (!pile->NbElem == MaxElem) return ((int)0); // pile saturee
    if (pile->debut == -1) pile->debut++; // insertion de premier element
    pile->fin++;
    pile->tab[pile->fin] = val; // insertion en tete
    pile->NbElem++; // incrementation du nombre d'element
    return ((int)1);
}
int TransfererTabPile(TAB *tab, TAB *pile)
{
    int rt, max;
    if (!tab) return ((int)-1);
    while (tab->NbElem)
    {
        max = tab->tab[0];
        for (int i = 0; i < tab->NbElem-1; i++)
        {
            if (max < tab->tab[i+1]) 
            {
                tab->tab[i] = max;
                max = tab->tab[i+1];
            }
            else tab->tab[i] = tab->tab[i+1];
        }
        tab->fin--;
        tab->NbElem--;
        rt = Empiler(pile,max);
    }
    return ((int)1);
}

void main()
{
    int rt;
    TAB tab, pile;
    tab.debut = tab.fin = -1;
    tab.NbElem = 0;
    pile.debut = pile.fin = -1;
    pile.NbElem = 0;
    tab.debut = 1;
    tab.tab[++tab.fin] = 12;
    tab.tab[++tab.fin] = 1;
    tab.tab[++tab.fin] = 14;
    tab.tab[++tab.fin] = 4;
    tab.tab[++tab.fin] = 15;
    tab.tab[++tab.fin] = 14;
    tab.tab[++tab.fin] = 12;
    tab.tab[++tab.fin] = 12;
    tab.tab[++tab.fin] = 5;
    tab.tab[++tab.fin] = 7;
    tab.tab[++tab.fin] = 2;
    tab.tab[++tab.fin] = 10;
    tab.NbElem = 12;
    printf("\nTab : ");
    for (int i=0; i< tab.NbElem; i++)
    {
        printf("%d\t",tab.tab[i]);
    }

    rt = TransfererTabPile(&tab,&pile);
    printf("\nPile : ");
    for (int i=pile.fin; i >= 0; i--)
    {
        printf("%d\t",pile.tab[i]);
    }
}