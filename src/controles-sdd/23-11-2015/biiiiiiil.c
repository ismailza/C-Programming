#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int champ1, champ2;
}Bi;

typedef struct CL
{
    int info;
    struct CL *svt;
}Cellule;

typedef struct BL
{
    Bi *B;
    Cellule *liste;
}Bil;

typedef struct NB
{
    Bil *Bl;
    struct NB *fgc, *fdt;
}NoBil;
Cellule *CreerCellule(int val)
{
    Cellule *CL;
    CL = (Cellule *)malloc(sizeof(Cellule)); // Allocation de la memoire
    if (!CL) 
    {   // Erreur d'allocation de la memoire
        printf("\nErreur d'allocation de la memoire!");
        exit(0); // Quitter le programme
    }
    CL->info = val; // Affecter la valeur
    CL->svt = NULL; // Initialiser le pointeur suivant par NULL
    return ((Cellule *)CL); // retourne CL
}

Cellule *InsererPListeOrdonnee(Cellule *liste, int val)
{
    Cellule *CL, *courant;
    // tester si la liste existe
    if (!liste) return ((Cellule *)CreerCellule(val)); 
    CL = CreerCellule(val);
    // insertion en tete
    if (val < liste->info)
    {
        CL->svt = liste;
        return ((Cellule *)CL);
    }
    courant = liste; // pointer courant en tete
    while (courant->svt) // tant que courant a un svt
    {
        if (val < courant->svt->info )
        {   // Insertion en milieu
            CL->svt = courant->svt;
            courant->svt = CL;
            return ((Cellule *)liste);
        }
        courant = courant->svt;
    }
    // Insertion en queue
    courant->svt = CL;
    return ((Cellule *)liste);
}

void AfficherPListe(Cellule *liste)
{
    Cellule *courant;
    // si la liste est vide
    if (!(liste)) printf("\nLa liste est vide");
    else
    {
        courant = liste; // initialiser courant par la tete de la liste
        printf("\nListe : ");
        while (courant)
        {   // tant qu'on a un element dans la liste
            printf("%d\t",courant->info); // afficher l'element
            courant = courant->svt; // passer au suivant
        }
    }
}

Bi *Init_Bi(Bi *B)
{
    if (!B) return ((Bi *)B);
    B->champ1 = B->champ2 = -1;
    return ((Bi *)B);
}

int Bi_Est_Vide(Bi B)
{
    return ((int)((B.champ1 == -1) && (B.champ2 == -1))?1:0);
}
int Bi_Est_Saturee(Bi B)
{
    return ((int)((B.champ1 != -1) && (B.champ2 != -1))?1:0);
}

Bi *Inserer_Dans_Bi(Bi *B, int val)
{
    if (!B) return ((Bi *)NULL);
    if (!Bi_Est_Saturee(*B))
    {
        if (Bi_Est_Vide(*B)) B->champ1 = val;
        else
        {
            if (val < B->champ1)
            {
                B->champ2 = B->champ1;
                B->champ1 = val;
            }
            else B->champ2 = val;
        } 
    }
    return ((Bi *)B);
}

Bil *Init_Bil(Bil *Bl)
{
    if (!Bl) return ((Bil *)NULL);
    Bl->B = Init_Bi(Bl->B);
    Bl->liste = NULL;
    return ((Bil *)Bl);
}

int  Possible_Dans_Bil(Bil Bl, int val)
{
    return ((int)((Bl.B->champ1 <= val) && (val <= Bl.B->champ2))?1:0);
}

Bil *Inserer_Dans_Bil(Bil *Bl, int val)
{
    if (!Bl) return ((Bil *)NULL);
    if (!Bl->liste)
    {
        Bl->B = Inserer_Dans_Bi(Bl->B,val);
        Bl->B = Inserer_Dans_Bi(Bl->B,val+10);
    }
    if (Possible_Dans_Bil(*Bl,val)) Bl->liste = InsererPListeOrdonnee(Bl->liste, val);
    return ((Bil *)Bl);
}

NoBil *Init_NoBil()
{
    NoBil *NB = (NoBil *)malloc(sizeof(NoBil));
    if (!NB) exit(0);
    NB->Bl = (Bil *)malloc(sizeof(Bil));
    if (!NB->Bl) exit(0);
    NB->Bl = Init_Bil(NB->Bl);
    NB->fdt = NB->fgc = NULL;
    return ((NoBil *)NB);
}

int Possible_Dans_NoBil(NoBil NB, int val)
{
    return ((int)Possible_Dans_Bil(*(NB.Bl),val));
}

NoBil *Inserer_Dans_NoBil(NoBil *NB, int val, int *ret, int *borne)
{
    if (!NB)
    {
        NB = Init_NoBil(NB);
        
    }
}


int main()
{
    Bil *Bl = (Bil *)malloc(sizeof(Bil));
    Bl->B = (Bi *)malloc(sizeof(Bi));
    Bl = Init_Bil(Bl);

    Bl = Inserer_Dans_Bil(Bl,2);
    Bl = Inserer_Dans_Bil(Bl,6);
    Bl = Inserer_Dans_Bil(Bl,4);
    Bl = Inserer_Dans_Bil(Bl,9);
    Bl = Inserer_Dans_Bil(Bl,10);

    AfficherPListe(Bl->liste);
}