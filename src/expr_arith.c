/*                          Expression arithmétique                          */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Déclaration des constantes
#define RC '\n' // Caractère de retour à la ligne
#define BL ' '  // Caractère blanc
#define PL '+'  // Opérateur d'addition
#define MN '-'  // Opérateur de soustraction
#define ML '*'  // Opérateur de multiplication
#define DV '/'  // Opérateur de division
// Declaration des structures et unions
typedef union // Definition d'une union
{
  float operande;
  char operateur;
} Exp;
typedef struct ND // Definition de la structure d'arbre
{
  Exp info;             // champ d'information de l'arbre
  struct ND *fgc, *fdt; // pointeur de fils gauche et droit
} Noeud;
typedef struct CL // Definition de la structure de pile
{
  Exp info;       // champ d'information de la pile
  struct CL *svt; // pointeur suivant
} Cellule;

/* ******************************************************************************
| AffichageHorizontal
| Entrées : Noeud* Arb - la racine de l'arbre
|           int n - niveau de la racine pour le nombre de tabulations
| Sorties : Aucune
| La fonction permet d'afficher l'arbre graphiquement en commençant par l'affichage
| du nœud le plus à droite, puis la racine, et enfin le nœud à gauche.
*/
void AffichageHorizontal(Noeud *Arb, int n)
{
  if (Arb)
  {
    if (Arb->fdt) AffichageHorizontal(Arb->fdt, n + 1);
    printf("\n");
    for (int i = 0; i < n; i++) printf("\t");
    if (!Arb->fgc && !Arb->fdt) printf("%.2f", Arb->info.operande);
    else printf("%c", Arb->info.operateur);
    if (Arb->fgc) AffichageHorizontal(Arb->fgc, n + 1);
  }
}
/* ******************************************************************************
| AffichageInfixe
| Entrées : Noeud* Arb - la racine de l'arbre
| Sorties : Aucune
| La fonction permet d'afficher l'arbre sous forme d'expression infixée en
| effectuant un parcours infixe de l'arbre.
*/
void AffichageInfixe(Noeud *Arb)
{
  if (Arb)
  {
    AffichageInfixe(Arb->fgc);
    if (!Arb->fgc && !Arb->fdt) printf("%.2f ", Arb->info.operande);
    else printf("%c ", Arb->info.operateur);
    AffichageInfixe(Arb->fdt);
  }
}
/* ******************************************************************************
| CreerNoeud
| Sorties : Noeud* NE - le nœud créé
| La fonction permet de créer un nœud de l'arbre et le retourne.
*/
Noeud *CreerNoeud()
{
  Noeud *NE = (Noeud *)malloc(sizeof(Noeud)); // Allocation de la memoire
  if (!NE)
  {
    printf("\nErreur d'allocation de la memoire!");
    exit(0);
  }
  NE->fgc = NE->fdt = NULL; // Initialiser les fils au NULL
  return ((Noeud *)NE);
}
/* ******************************************************************************
| CreerCellule
| Sorties : Cellule* NE - la cellule créée
| La fonction permet de créer une cellule de la pile et la retourne.
*/
Cellule *CreerCellule()
{
  Cellule *NE = (Cellule *)malloc(sizeof(Cellule)); // Allocation de la memoire
  if (!NE)
  {
    printf("\nErreur d'allocation de la memoire!");
    exit(0);
  }
  NE->svt = NULL; // Initialisation de pointeur suivant
  return ((Cellule *)NE);
}
/* ******************************************************************************
| Epeurer_Blanc
| Entrées : char c - un caractère
| Sorties : char c - un caractère non blanc
| La fonction permet d'ignorer les caractères blancs jusqu'à trouver un
| caractère non blanc, puis le retourne.
*/
char Epeurer_Blanc(char c)
{
  return ((char)(c == BL) ? Epeurer_Blanc(getchar()) : c);
}
/* ******************************************************************************
| EstNumerique
| Entrées : char c - un caractère
| Sorties : int - un entier pour indiquer si le caractère est un chiffre
| La fonction permet de vérifier si un caractère est un chiffre. Elle retourne
| un entier entre 0 et 9 pour un chiffre, 11 pour un blanc, 12 pour un point,
| et -1 pour tout autre caractère.
*/
int EstNumerique(char c) 
{
    if (('0' <= c) && (c <= '9')) return (int)(c - '0'); // Caractère numérique
    if (c == ' ') return 11;                             // Caractère blanc
    if (c == '.') return 12;                             // Point décimal
    return -1;
}
/* ******************************************************************************
| EstOperateur
| Entrées : char c - un caractère
| Sorties : int - un entier pour indiquer si le caractère est un opérateur
| La fonction permet de vérifier si un caractère est un opérateur arithmétique.
| Elle retourne 1 pour '+', 2 pour '-', 3 pour '*', 4 pour '/', 0 pour un
| retour chariot, et -1 pour tout autre caractère.
*/
int EstOperateur(char c)
{
  switch (c)
  {
  case RC: return ((int)0);
  case PL: return ((int)1);
  case MN: return ((int)2);
  case ML: return ((int)3);
  case DV: return ((int)4);
  default: return ((int)-1);
  }
}
/* ******************************************************************************
| Transforme
| Entrées : float* operande - pour stocker la valeur du nombre extrait
| Sorties : char c - le caractère non blanc après le nombre extrait
| La fonction permet d'extraire un nombre réel à partir d'une chaîne de
| caractères saisie par l'utilisateur. Elle retourne le caractère non blanc
| qui suit le nombre extrait.
*/
char Transforme(float *operande)
{
  int control;        // Valeur retournée par "EstNumerique(char)"
  int firstPass = 1;  // Indique si c'est la première lecture
  int f = 0;          // Distingue la partie entière de la partie décimale
  int signe = 1;      // Stocke le signe du nombre
  float result = 0;   // Stocke le nombre extrait
  char c = getchar();
  c = Epeurer_Blanc(c); // Ignorer les blancs
  do
  {
    if (firstPass == 1) // Lors de la lecture du premier caractere
    {
      firstPass = 0; // Indiquer qu'on a lu le premier caractère
      if ((c == '-') || (c == '+')) // Récupérer le signe du nombre
      { 
        if (c == '-') signe = -1;
        c = getchar();
        continue; // passer a l'iteration suivante
      }
    }
    control = EstNumerique(c);
    switch (control)
    {
    case -1:
      printf("\nErreur: caractere non numerique!");
      exit(0);
    case 11: // un blanc
      c = Epeurer_Blanc(c);
      *operande = (float)(result * signe);
      return ((char)c);
    case 12:      // un point
      if (f == 0) // on y encore dans la partie entiere
      {
        f = -1; // passer a la partier reel
        break;
      }
      printf("\nErreur: un autre point est tape!");
      exit(0);
    default: // caractere numerique
      if (f == 0) result = result * 10 + (float)control;
      else result += (float)((float)(control)*pow(10, f--));
    }
    c = getchar();
  } while ((c != PL) && (c != MN) && (c != ML) && (c != DV) && (c != RC));
  *operande = (float)(result * signe);
  return ((char)c);
}
/* ******************************************************************************
| Construire_Arbre_Exp
| Sorties : Noeud* Arb - un arbre représentant une expression arithmétique
| La fonction permet de lire une expression arithmétique et de la représenter
| sous forme d'un arbre binaire.
*/
Noeud *Construire_Arbre_Exp()
{
  Noeud *Arb = NULL, *NOperateur, *NOperande, *courant;
  char operateur; // pour stocker l'operateur lue
  float operande; // pour stocker l'operande extrait
  int control;    // pour stocker la valeur retournee par "EstOperateur(char)"
  int dir = 1;    // pour indiquer la direction d'insertion d'un sous arbre
  printf("\nEntrer une expression arithmetique : ");
  while ((operateur = Transforme(&operande)) != RC)
  {
    control = EstOperateur(operateur);
    if (control == -1)
    {
      printf("\nOperateur non defini!");
      exit(0);
    }
    NOperande = CreerNoeud();               // Créer un nœud pour l'opérande
    NOperande->info.operande = operande;    // Affecter la valeur de l'opérande
    NOperateur = CreerNoeud();              // Créer un nœud pour l'opérateur
    NOperateur->info.operateur = operateur; // Affecter l'opérateur
    if (!Arb) // Arbre vide
    {
      Arb = NOperateur;     // L'opérateur devient la racine de l'arbre
      Arb->fgc = NOperande; // L'opérande devient son fils gauche
      courant = Arb;        // Initialiser courant par la racine de l'arbre
    }
    else  // L'opérande devient le fils libre du dernier opérateur inséré
    {
      if (!courant->fdt) courant->fdt = NOperande;
      else courant->fgc = NOperande;
      // Si l'opérateur est un '+' ou '-'
      if ((control == 1) || (control == 2))
      {
        if (control == 1) // le cas d'un '+'
        {
          if (dir == 0) NOperateur->fgc = Arb;
          else NOperateur->fdt = Arb;
          dir = 1 - dir; // changer dir pour la prochaine insertion
        }
        // le cas d'un '-' l'arbre devient sous arbre gauche de l'operateur
        else NOperateur->fgc = Arb;
        Arb = NOperateur; // l'operateur devient la racine de l'arbre
      }
      else // l'operateur est '*' ou '/'
      {    // le dernier operateur inserer est '+'
        if (courant->info.operateur == PL)
        {
          if (dir == 0)
          {
            NOperateur->fgc = Arb->fgc;
            Arb->fgc = NOperateur;
          }
          else
          {
            NOperateur->fgc = Arb->fdt;
            Arb->fdt = NOperateur;
          }
          dir = 1 - dir; // changer dir pour la prochaine insertion
        }
        else
        { // le dernier operateur inserer est '-'
          if (courant->info.operateur == MN)
          {
            NOperateur->fgc = Arb->fdt;
            Arb->fdt = NOperateur;
          }
          else // le dernier operateur inserer est '*' ou '/'
          {    // le dernier operateur devient fils gauche
            NOperateur->fgc = courant;
            if (Arb == courant) Arb = NOperateur;
            else Arb->fdt = NOperateur;
          }
        }
      }
      courant = NOperateur;
    }
  }
  // le dernier operande
  NOperande = CreerNoeud();            // Creer un noeud pour l'operande
  NOperande->info.operande = operande; // affecte la valeur de l'operande
  if (!Arb) return ((Noeud *)NOperande); // si l'arbre est vide
  if (!courant->fdt) courant->fdt = NOperande;
  else courant->fgc = NOperande;
  return ((Noeud *)Arb);
}
/* ****************************************************************************
| Calculer_Exp
| Entrées : float op1      : le premier opérande
|           char operateur : un opérateur
|           float op2      : le deuxième opérande
| Sorties : float result   : le résultat de l'opération
| La fonction permet d'effectuer une opération arithmétique de deux opérandes 
| et de retourner le résultat.
*/
float Calculer_Exp(float Op1, char operateur, float Op2)
{
  switch (operateur)
  {
  case '+': return ((float)Op1 + Op2);
  case '-': return ((float)Op1 - Op2);
  case '*': return ((float)Op1 * Op2);
  case '/': 
    if (Op2 != 0) return ((float)Op1 / Op2);
    // Cas de division par 0
    printf("\nErreur: Division par 0!!");
    exit(0);
  }
}
/* ****************************************************************************
| Evaluer_Arbre_Exp
| Entrées : Noeud *Arb : la racine de l'arbre
| Sorties : float : le résultat de l'évaluation de l'expression arithmétique
| La fonction permet d'évaluer l'expression arithmétique qui est représentée sous
| forme d'un arbre binaire en effectuant un parcours infixe de l'arbre.
*/
float Evaluer_Arbre_Exp(Noeud *Arb)
{
  if (Arb)
  {
    // Si le nœud est une feuille, renvoyer la valeur de l'opérande
    if (!Arb->fgc && !Arb->fdt) return ((float)Arb->info.operande);
    // Évaluer le sous-arbre gauche, l'opérateur, et le sous-arbre droit
    return ((float)Calculer_Exp(Evaluer_Arbre_Exp(Arb->fgc),
                                Arb->info.operateur,
                                Evaluer_Arbre_Exp(Arb->fdt)));
  }
}
/* ****************************************************************************
| Empiler
| Entrées : Cellule *pile : une pile
|           Cellule *cell : la cellule à insérer
| Sorties : Cellule *pile : la pile après l'insertion de cell
| Description : La fonction permet d'insérer une cellule au sommet de la pile.
*/
Cellule *Empiler(Cellule *pile, Cellule *cell)
{
  if (!ceil) return ((Cellule *)pile);
  cell->svt = pile;
  pile = cell;
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Depiler
| Entrées : Cellule *pile : une pile
|           Cellule *cell[1] : pour récupérer le sommet
| Sorties : Cellule *pile : la pile après la récupération du sommet
| Description : La fonction permet de récupérer le sommet de la pile. Elle retire
|               la cellule en tête de la pile et la renvoie dans le tableau cell.
*/
Cellule *Depiler(Cellule *pile, Cellule *cell[1])
{
  cell[0] = pile;
  if (!pile) return ((Cellule *)NULL);
  pile = pile->svt;
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Evaluer_Operation_Pile
| Entrées : Cellule *pile : une pile
| Sorties : Cellule *pile : la pile après l'évaluation de l'opération
| La fonction permet de calculer une opération dans la pile en dépilant l'opérande,
| l'opérateur et le deuxième opérande, puis en empilant le résultat dans la pile.
*/
Cellule *Evaluer_Operation_Pile(Cellule *pile)
{
  Cellule *cell[1];
  float op1, op2, result;
  char operateur;
  if (!pile) return ((Cellule *)NULL); // Si la pile est vide, renvoyer NULL
  // Dépiler le premier opérande dans la pile et l'empiler dans cell
  pile = Depiler(pile, cell);
  op1 = cell[0]->info.operande; // Récupérer le premier opérande
  free(cell[0]); // Libérer la mémoire de la cellule dépilée
  // Dépiler l'opérateur dans la pile et l'empiler dans cell
  pile = Depiler(pile, cell);
  operateur = cell[0]->info.operateur; // Récupérer l'opérateur
  free(cell[0]); // Libérer la mémoire de la cellule dépilée
  // Dépiler le deuxième opérande dans la pile et l'empiler dans cell
  pile = Depiler(pile, cell);
  op2 = cell[0]->info.operande; // Récupérer le deuxième opérande
  free(cell[0]); // Libérer la mémoire de la cellule dépilée
  // Effectuer le calcul en appelant la fonction Calculer_Exp
  result = Calculer_Exp(op1, operateur, op2);
  // Empiler une nouvelle cellule dans la pile pour stocker le résultat
  pile = Empiler(pile, CreerCellule());
  pile->info.operande = result; // Affecter le résultat au sommet de la pile
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Expression_Arithmetique_Pile
| Sorties : Cellule *pile : une pile contenant une expression arithmétique
| La fonction permet de lire une expression arithmétique et de la représenter 
| sous forme d'une pile. Elle lit les opérateurs et les opérandes de l'expression
| saisie et les empile dans la pile. Lorsque la saisie se termine par un retour 
| chariot, la pile contient l'expression arithmétique sous forme inversée.
*/
Cellule *Expression_Arithmetique_Pile()
{
  Cellule *pile = NULL, *NE;
  char operateur;
  float operande;
  int control;
  printf("\nEntrer une expression arithmetique : ");
  do
  {
    // Extraire l'opérateur et l'opérande de l'entrée
    operateur = Transforme(&operande); 
    control = EstOperateur(operateur);
    if (control == -1)
    {
      printf("\nErreur: Operateur non valide!"); // Vérifier si l'opérateur est valide
      exit(0);
    }
    NE = CreerCellule();          // Créer une cellule pour l'opérande
    NE->info.operande = operande; // Affecter la valeur de l'opérande à la cellule
    pile = Empiler(pile, NE);     // Empiler la cellule dans la pile
    if (control != 0)
    {                                 // Si l'opérateur n'est pas un retour chariot (fin de l'expression)
      NE = CreerCellule();            // Créer une cellule pour l'opérateur
      NE->info.operateur = operateur; // Affecter l'opérateur à la cellule
      pile = Empiler(pile, NE);       // Empiler la cellule dans la pile
    }
  } while (operateur != RC); // Continuer tant que l'opérateur n'est pas un retour chariot
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Evaluer_Pile_Exp
| Entrées : Cellule *pile : une pile contenant une expression arithmétique
| Sorties : float : le résultat d'évaluation de l'expression arithmétique
| La fonction permet d'évaluer l'expression arithmétique qui est représentée sous
| forme d'une pile. Elle effectue les opérations arithmétiques en désempilant les
| opérandes et les opérateurs de la pile, puis en empilant les résultats intermédiaires
| jusqu'à obtenir le résultat final. Le résultat est retourné en tant que valeur de type float.
*/
float Evaluer_Pile_Exp(Cellule *pile)
{
  Cellule *tmp = NULL, *cell[1];
  char operateur;
  if (!pile) // Si la pile est vide
  {
    printf("\nPile vide!!");
    return ((float)0);
  }
  // Dépiler le premier opérande de la pile et l'empiler dans tmp
  pile = Depiler(pile, cell);
  tmp = Empiler(tmp, cell[0]);
  while (pile) // Tant que la pile n'est pas vide
  {
    // Dépiler l'opérateur de la pile et l'empiler dans la pile tmp
    pile = Depiler(pile, cell);
    tmp = Empiler(tmp, cell[0]);
    operateur = cell[0]->info.operateur; // Conserver l'opérateur
    // Dépiler le deuxième opérande de la pile et l'empiler dans tmp
    pile = Depiler(pile, cell);
    tmp = Empiler(tmp, cell[0]);
    if (pile)
    {
      if (pile->info.operateur == PL)
      { // Si l'opérateur est un '+', évaluer toutes les opérations dans la pile tmp
        while (tmp->svt) tmp = Evaluer_Operation_Pile(tmp);
      }
      else if (pile->info.operateur != DV)
      { // Si l'opérateur n'est pas un '/', évaluer les opérations jusqu'à l'opérateur '+' ou '-'
        while (tmp->svt)
        {
          if ((tmp->svt->info.operateur == PL) || (tmp->svt->info.operateur == MN)) break;
          tmp = Evaluer_Operation_Pile(tmp);
        }
      }
    }
  }
  // Évaluer toutes les opérations restantes dans la pile tmp
  while (tmp->svt) tmp = Evaluer_Operation_Pile(tmp);
  return ((float)tmp->info.operande);
}
/* ****************************************************************************
| AfficherPile
| Entrées : Cellule *pile : une pile
| Description : La fonction permet d'afficher le contenu de la pile passée en
|               paramètre. Elle parcourt la pile en inversant son ordre, puis
|               affiche les opérandes et les opérateurs dans l'ordre correct.
|               Si la pile est vide, elle affiche un message indiquant que la
|               pile est vide.
*/
void AfficherPile(Cellule *pile)
{
  Cellule *tmp = NULL, *courant;
  if (!pile) printf("\nPile vide"); // Si la pile est vide
  else
  {
    printf("\nPile : ");
    while (pile)
    {
      courant = pile;
      pile = pile->svt;
      courant->svt = tmp;
      tmp = courant;
    }
    while (tmp)
    {
      printf("%.2f ", tmp->info.operande);
      courant = tmp;
      tmp = tmp->svt;
      courant->svt = pile;
      pile = courant;
      if (tmp)
      {
        printf("%c ", tmp->info.operateur);
        courant = tmp;
        tmp = tmp->svt;
        courant->svt = pile;
        pile = courant;
      }
    }
  }
}


void main()
{
  Cellule *pile;
  Noeud *Arbre;
  int choix;
  printf("\n***** Expression Arithmetique *****");
  do
  {
    printf("\nSelectionner votre choix :");
    printf("\n0 : Arreter le programme.");
    printf("\n1 : Mise en oeuvre a l'aide d'un arbre.");
    printf("\n2 : Mise en oeuvre a l'aide d'une pile.");
    printf("\n--> ");
    scanf("%d", &choix);
    getchar();
    switch (choix)
    {
    case 0: break;
    case 1:
      Arbre = Construire_Arbre_Exp();
      printf("\nAffichage Horizontal : ");
      AffichageHorizontal(Arbre, 0);
      // printf("\nAffichage Infixe : ");
      // AffichageInfixe(Arbre);
      printf("\nE = %f", Evaluer_Arbre_Exp(Arbre));
      break;
    case 2:
      pile = Expression_Arithmetique_Pile();
      AfficherPile(pile);
      printf("\nE = %f", Evaluer_Pile_Exp(pile));
      break;
    default: printf("\nChoix non valide!!");
    }
  } while (choix);
}