#include <stdio.h>
#include <stdlib.h>

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

Cellule *Empiler(Cellule *pile, int n)
{
  Cellule *NE = CreerCellule(n);
  if (pile)
    NE->svt = pile;
  return ((Cellule *)NE);
}

Cellule *Depiler(Cellule *pile, int *n)
{
  Cellule *ptr = pile;
  if (pile)
  {
    *n = pile->n;
    ptr = pile;
    pile = pile->svt;
    free(ptr);
  }
  return ((Cellule *)pile);
}

void Chemin_s_t(int s, int t, Matrice *M)
{
  if (!M) // test d'existance de la matrice
  {
    printf("\nErreur : matrice n'existe pas !");
    exit(0);
  }
  // tester le sommet de depart et d'arrive s'ils sont corrects
  if ((s <= 0 || M->n < s) || (t <= 0 || M->n < t))
  {
    printf("\nErreur : sommet n'existe pas !");
    return;
  }
  s--;
  t--; // pour faciliter l'acces a la matrice
  int x, i;
  Cellule *pile = NULL; // la pile des sommets a visiters
  int m[M->n];          // tableau des sommets marques
  for (i = 0; i < M->n; m[i++] = -1)
    ;                      // initialisation du tableau m
  pile = Empiler(pile, s); // inserer le sommet de depart dans la pile
  // tant que la pile est non vide et le sommet d'arrive est non marque
  while (pile && m[t] == -1)
  {
    pile = Depiler(pile, &x);  // depiler et recuperer la tete de la pile
    for (i = 0; i < M->n; i++) // pour tout sommet
    {                          // si le sommet 'i' est un successeur de 'x' et non marque
      if (M->matrice[x][i] && m[i] == -1)
      {
        m[i] = x;                // marque le sommet 'i'
        pile = Empiler(pile, i); // empiler 'i' dans la pile
      }
    }
  }
  // si le sommet d'arrive n'est pas marque alors le chemin n'existe pas
  if (m[t] == -1)
    printf("\nPas de chemin de %d a %d", s + 1, t + 1);
  else
  { // Affichage de chemin dans l'ordre inverse
    printf("\nChemin de %d a %d dans l'ordre inverse : ", s + 1, t + 1);
    for (i = t; i != s; i = m[i])
      printf("%d -> ", i + 1);
    printf("%d", s + 1);
  }
}

void main()
{
  Matrice *M = remplirMatrice("graphe.txt");
  int s, t;
  printf("\nSommet de depart : ");
  scanf("%d", &s);
  printf("\nSommet d'arriver : ");
  scanf("%d", &t);
  Chemin_s_t(s, t, M);
}