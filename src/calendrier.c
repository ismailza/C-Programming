#include <stdio.h>
#include <stdlib.h>

#define MOD7(v) v % 7
#define MOD4(v) v % 4
#define DIV4(v) v / 4
// la date reference "Le Mardi 1-1-1901"
#define JR 1
#define MR 1
#define AR 1901

/* ****************************************************************************
| Est_Bessixtile
| Entrées : int a - L'année à tester
| Sorties : int - 1 si l'année est bissextile, 0 sinon
| La fonction permet de déterminer si une année est bissextile.
*/
int Est_Bessixtile(int a)
{
  if (a % 100 == 0 && a % 400 != 0) return ((int)0);
  return ((int)(MOD4(a) == 0 ? 1 : 0));
}
/* ****************************************************************************
| nb_jours_des_annees
| Entrées : int a - L'année
| Sorties : int - Le nombre de jours écoulés depuis l'année de référence (1901)
| La fonction permet de calculer le nombre de jours écoulés depuis l'année de référence.
*/
int nb_jours_des_annees(int a)
{
  int l = a - AR;
  return ((int)(365 * l + DIV4(l)));
}
/* ****************************************************************************
| nb_jours_dans_annee
| Entrées : int m - Le mois
|           int a - L'année
| Sorties : int - Le nombre de jours dans l'année jusqu'au mois donné
| La fonction permet de calculer le nombre de jours dans l'année jusqu'au mois donné.
*/
int nb_jours_dans_annee(int m, int a)
{
  int nbjours = 0;
  switch (m - 1)
  {
  case 11: nbjours += 30;
  case 10: nbjours += 31;
  case 9: nbjours += 30;
  case 8: nbjours += 31;
  case 7: nbjours += 31;
  case 6: nbjours += 30;
  case 5: nbjours += 31;
  case 4: nbjours += 30;
  case 3: nbjours += 31;
  case 2: nbjours += 28 + Est_Bessixtile(a);
  case 1: nbjours += 31;
  }
  return ((int)nbjours);
}
/* ****************************************************************************
| nb_jours_dans_mois
| Entrées : int j - Le jour
| Sorties : int - Le nombre de jours écoulés dans le mois donné
| La fonction permet de calculer le nombre de jours écoulés dans le mois donné.
*/
int nb_jours_dans_mois(int j)
{
  return ((int)(j - 1));
}
/* ****************************************************************************
| nb_jours
| Entrées : int j - Le jour
|           int m - Le mois
|           int a - L'année
| Sorties : int - Le nombre total de jours écoulés depuis l'année de référence
| La fonction permet de calculer le nombre total de jours écoulés depuis l'année de référence
| jusqu'à la date donnée.
*/
int nb_jours(int j, int m, int a)
{
  return ((int)nb_jours_des_annees(a) + nb_jours_dans_annee(m, a) + nb_jours_dans_mois(j));
}
/* ****************************************************************************
| controle_des_donnees
| Entrées : int j - Le jour
|           int m - Le mois
|           int a - L'année
| Sorties : int - Code de contrôle indiquant la validité de la date
| La fonction permet de vérifier si une date est valide et renvoie un code de contrôle correspondant.
*/
int controle_des_donnees(int j, int m, int a)
{
  int joursMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((a < 1901) || (a > 2099)) return ((int)-1);
  if ((m < 1) || (m > 12)) return ((int)-2);
  joursMois[1] += Est_Bessixtile(a);
  if ((j < 1) || (j > joursMois[m - 1])) return ((int)-3);
  return ((int)1);
}
/* ****************************************************************************
| lecture_donnees
| Entrées : int* j - Pointeur vers la variable du jour
|           int* m - Pointeur vers la variable du mois
|           int* a - Pointeur vers la variable de l'année
| Sorties : Aucune
| La fonction permet de lire les données de la date depuis l'entrée standard
| et effectue une boucle de saisie tant que la date n'est pas valide.
*/
void lecture_donnees(int *j, int *m, int *a)
{
  do
  {
    printf("\nEntrer la date :");
    printf("\nJour  : ");
    scanf("%d", j);
    printf("\nMois  : ");
    scanf("%d", m);
    printf("\nAnnee : ");
    scanf("%d", a);
  } while (controle_des_donnees(*j, *m, *a) != 1);
}
/* ****************************************************************************
| date
| Entrées : Aucune
| Sorties : Aucune
| La fonction permet de demander la saisie d'une date valide, puis affiche le jour correspondant.
*/
void date()
{
  int j, m, a, rt;
  lecture_donnees(&j, &m, &a);
  rt = controle_des_donnees(j, m, a);
  switch (rt)
  {
  case -1:
    printf("\nAnnée non valide");
    break;
  case -2:
    printf("\nMois non valide");
    break;
  case -3:
    printf("\nJours non valide");
    break;
  default:
    rt = nb_jours(j, m, a);
    printf("\nLe jours correspond a la date %2d/%2d/%d est le ", j, m, a);
    switch (MOD7(rt))
    {
    case 0:
      printf("Mardi");
      break;
    case 1:
      printf("Mercredi");
      break;
    case 2:
      printf("Jeudi");
      break;
    case 3:
      printf("Vendredi");
      break;
    case 4:
      printf("Samdi");
      break;
    case 5:
      printf("Dimanche");
      break;
    case 6:
      printf("Lundi");
      break;
    }
  }
}

void main()
{
  date();
}