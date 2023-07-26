#include<stdio.h>
#include<stdlib.h>
// Declaration des constantes
#define NbElem 30 // Taille maximale des tableaux
// Definition de la structure
typedef struct
{
    int info[NbElem]; // Tableau des elements
    int Sommet; // Indice du Dernier Element 
}TPile;

// 1- Initialiser la pile
int Init_TPile(TPile *pile)
{
    if (!pile) return ((int)0); // test si la zone memoire existe
    pile->Sommet = -1; // La pile est vide
    return ((int)1);
}
// 2- S'avoir si la pile est vide
int EstVide(TPile *pile)
{
    if (!pile) return ((int)-1); // test si la zone memoire existe
    return ((int)(pile->Sommet == -1));
}
// 3- S'avoir si la pile est saturee
int EstSaturee(TPile *pile)
{
    if (!pile) return ((int)-1); // test si la zone memoire existe
    return ((int)pile->Sommet == (NbElem-1));
}
// 5- Afficher la pile
void AfficherTPile(TPile *pile)
{
    int i;
    if (!pile) // test si la zone memoire existe
    {
        printf("\nPile inexiste!");
        exit(0);
    }
    if (EstVide(pile)) printf("\nLa pile est vide");
    else
    {
        printf("\nPile : ");
        for (i = pile->Sommet; i >= 0; i--)
            printf("%d\t",pile->info[i]);
    }
}
// 6- Inserer un element au sommet de la pile
int EmpilerTPile(TPile *pile, int val)
{
    if (!pile) return ((int)-1); // tester si la zone memoire existe
    if (EstSaturee(pile)) return ((int)0); // test er si la pile est saturee
    pile->info[++pile->Sommet] = val; // Inserer la valeur
    return ((int)1);
}
// 7- Supprimer un element au sommet de la pile
int DepilerTPile(TPile *pile, int *val)
{
    if (!pile) return ((int)-1); // tester si la zone memoire existe
    if (EstVide(pile)) return ((int)0); // tester si la pile est vide
    *val = pile->info[pile->Sommet--];
    return ((int)1);
}
int MinPile(TPile *pile, int *Min, int SommetTMP)
{
    int IdSommet = SommetTMP;
    if (EstVide(pile)) return ((int)0);
    if (EstSaturee(pile)) return ((int)-1);
    *Min = pile->info[pile->Sommet];
    pile->Sommet--;
    while (!EstVide(pile))
    {        
        if (pile->info[pile->Sommet] < *Min) 
        {
            pile->info[SommetTMP] = *Min;
            *Min = pile->info[pile->Sommet];
        }else 
            pile->info[SommetTMP] = pile->info[pile->Sommet];
        SommetTMP--;
        pile->Sommet--;
    }
    while (SommetTMP != IdSommet)
    {
        pile->info[++pile->Sommet] = pile->info[++SommetTMP];
    }
    return ((int)1);
}
// Trier une pile
int TrierPile(TPile *pile)
{
    int rt, min, SommetTMP = NbElem-1;
    if (!pile) return ((int)-1); // tester si la zone memoire existe
    if (EstVide(pile)) return ((int)0); // tester si la pile est vide

    while (!EstVide(pile))
    {
        rt = MinPile(pile,&min,SommetTMP);
        pile->info[SommetTMP] = min;
        SommetTMP--;
    }
    while (SommetTMP != NbElem-1)
    {
        pile->info[++pile->Sommet] = pile->info[++SommetTMP];
    }
    return ((int)1);
}

void main()
{
    TPile pile;
    int min;
    Init_TPile(&pile);
    EmpilerTPile(&pile,13);
    EmpilerTPile(&pile,10);
    EmpilerTPile(&pile,15);
    EmpilerTPile(&pile,16);
    EmpilerTPile(&pile,11);
    EmpilerTPile(&pile,18);
    AfficherTPile(&pile);
    TrierPile(&pile);
    AfficherTPile(&pile);
}