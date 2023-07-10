/* ************************************************************
                Liste à l'aide d'un tableau
************************************************************ */
#include<stdio.h>
#include<stdlib.h>
#define NbElem 25

// A- Supprimer les repetitions d'entiers dans un tableau 
typedef struct // Definition de la structure
{
    int info[NbElem];   // tableau d'entiers
    int IdElem;         // indice du dernier element
}TAB;

int SupprimerRepetitionListe(TAB *tab)
{
    int i = 0, k, tmp;
    if (!tab) return ((int)0);
    while (i < (tab->IdElem))
    {
        tmp = i;
        k = i+1;
        while (k <= tab->IdElem)
        {
            if ((tab->info[k]) != (tab->info[i])) 
            {
                tmp++; 
                tab->info[tmp] = tab->info[k];
            }
            k++;
        }
        tab->IdElem = tmp;
        i++;
    }
    return ((int)1);
}
void AfficherListe(TAB *tab)
{
    if (!tab) {printf("\ntableau non existe!"); exit(0); }
    if (tab->IdElem == -1) printf("\ntableau Vide");
    else
    {
        printf("\nTAB : \t");
        for (int i = 0; i <= tab->IdElem; i++) printf("%d\t",tab->info[i]);
    }
}

// B- Liste a l'aide de tableau
// a- Definition de la structure
typedef struct list
{
    int info[NbElem];   // tableau d'entiers
    int IdTete;         // indice de la tete du tableau
    int IdQueue;        // indice de la queue du tableau
}TListe;
// Prototype
int Existe_TListe(TListe *liste)
{
    return ((int)(!liste ? 0:1));
}
int Est_Vide_TListe(TListe *liste)
{
    if (!Existe_TListe(liste)) return ((int)-1);
    return ((int)(liste->IdTete==-1 ? 1:0));
}
int Est_Saturee_TListe(TListe *liste)
{
    if (!Existe_TListe(liste)) return ((int)-1);
    return ((int)((liste->IdQueue-liste->IdTete+1)==NbElem ? 1:0));
}

// b- Init_TListe;
int Init_TListe(TListe *liste)
{
    if (!Existe_TListe(liste)) return ((int)0);
    liste->IdTete = -1;
    liste->IdQueue = -1;
    return ((int)1);
}
// c- Supp_1Elem_TListe;
int Supp_1Elem_TListe(TListe *liste)
{
    if (!Existe_TListe(liste)) return ((int)-1);
    if (Est_Vide_TListe(liste)) return ((int)0);
    if (liste->IdTete == liste->IdQueue) liste->IdTete = liste->IdQueue = -1;
    else liste->IdTete++;
    return ((int)1);
}
// d- Supp_Val_1Occur_TListe;
int Supp_Val_1Occur_TListe(TListe *liste, int val)
{
    int i;
    if (!Existe_TListe(liste)) return ((int)-1);
    if (Est_Vide_TListe(liste)) return ((int)0);
    if (liste->info[liste->IdTete] == val) return ((int)Supp_1Elem_TListe(liste));
    else
    {
        i = liste->IdTete+1;
        while ((i <= liste->IdQueue) && (liste->info[i]!=val)) i++;
        if (liste->info[i] != val) return ((int)0);
        while (i < liste->IdQueue)
        {
            liste->info[i] = liste->info[i+1];
            i++;
        }
        liste->IdQueue--;
    }
    return ((int)1);
}
// e- Supp_Val_TListe;
int Supp_Val_TListe(TListe *liste, int val)
{
    int i, tmp;
    if (!Existe_TListe(liste)) return ((int)-1);
    if (Est_Vide_TListe(liste)) return ((int)0);
    while ((liste->IdTete != -1) && (liste->info[liste->IdTete] == val)) i = Supp_1Elem_TListe(liste);
    tmp = liste->IdTete;
    i = tmp+1;
    while (i <= liste->IdQueue)
    {
        if (liste->info[i] != val) 
        {
            tmp++;
            liste->info[tmp] = liste->info[i];
        }
        i++;
    }
    liste->IdQueue = tmp;
    return ((int)1);   
}
// f- Insert_Val_TListe;
int Insert_Val_TListe(TListe *liste, int val, int pos)
{
    int i;
    if (!Existe_TListe(liste)) return ((int)-1);
    if (Est_Saturee_TListe(liste)) return ((int)0);
    if ((pos < 1) || (pos > (liste->IdQueue-liste->IdTete+2))) return ((int)-2);
    if (Est_Vide_TListe(liste)) 
    {
        liste->info[++liste->IdTete] = val;
        liste->IdQueue++;
    }
    else
    {
        if (liste->IdTete)
        {
            liste->IdTete--;
            for (i = liste->IdTete; i < liste->IdTete+pos-1; i++) liste->info[i] = liste->info[i+1];
            liste->info[i] = val;
        }
        else
        {
            liste->IdQueue++;
            for (i = liste->IdQueue; i >= pos; i--) liste->info[i] = liste->info[i-1];
            liste->info[i] = val;
        }
    }   
    return ((int)1);
}
// AfficherTListe
void AfficherTListe(TListe *liste)
{
    if (!Existe_TListe(liste)) exit(0);
    if (Est_Vide_TListe(liste)) printf("\nListe vide");
    else
    {
        printf("\nListe :\t");
        for (int i = liste->IdTete; i <= liste->IdQueue; i++)
            printf("%d\t",liste->info[i]);
    }
}

void main()
{
    int rt;
    TListe *liste = (TListe *)malloc(sizeof(TListe));
    rt = Init_TListe(liste);
    rt = Insert_Val_TListe(liste,6,1);
    rt = Insert_Val_TListe(liste,8,1);
    rt = Insert_Val_TListe(liste,8,2);
    rt = Insert_Val_TListe(liste,12,3);
    rt = Insert_Val_TListe(liste,6,4);
    rt = Insert_Val_TListe(liste,12,3);
    rt = Insert_Val_TListe(liste,8,5);
    rt = Insert_Val_TListe(liste,6,3);
    AfficherTListe(liste);
    rt = Supp_Val_TListe(liste,8);
    AfficherTListe(liste);
    rt = Insert_Val_TListe(liste,50,3);
    AfficherTListe(liste);
    // TAB *tab = (TAB *)malloc(sizeof(TAB));
    // tab->IdElem = -1;
    
    // tab->info[++tab->IdElem] = 1;
    // tab->info[++tab->IdElem] = 0;
    // tab->info[++tab->IdElem] = 2;
    // tab->info[++tab->IdElem] = 1;
    // tab->info[++tab->IdElem] = 5;
    // tab->info[++tab->IdElem] = 4;
    // tab->info[++tab->IdElem] = 1;
    // tab->info[++tab->IdElem] = 2;
    // tab->info[++tab->IdElem] = 5;
    // tab->info[++tab->IdElem] = 6;
    // AfficherListe(tab);
    // rt = SupprimerRepetitionListe(tab);
    // AfficherListe(tab);


}