/* Programme qui lit des caracteres sur une seule ligne puis les reecrit sur l'ecran */ 
// declaration des bibliotheques
#include<stdio.h>
#include<stdlib.h>
// declaration des constantes
#define RC '\n'
// le programme principale
void main()
{
    char c;
    printf("Saisir une suite de caractères :\n");
    while ((c = getchar()) != RC) // on lit caractère par caractère jusqu'à le caractère '\n'
        printf("%c",c); //Afficher le caractère lu 
}