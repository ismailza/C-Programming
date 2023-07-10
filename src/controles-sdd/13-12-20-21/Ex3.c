#include<stdio.h>
#include<stdlib.h>

// A- 
typedef struct CEL
{
    int info;
    struct CEL *suivant;
}Cellule;

Cellule *CreerCellule(int val)
{
    Cellule *CL;
    CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL) 
    {   
        printf("\nErreur d'allocation de la memoire!");
        exit(0); 
    }
    CL->info = val; 
    CL->suivant = NULL; 
    return ((Cellule *)CL); 
}
Cellule *Empiler(Cellule *pile, int val)
{
    Cellule *CL;
    CL = CreerCellule(val);
    if (!pile) return ((Cellule *)CL);
    CL->suivant = pile;
    return ((Cellule *)CL);
}

Cellule *Depiler(Cellule *pile)
{
    Cellule *Supp;
    if (!pile) return ((Cellule *)NULL);
    Supp = pile;
    pile = pile->suivant;
    free(Supp);
    return ((Cellule *)pile);
}

Cellule *Supprimer_Repetitions(Cellule *pile)
{
    Cellule *tmpSR = NULL, *tmpAR = NULL;
    while (pile)
    {
        tmpSR = Empiler(tmpSR,pile->info);
        pile = Depiler(pile);
        while (pile)
        {
            if (pile->info != tmpSR->info) tmpAR = Empiler(tmpAR,pile->info);
            pile = Depiler(pile);
        }
        while (tmpAR)
        {
            pile = Empiler(pile,tmpAR->info);
            tmpAR = Depiler(tmpAR);
        }
    }
    while (tmpSR)
    {
        pile = Empiler(pile,tmpSR->info);
        tmpSR = Depiler(tmpSR);
    }
    return ((Cellule *)pile);
}

// B
#define MaxElem 25

typedef struct 
{
    int info[MaxElem];
    int Sommet;
}Pile;

int Init_Pile(Pile *pile)
{
    if (!pile) return ((int)0);
    pile->Sommet = -1;
    return ((int)1);
}
int Est_Saturee(Pile *pile)
{
    if (!pile) return ((int)-1);
    return ((int)(pile->Sommet == MaxElem-1 ? 1:0));
}
int Insert_Pile_Pos(Pile *pile, int val, int pos)
{
    int tmpId = MaxElem;
    if (!pile) return ((int)-1);
    if (Est_Saturee(pile)) return ((int)0);
    if (pos < 0 || pos > pile->Sommet+1) return ((int)-2);
    while (pos <= pile->Sommet)
    {
        tmpId--;
        pile->info[tmpId] = pile->info[pile->Sommet];
        pile->Sommet--;
    }
    pile->info[++pile->Sommet] = val;
    while (tmpId != MaxElem)
    {
        pile->info[++pile->Sommet] = pile->info[tmpId];
        tmpId++;
    }
    return ((int)1);
}
void Afficher_Pile(Pile *pile)
{
    int rt;
    Pile *tmp;
    if (!pile) printf("\nPile n'existe pas!");
    else
    {
        if (pile->Sommet == -1) printf("\nPile vide");
        else
        {
            tmp = (Pile *)malloc(sizeof(Pile));
            rt = Init_Pile(tmp);
            printf("\nPile :\t");
            while (pile->Sommet != -1)
            {
                printf("%d\t",pile->info[pile->Sommet]);
                tmp->info[++tmp->Sommet] = pile->info[pile->Sommet];
                pile->Sommet--;
            }
            while (tmp->Sommet != -1)
            {
                pile->info[++pile->Sommet] = tmp->info[tmp->Sommet];
                tmp->Sommet--;
            }
            free(tmp);            
        }
    }
}

// C-
typedef struct FL
{
    Cellule *Tete, *Queue;
}File;

int Enfiler(File *file, int val)
{
    if (!file) return ((int)0);
    if (!file->Tete) 
    {
        file->Queue = Empiler(file->Queue,val);
        file->Tete = file->Queue;
    }
    else 
    {
        file->Queue->suivant = Empiler(file->Queue->suivant,val);
        file->Queue = file->Queue->suivant;
    }
    return ((int)1);
}
int Defiler(File *file)
{
    if (!file) return ((int)0);
    file->Tete = Depiler(file->Tete);
    if (!file->Tete) file->Queue = NULL;
    return ((int)1);
}
void Afficher_File(File *file)
{
    int rt;
    Cellule *ptr;
    if (!file) printf("\nFile n'existe pas");
    else
    {
        if (!file->Tete) printf("\nFile vide");
        else
        {
            ptr = file->Queue;
            printf("\nFile :\t");
            while (file->Tete != ptr)
            {
                printf("%d\t",file->Tete->info);
                rt = Enfiler(file,file->Tete->info);
                rt = Defiler(file);
            }
            printf("%d\t",file->Tete->info);
            rt = Enfiler(file,file->Tete->info);
            rt = Defiler(file);            
        }
    }
}


void main()
{
    File *file = (File *)malloc(sizeof(File));
    file->Tete = file->Queue = NULL;

    Enfiler(file,13);
    Enfiler(file,14);
    printf("%d\t%d\t",file->Tete->info,file->Queue->info);
    Afficher_File(file);

}