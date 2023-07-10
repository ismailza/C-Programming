#include<stdio.h>
#include<stdlib.h>

#define MaxElem 25

typedef struct 
{
    int info[MaxElem];
    int NbElem;
}StTable;
// a-
int Ind_Elem_Relatif(StTable *tab, int Ind, int val)
{
    int i = Ind;
    if (!tab) return ((int)-2);
    while (i < tab->NbElem)
    {
        if (tab->info[i] == val) return ((int)i);
        i++;
    }
    return ((int)-1);
}
// b- 
int Echange_Elem(StTable *tab, int Ind1, int Ind2)
{
    int tmp;
    if (!tab) return ((int)-1);
    if ((Ind1 < 0 || Ind1 >= tab->NbElem) && (Ind2 < 0 || Ind2 >= tab->NbElem)) return ((int)0);
    tmp = tab->info[Ind1];
    tab->info[Ind1] = tab->info[Ind2];
    tab->info[Ind2] = tmp;
    return ((int)1);
}
// c-
int Ind_Min_Relatif(StTable *tab, int IndD)
{
    int i, idmin = IndD;
    if ((IndD < 0) || (IndD >= tab->NbElem)) return ((int)-1);
    for (i = IndD; i < tab->NbElem; i++)
    {
        if (tab->info[i] < tab->info[idmin]) idmin = i;
    }
    return ((int)idmin);   
}
// d-
void Tri_Double(StTable *tab)
{
    int i = 0, rt, val, finished = 0;
    while (i < tab->NbElem)
    {
        rt = Ind_Min_Relatif(tab,i);
        rt = Echange_Elem(tab,i,rt);
        val = tab->info[i];
        do
        {
            finished = 0;
            while ((rt = Ind_Elem_Relatif(tab,i,val)) != -1)
            {
                rt = Echange_Elem(tab,i,rt);
                i++;
                finished = 1;
            }
            val *= 2;
        } while (finished == 1);
    }
}

void main()
{
    int rt;
    StTable *tab = (StTable *)malloc(sizeof(StTable));
    tab->NbElem = 0;
    tab->info[tab->NbElem++] = 5; 
    tab->info[tab->NbElem++] = 6; 
    tab->info[tab->NbElem++] = 1; 
    tab->info[tab->NbElem++] = 2;
    tab->info[tab->NbElem++] = 3;
    tab->info[tab->NbElem++] = 4;
    tab->info[tab->NbElem++] = 6;
    tab->info[tab->NbElem++] = 4;
    tab->info[tab->NbElem++] = 2;
    tab->info[tab->NbElem++] = 1;
    tab->info[tab->NbElem++] = 0;
    tab->info[tab->NbElem++] = 3;
    tab->info[tab->NbElem++] = 10;
    tab->info[tab->NbElem++] = 7;
    tab->info[tab->NbElem++] = 8;
    tab->info[tab->NbElem++] = 10;
    tab->info[tab->NbElem++] = 11;
    tab->info[tab->NbElem++] = 12;
    tab->info[tab->NbElem++] = 0;

    for (int i = 0; i < tab->NbElem; i++)
    {
        printf("%d\t",tab->info[i]);
    }

    Tri_Double(tab);

    printf("\n***************\n");
    for (int i = 0; i < tab->NbElem; i++)
    {
        printf("%d\t",tab->info[i]);
    }
    
}