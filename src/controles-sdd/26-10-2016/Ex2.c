#include<stdio.h>
#include<stdlib.h>
#define NbElem 30
typedef struct
{
    int Tab[NbElem]; // tableau des entiers
    int IdElem; // indice du dernier element
}TAB;

int doublonsTab(TAB tab)
{
    int i;
    int v = 0, rang;
    if (tab.IdElem == -1) return ((int)0);
    for (i = 0; i<= tab.IdElem; i++)
    {
        if (tab.Tab[i]==tab.Tab[i+1]) continue;
        rang = i;
        while (tab.Tab[++i] <= 2*tab.Tab[rang])
        {
            if (tab.Tab[i] == 2*tab.Tab[rang]){
                if (!v) printf("\nLa valeur %d a pour rang %d, les rang de ses doublons : \t",tab.Tab[rang],rang);
                printf("%d\t",i);
                v = 1;
            }
        }
        v = 0;
        i = rang;
    }
    return ((int)1);
}

void main()
{
    int rt;
    TAB tab;
    tab.IdElem = -1;
    tab.Tab[++tab.IdElem] = 1; // 0
    tab.Tab[++tab.IdElem] = 2; // 1
    tab.Tab[++tab.IdElem] = 3; // 2
    tab.Tab[++tab.IdElem] = 3; // 3
    tab.Tab[++tab.IdElem] = 4; // 4
    tab.Tab[++tab.IdElem] = 5;
    tab.Tab[++tab.IdElem] = 10;
    tab.Tab[++tab.IdElem] = 10;
    tab.Tab[++tab.IdElem] = 10;
    tab.Tab[++tab.IdElem] = 15;
    tab.Tab[++tab.IdElem] = 30;
    tab.Tab[++tab.IdElem] = 45;
    rt = doublonsTab(tab);
}