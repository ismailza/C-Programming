#include<stdio.h>
#include<stdlib.h>
#define NbElem 25
// a
typedef struct 
{
    int tab[NbElem];
    int IdElem;
}TAB;

typedef struct cell
{
    int info;
    struct cell *suivant;
}Cellule;

typedef struct 
{
    Cellule *Tete, *Queue;
}File;

typedef struct 
{
    TAB *tab;
    Cellule *liste, *pile;
    File *file;
}QuatresStructs;

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
    CL->suivant = NULL; // Initialiser le pointeur suivant par NULL
    return ((Cellule *)CL); // retourne CL
}
// b
Cellule *Insert_Ord_Liste(Cellule *liste, int val)
{
    Cellule *courant;
    Cellule *CL = CreerCellule(val);
    // liste vide
    if (!liste) return ((Cellule *)CL);
    // insertion en tete
    if (val <= liste->info) 
    {
        CL->suivant = liste;
        return ((Cellule *)CL);
    }
    courant = liste;
    while (courant->suivant)
    {   // insertion en milieu
        if (val <= courant->suivant->info)
        {
            CL->suivant = courant->suivant;
            courant->suivant = CL;
            return ((Cellule *)liste);
        }
        courant = courant->suivant;
    }
    // insertion en queue    
    courant->suivant = CL;
    return ((Cellule *)liste);
}
// b
int Insert_Ord_File(File *file, int val)
{
    int rt, inserted = 0;
    Cellule *CL, *courant;
    if (!file) return ((int)-1);
    CL = CreerCellule(val);
    // file vide
    if (!file->Tete) 
    {
        file->Tete = CL;
        file->Queue = CL;
        return ((int)1);
    }
    // insertion en Queue
    if (file->Queue->info <= val)
    {
        file->Queue->suivant = CL;
        file->Queue = CL;
    }
    else
    {
        do
        {
            if ((val <= file->Tete->info) && (!inserted))
            {
                file->Queue->suivant = CL;
                file->Queue = CL;
                inserted = 1;
            }
            courant = file->Tete;
            file->Tete = file->Tete->suivant;
            courant->suivant = NULL;
            file->Queue->suivant = courant;
            file->Queue = courant;
        } while (file->Tete->info >= file->Queue->info);
    }
    return ((int)1);
}
// c
Cellule *EmpilerPPile(Cellule *pile, int val);
Cellule *DepilerPPile(Cellule *pile);
Cellule *Insert_Ord_Pile(Cellule *pile, int val)
{
    Cellule *tmp = NULL;
    while (pile)
    {
    if (val <= pile->info) break;
    tmp = EmpilerPPile(tmp,pile->info);
    pile = DepilerPPile(pile);
    }
    pile = EmpilerPPile(pile,val);
    while (tmp)
    {
        pile = EmpilerPPile(pile,tmp->info);
        tmp = DepilerPPile(tmp);
    }
    return ((Cellule *)pile);
}

void AfficherPFile(File *file)
{
    int i;
    Cellule *ptQueue, *courant;
    if (!file) // tester si la file existe
    {
        printf("\nFile inexiste!");
        exit(0);
    }
    if(!file->Tete) printf("\nLa file est vide");
    else {
        printf("\nFile : ");
        ptQueue = file->Queue;
        while (file->Tete != ptQueue)
        {
            printf("%d\t",file->Tete->info);
            courant = file->Tete;
            file->Tete = file->Tete->suivant;
            courant->suivant = NULL;
            file->Queue->suivant = courant;
            file->Queue = courant;
        }
        printf("%d\t",file->Tete->info);
        courant = file->Tete;
        file->Tete = file->Tete->suivant;
        courant->suivant = NULL;
        file->Queue->suivant = courant;
        file->Queue = courant;
    }
}
// e
/*
tab   : positifs pairs
liste : positifs impairs
pile  : negatifs impairs
file  : negatifs pairs
*/
int Trans_Tab_to_ListeFile_Pile(QuatresStructs *structs)
{
    int i, IdTmp = -1, rt;
    // structure innexiste
    if (!structs) return ((int)-1);
    // tableau vide
    if (!structs->tab->IdElem == -1) return ((int)0);

    for (i = 0; i <= structs->tab->IdElem; i++)
    { 
        if (structs->tab->tab[i] >= 0)
        {
            if (structs->tab->tab[i]%2==0) structs->tab->tab[++IdTmp] = structs->tab->tab[i];
            else structs->liste = Insert_Ord_Liste(structs->liste,structs->tab->tab[i]);
        }
        else
        {
            if (structs->tab->tab[i]%2==0) rt = Insert_Ord_File(structs->file,structs->tab->tab[i]);
            else structs->pile = Insert_Ord_Pile(structs->pile,structs->tab->tab[i]);
        }
    }
    structs->tab->IdElem = IdTmp;
    return ((int)1);
}

