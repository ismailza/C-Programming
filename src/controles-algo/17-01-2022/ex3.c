#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BL ' '
#define RC '\n'

typedef struct 
{
    char mot[26];
    int nb_rep, longuer;
}Mot;
typedef struct MT
{
    Mot M;
    struct MT *svt; 
}Cellule;

char Epeurer_Blan()
{
    char c;
    while ((c = getchar()) == BL);
    return ((char)c);
}

void Init_Text(Cellule *Text[36])
{
    for (int i = 0; i < 36; i++) Text[i] = NULL;
}

Cellule *CreerCellule(Mot m)
{
    Cellule *mot = (Cellule *)malloc(sizeof(Cellule));
    if (!mot) exit(0);
    mot->M = m;
    mot->M.nb_rep = 1;
    mot->svt = NULL;
    return ((Cellule *)mot);
}

void Insert_Word(Cellule *Text[36], int i, Mot m)
{
    int inserted = 0;
    Cellule *NM, *pred = NULL, *courant = Text[i];
    if (!courant) Text[i] = CreerCellule(m);
    else
    {
        while (courant)
        {
            if (strcmp(m.mot,courant->M.mot) == 0) 
            {
                courant->M.nb_rep++;
                inserted = 1;
                break;
            }
            if (m.longuer >= courant->M.longuer) break;
            pred = courant;
            courant = courant->svt;
        }
        if (inserted == 0)
        {
            NM = CreerCellule(m);
            NM->svt = courant;
            if (pred) pred->svt = NM;
            else Text[i] = NM;
        }
    }
}
// b- 
void Lire_Texte(Cellule *Text[36])
{
    char c;
    int i;
    Mot m;
    printf("\nTaper votre texte : ");
    do
    {
        c = Epeurer_Blan();
        i = 0;
        while ((c != RC) && (c != BL) && (c != '\\'))
        {
            m.mot[i++] = c;
            c = getchar();
        }
        if (i)
        {
            m.mot[i] = '\0';
            m.longuer = i;
            if (('a' <= m.mot[0]) && (m.mot[0] <= 'z')) i = (int)m.mot[0] - 'a';
            else if (('A' <= m.mot[0]) && (m.mot[0] <= 'Z')) i = (int)m.mot[0] - 'A';
            else if (('0' <= m.mot[0]) && (m.mot[0] <= '9')) i = (int)m.mot[0] - '0' + 26;
            Insert_Word(Text,i,m);
        }
        if (c == '\\') getchar();
    } while (c != RC);    
}
// c- 
void Apparition_Lettres(Cellule *Text[36], int AppLettre[36])
{
    Cellule *courant;
    int i,j,k;
    for (i = 0; i < 36; AppLettre[i++] = 0);
    for (i = 0; i < 36; i++)
    {
        courant = Text[i];
        while (courant)
        {
            j = 0;
            while (courant->M.mot[j] != '\0') 
            {
                if (('a' <= courant->M.mot[j]) && (courant->M.mot[j] <= 'z')) k = (int)courant->M.mot[j] - 'a';
                else if (('A' <= courant->M.mot[j]) && (courant->M.mot[j] <= 'Z')) k = (int)courant->M.mot[j] - 'A';
                else if (('0' <= courant->M.mot[j]) && (courant->M.mot[j] <= '9')) k = (int)courant->M.mot[j] - '0' + 26;
                AppLettre[k] += courant->M.nb_rep;
                j++;
            } 
            courant = courant->svt;
        }
    }
}
// d- La lettre la plus représentée
char Lettre_Plus_Representee(int AppLettre[36])
{
    int l = 0;
    for (int i = 1; i < 26; i++) if (AppLettre[i] > AppLettre[l]) l = i;
    return ((char)l+'a');
}
// e- Le mot le plus frequent
Mot Mot_Plus_Frequent(Cellule *Text[36])
{
    int i;
    Cellule *courant;
    Mot m;
    m.nb_rep = 0;
    for (i = 0; i < 36; i++)
    {
        courant = Text[i];
        while (courant)
        {
            if (courant->M.nb_rep > m.nb_rep) m = courant->M;
            courant = courant->svt;
        }
    }
    return ((Mot)m);
}
// f- Le(s) mot(s) plus long
void Mots_Plus_Long(Cellule *Text[36])
{
    int i, l = 0;
    Cellule *courant;
    for (i = 0; i < 36; i++)
    {
        if (Text[i]) if (Text[i]->M.longuer > l) l = Text[i]->M.longuer;
    }
    for (i = 0; i < 36; i++)
    {
        courant = Text[i];
        while (courant)
        {
            if (courant->M.longuer == l) printf("\n%s",courant->M.mot);
            else break;
            courant = courant->svt;
        }
    }
}


void Afficher_Text(Cellule *Text[36])
{
    Cellule *courant;
    for (int i = 0; i < 36; i++)
    {
        courant = Text[i];
        while (courant)
        {
            printf("\n%s \tL = %d \t Rep : %d",courant->M.mot,courant->M.longuer,courant->M.nb_rep);
            courant = courant->svt;
        }
    }
}
void main()
{
    Cellule *Text[36];
    int AppLettres[36];
    int i,a = 'a';
    Init_Text(Text);
    Lire_Texte(Text);
    Afficher_Text(Text);
    Apparition_Lettres(Text,AppLettres);
    printf("\n*************");
    for (i = 0; i < 26; i++) printf("\n%c --> %d",a++,AppLettres[i]);
    a= 0;
    for (i = 26; i < 36; i++) printf("\n%d --> %d",a++,AppLettres[i]);
    printf("\nLa lettre la plus representee est %c",Lettre_Plus_Representee(AppLettres));
    printf("\nLe mot le plus frequent : %s",Mot_Plus_Frequent(Text).mot);
    Mots_Plus_Long(Text);
    
}