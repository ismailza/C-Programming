#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
// declaration des types
FILE *pt_fichier;
typedef struct indiv
{
    char Nom[10];
    char Prenom[10];
    int Age;
}individu;
// Programme principal
void main()
{
    individu *pt_individu;
    char *Nom_fich;
    int nb_ind, ind;
    // allocation de la place mémoire pour la variable pointeur avant son utilisation
    pt_individu = (individu*)malloc(sizeof(individu));
    // allocation de la memoire pour la variable Nom_fich
    printf("\nEntrer le nom du fichier ou les informations seront stockees : ");
    Nom_fich = (char*)malloc(20*sizeof(char));
    scanf("%s",Nom_fich); 
    getchar();
    if(Nom_fich == NULL)
    {
        printf("\nErreur d'allocation de la place memoire pour le nom du fichier");
        exit(0);
    }
    // ouverture du fichier en mode ecriture
    pt_fichier = fopen(Nom_fich,"w");
    if(pt_fichier==NULL)
    {   // verification de l'ouverture du fichier
        printf("Erreur d'ouverture du fichier");
        exit(0);
    }
    printf("\nCombien d'individu voulez vous saisir : ");
    scanf("%d",&nb_ind); getchar();
    // saisie des donnees
    for(ind = 0; ind < nb_ind; ind++)
    {
        // lecture du nom
        printf("\nEntrer le nom du %de individu : ",ind+1);
        scanf("%s",pt_individu->Nom); getchar();
        // lecture du prenom
        printf("\nEntrer le prenom du %de individu : ",ind+1);
        scanf("%s",pt_individu->Prenom); getchar();
        // lecture de l'age
        printf("\nEntrer l'age du %de individu : ",ind+1);
        scanf("%d",&pt_individu->Age);
        // ecriture dans le fichier les informations relatives a un individu
        fwrite(pt_individu,1,sizeof(individu),pt_fichier);
        //fprintf(pt_fichier,"%s %s %d\n",pt_individu->Nom,pt_individu->Prenom,pt_individu->Age);
    }
    // ferme le fichier en mode ecriture 
    fclose(pt_fichier);
}