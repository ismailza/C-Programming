#include<stdio.h>
#include<stdlib.h>
// b- 
typedef struct Tmp
{
    float Tj, Tn, Pl;
}TEMP;

int Nb_Jour_Mois(int M)
{
    int jours[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    if (M < 1 || M > 12) return ((int)0);
    return ((int)jours[M-1]);
}
int Jour_Valide(int J, int M)
{
    int rt = Nb_Jour_Mois(M);
    if (!rt) return ((int)-1);
    if (J < 1 || J > rt) return ((int)0);
    return ((int)1);
}
// c- 
int Temperature_Jour_Donne(TEMP *T[12][31], int J, int M, int jn, float *t)
{
    int rt;
    rt = Jour_Valide(J,M);
    if (!rt) return ((int)0);
    if (jn) *t = T[M-1][J-1]->Tj;
    else *t = T[M-1][J-1]->Tn;
    return ((int)1);    
}
// d- 
int Pluviometrie_Jour_Donne(TEMP *T[12][31], int J, int M, float *p)
{
    int rt;
    rt = Jour_Valide(J,M);
    if (!rt) return ((int)0);
    *p = T[M-1][J-1]->Pl;
    return ((int)1);
}
// e-
int Jour_Chaud_Mois(TEMP *T[12][31], int M)
{
    int rt, ic = 0, i;
    rt = Nb_Jour_Mois(M);
    if (!rt) return ((int)0);
    for (i = 1; i < rt; i++) if (T[M-1][i]->Tj > T[M-1][ic]->Tj) ic = i;
    return ((int)ic+1);   
}
// f-
int Nuit_Chaud_Mois(TEMP *T[12][31], int M)
{
    int rt, ic = 0, i;
    rt = Nb_Jour_Mois(M);
    if (!rt) return ((int)0);
    for (i = 1; i < rt; i++) if (T[M-1][i]->Tn > T[M-1][ic]->Tn) ic = i;
    return ((int)ic+1);   
}
// g-
int Jour_Pluvieux_Mois(TEMP *T[12][31], int M)
{
    int rt, ic = 0, i;
    rt = Nb_Jour_Mois(M);
    if (!rt) return ((int)0);
    for (i = 1; i < rt; i++) if (T[M-1][i]->Pl > T[M-1][ic]->Pl) ic = i;
    return ((int)ic+1);   
}
// h- 
int Moyenne_Temperature_Jour_Mois(TEMP *T[12][31], int M, float *Moy)
{
    int rt, i;
    rt = Nb_Jour_Mois(M);
    if (!rt) return ((int)0);
    for (i = 0; i < rt; i++) *Moy += T[M-1][i]->Tj;
    *Moy /= rt;
    return ((int)1); 
}
// i-
int Moyenne_Temperature_Nuit_Mois(TEMP *T[12][31], int M, float *Moy)
{
    int rt, i;
    rt = Nb_Jour_Mois(M);
    if (!rt) return ((int)0);
    for (i = 0; i < rt; i++) *Moy += T[M-1][i]->Tn;
    *Moy /= rt;
    return ((int)1); 
}
// j-
int Moyenne_Pluviometrie_Mois(TEMP *T[12][31], int M, float *Moy)
{
    int rt, i;
    rt = Nb_Jour_Mois(M);
    if (!rt) return ((int)0);
    for (i = 0; i < rt; i++) *Moy += T[M-1][i]->Pl;
    *Moy /= rt;
    return ((int)1); 
}
// k-
int Mois_Chaud_Jour(TEMP *T[12][31])
{
    int i, j, rt, M = 1;
    float MoyI, Moy;
    rt = Moyenne_Temperature_Jour_Mois(T,1,&MoyI);
    for (i = 2; i <= 12; i++)
    {
        rt = Moyenne_Temperature_Jour_Mois(T,i,&Moy);
        if (Moy > MoyI) M = i;   
    }
    return ((int)M);
}
// l-
int Mois_Pluvieux(TEMP *T[12][31])
{
    int i, j, rt, M = 1;
    float MoyI, Moy;
    rt = Moyenne_Pluviometrie_Mois(T,1,&MoyI);
    for (i = 2; i <= 12; i++)
    {
        rt = Moyenne_Pluviometrie_Mois(T,i,&Moy);
        if (Moy > MoyI) M = i;   
    }
    return ((int)M);
}