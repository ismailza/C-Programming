#include <stdio.h>
#include <stdlib.h>

#define N 6 // Taille du tableau

// 1. Affichage de l'échiquier
void imprime(unsigned char echiquier[N][N])
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
      printf("%d\t", echiquier[i][j]);
    printf("\n");
  }
}

// 2. Calcul du nombre de voisins à 1 d'une case
int nbVoisins(unsigned char echiquier[N][N], int i, int j)
{
  if ((i < 0) || (i >= N) || (j < 0) || (j >= N))
    return -1;
  int nb = 0;
  if (i > 0)
    nb += echiquier[i - 1][j];
  if (i < N - 1)
    nb += echiquier[i + 1][j];
  if (j > 0)
    nb += echiquier[i][j - 1];
  if (j < N - 1)
    nb += echiquier[i][j + 1];
  return nb;
}

// 3. Initialisation de la bordure du tableau
void configInit(unsigned char echiquier[N][N])
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    echiquier[i][0] = 0;
    echiquier[i][N - 1] = 0;
  }
  for (j = 0; j < N; j++)
  {
    echiquier[0][j] = 0;
    echiquier[N - 1][j] = 0;
  }
}

// 4. Calcul de la nouvelle valeur d'une case
int estVivante(unsigned char echiquier[N][N], int i, int j)
{
  int nb = nbVoisins(echiquier, i, j);
  if (nb == -1)
    return -1;
  if ((nb == 0) || (nb == 4))
    return 0;
  if ((nb == 2) || (nb == 3))
    return 1;
  return echiquier[i][j];
}

// 5. Calcul de la nouvelle configuration de l'échiquier
void changeEtat(unsigned char echiquier[N][N])
{
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      echiquier[i][j] = estVivante(echiquier, i, j);
}
