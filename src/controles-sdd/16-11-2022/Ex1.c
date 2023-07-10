#include<stdio.h>
#include<stdlib.h>

#define BL ' '
#define RC '\n'

void LirePhrase(char phrase[20][25])
{
    char c;
    int i = 0, j;
    for (i = 0; i < 20; i++) phrase[i][0] = '\0';    
    i = 0;
    printf("\nTaper votre phrase : ");
    do
    {
        // Epeurer blanc
        while ((c = getchar()) == ' ');
        j = 0;
        while ((c != ' ') && (c != RC))
        {
            phrase[i][j++] = c;
            c = getchar();
        }
        phrase[i++][j] = '\0';
    } while (c != RC);
}

int Taille_Mot(char mot[25])
{
    int i=0;
    while (mot[i] != '\0') i++;
    return ((int)i+1);
}

void Mot_Plus_Long(char phrase[20][25], char mot[25], int *rang)
{
    int i=0, j=0;
    while (phrase[i][j] != '\0') mot[j] = phrase[i][j++];
    mot[j] = '\0';
    *rang = 0;
    while ((phrase[++i][0] != '\0') && (i < 20))
    {
        if (Taille_Mot(mot) < Taille_Mot(phrase[i]))
        {
            for (j = 0; j < Taille_Mot(phrase[i]); j++) mot[j] = phrase[i][j]; 
            mot[j] = '\0';
            *rang = i;
        }
    }
}

int Poids_Mot(char mot[25])
{
    int i = 0, poids = 0;
    while (mot[i] != '\0') poids += (int)(mot[i++]);
    return ((int)poids);
}

int Mot_Poids_Imp(char phrase[20][25], char mot[25], int *rang)
{
    int poids, i = 0, j = 0;
    poids = Poids_Mot(phrase[0]);
    while (phrase[i][j] != '\0') mot[j] = phrase[i][j++];
    mot[j] = '\0';
    *rang = 0;
    while ((phrase[++i][0] != '\0') && (i < 20))
    {
        if (Poids_Mot(phrase[i]) > poids) 
        {
            j = 0;
            poids = Poids_Mot(phrase[i]);
            while (phrase[i][j] != '\0') {mot[j] = phrase[i][j]; j++; }
            mot[j] = '\0';
            *rang = i;
        }
    }
    return ((int)poids);
}

void main()
{
    char phrase[20][25], mot[25];
    int rt, rang;

    LirePhrase(phrase);
    Mot_Plus_Long(phrase,mot,&rang);
    printf("\nLe mot le plus long est << %s >>, son rang : %d",mot,rang);
    
    rt = Mot_Poids_Imp(phrase,mot,&rang);
    printf("\nLe mot qui a le poids important est << %s >>, son poids : %d , son rang : %d",mot,rt,rang);

}