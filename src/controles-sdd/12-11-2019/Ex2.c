#include<stdio.h>
#include<stdlib.h>

#define NbElem 30

// a- Definition de la structure de tableau
typedef struct 
{
    int Tab[NbElem];    // Tableau d'entiers 
    int IdElem;         // Indice du dernier element du tableau
}Tableau;

// Definition de la structure de la liste
typedef struct Liste
{
    int info; 
    struct Liste *suivant; // Pointeur vers l'element suivant
}Cellule;

// b- Inserer un element a la fin du tableau
int Insert_End(Tableau *Table, int val)
{
    // tester l'existance du tableau
    if (!Table) return ((int)-1);
    // Tester si le tableau est sature
    if (Table->IdElem == NbElem-1) return ((int)0);
    // Incrementer l'indice du dernier element puis ajouter l'element
    Table->Tab[++Table->IdElem] = val;
    return ((int)1);
}

int Delete_Pos(Tableau *Table, int Pos)
{
    int i;
    // tester l'existance du tableau
    if (!Table) return ((int)-1);
    // Tester la position entree
    if ((Pos < 0 )|| (Pos > Table->IdElem+1)) return ((int)0);
    // Suppression
    for (i = Pos; i < Table->IdElem; i++) Table->Tab[i] = Table->Tab[i+1];
    Table->IdElem--;
    return ((int)1);
}

// c- Inserer un element a une position
int Insert_Pos(Tableau *Table, int val, int Pos)
{
    int i;
    // tester l'existance du tableau
    if (!Table) return ((int)-1);
    // Tester si le tableau est sature
    if (Table->IdElem == NbElem-1) return ((int)0);
    // Tester la position entree
    if ((Pos < 0 )|| (Pos > Table->IdElem+1)) return ((int)-2);
    // Tasser les elements apres la position
    for (i = Table->IdElem; i >= Pos; i--) Table->Tab[i+1] = Table->Tab[i];
    // Insertion dans la position
    Table->Tab[Pos] = val;
    Table->IdElem++;
    return ((int)1);
}

// d- Remplacer un element du tableau
int Rempl_Pos(Tableau *Table, int val, int Pos)
{
    // tester l'existance du tableau
    if (!Table) return ((int)-1);
    // Tester la position entree
    if ((Pos < 0 )|| (Pos > Table->IdElem+1)) return ((int)0);
    // Remplacer dans la position
    Table->Tab[Pos] = val;
    return ((int)1);
}

// e- Transferer le contenu de la position i du premier tableau dans le deuxieme tableau a la position j et inversement.
int Trans_Pos_ij(Tableau *Table1, Tableau *Table2, int i, int j)
{
    int tmp;
    // tester l'existance des tableaux
    if (!Table1 || !Table2) return ((int)-1);
    // Tester les positions entrees
    if (((i < 0 )|| (i > Table1->IdElem)) || 
        ((j < 0 )|| (j > Table2->IdElem))) return ((int)0);
    // Transformation
    tmp = Table1->Tab[i];
    Rempl_Pos(Table1,Table2->Tab[j],i);
    Rempl_Pos(Table2,tmp,j);
    return ((int)1);
}

// f- transfere les nombre positifs dans le premier tableau et les nombre negatifs dans le deuxieme
int Separer_Pos_Neg(Tableau *Table1, Tableau *Table2)
{
    int i, j, rt;
    // tester l'existance des tableaux
    if (!Table1 || !Table2) return ((int)-1);
    for (i = 0; i <= Table1->IdElem; i++)
    {
        if (Table1->Tab[i] < 0)
        {
            for (j = 0; j <= Table2->IdElem; j++)
            {
                if (Table2->Tab[j] >= 0) 
                {
                    rt = Trans_Pos_ij(Table1,Table2,i,j);
                    break;
                }
            }
            if ((Table2->IdElem == -1) || (j == Table2->IdElem+1))
            {
                rt = Insert_End(Table2,Table1->Tab[i]);
                if (!rt) return ((int)0); // Si la table 2 est saturee
                rt = Delete_Pos(Table1,i);
                i--;
            }
        }
    }
    for (i = 0; i <= Table2->IdElem; i++)
    {
        if (Table2->Tab[i] >= 0)
        {
            rt = Insert_End(Table1,Table2->Tab[i]);
            if (!rt) return ((int)0); // Si la table 1 est saturee
            Delete_Pos(Table2,i);
            i--;
        }
    }
    return ((int)1);
}

void AfficherTab(Tableau *tab)
{
    if (!tab) 
    {
        printf("\nTable inexiste!");
        exit(0);
    }
    if (tab->IdElem == -1) printf("\nTable vide");
    else
    {
        printf("\nTab : ");
        for (int i = 0; i <= tab->IdElem; i++) printf("%d\t",tab->Tab[i]);
    }
}

void main()
{
    Tableau tab1, tab2;
    int rt;
    tab1.IdElem = -1;
    tab2.IdElem = -1;
    rt = Insert_End(&tab2,12);
    rt = Insert_End(&tab2,-3);
    rt = Insert_End(&tab2,2);
    rt = Insert_End(&tab2,4);
    rt = Insert_End(&tab2,-8);
    rt = Separer_Pos_Neg(&tab1,&tab2);
    printf("\n%d",rt);
    AfficherTab(&tab1);
    AfficherTab(&tab2);
}