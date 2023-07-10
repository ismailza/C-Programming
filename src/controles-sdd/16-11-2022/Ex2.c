#include<stdio.h>
#include<stdlib.h>

#define MaxElem 100 // Max d'element d'un tableau
#define Min_2_Nb(a,b) (a<b)?a:b
#define Min_3_Nb(a,b,c) ((Min_2_Nb(a,b))<c)?(Min_2_Nb(a,b)):c
// Structure d'un tableau de MaxElem Possible et qui contient NbElem
typedef struct TB
{
    int Tab[MaxElem];   // Tableau d'entiers
    int NbElem;         // nombre d'elements dans le tableau
}TAB;
// Structure pour la definition d'une liste et d'une pile
typedef struct cel
{
    int entier;         // Valeur de la cellule
    struct cel *svt;    // un pointeur sur le suivant
}Cellule;
// Structure pour la definition d'une file
typedef struct FL
{
    Cellule *Tete;      // un pointeur sur la tete de la file
    Cellule *Queue;     // un pointeur sur la queue de la file 
}File;
// Structure pour rassembler d'autres structures
typedef struct ns
{
    TAB *tab;           // structure d'un tableau
    Cellule *pile;      // structure d'une pile
    File *file;         // structure d'une file
}NewStruct;

// I- Fonctions de manipulation des structures
Cellule *CreerCellule(int val)
{
    Cellule *CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL)
    {
        printf("\nErreur !!");
        exit(0);
    }
    CL->entier = val;
    CL->svt = NULL;
    return ((Cellule *)CL);
}
// a- Insertion d'un entier dans une pile
Cellule *EmpilerPile(Cellule *pile, int val)
{
    Cellule *CL = CreerCellule(val);
    CL->svt = pile;
    return ((Cellule *)CL);
}
// b- Insertion d'un entier dans une file
int EnfilerFile(File *file, int val)
{
    Cellule *CL;
    if (!file) return ((int)0);
    CL = CreerCellule(val);
    if (!file->Tete) file->Tete = CL;
    else file->Queue->svt = CL;
    file->Queue = CL;
    return ((int)1);
}
// c- Insertion d'un entier a la bonne place dans un tableau ordonne
int InsererTabOrdonne(TAB *tab, int val)
{
    int i;
    if (!tab) return ((int)-1);
    if (tab->NbElem == MaxElem) return ((int)0);
    i = tab->NbElem;
    while ((i > 0) && (val < tab->Tab[i-1]))
    {
        tab->Tab[i] = tab->Tab[i-1];
        i--;
    }
    tab->Tab[i] = val;
    tab->NbElem++;
    return ((int)1);
}
// II- Manipulation des structures
// a- 
Cellule *TransfererListe(Cellule *liste, NewStruct *NS)
{
    Cellule *courant;
    int rt;
    if (!NS) 
    {
        printf("\nErreur : Les structures non existes!!");
        exit(0);
    }
    if (!liste) return ((Cellule *)NULL);
    courant = liste;
    while (courant)
    {
        if (!NS->pile) NS->pile = EmpilerPile(NS->pile,courant->entier);
        else if (courant->entier <= NS->pile->entier) NS->pile = EmpilerPile(NS->pile,courant->entier);
        else if (!NS->file->Tete) rt = EnfilerFile(NS->file,courant->entier);
        else if (NS->file->Queue->entier <= courant->entier) rt = EnfilerFile(NS->file,courant->entier);
        else rt = InsererTabOrdonne(NS->tab,courant->entier);
        courant = courant->svt;
    }
    return ((Cellule *)liste);
}
// b- 
Cellule *DepilerPile(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL);
    Supp = pile;
    pile = pile->svt;
    free(Supp);
    return ((Cellule *)pile);
}
int DefilerFile(File *file)
{
    Cellule *Supp;
    if (!file) return ((int)-1);
    if (!file->Tete) return ((int)0);
    Supp = file->Tete;
    file->Tete = file->Tete->svt;
    free(Supp);
    if (!file->Tete) file->Queue = NULL;
    return ((int)1);
}
// Seven while
void AffichageNewStructs(NewStruct *NS)
{
    int i = 0, min, rt;
    if (!NS)
    {
        printf("\nErreur");
        exit(0);
    }
    if (!NS->pile && !NS->file->Tete && !NS->tab->NbElem) printf("\nStructures vides");
    else
    {
        printf("\nAffichage : ");
        while ((NS->pile) && (NS->file->Tete) && (i < NS->tab->NbElem))
        {
            min = Min_3_Nb(NS->pile->entier,NS->file->Tete->entier,NS->tab->Tab[i]);
            printf("%d\t",min);
            if (NS->pile->entier == min) NS->pile = DepilerPile(NS->pile);
            else if (NS->file->Tete->entier == min) rt = DefilerFile(NS->file);
            else i++;
        }
        while ((NS->pile) && (NS->file->Tete))
        {
            min = Min_2_Nb(NS->pile->entier,NS->file->Tete->entier);
            printf("%d\t",min);
            if (NS->pile->entier == min) NS->pile = DepilerPile(NS->pile);
            else rt = DefilerFile(NS->file);
        }
        while ((NS->pile) && (i < NS->tab->NbElem))
        {
            min = Min_2_Nb(NS->pile->entier,NS->tab->Tab[i]);
            printf("%d\t",min);
            if (NS->pile->entier == min) NS->pile = DepilerPile(NS->pile);
            else i++;
        }
        while ((NS->file->Tete) && (i < NS->tab->NbElem))
        {
            min = Min_2_Nb(NS->file->Tete->entier,NS->tab->Tab[i]);
            printf("%d\t",min);
            if (NS->file->Tete->entier == min) rt = DefilerFile(NS->file);
            else i++;
        }
        while (NS->pile)
        {
            printf("%d\t",NS->pile->entier);
            NS->pile = DepilerPile(NS->pile);
        }
        while (NS->file->Tete)
        {
            printf("%d\t",NS->file->Tete->entier);
            rt = DefilerFile(NS->file);
        }
        while (i < NS->tab->NbElem)
        {
            printf("%d\t",NS->tab->Tab[i]);
            i++;
        }      
    }    
}

