
// Définition d'une constante MaxElem avec une valeur de 30
#define MaxElem 30 

// Structure de tableau
typedef struct
{
  int info[MaxElem]; // Tableau d'entiers de taille MaxElem
  int IDE;           // Indice du dernier élément
} TAB;

// Structure de liste et pile
typedef struct CL
{
  int info;       // La valeur de la cellule
  struct CL *svt; // Pointeur vers l'élément suivant dans la liste ou la pile
} Cellule;

// Structure de file
typedef struct FL
{
  Cellule *Tete;  // Pointeur vers la tête de la file
  Cellule *Queue; // Pointeur vers la queue de la file
} File;

// Structure d'arbre
typedef struct ND
{
  int info;
  struct ND *fgc; // Pointeur vers le fils gauche du nœud
  struct ND *fdt; // Pointeur vers le fils droit du nœud
} Noeud;
