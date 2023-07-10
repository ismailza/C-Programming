#include<stdio.h>
#include<stdlib.h>

#define NbElem 25

/*
    Premiere dimension pour l'information
    Deusieme dimension pour designer :
        -2 : emplacement libre
        -1 : pas de suivant
        [0,NbElem[ : indice du suivant
    IdTete designe la tete de la liste, -1 s'elle est vide
*/
typedef struct 
{
    int tab[2][NbElem];
    int IdTete; // indice de la tete de la liste
}TAB;

int Init_Liste(TAB *tab)
{
    if (!tab) return ((int)-1);
    for (int i = 0; i < NbElem; i++) tab->tab[1][i] = -2;
    tab->IdTete = -1;
    return ((int)1);
}

void AfficherListe(TAB *tab)
{
    int id;
    if (!tab) 
    {
        printf("\nErreur");
        exit(0);
    }
    if (tab->IdTete == -1) printf("\nListe vide");
    else
    {
        id = tab->IdTete;
        printf("\nListe : ");
        while (id != -1)
        {
            printf("%d\t",tab->tab[0][id]);
            id = tab->tab[1][id];
        }
    }
}

int InsererTeteListe(TAB *tab, int val)
{
    if (!tab) return ((int)-1);
    for (int i = 0; i < NbElem; i++)
    {
        if (tab->tab[1][i] == -2)
        {
            tab->tab[0][i] = val;
            tab->tab[1][i] = tab->IdTete;
            tab->IdTete = i;
            return ((int)1);
        }
    }
    return ((int)0);
}

int InsererQueueListe(TAB *tab, int val)
{
    int i, place, queue;
    if (!tab) return ((int)-1);
    if (tab->IdTete == -1) // liste vide
    {
        tab->tab[0][0] = val;
        tab->tab[1][0] = -1;
        tab->IdTete = 0;
        return ((int)1);
    }
    // chercher un emplacement libre
    for (place = 0; place < NbElem; place++)
    {
        if (tab->tab[1][place] == -2)
        {
            queue = tab->IdTete;
            i = tab->tab[1][queue];
            while (i != -1)
            {
                queue = i;
                i = tab->tab[1][i];
            }
            tab->tab[1][queue] = place;
            tab->tab[0][place] = val;
            tab->tab[1][place] = -1;
            return ((int)1);
        }
    }
    return ((int)0);
}

int InsererPosListe(TAB *tab, int val, int pos)
{
    int i, place, pred, cmp = 1;
    if (!tab) return ((int)-1);
    if (pos == 1) return ((int)InsererTeteListe(tab,val));
    // chercher un emplacement libre
    for (place = 0; place < NbElem; place++)
    {
        if (tab->tab[1][place] == -2)
        {
            pred = tab->IdTete;
            i = tab->tab[1][pred];
            while (i != -1)
            {
                cmp++;
                if (cmp == pos)
                {
                    tab->tab[1][pred] = place;
                    tab->tab[0][place] = val;
                    tab->tab[1][place] = i;
                    return ((int)1); // Insertion effectuee
                }
                pred = i;
                i = tab->tab[1][i];
            }
            if (pos == cmp+1)
            {
                tab->tab[1][pred] = place;
                tab->tab[0][place] = val;
                tab->tab[1][place] = i;
                return ((int)1); // Insertion effectuee
            }
            return ((int)-2); // Position non valide
        }
    }
    return ((int)0); // liste sauree
}

void main()
{
    int rt;
    TAB *tab = (TAB *)malloc(sizeof(TAB));
    rt = Init_Liste(tab);
    AfficherListe(tab);
    rt = InsererTeteListe(tab,5);
    rt = InsererQueueListe(tab,13);
    rt = InsererPosListe(tab,8,2);
    rt = InsererPosListe(tab,3,3);
    AfficherListe(tab);

}