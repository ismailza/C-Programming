#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structures.h"
#include"connection.h"
#include"fonctions.h"


int Type_Affichage(int classe, int *choix2)
{
    int i, choix, an_sem;
    printf("\n1: Afficher les notes de l'annee");
    printf("\n2: Afficher les notes de semestre");
    printf("\n--> Choix : "); scanf("%d",&choix);
    if (choix == 1)
    {
        if (classe == 1) an_sem = 1;
        else
        {
            for (i = 1; i <= classe; i++) printf("\n%d : pour l'annee %d",i,i);
            printf("\n--> "); scanf("%d",&an_sem);
        }
    }
    else
    {
        for (i = 1; i <= 2*classe; i++) printf("\n%d : pour S%d",i,i);
        printf("\n--> "); scanf("%d",&an_sem);
    }
    *choix2 = an_sem;
    return ((int)choix);
}

int Choix_Ordre(Cellule *Promo[3][26])
{
    int choix;
    Init_Tab_Alpha_Promo(Promo);
    do
    {
        printf("\n1 : Par ordre alphabetique");
        printf("\n2 : Par ordre de merite");
        printf("\n-->Choix : "); scanf("%d",&choix);
        if ((choix != 1) && (choix != 2)) printf("\nChoix non valide");
        else Import_Etudiants(Promo,choix);
    } while ((choix != 1) && (choix != 2));
    return ((int)choix);
}

void Statistic()
{
    int choix,classe,annee = 1,rt;
    Cellule *Promo[3][26];
    printf("\n\t\tStatistiques ");
    do
    {
        printf("\n0 : Retour au menu precedent");
        printf("\n1 : Afficher les etudiants valides");
        printf("\n2 : Afficher les etudiants non valides");
        printf("\n3 : Afficher les etudiants dont la note entre 10 et 12");
        printf("\n--> Choix : "); scanf("%d",&choix);
        do
        {
            printf("\nQuelle classe : 1, 2 ou 3 :");
            scanf("%d",&classe);
        } while (classe <= 0 || classe > 3);
        if (classe > 1) 
        {
            for (int i = 1; i <= classe; i++) printf("\n%d : l'annee %d",i,i);
            printf("\n-->"); scanf("%d",&annee);
        }
        rt = Choix_Ordre(Promo);
        switch (choix)
        {
            case 0: break;
            case 1: Etudiants_Valides(Promo,classe,annee,rt); break;
            case 2: Etudiants_Non_Valides(Promo,classe,annee,rt); break;
            case 3: Etudiants_Note_Entre_10_12(Promo,classe,annee,rt); break;
        }
    } while (choix);
}
void Afficher(Cellule *Promo[3][26], int classe, int an_sem, int type)
{
    Cellule *courant;
    int i;
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve");
    for (i = 0; i < 26; i++)
    {
        courant = Promo[classe-1][i];
        while (courant)
        {
            Afficher_Info_Etudiant(courant->etu);
            Affichage_Notes(courant->note,an_sem,type);
            courant = courant->svt;
        }
    }
}

void main()
{   
    int choix, classe, rt,choix2;
    char Nom[26];
    Cellule *Promo[3][26];
    printf("\nGestion d'une promotion ILISI");
    do
    {
        Init_Tab_Alpha_Promo(Promo);
        printf("\n0 : Arreter le programme");
        printf("\n1 : Afficher les etudiants");
        printf("\n2 : Afficher les etudiants qui obtient leurs diplome");
        printf("\n3 : Chercher un etudiant");
        printf("\n4 : Consultation de validation");
        printf("\n5: Afficher les notes des etudiants");
        printf("\n--> Choix : "); scanf("%d",&choix);
        switch (choix)
        {
            case 0: break;
            case 1: 
                do
                {
                    printf("\nQuelle classe : 1, 2 ou 3 :");
                    scanf("%d",&classe);
                } while (classe <= 0 || classe > 3);
                rt = Choix_Ordre(Promo);
                Afficher_Etudiants_Promo_Ordre(Promo,classe,rt);
                break;
            case 2: rt = Choix_Ordre(Promo);
                Etudiants_Obtient_Diplome(Promo,rt);
                break;
            case 3: 
                Import_Etudiants(Promo,1);
                printf("\nQuelle annee : 1, 2 ou 3 :");
                scanf("%d",&classe);
                printf("\nSaisir le nom : "); scanf("%s",&Nom);
                Recherche_Etudiant_Nom(Promo,classe,Nom);
                break;
            case 4: Statistic();
                break;
            case 5: 
                Import_Etudiants(Promo,1);
                do
                {
                    printf("\nQuelle classe : 1, 2 ou 3 :");
                    scanf("%d",&classe);
                } while (classe <= 0 || classe > 3);
                rt = Type_Affichage(classe,&choix2);
                Afficher(Promo,classe,choix2,rt);
                break;
            default : printf("\nChoix non valide!");
        }
    } while (choix);
}