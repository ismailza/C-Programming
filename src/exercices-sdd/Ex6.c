/* Lire une suite de caractere numerique puis retoure le nombre equivalent */
// declaration des bibliotheques
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// Declaration des constante
#define RC '\n'
// Prototype
int Transforme();
int EstNumerique(char c);
// Programme principale
int main()
{
    int a = Transforme();
    printf("\nl'entier extrait de la chaine numerique est : %f",a);
    return 0;
}
// la fonction qui retourn l'entier equivalent d'une suite de caractere numerique
int Transforme()
{
    char c;
    int control; // pour stocker la valeur retournee par la fonction "EstNumerique"
    int firstPass = 1; // pour tester la premiere lecture 
    int signe = 1; // pour stocker le signe du nombre
    int result = 0; // pour stocker le nombre extrait
    printf("\nEntrer une chaine numerique : "); 
    while ((c = getchar())!= RC)
    {
        if(firstPass == 1){ // Lors de la lecture du premier caractere
            firstPass = 0; // pour indiquer qu'on a lu le premier caractere
            if ((c == '-') || (c == '+'))
            {   // recuperer le signe du nombre
                if (c == '-')
                    signe = -1; 
                continue; // passer a l'iteration suivante
            }        
        }
        control = EstNumerique(c); 
        switch (control)
        {
            case -1:
                printf("\nErreur: caractere non numerique!");
                exit(0);  
            case 11:
                return ((int)(result*signe));  
            default:
                result = result*10 + (int)control;
        }
    }
    return ((int)(result*signe));
}
// fonction qui test le caractere en parametre s'il est numerique
int EstNumerique(char c)
{
    if(('0'<=c) && (c<='9')) // le caractere est un nombre
        return ((int)(c-'0'));
    if(c == ' ') // le caractere est un blanc
        return ((int)11);
    return ((int)(-1)); // sinon
}