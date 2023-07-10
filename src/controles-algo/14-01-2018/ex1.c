#include<stdio.h>
#include<stdlib.h>
// A
void Histogramme(unsigned char image[256][256], unsigned int histo[256])
{
    int i, j;
    for (i = 0; i < 256; histo[i++] = 0); // initialisation
    for (i = 0; i < 256; i++) for (j = 0; j < 256; histo[(int)image[i][j++]]++);
}
int Max_Min_ng(unsigned int histo[256], int *Min)
{
    int i, Max = 0;
    *Min = 0;
    for (i = 1; i < 256; i++)
    {
        if (histo[i] < histo[*Min]) *Min = i;
        if (histo[i] > histo[Max]) Max = i;
    }
    return ((int)Max);
}
// B
void Mat_Cooccur(unsigned char image[256][256], unsigned int cooccur[256][256])
{
    int i, j;
    for (i = 0; i < 256; i++) for (j = 0; j < 256; cooccur[i][j++] = 0); // initialisation
    for (i = 0; i < 256; i++) for (j = 0; j < 255; cooccur[(int)image[i][j++]][(int)image[i][j]]++);
}
void Max_Min_Cooccur(unsigned int cooccur[256][256], int *MinL, int *MinR, int *MaxL, int *MaxR)
{
    int i, j;
    *MinL = *MinR = *MaxL = *MaxR = 0;
    for (i = 0; i < 256; i++)
    {
        for (j = 1; j < 256; j++)
        {
            if (cooccur[i][j] < cooccur[*MinL][*MinR]) 
            {
                *MinL = i;
                *MinR = j;
            }
            if (cooccur[i][j] > cooccur[*MaxL][*MaxR]) 
            {
                *MaxL = i;
                *MaxR = j;
            }
        }
    }
}
// C
typedef struct CL
{
    int info;
    struct CL *svt;
}Cellule;
Cellule *CreerCellule(int info)
{
    Cellule *NC = (Cellule *)malloc(sizeof(Cellule));
    if (!NC) exit(0);
    NC->info = info;
    NC->svt = NULL;
    return ((Cellule *)NC);
}
void Insert_Plage(Cellule *Plages[256], int niv, int longueur)
{
    Cellule *courant, *NC;
    NC = CreerCellule(longueur);
    if (!Plages[niv]) Plages[niv] = NC;
    else if (longueur <= Plages[niv]->info) 
    {
        NC->svt = Plages[niv];
        Plages[niv] = NC;
    }
    else
    {
        courant = Plages[niv];
        while (courant->svt)
        {
            if (longueur <= courant->svt->info)
            {
                NC->svt = courant->svt;
                break;
            }
            courant = courant->svt;
        }
        courant->svt = NC;
    }
}
void Mat_LdP(unsigned char image[256][256], Cellule *Plages[256])
{
    int i, j, nb = 0;
    // Initialisation
    for (i = 0; i < 256; Plages[i++] = NULL);
    for (i = 0; i < 256; i++)
    {
        for (j = 0; j < 256; j++)
        {
            nb++;
            if ((j < 255) && (image[i][j] == image[i][j+1])) continue;
            Insert_Plage(Plages,j,nb);
            nb = 0;
        }
    }
}
int Max_Min_LdP(Cellule *Plages[256], int *Min)
{
    int i = 0, Max;
    Cellule *courant, *ptr;
    while (!Plages[i] && (i < 256)) i++;
    if (!Plages[i]) return ((int)0);
    *Min = Max = i;
    ptr = Plages[i++];
    while (ptr->svt) ptr = ptr->svt;
    for ( ; i < 256; i++)
    {
        if (!Plages[i]) continue;
        if (Plages[i]->info < Plages[*Min]->info) *Min = i;
        courant = Plages[i];
        while (courant->svt) courant = courant->svt;
        if (courant->info > ptr->info) Max = i;
    }
    return ((int )Max);
}
float LongMoy_LdP(Cellule *Plages[256], int niv)
{
    int nb = 0, p = 0;
    Cellule *courant = Plages[niv];
    if (!Plages[niv]) return ((float)0);
    while (courant)
    {
        p += courant->info;
        nb++;
        courant = courant->svt;
    }
    return ((float)p/nb);
}
float Max_LongMoy_LdP(Cellule *Plages[256])
{
    int i;
    float rt, lm = 0;
    for (i = 0; i < 256; i++)
    {
        rt = LongMoy_LdP(Plages,i);
        if (lm < rt) lm = rt;
    }
    return ((float)lm);    
}
