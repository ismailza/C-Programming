#include"../structures.h"

typedef struct NP
{
    Cellule *pile;
    struct NP *fgc, *fdt;
}NoeudP;

Cellule *Insertion_Pile(Cellule *pile, int val, int *ret, int *rec)
{
    Cellule *tmp = NULL;
    *ret = 0;
    if (!pile) return ((Cellule *)CreerCellule(val));
    tmp = Empiler(tmp,pile->info);
    pile = Depiler(pile);
    if (!pile)
    {
        if (tmp->info < val) pile = Empiler(pile,val);
        pile = Empiler(pile,tmp->info);
        tmp = Depiler(tmp);
        if (!pile->svt) pile = Empiler(pile,val);
        return ((Cellule *)pile);
    }
    if (pile->info <= val) *ret = 1;
    else if (val <= tmp->info) *ret = -1;
    else 
    {
        *rec = pile->info;
        *ret = 2;
        pile->info = val;
    }
    pile = Empiler(pile,tmp->info);
    tmp = Depiler(tmp);
    return ((Cellule *)pile);
}
NoeudP *CreerNoeudP(Cellule *pile)
{
    NoeudP *NP = (NoeudP *)malloc(sizeof(NoeudP));
    if (!NP) exit(0);
    NP->pile = pile;
    NP->fdt = NP->fgc = NULL;
    return ((NoeudP *)NP);
}
NoeudP *Insertion_Arbre_Pile(NoeudP *Arb, int val)
{
    int ret, rec;
    if (!Arb) return ((NoeudP *)CreerNoeudP(CreerCellule(val)));
    Arb->pile = Insertion_Pile(Arb->pile,val,&ret,&rec);
    switch (ret)
    {
        case -1: Arb->fgc = Insertion_Arbre_Pile(Arb->fgc,val);
        case 0: return ((NoeudP *)Arb);
        case 2: val = rec;
        case 1: Arb->fdt = Insertion_Arbre_Pile(Arb->fdt,val);
    }
    return ((NoeudP *)Arb);
}
void Afficher_Arbre_Pile(NoeudP *Arb)
{
    if (Arb)
    {
        Afficher_Arbre_Pile(Arb->fgc);
        AfficherPile(Arb->pile);
        Afficher_Arbre_Pile(Arb->fdt);
    }
}
void main()
{
    NoeudP *Arbre = NULL;
    Arbre = Insertion_Arbre_Pile(Arbre,12);
    Arbre = Insertion_Arbre_Pile(Arbre,20);
    Arbre = Insertion_Arbre_Pile(Arbre,5);
    Arbre = Insertion_Arbre_Pile(Arbre,22);
    Arbre = Insertion_Arbre_Pile(Arbre,15);
    Arbre = Insertion_Arbre_Pile(Arbre,8);
    Afficher_Arbre_Pile(Arbre);
}