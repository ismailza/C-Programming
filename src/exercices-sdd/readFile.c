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
    char *Nom_fich; // j'utilise un pointeur afin que la gestion de la chaine soit faite par le C 
    int nb_ind, ind;
    long l;
    // allocation de la place mémoire pour la variable pointeur avant son utilisation
    pt_individu = (individu*)malloc(sizeof(individu));
    // allocation de la memoire pour la variable Nom_fich
    printf("\nEntrer le nom du fichier ou les informations sont stockees : ");
    Nom_fich = (char*)malloc(20*sizeof(char));
    scanf("%s",Nom_fich); 
    getchar();
    if(Nom_fich == NULL)
    {
        printf("\nErreur d'allocation de la place memoire pour le nom du fichier");
        exit(0);
    }
    // ouverture du fichier en mode lecture
    pt_fichier = fopen(Nom_fich,"r");
    if(pt_fichier==NULL)
    {   // verification de l'ouverture du fichier
        printf("Erreur d'ouverture du fichier");
        exit(0);
    }
    ind = 0;
    fread(pt_individu,1,sizeof(individu),pt_fichier);
    while (!feof(pt_fichier))
    {
        printf("\nLe nom du %de individu : %s",ind+1,pt_individu->Nom);
        printf("\nLe prenom du %de individu : %s",ind+1,pt_individu->Prenom);
        printf("\nL'age du %de individu : %d",ind+1,pt_individu->Age);
        fread(pt_individu,1,sizeof(individu),pt_fichier);
        ind++;
    }
    // lecture en choisissons l'element a lire en positionnant
    rewind(pt_fichier);
    ind = 1;
    l = (long)(sizeof(individu)*ind);
    fseek(pt_fichier,1,0);
    fread(pt_individu,1,sizeof(individu),pt_fichier);
    printf("\nLe nom du %de individu : %s",ind,pt_individu->Nom);
    printf("\nLe prenom du %de individu : %s",ind,pt_individu->Prenom);
    printf("\nL'age du %de individu : %d",ind,pt_individu->Age);
    // ferme le fichier en mode ecriture 
    fclose(pt_fichier);
}