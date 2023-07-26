#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *regles[11] = {"TP", "+TP", "e", "FV", "FV", "e", "(R)S", "aS", "bS", "*S", "e"};

int M[6][7] =
            {
              {0, 1, 0, 1, 1, 0, 0},       // R
              {2, 0, 3, 0, 0, 0, 3},       // P
              {0, 4, 0, 4, 4, 0, 0},       // T
              {6, 5, 6, 5, 5, 0, 6},       // V
              {0, 7, 0, 8, 9, 0, 0},       // F
              {11, 11, 11, 11, 11, 10, 11} // S
            };

typedef struct pl
{
  char x;
  struct pl *svt;
} node;
/******************************************************************************
 * createnode;
 * Entrées: char c - un caractère à stocker dans le noeud
 * Sorties: node* - un pointeur vers le nouveau noeud créé
 * Cette fonction crée un nouveau noeud pour stocker un caractère donné.
 * Elle alloue la mémoire nécessaire pour le nouveau noeud et initialise ses champs.
 */
node *createnode(char c)
{
  node *n = (node *)malloc(sizeof(node));
  if (!n)
  {
    printf("\nErreur d'allocation memoire");
    exit(0);
  }
  n->x = c;
  n->svt = NULL;
  return (node *)n;
}
/******************************************************************************
 * insert_node;
 * Entrées: node *n - un pointeur vers une liste chaînée de noeuds
 *          char c - un caractère à insérer dans la liste chaînée
 * Sorties: node* - un pointeur vers la nouvelle liste chaînée avec le caractère inséré
 * Cette fonction insère un nouveau noeud contenant le caractère donné dans la liste chaînée spécifiée.
 */
node *insert_node(node *n, char c)
{
  node *ne = createnode(c), *ptr = n;
  if (n) ne->svt = n;
  return (node *)ne;
}
/******************************************************************************
 * insert_to_pile;
 * Entrées: node *pile - un pointeur vers une pile représentée par une liste chaînée
 *          char *exp - une chaîne de caractères à insérer dans la pile
 * Sorties: node* - un pointeur vers la nouvelle pile avec la chaîne de caractères insérée
 * Cette fonction insère une chaîne de caractères dans la pile (liste chaînée).
 */
node *insert_to_pile(node *pile, char *exp)
{
  if (!exp) return (node *)NULL;
  node *tmp = NULL, *ptr;
  for (int i = 0; exp[i] != '\0'; i++) tmp = insert_node(tmp, exp[i]);
  while (tmp)
  {
    ptr = tmp;
    tmp = tmp->svt;
    ptr->svt = pile;
    pile = ptr;
  }
  return (node *)pile;
}
/******************************************************************************
 * depiler;
 * Entrées: node *pile - un pointeur vers une pile représentée par une liste chaînée
 *          char *d - un pointeur vers une variable pour stocker le caractère dépilé
 * Sorties: node* - un pointeur vers la nouvelle pile après le dépilement
 * Cette fonction dépile le premier noeud de la pile et stocke le caractère contenu dans ce noeud dans la variable spécifiée.
 */
node *depiler(node *pile, char *d)
{
  if (!pile) return (node *)pile;
  node *ptr = pile;
  *d = pile->x;
  pile = pile->svt;
  free(ptr);
  return (node *)pile;
}
/******************************************************************************
 * isterminal;
 * Entrées: char x - un caractère
 * Sorties: int - 1 si le caractère est un terminal, 0 sinon
 * Cette fonction vérifie si un caractère donné est un terminal (fait partie des caractères terminaux de la grammaire).
 */
int isterminal(char x)
{ // terminal = {'+','(',')','a','b','*','$'};
  switch (x)
  {
  case '+': return 0;
  case '(': return 1;
  case ')': return 2;
  case 'a': return 3;
  case 'b': return 4;
  case '*': return 5;
  case '$': return 6;
  default:  return -1;
  }
}
/******************************************************************************
 * isnonterminal;
 * Entrées: char X - un caractère
 * Sorties: int - 1 si le caractère est un non-terminal, 0 sinon
 * Cette fonction vérifie si un caractère donné est un non-terminal (fait partie des caractères non-terminaux de la grammaire).
 */
int isnonterminal(char X)
{ // nonterminal = {'R','P','T','V','F','S'};
  switch (X)
  {
  case 'R': return 0;
  case 'P': return 1;
  case 'T': return 2;
  case 'V': return 3;
  case 'F': return 4;
  case 'S': return 5;
  default:  return -1;
  }
}
/******************************************************************************
 * fnct;
 * Entrées: char *m - une chaîne de caractères représentant une expression
 * Sorties: int - 1 si l'expression est valide selon la grammaire, 0 sinon
 * Cette fonction est l'analyseur syntaxique qui vérifie si une expression donnée est valide selon les règles de la grammaire.
 * Elle utilise une pile (représentée par une liste chaînée) pour stocker les symboles de la grammaire lors de l'analyse de l'expression.
 * La table de parsing `M` est utilisée pour déterminer les règles de production à appliquer lors de l'analyse.
 */
int fnct(char *m)
{
  if (!m) return 0;
  node *pile = NULL;
  pile = insert_to_pile(pile, "R$");
  int i = 0, X, r;
  char ps, lnt;
  do
  {
    ps = m[i];
    if ((X = isnonterminal(pile->x)) != -1)
    {
      if ((r = M[X][isterminal(ps)]) == 0) return 0;
      pile = depiler(pile, &lnt);
      pile = insert_to_pile(pile, regles[r - 1]);
      printf("\nSortie : %c -> %s", lnt, regles[r - 1]);
    }
    else
    {
      if (pile->x == 'e')
      {
        pile = depiler(pile, &lnt);
        continue;
      }
      if (pile->x == '$')
      {
        if (ps == '$') return 1;
        else return 0;
      }
      else
      {
        if (pile->x != ps) return 0;
        pile = depiler(pile, &lnt);
        i++;
      }
    }
  } while (1);
}
/******************************************************************************
 * main;
 * Entrées: aucune
 * Sorties: int - code de sortie du programme
 * Cette fonction est le point d'entrée du programme principal.
 * Elle présente un menu à l'utilisateur avec les options "Lancer" et "Arreter".
 * L'utilisateur peut choisir l'option "Lancer" pour entrer une expression à analyser.
 * L'analyseur syntaxique vérifie si l'expression est valide selon la grammaire et affiche le résultat ("Valide" ou "Invalide").
 * Le programme s'arrête lorsque l'utilisateur choisit l'option "Arreter".
 */
int main()
{
  char *m = (char *)malloc(sizeof(char) * 50);
  int choix;
  do
  {
    printf("\n0: Arreter");
    printf("\n1: Lancer");
    printf("\n--> ");
    scanf("%d", &choix);
    if (!choix) break;
    printf("\nEntrer votre expression : ");
    scanf("%s", m);
    strcat(m, "$");
    if (fnct(m)) printf("\nValide");
    else printf("\nInvalide");
  } while (choix);
  return 0;
}