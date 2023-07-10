#include<stdio.h>
#include<stdlib.h>

// a
char Minus_To_Majus(char c)
{
    return ((char)('A'+c-'a'));
}
// b
char Majus_To_Minus(char c)
{
    return ((char)('a'+c-'A'));
}
// c
int Car_To_TAB(char c, char TAB[4])
{
    TAB[0] = 'T';
    TAB[1] = 'A';
    TAB[2] = 'B';
    TAB[3] = '\0';
}
// d
int Car_To_BLC(char c, char BLC[4])
{
    BLC[0] = 'B';
    BLC[1] = 'L';
    BLC[2] = 'C';
    BLC[3] = '\0';
}
// e
int Trans_Num(char c)
{
    switch (c)
    {
        case '0': return ((int)5);break;
        case '1': return ((int)6);break;
        case '2': return ((int)7);break;
        case '3': return ((int)8);break;
        case '4': return ((int)9);break;
        case '5': return ((int)0);break;
        case '6': return ((int)1);break;
        case '7': return ((int)2);break;
        case '8': return ((int)3);break;
        case '9': return ((int)4);break;
        default : return ((int)-1);
    }
}
// f
int Type_Carac(char c)
{
    if (('a' <= c) && (c <= 'z')) return ((int)1);
    if (('A' <= c) && (c <= 'Z')) return ((int)2);
    if (c == '\t') return ((int)3);
    if (c == ' ') return ((int)4);
    if (('0' <= c) && (c <= '9')) return ((int)5);
    return ((int)0);
}
// g
void Transformation()
{
    char c, tab[4];
    int rt;
    printf("\nTaper votre phrase : ");
    while ((c = getchar()) != '\n')
    {
        rt = Type_Carac(c);
        switch (rt)
        {
            case 1: printf("%c",Minus_To_Majus(c));break;
            case 2: printf("%c",Majus_To_Minus(c));break;
            case 3: rt = Car_To_TAB(c,tab);
                printf("%s",tab);break;
            case 4: rt = Car_To_BLC(c,tab);
                printf("%s",tab);break;
            case 5: printf("%d",Trans_Num(c));break;
            default : printf("%c",c);
        }
    }
}

void main()
{
    Transformation();
}