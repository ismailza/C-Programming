#include<stdio.h>
#include<stdlib.h>

typedef struct CL
{
    int info;
    struct CL *svt;
}Cellule;
// Structure de file
typedef struct FL
{
    Cellule *Tete, *Queue;
}File;
typedef struct NC
{
    Cellule CL;
    struct NC *fgc, *fdt;
}NoeudC;

File *CreerFile()
{
    File *FL;
    FL = (File *)malloc(sizeof(File));
    if (!FL)
    {   // Erreur d'allocation de la memoire
        printf("\nErreur d'allocation de la memoire!");
        exit(0);
    }
    FL->Tete = FL->Queue = NULL;
    return ((File *)FL);
}
NoeudC *CreerNoeudC(Cellule *CL)
{
    if (!CL) return ((NoeudC *)NULL);
    NoeudC *NC = (NoeudC *)malloc(sizeof(NoeudC));
    if (!NC) exit(0);
    NC->CL = *CL;
    NC->fdt = NC->fgc = NULL;
    return ((NoeudC *)NC);
}

int Enfiler_Cellule(File *file, Cellule *cl)
{
    if (!file) return ((int)0);
    if (!file->Tete) file->Tete = cl;
    else file->Queue->svt = cl;
    file->Queue = cl;
    return ((int)1);
}
int Defiler_Cellule(File *file, Cellule *cl[1])
{
    if (!file) return ((int)-1);
    if (!file->Tete) return ((int)0);
    cl[0] = file->Tete;
    file->Tete = file->Tete->svt;
    if (!file->Tete) file->Queue = NULL;
    return ((int)1);
}
File *Trans_Liste_File_Ordonnee(Cellule *liste)
{
    int rt;
    Cellule *ptr, *courant, *tmp[1];
    File *file = CreerFile();
    while (liste)
    {
        courant = liste;
        liste = liste->svt;
        courant->svt = NULL;

        if (!file->Tete) rt = Enfiler_Cellule(file, courant);
        else if (file->Queue->info <= courant->info) rt = Enfiler_Cellule(file, courant);
        else
        {
            ptr = file->Queue;
            while (file->Tete->info < courant->info)
            {
                rt = Defiler_Cellule(file, tmp);
                rt = Enfiler_Cellule(file, tmp[0]);
            }
            rt = Enfiler_Cellule(file, courant);
            while (file->Tete != ptr)
            {
                rt = Defiler_Cellule(file, tmp);
                rt = Enfiler_Cellule(file, tmp[0]);
            }
            rt = Defiler_Cellule(file, tmp);
            rt = Enfiler_Cellule(file, tmp[0]);            
        } 
    }
    return ((File *)file);
}

NoeudC *Inserer_Cellule_Arbre_Ordonne(NoeudC *Arb, Cellule *cl)
{
    if (!Arb) return ((NoeudC *)CreerNoeudC(cl));
    if (cl->info <= Arb->CL.info) Arb->fgc = Inserer_Cellule_Arbre_Ordonne(Arb->fgc,cl);
    else Arb->fdt = Inserer_Cellule_Arbre_Ordonne(Arb->fdt,cl);
    return ((NoeudC *)Arb);
}

NoeudC *Trans_Liste_Arbre_Ordonne(Cellule *liste)
{
    NoeudC *Arbre = NULL;
    Cellule *courant;
    while (liste)
    {
        courant = liste;
        liste = liste->svt;
        courant->svt = NULL;

        Arbre = Inserer_Cellule_Arbre_Ordonne(Arbre,courant);
    }
    return ((NoeudC *)Arbre);
}

Cellule *Trans_Arbre_Pile_rec(NoeudC *Arb, Cellule *pile)
{
    if (Arb)
    {
        if (Arb->fgc)
        {
            pile = Trans_Arbre_Pile_rec(Arb->fgc,pile);
            Arb->fgc = NULL;
        }
        Arb->CL.svt = pile;
        pile = &Arb->CL;
        if (Arb->fdt)
        {
            pile = Trans_Arbre_Pile_rec(Arb->fdt,pile);
            Arb->fdt = NULL;
        }
    }
    return ((Cellule *)pile);    
}

Cellule *Trans_Arbre_Pile(NoeudC *Arb)
{
    Cellule *pile = NULL;
    return ((Cellule *)Trans_Arbre_Pile_rec(Arb,pile));
}

void Affichage_Infixe_Arbre_Cellule(NoeudC *Arb)
{
    if (Arb)
    {
        Affichage_Infixe_Arbre_Cellule(Arb->fgc);
        printf("%d\t",Arb->CL.info);
        Affichage_Infixe_Arbre_Cellule(Arb->fdt);
    }
}

Cellule *CreerCellule(int val)
{
    Cellule *CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL)
    {
        printf("\nErreur d'allocation de la memoire pour la cellule!");
        exit(0);
    }
    CL->info = val;
    CL->svt = NULL;
    return ((Cellule *)CL);
}
Cellule *Inserer_Liste_Fin(Cellule *liste, int val)
{
    Cellule *CL, *courant;
    CL = CreerCellule(val); 
    if (!liste) return ((Cellule *)CL); 
    courant = liste; 
    while (courant->svt) courant = courant->svt; 
    courant->svt = CL; 
    return ((Cellule *)liste); 
}
void Affichage_Liste(Cellule *liste)
{
    Cellule *courant;
    if (!liste) printf("\nListe vide");
    else
    {
        printf("\nListe :  ");
        courant = liste;
        while (courant)
        {
            printf("%d\t",courant->info);
            courant = courant->svt;
        }
    }
}

void main()
{
    Cellule *liste = NULL, *liste1 = NULL, *pile;
    File *file;
    NoeudC *Arbre;
    for (int i = 0; i < 16; i++)
    {
        liste = Inserer_Liste_Fin(liste,rand()%50);
        liste1 = Inserer_Liste_Fin(liste1,rand()%50);
    }
    Affichage_Liste(liste);
    file = Trans_Liste_File_Ordonnee(liste);
    Affichage_Liste(file->Tete);  
    Affichage_Liste(liste1);
    Arbre = Trans_Liste_Arbre_Ordonne(liste1);
    printf("\n");
    Affichage_Infixe_Arbre_Cellule(Arbre);
    pile = Trans_Arbre_Pile(Arbre);
    printf("\n--");
    Affichage_Liste(pile);
}