Cellule *EmpilerPPile(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    if (!pile) return ((Cellule *)CL); // tester si la pile existe
    CL->suivant = pile; // Inserer au sommet
    return ((Cellule *)CL);
}
// 3- Supprimer un element au sommet de la pile
Cellule *DepilerPPile(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); // tester si la pile existe
    Supp = pile;
    pile = pile->suivant;
    free(Supp);
    return ((Cellule *)pile);
}
void AfficherPPile(Cellule *pile)
{
    Cellule *pile2 = NULL;
    if (!pile) // tester si la pile existe
    {
        printf("\nPile inexiste ou vide!");
        exit(0);
    }
    printf("\nPile : ");
    while (pile) // tant qu'on a un element dans la pile
    {   // Afficher l'element et le depiler
        printf("%d\t",pile->info);
        pile2 = EmpilerPPile(pile2, pile->info);
        pile = DepilerPPile(pile);
    }
    while (pile2)
    {   // Récupperer la pile
        pile = EmpilerPPile(pile, pile2->info);
        pile2 = DepilerPPile(pile2);
    }
}
void main()
{
    int rt;
    /*
    Cellule *pile = NULL;
    File *file = (File *)malloc(sizeof(File));
    file->Tete = file->Queue = NULL;
    rt = Insert_Ord_File(file,12);
    rt = Insert_Ord_File(file,14);
    rt = Insert_Ord_File(file,10);
    rt = Insert_Ord_File(file,18);
    rt = Insert_Ord_File(file,16);
    AfficherPFile(file);
    pile = Insert_Ord_Pile(pile,13);
    pile = Insert_Ord_Pile(pile,12);
    pile = Insert_Ord_Pile(pile,15);
    pile = Insert_Ord_Pile(pile,19);
    pile = Insert_Ord_Pile(pile,16);
    AfficherPPile(pile);
    */
    QuatresStructs *str = (QuatresStructs *)malloc(sizeof(QuatresStructs));
    str->file = (File *)malloc(sizeof(File));
    str->file->Tete = str->file->Queue = NULL;
    str->liste = NULL;
    str->pile = NULL;
    str->tab = (TAB *)malloc(sizeof(TAB));
    str->tab->IdElem = -1;

    str->tab->tab[++str->tab->IdElem] = 5;
    str->tab->tab[++str->tab->IdElem] = 4;
    str->tab->tab[++str->tab->IdElem] = -5;
    str->tab->tab[++str->tab->IdElem] = -3;
    str->tab->tab[++str->tab->IdElem] = -6;
    str->tab->tab[++str->tab->IdElem] = 9;
    for (int i = 0; i <= str->tab->IdElem; i++)
    {
        printf("%d\t",str->tab->tab[i]);
    }
    rt = Trans_Tab_to_ListeFile_Pile(str);
    for (int i = 0; i <= str->tab->IdElem; i++)
    {
        printf("\nTab : ");
        if (str->tab->IdElem == -1) printf("\nTable vide");
        printf("%d\t",str->tab->tab[i]);
    }
    AfficherPFile(str->file);
    AfficherPPile(str->pile);
    printf("\nListe : %d\t%d",str->liste->info,str->liste->suivant->info);
}