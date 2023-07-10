#include <stdio.h>
#include <stdlib.h>

// Le nombre maximal de sommets de la matrice
#define MAX 25
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

int Est_Existe_Liste(Cellule *liste, int n)
{
  Cellule *ptr = liste;
  while (ptr)
  {
    if (ptr->n == n)
      return ((int)1);
    ptr = ptr->svt;
  }
  return ((int)0);
}

Cellule *Intersection_2_Listes(Cellule *liste1, Cellule *liste2)
{
  if (!liste1 || !liste2)
    return ((Cellule *)NULL);
  Cellule *ptr1 = liste1, *ptr2, *liste = NULL;
  while (ptr1)
  {
    ptr2 = liste2;
    while (ptr2)
    {
      if (ptr1->n == ptr2->n)
      {
        liste = Inserer_Fin_Liste(liste, ptr1->n);
        break;
      }
      ptr2 = ptr2->svt;
    }
    ptr1 = ptr1->svt;
  }
  return ((Cellule *)liste);
}

Cellule *Substrct_2_Ordered_Lists(Cellule *liste1, Cellule *liste2)
{
  if (!liste1)
    return ((Cellule *)NULL);
  if (!liste2)
    return ((Cellule *)liste1);
  Cellule *ptr1 = liste1, *ptr2 = liste2, *ptr = NULL, *del;
  while (ptr1 && ptr2)
  {
    if (ptr1->n == ptr2->n)
    {
      del = ptr1;
      ptr1 = ptr1->svt;
      if (!ptr)
        liste1 = ptr1;
      else
        ptr->svt = ptr1;
      free(del);
      ptr2 = ptr2->svt;
      continue;
    }
    if (ptr1->n < ptr2->n)
    {
      ptr = ptr1;
      ptr1 = ptr1->svt;
    }
    else
      ptr2 = ptr2->svt;
  }
  return ((Cellule *)liste1);
}

Cellule *Trier_Liste(Cellule *liste)
{
  if (!liste)
    return ((Cellule *)NULL);
  Cellule *ptr1, *ptr2; // pointeurs pour le parcours la liste
  int tmp;
  ptr1 = liste->svt;
  while (ptr1)
  {
    ptr2 = liste;
    while (ptr2 != ptr1)
    {
      if (ptr2->n > ptr1->n)
      {
        tmp = ptr1->n;
        ptr1->n = ptr2->n;
        ptr2->n = tmp;
      }
      ptr2 = ptr2->svt;
    }
    ptr1 = ptr1->svt;
  }
  return (Cellule *)liste;
}

Cellule *CFC_a(TableLists *L, Cellule *X, int a)
{
  Cellule *X_plus = NULL, // X+ : liste des sommets atteindent par a
      *X_moins = NULL,    // X- : liste des sommets qui atteindent a
      *X_prime,           // X' : la composante fortement connexe
      *ptr, *ptrX;        // pointeur pour le parcours des listes
  int i;
  if (!L || !X) // si la matrice n'existe pas ou l'ensemble des sommets est vide
  {
    printf("\nErreur : matrice n'existe pas !");
    exit(0);
  }
  if (a < 0 || L->n <= a) // si le sommet n'est pas correct
  {
    printf("\nErreur : sommet %d n'existe pas !", a + 1);
    return ((Cellule *)NULL);
  }
  int m[L->n];                           // tableau des sommets marques
  X_plus = Inserer_Fin_Liste(X_plus, a); // initialiser X+ par 'a'
  for (i = 0; i < L->n; m[i++] = 0)
    ;       // initialisation du tableau m
  m[a] = 1; // marquer le sommet 'a'
  ptr = X_plus;
  while (ptr)
  {
    ptrX = L->liste[ptr->n];
    while (ptrX)
    {
      if (Est_Existe_Liste(X, ptrX->n) && !m[ptrX->n])
      { // on insere l'extrimite terminale dans X_plus
        X_plus = Inserer_Fin_Liste(X_plus, ptrX->n);
        m[ptrX->n] = 1;
      }
      ptrX = ptrX->svt; // le sommet successeur suivant
    }
    ptr = ptr->svt;
  }
  X_moins = Inserer_Fin_Liste(X_moins, a); // initialiser X- par 'a'
  for (i = 0; i < L->n; m[i++] = 0)
    ;       // re-initialisation du tableau m
  m[a] = 1; // marquer le sommet 'a'
  ptr = X_moins;
  while (ptr)
  {
    for (i = 0; i < L->n; i++)
    {
      ptrX = L->liste[i];
      while (ptrX)
      {
        if ((ptrX->n == ptr->n) && Est_Existe_Liste(X, i) && !m[i])
        { // on insere l'extrimite initiale dans X_plus
          X_moins = Inserer_Fin_Liste(X_moins, i);
          m[i] = 1;
          break;
        }
        ptrX = ptrX->svt;
      }
    }
    ptr = ptr->svt;
  }
  X_prime = Intersection_2_Listes(X_plus, X_moins); // la CFC
  return ((Cellule *)Trier_Liste(X_prime));
}

