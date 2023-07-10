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
// Structure d'une cellule
typedef struct
{
  Cellule *tete;  // pointeur sur tete de la file
  Cellule *queue; // pointeur sur queue de la file
} File;
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
| Nom     : CreerFile;
| Sorties : File * : la structure de la file initialisee
| La fonction permet d'allouer un espace memoire pour la structure de la file
| et d'initialiser ses champs
*/
File *CreerFile()
{
  File *F = (File *)malloc(sizeof(File));
  if (!F)
  {
    printf("\nErreur d'allocation memoire !");
    exit(0);
  }
  F->tete = F->queue = NULL;
  return ((File *)F);
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
/********************************************************************************
| Nom     : Empiler;
| Entrees : Cellule * : la pile ou on veut inserer
|           int       : la valeur a inserer dans la pile
| Sorties : Cellule * : la pile apres l'insertion
| La fonction permet d'inserer un entier au sommet de la pile
*/
Cellule *Empiler(Cellule *pile, int n)
{
  Cellule *NE = CreerCellule(n);
  if (pile)
    NE->svt = pile;
  return ((Cellule *)NE);
}
/********************************************************************************
| Nom     : Depiler;
| Entrees : Cellule * : la pile ou on veut supprimer
| Sorties : int *     : la valeur du sommet de la pile
|           Cellule * : la pile apres la suppression
| La fonction permet de supprimer le sommet de la pile
*/
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
/********************************************************************************
| Nom     : Enfiler;
| Entrees : File * : la file ou on veut inserer
|           int    : la valeur a inserer dans la file
| Sorties : int    : -1 si la file n'existe pas, 1 sinon
| La fonction permet d'inserer un entier a la queue de la file
*/
int Enfiler(File *file, int n)
{
  if (!file)
    return ((int)-1); // file n'existe pas
  Cellule *nc = CreerCellule(n);
  if (!file->queue)
    file->tete = nc; // file vide
  else
    file->queue->svt = nc;
  file->queue = nc;
  return ((int)1);
}
/********************************************************************************
| Nom     : Defiler;
| Entrees : File * : la file ou on veut supprimer
| Sorties : int *  : la valeur du sommet de la file
|           int    : -1 si la file n'existe pas, 1 sinon
| La fonction permet de supprimer le sommet de la file
*/
int Defiler(File *file, int *n)
{
  if (!file)
    return ((int)-1);
  if (file->tete)
  {
    Cellule *ptr = file->tete;
    *n = file->tete->n;
    file->tete = file->tete->svt;
    free(ptr);
  }
  return ((int)1);
}
/********************************************************************************
| Nom     : Inserer_ListeOrdonnee;
| Entrees : Cellule * : la liste ou on veut inserer
|         : int       : l'entier a inserer
| Sorties : Cellule * : la liste ordonnee apres l'insertion
| la fonction permet d'inserer un entier donne a dans une liste ordonnee
*/
Cellule *Inserer_ListeOrdonnee(Cellule *liste, Cellule *ne)
{
  Cellule *ptr;
  // si la liste est vide
  if (!liste)
    return ((Cellule *)ne);
  // insertion en tete
  if (ne->n < liste->n)
  {
    ne->svt = liste;
    return ((Cellule *)ne);
  }
  ptr = liste;     // pointeur sur la tete de la liste
  while (ptr->svt) // tant que la liste a un suivant
  {
    if (ne->n < ptr->svt->n)
    { // Insertion en milieu
      ne->svt = ptr->svt;
      ptr->svt = ne;
      return ((Cellule *)liste);
    }
    ptr = ptr->svt;
  }
  // Insertion en queue
  ptr->svt = ne;
  return ((Cellule *)liste);
}
/********************************************************************************
| Nom     : Trier_Liste;
| Entrees : Cellule * : une liste
| Sorties : Cellule * : la liste triee
| la fonction permet de trier une liste donnee
*/
Cellule *Trier_Liste(Cellule *liste)
{
  Cellule *OList = NULL, *ptr;
  if (!liste)
    return ((Cellule *)NULL);
  while (liste)
  {
    ptr = liste;
    liste = liste->svt;
    ptr->svt = NULL;
    OList = Inserer_ListeOrdonnee(OList, ptr);
  }
  return ((Cellule *)OList);
}
/********************************************************************************
| Nom     : Intersection_2_Listes;
| Entrees : Cellule * : la premiere liste
|         : Cellule * : la deuxieme liste
| Sorties : Cellule * : la liste resultante de l'intersection de 2 listes
| la fonction permet de faire l'intersection de deux listes
*/
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
/********************************************************************************
| Nom     : Substrct_2_Ordered_Lists;
| Entrees : Cellule * : la premiere liste ordonnee
|         : Cellule * : la deuxieme liste ordonnee
| Sorties : Cellule * : la liste resultante de la soustraction de 2 listes ordonnees
| la fonction permet de soustrire une liste ordonnee d'une autre
*/
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
