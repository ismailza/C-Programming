#include <stdio.h>
#include <stdlib.h>

typedef struct CL
{
    int info;
    struct CL *svt;
}Cellule;

typedef struct 
{
    Cellule *Tete, *Queue;
}File;



Cellule *Defiler_File_Enpiler_Pile(File *file, Cellule *pile)
{
    Cellule *tmp;
    if (!file->Tete) return ((Cellule *)NULL);
    tmp = file->Tete;
    file->Tete = file->Tete->svt;
    if (!file->Tete) file->Queue = NULL;
    tmp->svt = pile;
    return ((Cellule *)tmp);
}

Cellule *Depiler_Pile_Enfiler_File(File *file, Cellule *pile)
{
    Cellule *tmp;
    if (!pile) return ((Cellule *)NULL);
    tmp = pile;
    pile = pile->svt;
    if (!file->Tete) file->Tete = tmp;
    else file->Queue->svt = tmp;
    file->Queue = tmp;   
    tmp->svt = NULL; 
    return ((Cellule *)pile);
}

int Tri_File_Par_Une_Pile(File *file)
{
    Cellule *pile = NULL, *tmp;
    if (!file) return ((int)-1);
    // Tant que la file est non vide 
    while (file->Tete) 
    {
        // si la pile est vide
        if (!pile) pile = Defiler_File_Enpiler_Pile(file,pile);
        if (file->Tete)
        {
            if (file->Tete->info <= pile->info) pile = Defiler_File_Enpiler_Pile(file,pile);
            else 
            {
                while (pile)
                {
                    if (pile->info < file->Tete->info) pile = Depiler_Pile_Enfiler_File(file,pile);                        
                    else break;
                }
            }
        }
    }
    while (pile) pile = Depiler_Pile_Enfiler_File(file,pile);  
    return ((int)1);
}
