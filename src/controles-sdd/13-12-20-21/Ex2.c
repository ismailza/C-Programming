/* ************************************************************
            Arbre Binaire Ordonne Horizontalement
************************************************************ */
#include<stdio.h>
#include<stdlib.h>

typedef struct nd
{
    int info;
    struct nd *fgc, *fdt;
}Noeud;

Noeud *CreerNoeud(int val)
{
    Noeud *NE;
    NE = (Noeud *)malloc(sizeof(Noeud));    // Allocation de la memoire
    if (!NE)
    {   
        printf("\nErreur d'allocation de la memoire!");
        exit(0);
    }
    NE->info = val;             // Affectation de la valeur du noeud
    NE->fgc = NE->fdt = NULL;   // Initialiser les fils au NULL
    return ((Noeud *)NE);
}
Noeud *InsererArbBinOrdonne(Noeud *Arb, int val)
{
    Noeud *NE;
    if (!Arb)                   // Arbre vide
    {
        NE = CreerNoeud(val);   // Creer un noued
        return ((Noeud *)NE);
    }
    // Insertion dans la partie gauche
    if (val < Arb->info) Arb->fgc = InsererArbBinOrdonne(Arb->fgc,val);
    // Insertion dans la partie droite
    else Arb->fdt = InsererArbBinOrdonne(Arb->fdt,val);
    return ((Noeud *)Arb);
}

int RechercheArbBinOrdonne(Noeud *Arb, int val)
{
    if (!Arb) return ((int)-1);             // Arbre vide
    if (Arb->info == val) return ((int)1);  // Element trouve
    if (val < Arb->info)
    {
        if (!Arb->fgc) return ((int)0);
        return ((int)RechercheArbBinOrdonne(Arb->fgc,val));
    }
    if (!Arb->fdt) return ((int)0);
    return ((int)RechercheArbBinOrdonne(Arb->fdt,val));
}

int RechercheDoubles(Noeud *Arb, int val)
{
    int rt;
    rt = RechercheArbBinOrdonne(Arb,val);
    if (rt==1)
    {
        printf("\n%d",val);
        rt = RechercheDoubles(Arb,2*val);
        return ((int)1);
    }
    return ((int)0);
}

int RechercheDoublesInterval(Noeud *Arb, int val, int inf, int sup)
{
    int rt;
    if (inf <= val && val <= sup)
    {
        rt = RechercheArbBinOrdonne(Arb,val);
        if (rt==1)
        {
            printf("\n%d",val);
            rt = RechercheDoublesInterval(Arb,2*val,inf,sup);
            return ((int)1);
        }
    }
    return ((int)0);
}

void main()
{
    Noeud *Arb = NULL;
    int rt;
    Arb = InsererArbBinOrdonne(Arb,15);
    Arb = InsererArbBinOrdonne(Arb,10);
    Arb = InsererArbBinOrdonne(Arb,18);
    Arb = InsererArbBinOrdonne(Arb,13);
    Arb = InsererArbBinOrdonne(Arb,6);
    Arb = InsererArbBinOrdonne(Arb,2);
    Arb = InsererArbBinOrdonne(Arb,12);
    Arb = InsererArbBinOrdonne(Arb,8);
    Arb = InsererArbBinOrdonne(Arb,16);
    Arb = InsererArbBinOrdonne(Arb,24);
    Arb = InsererArbBinOrdonne(Arb,20);
    rt = RechercheDoubles(Arb,6);
    printf("\n*********");
    rt = RechercheDoublesInterval(Arb,6,2,16);
}