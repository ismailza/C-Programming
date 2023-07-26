#include<stdio.h>
#include<stdlib.h>
#define NBElem 30
/* Un tableau de NBElem admettant des entiers appartient à [0,20]
   non ordonne.
   Nous souhaitons transferer les elements du tableau dans differents 
   structures afin de pouvoir les afficher par ordre croissant.
*/
typedef struct 
{
    int tab[NBElem];
    int IdElem;
}TAB;
typedef struct CL
{
    int info, nb_occ;
    struct CL *svt;
}Cellule;
typedef struct ND
{
    int info, nb_occ;
    struct ND *fgc, *fdt;
}Noeud;

Cellule *CreerCellule(int val)
{
    Cellule *NC = (Cellule *)malloc(sizeof(Cellule));
    if (!NC) exit(0);
    NC->info = val;
    NC->nb_occ = 1;
    NC->svt = NULL;
    return ((Cellule *)NC);
}

// En utilisant un tableau:
void Transf_TAB_Tableau(TAB MaTab, int tableau[21])
{
    int i;
    for (i = 0; i < 21; tableau[i++] = 0); // Initialisation
    for (i = 0; i <= MaTab.IdElem; tableau[MaTab.tab[i++]]++);
}
void Afficher_TAB_Tableau(int tableau[21])
{
    int i, j;
    printf("\nTable :\t");
    for (i = 0; i < 21; i++)
        for (j = 0; j < tableau[i]; j++) printf("%d\t",i);
}

// En utilisant une liste:
Cellule *Transf_TAB_Liste(TAB MaTab)
{
    Cellule *liste = NULL, *NC, *courant;
    int i;
    for (i = 0; i <= MaTab.IdElem; i++)
    {
        if (!liste) liste = CreerCellule(MaTab.tab[i]);
        else
        {
            if (MaTab.tab[i] < liste->info) 
            {
                NC = CreerCellule(MaTab.tab[i]);
                NC->svt = liste;
                liste = NC;
            }
            else
            {
                if (MaTab.tab[i] == liste->info) liste->nb_occ++;
                else
                {
                    courant = liste;
                    while (courant->svt)
                    {
                        if (MaTab.tab[i] == courant->svt->info) 
                        {
                            courant->svt->nb_occ++;
                            break;
                        }
                        else
                        {
                            if (MaTab.tab[i] < courant->svt->info)
                            {
                                NC = CreerCellule(MaTab.tab[i]);
                                NC->svt = courant->svt;
                                courant->svt = NC;
                                break;
                            }
                        }
                        courant = courant->svt;
                    }
                    if (!courant->svt) courant->svt = CreerCellule(MaTab.tab[i]);
                }
            }
        }
    }
    return ((Cellule *)liste);
}
void AfficherListe(Cellule *liste)
{
    Cellule *courant;
    // si la liste est vide
    if (!liste) printf("\nLa liste est vide");
    else
    {
        courant = liste; // initialiser courant par la tete de la liste
        printf("\nListe :\t");
        while (courant)
        {   // tant qu'on a un element dans la liste
            for (int i = 0; i < courant->nb_occ; i++) printf("%d\t",courant->info);
            courant = courant->svt; // passer au suivant
        }
    }
}

// En utilisant une pile
Cellule *Transf_TAB_Pile(TAB MaTab)
{
    Cellule *pile = NULL, *tmp = NULL, *NC, *ptr;
    for (int i = 0; i <= MaTab.IdElem; i++)
    {
        while (pile)
        {
            if (MaTab.tab[i] > pile->info)
            {    
                ptr = pile;
                pile = pile->svt;
                ptr->svt = tmp;
                tmp = ptr;
            }
            else
            {
                if (MaTab.tab[i] == pile->info) pile->nb_occ++;
                break;
            }
        }
        if (pile)
        {
            if (MaTab.tab[i] < pile->info)
            {
                NC = CreerCellule(MaTab.tab[i]);
                NC->svt = pile;
                pile = NC;
            }
        }
        else pile = CreerCellule(MaTab.tab[i]);
        while (tmp)
        {
            ptr = tmp;
            tmp = tmp->svt;
            ptr->svt = pile;
            pile = ptr;
        }
    }
    return ((Cellule *)pile);
}
void AfficherPile(Cellule *pile)
{
    Cellule *tmp = NULL, *ptr;
    // si la liste est vide
    if (!pile) printf("\nLa pile est vide");
    else
    {
        printf("\nPile :\t");
        while (pile)
        {
            for (int i = 0; i < pile->nb_occ; i++) printf("%d\t",pile->info);
            ptr = pile;
            pile = pile->svt;
            ptr->svt = tmp;
            tmp = ptr;
        }
        while (tmp)
        {
            ptr = tmp;
            tmp = tmp->svt;
            ptr->svt = pile;
            pile = ptr;
        }
    }
}

// En utilisant un arbre


void main()
{
    TAB MaTab;
    int tableau[21];
    Cellule *liste, *pile;

    MaTab.IdElem = -1;
    MaTab.tab[++MaTab.IdElem] = 5;
    MaTab.tab[++MaTab.IdElem] = 9;
    MaTab.tab[++MaTab.IdElem] = 2;
    MaTab.tab[++MaTab.IdElem] = 5;
    MaTab.tab[++MaTab.IdElem] = 19;
    MaTab.tab[++MaTab.IdElem] = 1;
    MaTab.tab[++MaTab.IdElem] = 8;
    MaTab.tab[++MaTab.IdElem] = 1;
    MaTab.tab[++MaTab.IdElem] = 10;
    MaTab.tab[++MaTab.IdElem] = 6;

    // En utilisant un tableau
    printf("\nEn utilisant un tableau:");
    Transf_TAB_Tableau(MaTab,tableau);
    Afficher_TAB_Tableau(tableau);
    // En utilisant une liste
    printf("\nEn utilisant une liste:");
    liste = Transf_TAB_Liste(MaTab);
    AfficherListe(liste);
    // En utilisant une pile
    printf("\nEn utilisant une pile:");
    pile = Transf_TAB_Pile(MaTab);
    AfficherPile(pile);
}