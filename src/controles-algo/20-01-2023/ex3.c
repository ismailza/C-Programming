#include <stdio.h>
#include <stdlib.h>

typedef union 
{
    float opd;
    char opr;
}Info;

typedef struct CL
{
    Info info;
    struct CL *svt;
}Cellule;

float Calcule_Operation(float opd1, char opr, float opd2)
{
    switch (opr)
    {
        case '+': return ((float)opd1 + opd2);
        case '-': return ((float)opd1 - opd2);
        case '*': return ((float)opd1 * opd2);
        case '/': 
            if (opd2 != 0) return ((float)opd1 / opd2);
            printf("\nErreur : Division par 0");
            exit(0);
        default : printf("\nOperateur inconnu");
    }
}

float Evaluer_ExpArith(Cellule *liste)
{

}