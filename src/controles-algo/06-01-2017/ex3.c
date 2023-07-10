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
    int NbElem;
}FourFile;

void Init_FourFile(FourFile *file)
{
    file = (FourFile *)malloc(sizeof(FourFile));
    if (!file) exit(0);
    file->NbElem = 0;
    file->Tete = file->Queue = NULL;
}

Cellule *CreerCellule(int val)
{
    Cellule *CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL) exit(0);
    CL->info = val;
    CL->svt = NULL;
    return ((Cellule *)CL);
}
int EnfilerFile(FourFile *file, int val)
{
    Cellule *CL;
    if (!file) return ((int)-1); // tester si la file existe
    CL = CreerCellule(val); // creer l'element
    if (!file->Tete) file->Tete = CL;
    else file->Queue->svt = CL;
    file->Queue = CL;  
    file->NbElem++;  
    return ((int)1);
}
int DefilerFile(FourFile *file)
{
    Cellule *Supp;
    if (!file) return ((int)-1); // tester si la file existe
    if (!file->Tete) return ((int)0); // tester si la file est vide
    Supp = file->Tete; // pointer sur la tete de la file
    file->Tete = file->Tete->svt; // affecter au tete l'element suivant
    if (!file->Tete) file->Queue = NULL;
    file->NbElem--;
    free(Supp); // liberer la memoire
    return ((int)1);
}

int Enfiler_File_Ordonnee(FourFile *file, int val)
{
    int i, rt;
    if (!file) return ((int)0);
    if (!file->Tete) rt = EnfilerFile(file,val);
    else if (val >= file->Queue->info) rt = EnfilerFile(file,val);
    else
    {
        for (i = 0; i < file->NbElem; i++)
        {
            if (val <= file->Tete->info) break;
            rt = EnfilerFile(file,file->Tete->info);
            rt = DefilerFile(file);
        }
        rt = EnfilerFile(file,val);
        for (; i < file->NbElem-1; i++)
        {
            rt = EnfilerFile(file,file->Tete->info);
            rt = DefilerFile(file);
        }
    }
    return ((int)file->NbElem);   
}

typedef struct Fl
{
    FourFile Ffile;
    struct Fl *svt;
}FCellule;

typedef struct 
{
    FCellule *TFf, *QFf;
}File;

