/*
| TP4 : Algorithme de Bellman-Ford pour la recherche du plus court chemin dans un graphe

*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 20            // * Nombre max du sommet
#define GRAPHE "TP4.txt"  // * nom du fichier contient la matrice du graphe
// * Structure d'une liste
typedef struct CL
{
  int n;                // * le sommet
  int c;                // * le poids
  struct CL *svt;       // * pointeur sur le suivant
} Cellule;
// * Structure de la table de liste d'ajacence
typedef struct
{
  int n;                // * nombre de sommets
  Cellule *liste[MAX];  // * les listes d'adjacence
} TableLists;

/********************************************************************************
| Nom     : CreerCellule;
| Entrees : int       : le sommet
|           int       : le poids
| Sorties : Cellule * : la structure de la cellule initialisee
| La fonction permet d'allouer un espace memoire pour la structure de la cellule 
| et d'initialiser ses champs
*/
Cellule *CreerCellule (int n, int c)
{
  Cellule *N = (Cellule *)malloc(sizeof(Cellule));
  if (!N)
  {
    printf("\nErreur d'allocation memoire !");
    exit(0);
  }
  N->n = n;
  N->c = c;
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
TableLists *CreerTableLists (int n)
{
    TableLists *L = (TableLists *)malloc(sizeof(TableLists));
    if (!L)
    {
        printf("\nErreur d'allocation memoire !");
        exit(0);
    }
    L->n = n;
    for (int i = 0; i < n; i++) L->liste[i] = NULL;
    return ((TableLists *)L);
}
/********************************************************************************
| Nom     : Bellman_Ford_Algorithm;
| Entrees : TableLists * : table des listes d'adjacence du graphe
|           int          : le sommet de depart
|           int          : tableau pour enregistrer les plus court chemins
| Sorties : int          : indique si le graphe contient un circuit absorbant
| La fonction permet de trouver le plus court chemin d'un sommet donnee vers tous
| les autres sommets.
*/
int Bellman_Ford_Algorithm (TableLists *lists, int a, int paths[2][lists->n])
{
  if (!lists) return ((int)-1);                       // * Test d'existance
  if ((a < 0) || (lists->n <= a)) return ((int)-2);   // * sommet incorrect
  int i, j;
  Cellule *ptr;
  // * Initialisation 
  for (i = 0; i < lists->n; i++) 
  {
    paths[0][i] = -1;       // * indique le sommet anterieur
    paths[1][i] = INT_MAX;  // * indique le poids de l'arc (paths[0][i] i)
  }
  // * Initialiser le sommet de depart
  paths[0][a] = -2;
  paths[1][a] = 0;          
  // * Repeter |X|-1 fois
  for (i = 0; i < lists->n-1; i++)
  { // * Pour tout arc (u,v) de U
    for (j = 0; j < lists->n; j++)
    { 
      ptr = lists->liste[j];
      while (ptr)
      {
        if ((paths[1][j] + ptr->c) < paths[1][ptr->n])
        {
          paths[0][ptr->n] = j;
          paths[1][ptr->n] = paths[1][j] + ptr->c;
        }
        ptr = ptr->svt;
      }
    }
  } 
  // * Pour tout (u,v) de U
  for (i = 0; i < lists->n; i++)
  {
    ptr = lists->liste[i];
    while (ptr)
    {
      if ((paths[1][i] + ptr->c) < paths[1][ptr->n]) return ((int)0);
      ptr = ptr->svt; 
    }
  }
  return ((int)1);
}
/********************************************************************************
| Nom     : Inserer_Fin_Liste;
| Entrees : Cellule * : la liste ou on veut inserer
|         : int       : le sommet a inserer 
|           int       : le poids 
| Sorties : Cellule * : la liste apres l'insertion
| la fonction permet d'inserer un entier donne a la fin d'une liste donnee
*/
Cellule *Inserer_Fin_Liste (Cellule *liste, int n, int c)
{
  if (!liste) return ((Cellule *)CreerCellule(n, c));
  Cellule *ptr = liste;
  while (ptr->svt) ptr = ptr->svt;
  ptr->svt = CreerCellule(n, c);
  return ((Cellule *)liste);
}
/********************************************************************************
| Nom     : remplirTableLists;
| Entrees : char *       : le nom du fichier qui contient la matrice d'adjacence
| Sorties : TableLists * : la table de listes
| La fonction permet de construire une table de listes d'adjacence d'un graphe 
| lue a partir d'un fichier texte
*/
TableLists *remplirTableLists (char *filename)
{
  int n = 0, i, j, x;
  TableLists *L;
  // ouvrir le fichier qui contient la matrice d'adjacence
  FILE *file = fopen(filename, "r");  
  if (!file)  // si le fichier n'est pas ouvert
  {
    printf("\nErreur lors de l'ouverture du fichier \"%s\" !",filename);
    exit(0);
  }
  if (!feof(file)) fscanf(file, "%d", &n); // lire le nombre de sommets 
  L = CreerTableLists(n);
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n && !feof(file); j++)
    {
      fscanf(file, "%d", &x);
      if (x) L->liste[i] = Inserer_Fin_Liste(L->liste[i], j, x);
    }
  }
  fclose(file);                           // fermer le fichier
  return ((TableLists *)L);
}
/********************************************************************************
| Nom     : AfficherListe;
| Entrees : Cellule * : une liste
| la fonction permet d'afficher une liste donnee
*/
void AfficherListe (Cellule *liste)
{
  Cellule *ptr = liste;
  while (ptr)
  {
    printf("%d(%d) ",ptr->n+1, ptr->c);
    ptr = ptr->svt;
  }
}
/********************************************************************************
| Nom     : AfficherTableLists;
| Entrees : TableLists * : une table de listes
| la fonction permet d'afficher une table de listes
*/
void AfficherTableLists (TableLists *L)
{
  if (!L)
  {
    printf("\nErreur : Liste d'adjacence n'existe pas");
    exit(0);
  }
  for (int i = 0; i < L->n; i++)
  {
    printf("\n\t%d : ", i+1);
    AfficherListe(L->liste[i]);
  }
}
// * Programme principal
void main ()
{
  int s, rt, i;
  printf("\nTable de listes d'adjacence initiales : ");
  TableLists *L = remplirTableLists(GRAPHE);
  AfficherTableLists(L);

  printf("\nAlgorithme de Bellman Ford");
  printf("\nLe sommet de depart : ");
  scanf("%d",&s);
  int paths[2][L->n];
  rt = Bellman_Ford_Algorithm(L, s-1, paths);
  switch (rt)
  {
    case -2: printf("\nSommet de depart incorrect"); break;
    case -1: printf("\nErreur : liste n'existe pas"); break;
    case  0: printf("\nLe graphe contient un circuit absorbant"); break;
    case  1: 
      for (i = 0; i < L->n; i++) printf("\n%d -> %d : %d", i+1, paths[0][i]+1, paths[1][i]);
  }
}