#include<stdio.h>
#include<stdlib.h>

void main(int argc, char const *argv[])
{
    int i; 
    char c,var_c;
    // saisir un entier
    printf("Entrer le valeur de votre entier?: ");
    scanf("%d",&i);
    printf("L'entier saisi est %d \n",i);
    // saisir un caractere
    printf("Entrer un caractère au clavier : ");
    scanf("%c",&c);
    printf("Le caractere lu est : %c son code ASCII est %d ",c,c);
    // Saissie non formatée au clavier
    getchar(); //lecture perdue
    var_c = getchar(); //lecture d'un caractère affecté à la variable var_c
    printf("%c \n",var_c);
}
