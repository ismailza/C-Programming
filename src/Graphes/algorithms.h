
#include "fncts.h"

// Prototyping
int DFS(Matrice *, int, int[MAX]);
int BFS(Matrice *, int, int[MAX]);
int DFSR(Matrice *, int, int);
int detecterCircuit(Matrice *);

/********************************************************************************
| Nom     : DFS;
| Entrees : Matrice * : la structure de la matrice
|           int       : sommet de depart
| Sorties : int [MAX] : tableau des sommets atteignables par le sommet de depart
|           int       : 0 si le sommet de deppart est incorrect, 1 sinon
| La fonction permet de determiner tous les sommets atteignables depuis un sommet
| de depart donne par un parcours en profond
*/
int DFS(Matrice *M, int s, int stat[MAX])
{
  if (!M) // matrice n'existe pas
  {
    printf("\nErreur : matrice n'existe pas!");
    exit(0);
  }
  if (s < 0 && M->n <= s)
    return ((int)0);
  int i, x;
  Cellule *pile = NULL; // pile des sommets a visiter
  // initialisation de tableau des sommets marques
  for (i = 0; i < M->n; stat[i++] = 0)
    ;
  stat[s] = 1;
  pile = Empiler(pile, s);
  do
  {
    pile = Depiler(pile, &x);
    for (i = 0; i < M->n; i++)
    {
      if (M->matrice[x][i] && !stat[i])
      {
        stat[i] = 1;
        pile = Empiler(pile, i);
      }
    }
  } while (pile);
  return ((int)1);
}
/********************************************************************************
| Nom     : BFS;
| Entrees : Matrice * : la structure de la matrice
|           int       : sommet de depart
| Sorties : int [MAX] : tableau des sommets atteignables par le sommet de depart
|           int       : 0 si le sommet de deppart est incorrect, 1 sinon
| La fonction permet de determiner tous les sommets atteignables depuis un sommet
| de depart donne par un parcours en largeur
*/
int BFS(Matrice *M, int s, int stat[MAX])
{
  if (!M) // matrice n'existe pas
  {
    printf("\nErreur : matrice n'existe pas!");
    exit(0);
  }
  if (s < 0 && M->n <= s)
    return ((int)0);
  int i, x, rt;
  File *file = CreerFile(); // file des sommets a visiter
  // initialisation de tableau des sommets marques
  for (i = 0; i < M->n; stat[i++] = 0)
    ;
  stat[s] = 1;
  rt = Enfiler(file, s);
  do
  {
    rt = Defiler(file, &x);
    for (i = 0; i < M->n; i++)
    {
      if (M->matrice[x][i] && !stat[i])
      {
        stat[i] = 1;
        rt = Enfiler(file, i);
      }
    }
  } while (file->tete);
  return ((int)1);
}

void DFSRecursifPrefixe(Matrice *M, int a, int stat[MAX])
{
  stat[a] = 1;
  printf("%d\t", a + 1);
  for (int i = 0; i < M->n; i++)
  {
    if (M->matrice[a][i] && !stat[i])
      DFSRecursifPrefixe(M, i, stat);
  }
}
void DFSRecursifSufixe(Matrice *M, int a, int stat[MAX])
{
  stat[a] = 1;
  for (int i = 0; i < M->n; i++)
  {
    if (M->matrice[a][i] && !stat[i])
      DFSRecursifSufixe(M, i, stat);
  }
  printf("%d\t", a + 1);
}

int DFSR(Matrice *M, int s, int ps)
{
  if (!M)
  {
    printf("\nErreur : Matrice n'existe pas!");
    exit(0);
  }
  if (s < 0 && M->n <= s)
    return ((int)0);
  int stat[MAX];
  for (int i = 0; i < M->n; stat[i++] = 0)
    ;
  if (ps == 1)
    DFSRecursifPrefixe(M, s, stat);
  else if (ps == 2)
    DFSRecursifSufixe(M, s, stat);
}

int visiter(Matrice *M, int a, int visite[MAX], int critic[MAX])
{
  visite[a] = 1;
  if (critic[a])
    return ((int)1);
  // Marquer le sommet courant dans la liste critique
  critic[a] = 1;
  for (int i = 0; i < M->n; i++)
  {
    if (M->matrice[a][i])
      if (visiter(M, i, visite, critic))
        return ((int)1);
  }
  critic[a] = 0;
  return ((int)0);
}

int detecterCircuit(Matrice *M)
{
  if (!M)
    return ((int)-1);
  int i, visite[MAX], critic[MAX];
  for (i = 0; i < M->n; i++)
    visite[i] = critic[i] = 0;
  for (i = 0; i < M->n; i++)
    if (visiter(M, i, visite, critic))
      return ((int)1);
  return ((int)0);
}
