#include<stdio.h>
#include<stdlib.h>

typedef struct ND
{
    int info;
    struct ND *fgc, *fdt;
}Noeud;

Noeud *CreerNoeud(int val)
{
    Noeud *NE = (Noeud *)malloc(sizeof(Noeud));
    if (!NE) exit(0);
    NE->info = val;
    NE->fgc = NE->fdt = NULL;
    return ((Noeud *)NE);
}

void Affichage_Infixe_Bornee(Noeud *Arb, int Inf, int Sup)
{
    if (Arb)
    {
        if (Inf <= Arb->info) Affichage_Infixe_Bornee(Arb->fgc,Inf,Sup);
        if (Inf <= Arb->info && Arb->info <= Sup) printf("%d\t",Arb->info);
        if (Arb->info <= Sup) Affichage_Infixe_Bornee(Arb->fdt,Inf,Sup);
    }   
}
