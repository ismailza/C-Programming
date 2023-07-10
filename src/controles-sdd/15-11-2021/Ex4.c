#include<stdio.h>
#include<stdlib.h>

#define MaxElem 100

typedef struct TB
{
    int Tab[MaxElem];
    int NbElem;
}TAB;

typedef struct cel
{
    int entier;
    struct cel *svt;
}Cellule;

typedef struct FL
{
    Cellule *Tete, *Queue;
}File;

Cellule *CreerCellule(int val)
{
    Cellule *CL;
    CL = (Cellule *)malloc(sizeof(Cellule)); // Allocation de la memoire
    if (!CL) 
    {   // Erreur d'allocation de la memoire
        printf("\nErreur d'allocation de la memoire!");
        exit(0); // Quitter le programme
    }
    CL->entier = val; // Affecter la valeur
    CL->svt = NULL; // Initialiser le pointeur suivant par NULL
    return ((Cellule *)CL); // retourne CL
}
Cellule *EmpilerPPile(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    if (!pile) return ((Cellule *)CL); // tester si la pile existe
    CL->svt = pile; // Inserer au sommet
    return ((Cellule *)CL);
}
Cellule *DepilerPPile(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); // tester si la pile existe
    Supp = pile;
    pile = pile->svt;
    free(Supp);
    return ((Cellule *)pile);
}
int EmfilerPFile(File *file, int val)
{
    Cellule *CL;
    if (!file) return ((int)-1); // tester si la file existe
    CL = CreerCellule(val); // creer l'element
    if (!file->Tete) // tester si la file est vide
        file->Tete = CL;
    else 
        file->Queue->svt = CL;
    file->Queue = CL;    
    return ((int)1);
}
// 5- Supprimer un element en tete de la file
int DefilerPFile(File *file)
{
    Cellule *Supp;
    if (!file) return ((int)-1); // tester si la file existe
    if (!file->Tete) return ((int)0); // tester si la file est vide
    Supp = file->Tete; // pointer sur la tete de la file
    file->Tete = file->Tete->svt; // affecter au tete l'element suivant
    free(Supp); // liberer la memoire
    return ((int)1);
}
int TaillePFile(File *file)
{
    int taille = 0;
    Cellule *DCL; // pour memoriser la derniere cellule
    if (!file) return ((int)-1); // tester si la file existe
    if (!file->Tete) return ((int)0); // si la file est vide
    DCL = file->Queue;
    while (file->Tete != DCL)
    {
        taille++;
        EmfilerPFile(file,file->Tete->entier);
        DefilerPFile(file);
    }
    EmfilerPFile(file,file->Tete->entier);
    DefilerPFile(file);
    return ((int)++taille);
}

/*
tab : positifs pairs
liste : positifs impairs
pile : negatifs impairs
file : negatifs pairs
*/
void Afficher(TAB *tab, Cellule *liste, Cellule *pile, File *file)
{
    int rt, i=0;
    Cellule *tmp = NULL, *courant;
    File *tmpf = (File *)malloc(sizeof(File));
    tmpf->Tete = tmpf->Queue = NULL;
    while (pile && file->Tete)
    {
        if (pile->entier < file->Tete->entier)
        {
            printf("%d\t",pile->entier);
            tmp = EmpilerPPile(tmp,pile->entier);
            pile = DepilerPPile(pile);
        }
        else
        {
            printf("%d\t",file->Tete->entier);
            rt = EmfilerPFile(tmpf,file->Tete->entier);
            rt = DefilerPFile(file);
        }
    }
    while (pile)
    {
        printf("%d\t",pile->entier);
        tmp = EmpilerPPile(tmp,pile->entier);
        pile = DepilerPPile(pile);
    }
    while (file->Tete)
    {
        printf("%d\t",file->Tete->entier);
        rt = EmfilerPFile(tmpf,file->Tete->entier);
        rt = DefilerPFile(file);
    }
    while (tmp)
    {
        pile = EmpilerPPile(pile,tmp->entier);
        tmp = DepilerPPile(pile);
    }
    file = tmpf; 
    courant = liste;   
    while ((courant) && (i!= tab->NbElem-1))
    {
        if (courant->entier < tab->Tab[i])
        {
            printf("%d\t",courant->entier);
            courant = courant->svt;
        }
        else printf("%d\t",tab->Tab[i++]);
    }
    while (courant)
    {
        printf("%d\t",courant->entier);
        courant = courant->svt;
    }
    while (i!= tab->NbElem-1) printf("%d\t",tab->Tab[i++]);    
}

Cellule *InsererPListeFin(Cellule *liste, int val)
{
    Cellule *CL, *courant;
    CL = CreerCellule(val); // Creer l'element
    if (!liste) return ((Cellule *)CL); // tester si la liste existe
    courant = liste; // Initialiser courant a la tete de la liste
    while (courant->svt) // tant que courant a un suivant
        courant = courant->svt; // passer a l'element suivant
    courant->svt = CL; // Inserer l'element
    return ((Cellule *)liste); 
}
void main()
{
    TAB tab;
    tab.NbElem = 0;
    Cellule *liste = NULL, *pile = NULL;
    File *file = (File *)malloc(sizeof(File));
    file->Tete = file->Queue = NULL;
    tab.Tab[tab.NbElem++] = 2;
    tab.Tab[tab.NbElem++] = 6;
    tab.Tab[tab.NbElem++] = 8;
    tab.Tab[tab.NbElem++] = 12;
    liste = InsererPListeFin(liste,1);
    liste = InsererPListeFin(liste,3);
    liste = InsererPListeFin(liste,7);
    liste = InsererPListeFin(liste,17);
    liste = InsererPListeFin(liste,21);
    pile = EmpilerPPile(pile,-1);
    pile = EmpilerPPile(pile,-5);
    pile = EmpilerPPile(pile,-9);
    pile = EmpilerPPile(pile,-13);
    EmfilerPFile(file,-12);
    EmfilerPFile(file,-10);
    EmfilerPFile(file,-8);
    EmfilerPFile(file,-6);
    EmfilerPFile(file,-2);
    Afficher(&tab,liste,pile,file);
}