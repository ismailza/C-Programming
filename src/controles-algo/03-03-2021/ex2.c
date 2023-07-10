#include<stdio.h>
#include<stdlib.h>

typedef struct ND
{
    int info;
    struct ND *fdt, *fgc;
}Noeud;

Noeud *Insert_Arb_Ordonne_H(Noeud *Arb, Noeud *ND)
{
    if (ND)
    {
        if (!Arb) return ((Noeud *)ND);                  
        if (ND->info < Arb->info) Arb->fgc = Insert_Arb_Ordonne_H(Arb->fgc,ND);
        else Arb->fdt = Insert_Arb_Ordonne_H(Arb->fdt,ND);
    }
    return ((Noeud *)Arb);
}
Noeud *Transf_ABQ_To_ABOH(Noeud *ABQ, Noeud *ABOH)
{
    if (ABQ)
    {
        if (ABQ->fgc)
        {
            ABOH = Transf_ABQ_To_ABOH(ABQ->fgc,ABOH);
            ABQ->fgc = NULL;
        }
        if (ABQ->fdt)
        {
            ABOH = Transf_ABQ_To_ABOH(ABQ->fdt,ABOH);
            ABQ->fdt = NULL;
        }
        ABOH = Insert_Arb_Ordonne_H(ABOH,ABQ);
    }
    return ((Noeud *)ABOH);
}
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
void AffichageInfixe(Noeud *Arb)
{
    if (Arb)
    {
        AffichageInfixe(Arb->fgc);
        printf("%d\t",Arb->info);
        AffichageInfixe(Arb->fdt);
    }
}
void main()
{
    Noeud *Arb1 = NULL, *ARB2 = NULL;

    Arb1 = CreerNoeud(12);
    Arb1->fgc = CreerNoeud(25);
    Arb1->fgc->fgc = CreerNoeud(30);
    Arb1->fgc->fdt = CreerNoeud(7);
    Arb1->fgc->fdt->fdt = CreerNoeud(5);
    Arb1->fdt = CreerNoeud(8);
    Arb1->fdt->fgc = CreerNoeud(19);
    Arb1->fdt->fdt = CreerNoeud(2);
    AffichageInfixe(Arb1);

    printf("\n");
    ARB2 = Transf_ABQ_To_ABOH(Arb1,ARB2);
    AffichageInfixe(ARB2);
    

}