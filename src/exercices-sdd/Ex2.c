/* Programme qui permet la lecture : 
- d'un entier puis l'afficher;
- d'un reel puis l'afficher;
- d'un caractere puis l'afficher;
- et en fin d'une chaine de caracteres puis l'afficher.
*/
// declaration des bibliotheques
#include<stdio.h>
#include<stdlib.h>
// le programme principale
void main()
{
    int i;
    float f;
    char c, s[20];
    printf("\nSaisir un entier : ");
    scanf("%d",&i); // Lire un entier
    printf("L'entier lu est : %d",i);
    printf("\nSaisir un réel : ");
    scanf("%f",&f); // Lire un réel
    printf("Le réel lu est : %f",f);
    printf("\nSaisir un caractere : ");
    getchar(); // pour lire le caractere '\n'
    scanf("%c",&c); // Lire un caractere
    printf("Le caractère lu est : %c",c);
    printf("\nSaisir une chaine de caractere : ");
    getchar();
    gets(s); // Lire une chaine de caracteres
    printf("La chaine lu est : %s",s);
}