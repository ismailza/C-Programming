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
}File;

typedef struct ND
{           
    File file;
    struct ND *fgc, *fdt;
}Noeud;

Cellule *CreerCellule(int val)
{
    Cellule *CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL) exit(0);
    CL->info = val;
    CL->svt = NULL;
    return ((Cellule *)CL);
}
int EnfilerFile(File *file, int val)
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
int DefilerFile(File *file)
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
int Enfiler_File_Ordonnee(File *file, int val)
{
    int rt, i;
    if (!file) return ((int)-1);
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
        for ( ; i < file->NbElem-1; i++)
        {
            rt = EnfilerFile(file,file->Tete->info);
            rt = DefilerFile(file);
        }
    }
    return ((int)1);   
}

Noeud *CreerNoeud(int val)
{
    Noeud *ND = (Noeud *)malloc(sizeof(Noeud));
    if (!ND) exit(0);
    ND->file.Tete = ND->file.Queue = CreerCellule(val);
    ND->file.NbElem = 1;
    ND->fdt = ND->fgc = NULL;
    return ((Noeud *)ND);
}

Noeud *Insert_ArbBin_File5(Noeud *Arb, int val)
{
    int rt, rec;
    if (!Arb) return ((Noeud *)CreerNoeud(val));
    if (Arb->file.NbElem < 5) rt = Enfiler_File_Ordonnee(&Arb->file,val);
    else 
    {
        if (val <= Arb->file.Tete->info) Arb->fgc = Insert_ArbBin_File5(Arb->fgc,val);
        else if (Arb->file.Queue->info <= val) Arb->fdt = Insert_ArbBin_File5(Arb->fdt,val);
        else
        {
            rt = Enfiler_File_Ordonnee(&Arb->file,val);
            val = Arb->file.Tete->info;
            rt = DefilerFile(&Arb->file);
            Arb->fgc = Insert_ArbBin_File5(Arb->fgc,val);
        }
    }
    return ((Noeud *)Arb);
}

void Affichage_File(File *file)
{
    int i;
    if (!file) // tester si la file existe
    {
        printf("\nFile inexiste!");
        exit(0);
    }
    if(!file->Tete) printf("\nLa file est vide");
    else {
        for (i = 0; i < file->NbElem; i++)
        {
            printf("%d\t",file->Tete->info);
            EnfilerFile(file,file->Tete->info);
            DefilerFile(file);
        }
    }
}
void Affichage(Noeud *Arb)
{
    if (Arb)
    {
        Affichage(Arb->fgc);
        Affichage_File(&Arb->file);
        Affichage(Arb->fdt);
    }
}

void main()
{
    Noeud *Arb = NULL;

    Arb = Insert_ArbBin_File5(Arb,4);
    Arb = Insert_ArbBin_File5(Arb,8);
    Arb = Insert_ArbBin_File5(Arb,7);
    Arb = Insert_ArbBin_File5(Arb,3);
    Arb = Insert_ArbBin_File5(Arb,12);
    Arb = Insert_ArbBin_File5(Arb,-5);
    Arb = Insert_ArbBin_File5(Arb,18);
    Arb = Insert_ArbBin_File5(Arb,-1);
    Arb = Insert_ArbBin_File5(Arb,20);
    Arb = Insert_ArbBin_File5(Arb,5);
    Arb = Insert_ArbBin_File5(Arb,6);
    Arb = Insert_ArbBin_File5(Arb,2);
    
    Affichage(Arb);

}