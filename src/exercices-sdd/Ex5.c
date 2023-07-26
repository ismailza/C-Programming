/* 
- Donner une fonction qui recoit un caractere alphabetique miniscule et le retourne en Majuscule .
- Donner une fonction qui recoit un caractere alphabetique Majuscule et le retourne en miniscule .
- Donner une fonction qui lit une phrase au clavier caractere par caractere sur une seule ligne puis transformer : 
    * le minus en Majus
    * le Majus en minus
    * ' ' en \BL
    * une tabulation en \TAB
*/
// Declaration dees bibliotheques
#include<stdio.h>
#include<stdlib.h>
// Declaration des constantes
#define RC '\n'
// Prototype
char minusToMajus(char c);
char MajusTominus(char c);
int NatureChar(char c);
void transformation();
// Programme principale
void main()
{
    transformation(); // Appel de la fonction transformation()
}
// la fonction qui recoit un caractere alphabetique miniscule et le retourne en Majuscule
char minusToMajus(char c)
{
    return ((char)('A'+c-'a'));
}
// le fonction qui recoit un caractere alphabetique Majuscule et le retourne en miniscule
char MajusTominus(char c)
{
    return ((char)('a'+c-'A'));
}
// fonction qui retourne un entier selon la nature du caractere en parametre
int Nature(char c)
{
    if (('a'<=c) && (c<='z')) return ((int)1); // si le caractere est un miniscule
    if (('A'<=c) && (c<='Z')) return ((int)2); // si le caractere est un majuscule
    if (c == ' ') return ((int)3); // si le caractere est un blanc
    if (c == '\t') return ((int)4); // si le caractere est une tabulation
    return ((int)5); // si le caractere n'est ni un alphabet, ni un blanc et ni une tabulation
}
// fonction qui transfome des caracteres d'une phrase
void transformation()
{
    char c;
    int nature;
    while ((c = getchar())!=RC)
    {
        nature = Nature(c); // Appel a la fonction nature qui retoune la nature du caractere passer en parametre
        switch (nature)
        {
        case 1:
            printf("%c",minusToMajus(c)); // Appel de la fonction minusToMajus
            break;
        case 2: 
            printf("%c",MajusTominus(c)); // Appel de la fonction MajusTominus
            break;  
        case 3: 
            printf("\\BL");
            break;
        case 4:
            printf("\\TAB");      
        case 5:
            printf("%c",c);
            break;
        }
    }
}