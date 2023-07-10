#include<stdio.h>
#include<stdlib.h>
// Arbre Pariculier : Sedra
typedef struct ND
{
    int info;
    struct ND *fils, *frere;
}Noeud;

Noeud *CreerNoeud(int val)
{
    Noeud *NE = (Noeud *)malloc(sizeof(Noeud));
    if (!NE) exit(0);
    NE->info = val;
    NE->fils = NE->frere = NULL;
    return ((Noeud *)NE);
}

Noeud *Insert_Arb(Noeud *Arb, int val)
{
    if (!Arb) return ((Noeud *)CreerNoeud(val));
    if (val < Arb->info) Arb->fils = Insert_Arb(Arb->fils,val);
    else Arb->frere = Insert_Arb(Arb->frere,val);
    return ((Noeud *)Arb);    
}

void Affichage_Infixe(Noeud *Arb)
{
    if (Arb)
    {
        Affichage_Infixe(Arb->fils);
        printf("%d\t",Arb->info);
        Affichage_Infixe(Arb->frere);
    }
}

void main()
{
    Noeud *Arb = NULL;
    Arb = Insert_Arb(Arb,15);
    Arb = Insert_Arb(Arb,4);
    Arb = Insert_Arb(Arb,2);
    Arb = Insert_Arb(Arb,8);
    Arb = Insert_Arb(Arb,3);
    Arb = Insert_Arb(Arb,1);
    Arb = Insert_Arb(Arb,6);
    Arb = Insert_Arb(Arb,9);
    Arb = Insert_Arb(Arb,7);
    Arb = Insert_Arb(Arb,5);
    Affichage_Infixe(Arb);
}