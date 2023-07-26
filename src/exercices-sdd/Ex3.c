/* Définir : 
- La fonction "Lire_Tab_Ent" permettant le remplissage d'un tableau avec des entiers (nombre d'entiers de votre choix);
- La fonction "Ecrire_Tab_Ent" permettant l'affichage du contenu d'un tableau d'entiers.
*/
// Declaration des bibliotheques
#include<stdio.h>
#include<stdlib.h>
// Declaration des constantes
#define NB_Elem 10 // nombre d'element du tableau
// Prototype
void Lire_Tab_Ent(int Tab[NB_Elem], int *NB_saisie);
void Ecrire_Tab_Ent(int Tab[NB_Elem], int Elem);
// le programme principale
void main()
{
    int Elem, tab[NB_Elem]; // declaration d'un tableau d'entier
    Lire_Tab_Ent(tab, &Elem); // appel de la fonction Lire_Tab_Ent()
    Ecrire_Tab_Ent(tab, Elem); // appel de la fonction Ecrire_Tab_Ent()
}
// La fonction Lire_Tab_Ent() pour remlir le tableau passe en parametre par des entiers
void Lire_Tab_Ent(int Tab[NB_Elem], int *NB_saisie)
{
    int i;
    do
    {   // Repeter d'entrer le nombre d'element a lire tant que le nombre saisie superieur au nombre d'lement du tableau
        printf("\nEntrer le nombre d'elements a lire : ");
        scanf("%d",NB_saisie);
        if(*NB_saisie > NB_Elem) 
            printf("Erreur: le nombre doit etre inferieur ou egal au nombre d'element du tableau!");
    } while (*NB_saisie > NB_Elem);
    for(i = 0; i < *NB_saisie; i++)
    {   // Lire et affecter a chaque element du tableau un entier
        printf("\nEntrer l'element Tab[%d] : ",i);
        scanf("%d",&Tab[i]);
    } 
}
// La fonction Ecrire_Tab_Ent() pour afficher le tableau en passe en parametre 
void Ecrire_Tab_Ent(int Tab[NB_Elem], int NB_Lire)
{
    int i;
    for (i = 0; i < NB_Lire; i++)
        printf("Tab[%d] = %d \n",i,Tab[i]);
}