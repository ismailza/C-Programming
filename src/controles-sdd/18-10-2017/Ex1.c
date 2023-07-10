#include<stdio.h>
#include<stdlib.h>

// a
int PoncToCarac(char c, char str[10])
{
    switch (c)
    {
        case ' ':
            str[0] = 'B'; str[1] = 'L'; str[2] = '\0';
            break;
        case '\t':
            str[0] = '\\'; str[1] = 't'; str[2] = '\0';
            break;
        case '\n': 
            str[0] = '\\'; str[1] = 'n'; str[2] = '\0';
            break;
        case ',':
            str[0] = '\\'; str[1] = 'v'; str[2] = 'i'; str[3] = 'r'; str[4] = 'g'; str[5] = '\0';
            break;
        case ':':
            str[0] = 'D'; str[1] = 'b'; str[2] = 'l'; str[3] = 'P'; str[4] = 't'; str[5] = '\0';
            break;
        default : return ((int)0);
    }
    return ((int)1);
}
// b
int NumToChne(char c, char Chne[10])
{
    switch (c)
    {
        case '1':
            Chne[0] = 'U'; Chne[1] = 'n'; Chne[2] = '\0';
            break;
        case '2':
            Chne[0] = 'D'; Chne[1] = 'e'; Chne[2] = 'u'; Chne[3] = 'x'; Chne[4] = '\0';
            break;
        case '3':
            Chne[0] = 'T'; Chne[1] = 'o'; Chne[2] = 'i'; Chne[3] = 's'; Chne[4] = '\0';
            break;
        /*
        .
        .
        .
        */
        default : return ((int)0);
    }
    return ((int)1);
}
// c
int EstDeType(char c)
{
    if ((('a'<=c) && (c<='z')) || (('A'<=c) && (c<='Z'))) return ((int)1);
    if (('0'<=c) && (c<='9')) return ((int)0);
    return ((int)-1);
}
// d
char UpDnEtInv(char c)
{
    if (('a'<=c) && (c<='z')) return ((char)('A'+c-'a'));
    if (('A'<=c) && (c<='Z')) return ((char)('a'+c-'A'));
    return ((char)c);
}
// e
void TransPhrase()
{
    char c, chne[10];
    int nbLu=0, nbTr=0, rt;
    while ((c=getchar())!='\n')
    {
        nbLu++;
        rt = EstDeType(c);
        switch (rt)
        {
            case -1: 
                printf("%c",c);
                break;
            case 0:
                rt = NumToChne(c,chne);
                printf("%s",chne);
                nbTr++;
                break;
            case 1: 
                printf("%c",UpDnEtInv(c));
                nbTr++;
                break;
        }
    }
    printf("\nNombre de caractere lu : %d",nbLu);
    printf("\nNombre de transformations : %d",nbTr);
}

void main()
{
    TransPhrase();
}