int CFC(TableLists *L, int tableCFCs[MAX])
{
  Cellule *X = NULL, // ensembles des sommets
      *X_prime,      // composante fortement connexe
      *ptr;          // pointeur pour le parcour
  int i, nb_cfc = 0;
  if (!L) // si la matrice n'existe pas
  {
    printf("\nErreur : matrice n'existe pas !");
    exit(0);
  }
  // initialisation de l'ensemble des sommets
  for (i = 0; i < L->n; i++)
    X = Inserer_Fin_Liste(X, i);
  while (X) // tant qu'on a des sommets non encore dans une CFC
  {
    X_prime = CFC_a(L, X, X->n); // la CFC contenant le sommet de X
    ptr = X_prime;
    while (ptr) // construir la classe d'equivalence
    {
      tableCFCs[ptr->n] = nb_cfc;
      ptr = ptr->svt;
    }
    nb_cfc++; // augmenter le nombre de classe d'equivalence
    // eliminer les sommets qui appartient deja a une CFC
    X = Substrct_2_Ordered_Lists(X, X_prime);
  }
  return ((int)nb_cfc);
}

TableLists *Graphe_Reduit(TableLists *L, int tableCFCs[MAX], int nb_cfc)
{
  if (!L)
  {
    printf("\nErreur : table de listes d'adjacence n'existe pas !");
    exit(0);
  }
  int i;
  TableLists *LAR = CreerTableLists(nb_cfc); // creation de listes pour le graphe reduit
  Cellule *ptr;
  for (i = 0; i < L->n; i++) // pour tout sommet
  {
    ptr = L->liste[i];
    while (ptr) // on parcours chaque liste d'adjacence
    {
      if (tableCFCs[i] != tableCFCs[ptr->n] &&
          !Est_Existe_Liste(LAR->liste[tableCFCs[i]], tableCFCs[ptr->n]))
      { // creation de l'arc
        LAR->liste[tableCFCs[i]] = Inserer_Fin_Liste(LAR->liste[tableCFCs[i]], tableCFCs[ptr->n]);
      }
      ptr = ptr->svt;
    }
  }
  return ((TableLists *)LAR);
}

void AfficherListe(Cellule *liste)
{
  Cellule *ptr = liste;
  while (ptr)
  {
    printf("%d ", ptr->n + 1);
    ptr = ptr->svt;
  }
}

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
  printf("\nTable de listes d'adjacence initiales : ");
  TableLists *L = remplirTableLists("graphe.txt");
  AfficherTableLists(L);

  int tableCFCs[MAX];
  int nb_cfc = CFC(L, tableCFCs);
  printf("\nNombre de composantes fortement connexes :  %d", nb_cfc);
  printf("\nTable des composantes fortement connexes : ");
  printf("\n\tSommet \tClasse d'equivalence");
  for (int i = 0; i < L->n; i++)
    printf("\n\t%d \t%d", i + 1, tableCFCs[i] + 1);

  printf("\nTable de listes d'adjacence du graphe reduit : ");
  TableLists *LAR = Graphe_Reduit(L, tableCFCs, nb_cfc);
  AfficherTableLists(LAR);

  printf("\nLa decision recommandee pour la direction : ");
  if (nb_cfc > 1)
    printf("\n==> \tNon faisable.");
  else
    printf("\n==> \tFaisable.");
}