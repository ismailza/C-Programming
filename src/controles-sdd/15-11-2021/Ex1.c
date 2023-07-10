#include<stdio.h>
#include<stdlib.h>

#define RC '\n'
#define NB 37

int Caractere(char c)
{
    if (('0' <= c) && (c <= '9')) return ((int)(c - '0'));
    if ((('a' <= c) && (c <= 'z'))) return ((int)(c - 'a' + 10));
    if ((('A' <= c) && (c <= 'Z'))) return ((int)(c - 'A' + 10));
    return ((int)(NB-1));
}
int Comptage_Caracteres(int Tab_Compte[NB])
{
    char c;
    int i, rt;
    //  initialisation
    for (i= 0; i< NB; Tab_Compte[i++] = 0); 
    while ((c=getchar()) != RC)
    {
        rt = Caractere(c);
        Tab_Compte[rt]++;
    }   
}
void Afficher(int Tab_Compte[NB])
{
    int i;
    char c = 'a';
    for (i=0; i< 10; i++)
        if (Tab_Compte[i]!= 0) printf("\n%d\t %d caracteres",i,Tab_Compte[i]);
    for (i=10; i< NB-1; i++)
    {
        if (Tab_Compte[i]!= 0) printf("\n%c\t %d caracteres",c,Tab_Compte[i]);
        c = (char)(c+1);
    }
    printf("\nAutre\t %d caracteres",Tab_Compte[NB-1]);
}

void main()
{
    int rt, Tab[NB];
    rt = Comptage_Caracteres(Tab);
    Afficher(Tab);
}