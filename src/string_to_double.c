/* Lire une suite de caractere numerique puis retoure le nombre equivalent */
// declaration des bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Declaration des constante
#define RC '\n'

/* ****************************************************************************
| EstNumerique
| Entrées : char c - Le caractère à tester
| Sorties : int - Le code de contrôle correspondant au caractère
| La fonction permet de vérifier si un caractère est numérique,
| et renvoie un code de contrôle correspondant.
*/
int EstNumerique(char c)
{
  if (('0' <= c) && (c <= '9')) return ((int)(c - '0'));
  if (c == ' ') return 11;
  if (c == '.') return 12;
  return -1;
}

/* ****************************************************************************
| Transforme
| Entrées : Aucune
| Sorties : double - Le nombre équivalent à la suite de caractères numériques
| La fonction permet de lire une suite de caractères numériques depuis l'entrée standard,
| puis retourne le nombre équivalent.
*/
double Transforme()
{
  char c;
  int control;
  int firstPass = 1;
  int f = 0;
  int signe = 1;
  double result = 0;
  printf("\nEntrer une chaine numerique : ");
  while ((c = getchar()) != RC)
  {
    if (firstPass)
    {
      firstPass = 0;
      if ((c == '-') || (c == '+'))
      {
        if (c == '-') signe = -1;
        continue;
      }
    }
    control = EstNumerique(c);
    switch (control)
    {
    case -1:
      printf("\nErreur: caractere non numerique!");
      exit(0);
    case 11:
      return result * signe;
    case 12:
      if (f == 0)
      {
        f = -1;
        break;
      }
      printf("\nErreur: un autre point est tape!");
      exit(0);
    default:
      if (f == 0) result = result * 10 + (double)control;
      else result += (double)control * pow(10, f--);
    }
  }
  return ((double)(result * signe));
}

int main()
{
  double a = Transforme();
  printf("\nle reel extrait de la chaine numerique est : %f", a);
  return 0;
}
