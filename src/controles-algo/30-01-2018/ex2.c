#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    int jour, mois, annee;
}Date;
typedef struct
{
    char Nom[30];      
    char Prenom[30];   
    Date date_Naiss;    
    char tele[10];
    char NSS[10];
}Patient;

typedef struct CL
{
    Patient Pt;
    struct CL *svt;
}Cellule;

typedef struct 
{
    Cellule *matinee;
    Cellule *apre_midi;
}Journee;

Journee *RDVs[12][31];

int Nb_Jour_Mois(int mois)
{
    int V[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    return ((int)((0 < mois) && (mois <= 12))? V[mois-1] : 0);
}

int Jour_Valide(int jour, int mois)
{
    return ((int)((0 < jour) && (jour <= Nb_Jour_Mois(mois))) ?1:0);
}
// b
int Nb_RDV_DemiJournee(Journee *RDVs[12][31], int mois, int jour, int mat_midi)
{
    Cellule *ptr;
    int Nb_RDVs = 0;
    if (!Jour_Valide(jour,mois)) return ((int)-1);
    if (mat_midi == 1) ptr = RDVs[mois-1][jour-1]->matinee;
    else if (mat_midi == 2) ptr = RDVs[mois-1][jour-1]->apre_midi;
    else return ((int)-2);
    while (ptr)
    {
        Nb_RDVs++;
        ptr = ptr->svt;
    }
    return ((int)Nb_RDVs);
}
// c
int Nb_RDV_Mois(Journee *RDVs[12][31], int mois)
{
    int i, Nb_RDVs = 0, nb_jm = Nb_Jour_Mois(mois);
    if (!nb_jm) return ((int)-1);
    for (i = 1; i <= nb_jm; i++)
    {
        Nb_RDVs += Nb_RDV_DemiJournee(RDVs,mois,i,1); // pour la matinee
        Nb_RDVs += Nb_RDV_DemiJournee(RDVs,mois,i,2); // pour l'apres-midi
    }
    return ((int)Nb_RDVs);
}
// d
int Max_RDV_Par_Mois(Journee *RDVs[12][31], int mois)
{
    int i, j = 1, Nb_RDVs, Max = 0, nb_jm = Nb_Jour_Mois(mois);
    if (!nb_jm) return ((int)-1);
    for (i = 1; i <= nb_jm; i++)
    {
        Nb_RDVs = Nb_RDV_DemiJournee(RDVs,mois,i,1) + Nb_RDV_DemiJournee(RDVs,mois,i,2);
        if (Nb_RDVs > Max) 
        {
            Max = Nb_RDVs;
            j = i;
        }
    }
    return ((int)j);
}
// e
int Min_RDV_Par_Mois(Journee *RDVs[12][31], int mois)
{
    int i, j = 1, Nb_RDVs, Min = 0, nb_jm = Nb_Jour_Mois(mois);
    if (!nb_jm) return ((int)-1);
    for (i = 1; i <= nb_jm; i++)
    {
        Nb_RDVs = Nb_RDV_DemiJournee(RDVs,mois,i,1) + Nb_RDV_DemiJournee(RDVs,mois,i,2);
        if (Nb_RDVs < Min) 
        {
            Min = Nb_RDVs;
            j = i;
        }
    }
    return ((int)j);
}
// f
int Max_RDV_Par_An(Journee *RDVs[12][31])
{
    int i, m = 1, Max = 0, Nb_RDVs;
    for (i = 1; i <= 12; i++)
    {
        Nb_RDVs = Nb_RDV_Mois(RDVs, i);
        if (Nb_RDVs > Max) 
        {
            m = i;
            Max = Nb_RDVs;
        }
    }
    return ((int)m);
}
// g
int Calculate_Age(Date date_naiss) {
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);

    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    int age = currentYear - date_naiss.annee;
    if (date_naiss.mois > currentMonth || (date_naiss.mois == currentMonth && date_naiss.jour > currentDay)) age--;
    
    return age;
}
int Tranche_Age(int age)
{
    if (age < 10) return ((int)0);
    if (age < 18) return ((int)1);
    if (age < 25) return ((int)2);
    return ((int)3);
}
void Tranches_Ages(Journee *RDVs[12][31])
{
    int i, j, nb_jm, T[4] = {0,0,0,0};
    Cellule *ptr;
    for (i = 0; i < 12; i++)
    {
        nb_jm = Nb_Jour_Mois(i+1);
        for (j = 0; j < nb_jm; j++)
        {
            ptr = RDVs[i][j]->matinee;
            while (ptr)
            {
                T[Tranche_Age(Calculate_Age(ptr->Pt.date_Naiss))]++;
                ptr = ptr->svt;
            }
            ptr = RDVs[i][j]->apre_midi;
            while (ptr)
            {
                T[Tranche_Age(Calculate_Age(ptr->Pt.date_Naiss))]++;
                ptr = ptr->svt;
            }
        }
    }
    printf("\nLes juveniles : %d",T[0]);
    printf("\nLes ados : %d",T[1]);
    printf("\nLes jeunes : %d",T[2]);
    printf("\nLes adultes : %d",T[3]);
}