Cellule *InsererListeDebut(Cellule *liste, int val)
{
    Cellule *CL = CreerCellule(val);
    CL->svt = liste;
    return ((Cellule *)CL);
}

void main()
{
    Cellule *liste = NULL;
    liste = InsererListeDebut(liste,3);
    liste = InsererListeDebut(liste,5);
    liste = InsererListeDebut(liste,12);
    liste = InsererListeDebut(liste,2);
    liste = InsererListeDebut(liste,1);
    liste = InsererListeDebut(liste,16);
    liste = InsererListeDebut(liste,22);
    liste = InsererListeDebut(liste,7);
    liste = InsererListeDebut(liste,17);
    liste = InsererListeDebut(liste,3);
    liste = InsererListeDebut(liste,11);
    liste = InsererListeDebut(liste,21);
    liste = InsererListeDebut(liste,13);
    liste = InsererListeDebut(liste,5);
    liste = InsererListeDebut(liste,14);
    Cellule *courant = liste;
    printf("\nListe : ");
    while (courant)
    {
        printf("%d\t",courant->entier);
        courant = courant->svt;
    }
    
    NewStruct *NS = (NewStruct *)malloc(sizeof(NewStruct));
    NS->pile = NULL;
    NS->file = (File *)malloc(sizeof(File));
    NS->file->Tete = NS->file->Queue = NULL;
    NS->tab = (TAB *)malloc(sizeof(TAB));
    NS->tab->NbElem = 0;

    liste = TransfererListe(liste,NS);
    printf("\nTAB : ");
    for (int i = 0; i < NS->tab->NbElem; i++)
    {
        printf("%d\t",NS->tab->Tab[i]);
    }
    printf("\nPile : ");
    courant = NS->pile;
    while (courant) 
    {   // Non respecte de principe de pile !!
        printf("%d\t",courant->entier);
        courant = courant->svt;
    }
    printf("\nFile : ");
    courant = NS->file->Tete;
    while (courant)
    {   // Non respecte de principe de file !!
        printf("%d\t",courant->entier);
        courant = courant->svt;
    }
    
    AffichageNewStructs(NS);
}