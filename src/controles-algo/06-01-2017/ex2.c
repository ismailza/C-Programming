#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char Minus_To_Majus(char c)
{
    return ((char)('A'+c-'a'));
}

char Majus_To_Minus(char c)
{
    return ((char)('a'+c-'A'));
}

char Transformer_Car(char c, char ch[7])
{
    char TAB[7] = {'<','\\','T','A','B','>','\0'};
    char BL[6] = {'<','\\','B','L','>','\0'};
    char CR[6] = {'<','\\','C','R','>','\0'};
    if (('a' <= c) && (c <= 'z')) return ((char)Minus_To_Majus(c));
    if (('A' <= c) && (c <= 'Z')) return ((char)Majus_To_Minus(c));
    if (c == '\t') strcpy(ch,TAB);
    else if (c == ' ') strcpy(ch,BL);
    else if (c == '\n') strcpy(ch,CR);
    return ((char)c);
}

void Transformation()
{
    char c, tab[7];
    printf("\nTaper votre phrase : ");
    do 
    {
        c = getchar();
        c = Transformer_Car(c,tab);
        if (c == '\t' || c == ' ' || c == '\n') printf("%s",tab);
        else printf("%c",c);
    } while (c != '\n');
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Lire_Texte()
{
    char c;
    int i;
    printf("\nTaper votre texte : ");
    do
    {
        c = getchar();
        i = 0;
       
        if (c == '\\') if ((c = getchar()) == '-') getchar();
    } while (c != '\n');    
}


void main()
{
    
}