/*
|   TP0 : Representation d'un graphe oriente G = (X,U) avec une matrice d'adjacence
|         et une table de listes d'adjacence.
|         Les informations du graphe sont lues a partir d'un fichier texte.
|         On suppose que les sommets de X sont numerotes de 1 a n, avec n = |X|.
|   Realiser par : ZAHIR Ismail
*/
#include <stdio.h>
#include <stdlib.h>

// Nom du fichier texte qui contient les information du graphe
#define FILE_NAME "graphe.txt"
// le nombre maximal de sommets de la matrice
#define MAX 25
// Structure de la matrice d'adjacence
typedef struct
{
  int n;                 // nombre de sommets
  int matrice[MAX][MAX]; // la matrice
} Matrice;
// Structure d'une cellule
typedef struct ND
{
  int n;          // la valeur
  struct ND *svt; // pointeur vers la suivante
} Cellule;
// Structure d'une table de listes d'adjacences
typedef struct
{
  int n;
  Cellule *liste[MAX];
} TableLists;

/********************************************************************************
| Nom     : CreerMatrice;
| Entrees : int       : le nombre de sommets de la matrice
| Sorties : Matrice * : la structure de la matrice
| La fonction permet d'allouer un espace memoire pour la structure de la matrice
*/
Matrice *CreerMatrice(int n)
{
  Matrice *m = (Matrice *)malloc(sizeof(Matrice));
  if (!m)
  {
    printf("\nErreur d'allocation memoire !");
    exit(0);
  }
  m->n = n;
  return ((Matrice *)m);
}
/********************************************************************************
| Nom     : CreerCellule;
| Entrees : int       : la valeur de la cellule
| Sorties : Cellule * : la structure de la cellule initialisee
| La fonction permet d'allouer un espace memoire pour la structure de la cellule
| et d'initialiser ses champs
*/
Cellule *CreerCellule(int n)
{
  Cellule *N = (Cellule *)malloc(sizeof(Cellule));
  if (!N)
  {
    printf("\nErreur d'allocation memoire !");
    exit(0);
  }
  N->n = n;
  N->svt = NULL;
  return ((Cellule *)N);
}
/********************************************************************************
| Nom     : CreerTableLists;
| Entrees : int          : le nombre de sommets
| Sorties : TableLists * : la table des listes d'adjacence initialisees
| La fonction permet d'allouer un espace memoire pour la structure de la table
| des listes et de l'initialiser
*/
TableLists *CreerTableLists(int n)
{
  TableLists *L = (TableLists *)malloc(sizeof(TableLists));
  if (!L)
  {
    printf("\nErreur d'allocation memoire !");
    exit(0);
  }
  L->n = n;
  for (int i = 0; i < n; i++)
    L->liste[i] = NULL;
  return ((TableLists *)L);
}
/********************************************************************************
| Nom     : remplirMatrice;
| Entrees : char *    : le nom du fichier qui contient la matrice d'adjacence
| Sorties : Matrice * : la matrice d'adjacence
| La fonction permet de lire la matrice d'adjacence a partir d'un fichier texte
| et la mettre dans une structure Matrice
*/
Matrice *remplirMatrice(char *filename)
{
  int n = 0, i, j;
  Matrice *M;
  // ouvrir le fichier qui contient la matrice d'adjacence
  FILE *file = fopen(filename, "r");
  if (!file) // si le fichier n'est pas ouvert
  {
    printf("\nErreur lors de l'ouverture du fichier \"%s\" !", filename);
    exit(0);
  }
  if (!feof(file))
    fscanf(file, "%d", &n); // lire le nombre de sommets
  M = CreerMatrice(n);      // creer la structure de la matrice
  for (i = 0; i < n; i++)   // remplir la matrice a partir du fichier
  {
    for (j = 0; j < n && !feof(file); j++)
      fscanf(file, "%d", &M->matrice[i][j]);
  }
  fclose(file); // fermer le fichier
  return ((Matrice *)M);
}
/********************************************************************************
| Nom     : AfficherMatrice;
| Entrees : Matrice * : une matrice d'adjacence
| la fonction permet d'afficher une matrice d'adjacence
*/
void AfficherMatrice(Matrice *M)
{
  if (!M)
  {
    printf("\nErreur : matrice n'existe pas");
    exit(0);
  }
  for (int i = 0; i < M->n; i++)
  {
    printf("\n\t");
    for (int j = 0; j < M->n; j++)
      printf("%d ", M->matrice[i][j]);
  }
}
/********************************************************************************
| Nom     : Inserer_Fin_Liste;
| Entrees : Cellule * : la liste ou on veut inserer
|         : int       : l'entier a inserer
| Sorties : Cellule * : la liste apres l'insertion
| la fonction permet d'inserer un entier donne a la fin d'une liste donnee
*/
Cellule *Inserer_Fin_Liste(Cellule *liste, int n)
{
  if (!liste)
    return ((Cellule *)CreerCellule(n));
  Cellule *ptr = liste;
  while (ptr->svt)
    ptr = ptr->svt;
  ptr->svt = CreerCellule(n);
  return ((Cellule *)liste);
}
/********************************************************************************
| Nom     : remplirTableLists;
| Entrees : char *       : le nom du fichier qui contient la matrice d'adjacence
| Sorties : TableLists * : la table de listes
| La fonction permet de construire une table de listes d'adjacence d'un graphe
| lue a partir d'un fichier texte
*/
TableLists *remplirTableLists(char *filename)
{
  int n = 0, i, j, x;
  TableLists *L;
  // ouvrir le fichier qui contient la matrice d'adjacence
  FILE *file = fopen(filename, "r");
  if (!file) // si le fichier n'est pas ouvert
  {
    printf("\nErreur lors de l'ouverture du fichier \"%s\" !", filename);
    exit(0);
  }
  if (!feof(file))
    fscanf(file, "%d", &n); // lire le nombre de sommets
  L = CreerTableLists(n);
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n && !feof(file); j++)
    {
      fscanf(file, "%d", &x);
      if (x)
        L->liste[i] = Inserer_Fin_Liste(L->liste[i], j);
    }
  }
  fclose(file); // fermer le fichier
  return ((TableLists *)L);
}
/********************************************************************************
| Nom     : AfficherListe;
| Entrees : Cellule * : une liste
| la fonction permet d'afficher une liste donnee
*/
void AfficherListe(Cellule *liste)
{
  Cellule *ptr = liste;
  while (ptr)
  {
    printf("%d ", ptr->n + 1);
    ptr = ptr->svt;
  }
}
/********************************************************************************
| Nom     : AfficherTableLists;
| Entrees : TableLists * : une table de listes
| la fonction permet d'afficher une table de listes
*/
void AfficherTableLists(TableLists *L)
{
  if (!L)
  {
    printf("\nErreur : Liste d'adjacence n'existe pas");
    exit(0);
  }
  for (int i = 0; i < L->n; i++)
  {
    printf("\n\t%d : ", i + 1);
    AfficherListe(L->liste[i]);
  }
}

void main()
{
  printf("\nLa matrice d'adjacence : ");
  Matrice *M = remplirMatrice(FILE_NAME);
  AfficherMatrice(M);
  printf("\nLa table de listes d'adjacence : ");
  TableLists *L = remplirTableLists(FILE_NAME);
  AfficherTableLists(L);
}