// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <stdlib.h>
#include"Ex3.c"

void Create_DB(TEMP *T[12][31])
{
    int i, j;
    for (i = 0; i < 12; i++)
    {
        for (j = 0; j < 31; j++) T[i][j] = malloc(sizeof(TEMP));
    }
}

float float_rand(float min, float max)
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

void Insert_Data(TEMP *T[12][31])
{
    int i, j, rt;
    for (i = 0; i < 12; i++)
    {
        rt = Nb_Jour_Mois(i+1);
        for (j = 0; j < rt; j++) 
        {
            T[i][j]->Tj = float_rand(3,45);
            T[i][j]->Tn = float_rand(-3,38);
            T[i][j]->Pl = float_rand(0,20);
        }
    }      
}

void Affichage_Meteo_Annee(TEMP *T[12][31])
{
    int i, j;
    printf("\nJour\tT jour\tT nuit\tPluviometrie");
    for (i = 0; i < 12; i++)
    {
        printf("\nMois %d\t------------------------",i+1);
        for (j = 0; j < 31; j++) printf("\n%d\t%.2f\t%.2f\t%.2f",j+1,T[i][j]->Tj,T[i][j]->Tn,T[i][j]->Pl);
    }
}

int main()
{
    int rt;
    float ret;
    TEMP *T[12][31];
    Create_DB(T);
    Insert_Data(T);
    Affichage_Meteo_Annee(T);
    printf("\n**************************************");
    rt = Temperature_Jour_Donne(T,17,4,1,&ret);
    printf("\nc- La temperature de la journe du 17/04 : %f",ret);
    rt = Temperature_Jour_Donne(T,17,4,0,&ret);
    printf("\nc- La temperature de la nuit du 17/04 : %f",ret);
    rt = Pluviometrie_Jour_Donne(T,17,4,&ret);
    printf("\nd- La pluviemetrie de 17/04 : %f",ret);
    rt = Jour_Chaud_Mois(T,4);
    printf("\ne- Le jour le plus chaud du mois 4 : %d",rt);
    rt = Nuit_Chaud_Mois(T,4);
    printf("\nf- La Niut la plus chaude du mois 4 : %d",rt);
    rt = Jour_Pluvieux_Mois(T,4);
    printf("\ng- Le jour le plus pluvieux du mois 4 : %d",rt);
    rt = Moyenne_Temperature_Jour_Mois(T,4,&ret);
    printf("\nh- La moyenne de T des jours du mois 4 : %f",ret);
    rt = Moyenne_Temperature_Nuit_Mois(T,4,&ret);
    printf("\ni- La moyenne de T des nuits du mois 4 : %f",ret);
    rt = Moyenne_Pluviometrie_Mois(T,4,&ret);
    printf("\nj- La moyenne de la pluviometrie du mois 4 : %f",ret);
    rt = Mois_Chaud_Jour(T);
    printf("\nk- Le mois le plus chaud : %d",rt);
    rt = Mois_Pluvieux(T);
    printf("\nk- Le mois le plus pluvieux : %d",rt);
}
