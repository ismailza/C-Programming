#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NbElem 30
typedef struct
{
    int Tab[NbElem];
    int IdElem;
}Tableau;

int SupprimerOccurenceElem(Tableau *tab, int val)
{
    int i = 0, occ = 0; // la variable occ pour stocker le nombre d'occurence
    if (!tab) return ((int)-1); // Tester si la zone memoire existe
    for (i = 0; i <= tab->IdElem; i++) // parcourir la tab
    {
        if(tab->Tab[i] == val)
        {   // si on trouve un element a supprimer
            occ++; // incrementer le nombre d'occurence d'apparition de l'element a supprimer
            continue; // passer a l'element suivant
        }
        if (occ != 0) // si on a deja trouver une occurence de l'element a supprimer
            tab->Tab[i-occ] = tab->Tab[i]; 
    }
    if (occ == 0) return ((int)0); // Element non trouve
    tab->IdElem -= occ; // changer l'indice du dernier element
    return ((int)1);
}
int SupprimerDoubles(Tableau *tab, int val)
{
    int i, rt;
    if (tab->IdElem == -1) return ((int)0);
    do
    {
        rt = SupprimerOccurenceElem(tab,val);
        val *= 2;
    } while (rt);
    return ((int)1);    
}

void Afficher(Tableau *tab)
{
    int i;
    if (!tab)
    {
        printf("\ntab inexiste!");
        exit(0); // Quitter le programme
    }
    if (tab->IdElem == -1) printf("\nLa table est vide"); // tab vide
    else
    {
        printf("\ntab : ");
        for (i = 0; i <= tab->IdElem; i++) // parcourir la tab
            printf("%d\t",tab->Tab[i]); // afficher element par element
    }  
}

void main()
{
    Tableau tab;
    int rt;
    tab.IdElem = -1;
    tab.Tab[++tab.IdElem] = 3;
    tab.Tab[++tab.IdElem] = 9;
    tab.Tab[++tab.IdElem] = 6;
    tab.Tab[++tab.IdElem] = 3;
    tab.Tab[++tab.IdElem] = 18;
    tab.Tab[++tab.IdElem] = 24;
    tab.Tab[++tab.IdElem] = 192;
    tab.Tab[++tab.IdElem] = 3;
    Afficher(&tab);
    rt= SupprimerDoubles(&tab,3);
    Afficher(&tab);   

}