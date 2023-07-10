#include <stdio.h>
#include <stdlib.h>

#include "fncts.h"

int DFSRecursif(Matrice *M, int a, int etat[MAX])
{
  etat[a] = 1;
  int nbCycle = 0;
  for (int i = 0; i < M->n; i++)
  {
    for (int j = i + 1; j < M->n; j++)
    {
      if (M->matrice[i][j])
      {
        if (!etat[j])
          nbCycle += DFSRecursif(M, j, etat);
        else
          nbCycle++;
        if (!etat[i])
          nbCycle += DFSRecursif(M, i, etat);
        else
          nbCycle++;
      }
    }
  }
  return ((int)nbCycle);
}

int DFS(Matrice *M)
{
  if (!M)
    return ((int)-1);
  int etat[MAX];
  for (int i = 0; i < M->n; etat[i++] = 0)
    ;
  return ((int)DFSRecursif(M, 0, etat));
}

int countChains(Matrice *M, int visited[MAX], int start, int length)
{
  if (length == 0)
    return 1; // La chaîne de longueur 5 est complétée, renvoie 1

  visited[start] = 1; // Marquer le sommet comme visité

  int count = 0;
  for (int i = 0; i < M->n; i++)
  {
    if (M->matrice[start][i] && !visited[i])
      count += countChains(M, visited, i, length - 1);
  }

  visited[start] = 0; // Remettre à zéro le marquage du sommet

  return count;
}

void main()
{
  Matrice *M = remplirMatrice("graphe1.txt");
  int nb = DFS(M);
  printf("\nle nombre de cycle dans le graphe est : %d", nb);

  int nbChaineSimple = 0;

  int visited[MAX];

  for (int i = 0; i < MAX; visited[i++] = 0)
    ;

  for (int i = 0; i < M->n; i++)
    nbChaineSimple += countChains(M, visited, i, 5);

  printf("\nle nombre de chaine de longueur 5 est : %d", nbChaineSimple);
}