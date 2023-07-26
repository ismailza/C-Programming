/* Définir : 
- la fonction "Lire_Tableau" permettant le remplissage d'un tableau avec des caracteres;
- la fonction "Ecrire_Tab_String" permettant l'ecriture su contenu du tableau en tant que String.
*/
// Declaration des bibliotheques
#include<stdio.h>
#include<stdlib.h>
// Declaration des constantes
#define NB_Elem 20 // nombre d'element du tableau
#define RC '\n'
// Prototype
void Lire_Tableau(char tab[NB_Elem]);
void Ecrire_Tab_String(char tab[NB_Elem]);
// le programme principale
void main()
{
    char tab[NB_Elem];
    Lire_Tableau(tab);
    Ecrire_Tab_String(tab);
}
// la fonction Lire_Tableau() permet de remplir le tableau en parametre par des caracteres
void Lire_Tableau(char tab[NB_Elem])
{
    int i;
    while ((i < NB_Elem-1) && (tab[i++] = getchar())!= RC);
    tab[i-1] = '\0';
}
// la fonction Ecrire_Tab_String() pour ecrire le contenu du tableau en parametre en tant qu'une chaine du caractaires
void Ecrire_Tab_String(char tab[NB_Elem])
{
    printf("%s",tab);
}