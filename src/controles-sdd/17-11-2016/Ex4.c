#include<stdio.h>
#include<stdlib.h>
#define NbElem 25
// a- Definition de la structure
typedef struct 
{
    int info[NbElem];
    int debut;
    int fin;
}TFile;
// b-
int Init_TFile(TFile file)
{
    file->debut = file->fin = -1;
    return ((int)1);
}
// c- 
int TFile_Est_Saturee(TFile file)
{
    if ((file.debut == 0) && (file.fin == NbElem-1)) return ((int)1);
    return ((int)0);
}
// d- 
int Tasser_TFile(TFile file)
{
    int i, t;
    if (TFile_Est_Saturee(file)) return ((int)-1);
    if (file.fin == NbElem-1) 
    {
        t = file.fin - file.debut +1;
        for (i = 0; i < t; i++) file.info[i] = file.info[file.debut+i];
        file.debut = 0;
        file.fin = file.fin - t +1;
        return ((int)1);
    }
    return ((int)0);
}
// e- 
int Inserer_TFile(TFile file, int val)
{
    int rt;
    if (TFile_Est_Saturee(file)) return ((int)0);
    if (file.fin == NbElem-1) rt = Tasser_TFile(file);
    file.info[++file.fin] = val;
    return ((int)1);
}
// f- 
int Defiler_TFile(TFile file)
{
    if (file.fin == -1) return ((int)0);
    file.debut++;
    return ((int)1);
}