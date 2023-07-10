#include<stdio.h>
#include<stdlib.h>

void PhraseAlphanumerique()
{
    char c;
    printf("\nTaper votre phrase : ");
    while ((c=getchar())!= '\n')
    {
        if (('a'<=c && c<='z') || 
            ('A'<=c && c<='Z') || 
            ('0'<=c && c<='9')) printf("%c",c);
    }
}

void main()
{
    PhraseAlphanumerique();
}