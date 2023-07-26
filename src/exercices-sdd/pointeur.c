#include<stdio.h>
#include<stdlib.h>

#define nb 10

void main(int argc, char const *argv[])
{
    int i, *pt_int;
    char c, *pt_char;
    i = 12548;
    c = 'a';
    pt_int = &i; //affecter l'adresse memoire de i à pt_int
    pt_char = &c; //affecter l'adresse memoire de c à pt_char
    printf("le contenu de i vaut %d\n",i);
    printf("le contenu de pt_int vaut %d\n",*pt_int);
    printf("le contenu de c vaut %c\n",c);
    printf("le contenu de pt_char vaut %c\n",*pt_char);
    // Pointeurs et tableaux
    int Tab_int[nb]; // declaration d'un tableau d'entiers
    int *ptr;
    ptr = &Tab_int[0]; // Ou bien ptr = Tab_int
    Tab_int[3] = 4; // Accès direct par indice
    *(Tab_int + 4) = 5; // Accès par pointeur
    printf("%d",Tab_int[4]);
}
