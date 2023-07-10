#include<stdio.h>
#include<stdlib.h>
#define NbElem 20
typedef struct 
{
    int Tab[NbElem];
    int IdElem;
}TAB;
typedef struct cel
{
    int val;
    struct cel *suivant;
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
    CL->val = val; // Affecter la valeur
    CL->suivant = NULL; // Initialiser le pointeur suivant par NULL
    return ((Cellule *)CL); // retourne CL
}
int InsererTabOrdonnee(TAB *tab, int val)
{
    int i;
    if (!tab) return ((int)-1);
    if (tab->IdElem == NbElem-1) return ((int)0);
    i = tab->IdElem;
    tab->IdElem++;
    while ((i >= 0) && (tab->Tab[i] > val)) 
    {
        tab->Tab[i+1] = tab->Tab[i];
        i--;
    }
    tab->Tab[i+1] = val; 
    return ((int)1);
}
Cellule *InsererListeOrdonnee(Cellule *liste, int val)
{
    Cellule *CL, *courant;
    CL = CreerCellule(val);
    // tester si la liste existe
    if (!liste) return ((Cellule *)CL); 
    // insertion en tete
    if (val < liste->val)
    {
        CL->suivant = liste;
        return ((Cellule *)CL);
    }
    courant = liste; // pointer courant en tete
    while (courant->suivant) // tant que courant a un suivant
    {
        if (val < courant->suivant->val )
        {   // Insertion en milieu
            CL->suivant = courant->suivant;
            courant->suivant = CL;
            return ((Cellule *)liste);
        }
        courant = courant->suivant;
    }
    // Insertion en queue
    courant->suivant = CL;
    return ((Cellule *)liste);
}
Cellule *EmpilerPPile(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    if (!pile) return ((Cellule *)CL); // tester si la pile existe
    CL->suivant = pile; // Inserer au sommet
    return ((Cellule *)CL);
}
Cellule *DepilerPPile(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL); // tester si la pile existe
    Supp = pile;
    pile = pile->suivant;
    free(Supp);
    return ((Cellule *)pile);
}
Cellule *EmpilerPileOrdonnee(Cellule *pile, int val)
{
    Cellule *CL, *tmp = NULL;
    while (pile)
    {
        if (val <= pile->val) break;
        tmp = EmpilerPPile(tmp,pile->val);
        pile = DepilerPPile(pile);
    }
    pile = EmpilerPPile(pile,val);
    while (tmp)
    {
        pile = EmpilerPPile(pile,tmp->val);
        tmp = DepilerPPile(tmp);
    }
    return ((Cellule *)pile);
}
int EstVide(File *file)
{
    if (!file) return ((int)-1); // tester si la file existe
    return ((int)(!file->Tete && !file->Queue));
}
int EmfilerPFile(File *file, int val)
{
    Cellule *CL;
    if (!file) return ((int)-1); // tester si la file existe
    CL = CreerCellule(val); // creer l'element
    // tester si la file est vide
    if (EstVide(file)) file->Tete = CL;
    else file->Queue->suivant = CL;
    file->Queue = CL;    
    return ((int)1);
}
int DefilerPFile(File *file)
{
    Cellule *Supp;
    if (!file) return ((int)-1); // tester si la file existe
    if (EstVide(file)) return ((int)0); // tester si la file est vide
    Supp = file->Tete; // pointer sur la tete de la file
    file->Tete = file->Tete->suivant; // affecter au tete l'element suivant
    free(Supp); // liberer la memoire
    return ((int)1);
}
int TaillePFile(File *file)
{
    int taille = 0;
    Cellule *DCL; // pour memoriser la derniere cellule
    if (!file) return ((int)-1); // tester si la file existe
    if (EstVide(file)) return ((int)0); // si la file est vide
    DCL = file->Queue;
    while (file->Tete != DCL)
    {
        taille++;
        EmfilerPFile(file,file->Tete->val);
        DefilerPFile(file);
    }
    EmfilerPFile(file,file->Tete->val); 
    DefilerPFile(file);
    return ((int)++taille);
}
int EmfilerFileOrdonnee(File *file, int val)
{
    int i, rt, v = 0, taille = TaillePFile(file);
    if (!file) return ((int)-1);
    if (!file->Tete) rt = EmfilerPFile(file,val);
    else
    {
        for (i = 0; i < taille; i++)
        {
            if ((val < file->Tete->val) && (v==0)) 
            {
                rt = EmfilerPFile(file,val);
                v = 1;
            }
            rt = EmfilerPFile(file,file->Tete->val);
            rt = DefilerPFile(file);
        }
        if (v==0) rt = EmfilerPFile(file,val);
    }
    return ((int)1);   
}
/*
Tableau : nombres positifs pairs
Liste : nombres positifs impairs
Pile : nombres negatifs pairs
File : nombres negatifs impairs
*/
int Separer(TAB *tab,Cellule *Aliste[1],Cellule *Apile[1],File *file,int nb)
{
    Cellule *liste = NULL, *pile = NULL;
    int i, val, rt;
    for (i= 0; i< nb; i++)
    {
        printf("\nTaper la valeur : ");
        scanf("%d",&val);
        if (val >= 0) 
        {
            if (val%2==0) rt = InsererTabOrdonnee(tab,val);
            else liste = InsererListeOrdonnee(liste,val);
        }
        else
        {
            if (val%2==0) pile = EmpilerPileOrdonnee(pile,val);
            else rt = EmfilerFileOrdonnee(file,val);
        }
    }
    Aliste[0] = liste;
    Apile[0] = pile;
    return ((int)1);
}

