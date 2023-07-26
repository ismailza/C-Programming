#include<stdio.h>
#include<stdlib.h>

void main(int argc, char const *argv[])
{
    // Affichage d'une chaine de caractère
    printf("Ceci permet l'affichage d'une chaine de caractères à l'écran sur une seule ligne\n");
    // Chaine de caractère avec les formats
    printf("chaine de caractère plus les formats à la bonne place\n");
    // Affichage d'un entier
    // a
    int i,j;
    i= 1258;
    printf("la variable entiere i a pour valeur %d \n",i);
    // b
    i = 10; j = 12;
    printf("La somme de %d et %d vaut %d .\n",i,j,i+j);
    // Affichage d'un caractère
    // a
    printf("La premiere lettre de l'alphabet est %c.\n",'a');
    // b
    char vari_c;
    vari_c = 'Z';
    printf("La dernière lettre de l'alphabet est %c .\n",vari_c);
    // c
    printf("%c et %c ont les code ASCII %d et %d \n",97,65,97,65);
    // Affichage formaté des chaines de caractères
    // a 
    printf("%s","C'est une chaine de caractères \n");
    // b
    char vari_string[] = "une variable de type chaine de caracteres";
    printf("de quelle type est la variabe vari_string?\nReponse : %s \n",vari_string);
    // Largeur minimal et précision
    printf("%s \n","cinq"); // Affichage normal
    printf("%2s \n","cinq"); //Affichage complété par le printf
    printf("%10s \n","cinq"); //Affichage complètè par des espaces
    printf("%2.3f\n%11.6f\n\n",3.1415,3.1415);
    printf("%5.5f\n%8.5f\n\n",314.0,314.0);
    printf("%6.6s\n%6.3s","string","string");
}