void AfficherListe(TAB *liste)
{
    int i;
    if (!liste)
    {
        printf("\nTableau inexiste!");
        exit(0); // Quitter le programme
    }
    if (liste->IdElem == -1) printf("\nLe Tableau est vide"); // liste vide
    else
    {
        printf("\nTab : ");
        for (i = 0; i <= liste->IdElem; i++) // parcourir la liste
            printf("%d\t",liste->Tab[i]); // afficher element par element
    }  
}
void AfficherPListe(Cellule *liste)
{
    Cellule *courant;
    // si la liste est vide
    if (!liste) printf("\nLa liste est vide");
    else
    {
        courant = liste; // initialiser courant par la tete de la liste
        printf("\nListe : ");
        while (courant)
        {   // tant qu'on a un element dans la liste
            printf("%d\t",courant->val); // afficher l'element
            courant = courant->suivant; // passer au suivant
        }
    }
}
void AfficherPPile(Cellule *pile)
{
    Cellule *pile2 = NULL;
    if (!pile) printf("\nPile vide!");
    else
    {
        printf("\nPile : ");
        while (pile) // tant qu'on a un element dans la pile
        {   // Afficher l'element et le depiler
            printf("%d\t",pile->val);
            pile2 = EmpilerPPile(pile2, pile->val);
            pile = DepilerPPile(pile);
        }
        while (pile2)
        {   // Récupperer la pile
            pile = EmpilerPPile(pile, pile2->val);
            pile2 = DepilerPPile(pile2);
        }
    }
}
void AfficherPFile(File *file)
{
    int i, taille = TaillePFile(file);
    if (!file) // tester si la file existe
    {
        printf("\nFile inexiste!");
        exit(0);
    }
    if(EstVide(file)) printf("\nLa file est vide");
    else {
        printf("\nFile : ");
        for (i = 0; i < taille; i++)
        {
            printf("%d\t",file->Tete->val);
            EmfilerPFile(file,file->Tete->val);
            DefilerPFile(file);
        }
    }
}
void main()
{
    TAB tab;
    tab.IdElem = -1;
    Cellule *liste[1], *pile[1];
    File *file = (File *)malloc(sizeof(File));
    file->Tete = file->Queue = NULL;

    Separer(&tab,liste,pile,file,6);    
    AfficherListe(&tab);
    AfficherPListe(liste[0]);
    AfficherPPile(pile[0]);
    AfficherPFile(file);
}