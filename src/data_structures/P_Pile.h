/*                                  Pile                                     */

/* ****************************************************************************
| Empiler
| Entrées : Cellule *pile - Pointeur vers la pile
|           int val - Valeur à empiler
| Sorties : Cellule * - Nouveau pointeur vers la pile après l'empilement
| La fonction permet d'empiler une valeur à la pile. Elle crée une nouvelle cellule avec la valeur donnée,
| puis la place au sommet de la pile en modifiant les pointeurs appropriés.
*/
Cellule *Empiler(Cellule *pile, int val)
{
  Cellule *CL = CreerCellule(val);
  if (!pile) return ((Cellule *)CL);
  CL->svt = pile; // Inserer au sommet
  return ((Cellule *)CL);
}
/* ****************************************************************************
| Depiler
| Entrées : Cellule *pile - Pointeur vers la pile
| Sorties : Cellule * - Nouveau pointeur vers la pile après le dépilement
| La fonction permet de dépiler un élément de la pile. Elle supprime la cellule du sommet de la pile
| et renvoie un nouveau pointeur vers la pile modifiée.
*/
Cellule *Depiler(Cellule *pile)
{
  Cellule *Supp;
  if (!pile) return ((Cellule *)NULL);
  Supp = pile;
  pile = pile->svt;
  free(Supp);
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Empiler_Pile_Pos
| Entrées : Cellule *pile - Pointeur vers la pile
|           int Pos - Position d'insertion
|           int val - Valeur à insérer
|           int *inserted - Pointeur vers une variable indiquant si l'insertion a été effectuée (1) ou non (0)
| Sorties : Cellule * - Nouveau pointeur vers la pile après l'insertion
| La fonction permet d'insérer une valeur à une position donnée dans la pile.
| Elle parcourt la pile en utilisant un pointeur temporaire, puis insère la valeur à la position spécifiée.
| Si l'insertion est réussie, le paramètre "inserted" est mis à 1.
*/
Cellule *Empiler_Pile_Pos(Cellule *pile, int Pos, int val, int *inserted)
{
  Cellule *tmp = NULL;
  int i = 1;
  *inserted = 0;
  if (Pos > 0)
  {
    while (pile)
    {
      if (Pos == i) break;
      tmp = Empiler(tmp, pile->info);
      pile = Depiler(pile);
      i++;
    }
    if (Pos == i)
    {
      pile = Empiler(pile, val);
      *inserted = 1;
    }
    while (tmp)
    {
      pile = Empiler(pile, tmp->info);
      tmp = Depiler(tmp);
    }
  }
  return ((Cellule *)pile);
}

/* ****************************************************************************
| Empiler_Pile_Fin
| Entrées : Cellule *pile - Pointeur vers la pile
|           int val - Valeur à insérer à la fin de la pile
| Sorties : Cellule * - Nouveau pointeur vers la pile après l'insertion
| La fonction permet d'insérer une valeur à la fin de la pile.
| Elle utilise un pointeur temporaire pour inverser la pile, puis insère la valeur au sommet de la pile inversée.
| Ensuite, elle rétablit l'ordre initial de la pile en inversant à nouveau les éléments.
*/
Cellule *Empiler_Pile_Fin(Cellule *pile, int val)
{
  Cellule *tmp = NULL;
  while (pile)
  {
    tmp = Empiler(tmp, pile->info);
    pile = Depiler(pile);
  }
  pile = Empiler(pile, val);
  while (tmp)
  {
    pile = Empiler(pile, tmp->info);
    tmp = Depiler(tmp);
  }
  return ((Cellule *)pile);
}

/* ****************************************************************************
| Empiler_Pile_Ordonnee
| Entrées : Cellule *pile - Pointeur vers la pile
|           int val - Valeur à insérer de manière ordonnée dans la pile
| Sorties : Cellule * - Nouveau pointeur vers la pile après l'insertion
| La fonction permet d'insérer une valeur de manière ordonnée dans la pile.
| Elle parcourt la pile en utilisant un pointeur temporaire, trouve l'emplacement approprié pour l'insertion
| en comparant les valeurs des éléments, puis insère la valeur à cet emplacement.
*/
Cellule *Empiler_Pile_Ordonnee(Cellule *pile, int val)
{
  Cellule *CL, *tmp = NULL;
  while (pile)
  {
    if (val <= pile->info) break;
    tmp = Empiler(tmp, pile->info);
    pile = Depiler(pile);
  }
  pile = Empiler(pile, val);
  while (tmp)
  {
    pile = Empiler(pile, tmp->info);
    tmp = Depiler(tmp);
  }
  return ((Cellule *)pile);
}

/* ****************************************************************************
| Depiler_Val
| Entrées : Cellule *pile - Pointeur vers la pile
|           int val - Valeur à supprimer de la pile
|           int *deleted - Pointeur vers une variable indiquant si la suppression a été effectuée (1) ou non (0)
| Sorties : Cellule * - Nouveau pointeur vers la pile après la suppression
| La fonction permet de supprimer toutes les occurrences d'une valeur donnée dans la pile.
| Elle parcourt la pile en utilisant un pointeur temporaire et supprime les éléments correspondant à la valeur donnée.
*/
Cellule *Depiler_Val(Cellule *pile, int val, int *deleted)
{
  Cellule *tmp = NULL;
  *deleted = 0;
  while (pile)
  {
    if (pile->info == val)
    {
      *deleted = 1;
      pile = Depiler(pile);
      break;
    }
    tmp = Empiler(tmp, pile->info);
    pile = Depiler(pile);
  }
  while (tmp)
  {
    pile = Empiler(pile, tmp->info);
    tmp = Depiler(tmp);
  }
  return ((Cellule *)pile);
}

/* ****************************************************************************
| Depiler_Dernier_Elem
| Entrées : Cellule *pile - Pointeur vers la pile
| Sorties : Cellule * - Nouveau pointeur vers la pile après la suppression du dernier élément
| La fonction permet de supprimer le dernier élément de la pile.
| Elle utilise un pointeur temporaire pour inverser la pile, puis effectue la suppression du premierélément (anciennement le dernier élément) de la pile inversée.
| Ensuite, elle rétablit l'ordre initial de la pile en inversant à nouveau les éléments.
*/
Cellule *Depiler_Dernier_Elem(Cellule *pile)
{
  Cellule *tmp = NULL;
  int firstPass = 0;
  while (pile)
  {
    tmp = Empiler(tmp, pile->info);
    pile = Depiler(pile);
  }
  while (tmp)
  {
    if (!firstPass)
    {
      tmp = Depiler(tmp);
      firstPass = 1;
      continue;
    }
    pile = Empiler(pile, tmp->info);
    tmp = Depiler(tmp);
  }
  return ((Cellule *)pile);
}

/* ****************************************************************************
| Depiler_Pos
| Entrées : Cellule *pile - Pointeur vers la pile
|           int Pos - Position de l'élément à supprimer
|           int *deleted - Pointeur vers une variable indiquant si la suppression a été effectuée (1) ou non (0)
| Sorties : Cellule * - Nouveau pointeur vers la pile après la suppression
| La fonction permet de supprimer l'élément à une position donnée dans la pile.
| Elle parcourt la pile en utilisant un pointeur temporaire et supprime l'élément à la position spécifiée.
*/
Cellule *Depiler_Pos(Cellule *pile, int Pos, int *deleted)
{
  Cellule *tmp = NULL;
  int i = 1;
  *deleted = 0;
  while (pile)
  {
    if (Pos == i)
    {
      *deleted = 1;
      pile = Depiler(pile);
      break;
    }
    i++;
    tmp = Empiler(tmp, pile->info);
    pile = Depiler(pile);
  }
  while (tmp)
  {
    pile = Empiler(pile, tmp->info);
    tmp = Depiler(tmp);
  }
  return ((Cellule *)pile);
}

/* ****************************************************************************
| Affichage_Pile
| Entrées : Cellule *pile - Pointeur vers la pile
| Sorties : void
| La fonction permet d'afficher les éléments de la pile. Elle utilise un pointeur
| temporaire pour inverser la pile, affiche les éléments un par un tout en les dépi-
| lant, puis rétablit l'ordre initial de la pile.
*/
void Affichage_Pile(Cellule *pile)
{
  Cellule *pile2 = NULL;
  if (!pile) printf("\nPile vide");
  else
  {
    printf("\nPile : ");
    while (pile) // tant qu'on a un element dans la pile
    {            // Afficher l'element et le depiler
      printf("%d\t", pile->info);
      pile2 = Empiler(pile2, pile->info);
      pile = Depiler(pile);
    }
    while (pile2)
    { // Récupperer la pile
      pile = Empiler(pile, pile2->info);
      pile2 = Depiler(pile2);
    }
  }
}

/* ****************************************************************************
| Taille_Pile
| Entrées : Cellule *pile - Pointeur vers la pile
| Sorties : int - Taille de la pile
| La fonction permet de calculer la taille de la pile en parcourant la pile
| en utilisant un pointeur temporaire et en comptant le nombre d'éléments.
| Elle renvoie la taille de la pile.
*/
int Taille_Pile(Cellule *pile)
{
  int taille = 0;
  Cellule *pile2 = NULL;
  if (!pile) return ((int)-1);
  while (pile)
  { // depiler dans la pile et calculer la taille
    taille++;
    pile2 = Empiler(pile2, pile->info);
    pile = Depiler(pile);
  }
  while (pile2)
  { // Récuperer la pile
    pile = Empiler(pile, pile2->info);
    pile2 = Depiler(pile2);
  }
  return ((int)taille);
}

/* ****************************************************************************
| Recherche_Val_Pile
| Entrées : Cellule *pile - Pointeur vers la pile
|           int val - Valeur à rechercher
| Sorties : int - Position de la valeur dans la pile
| La fonction permet de rechercher une valeur donnée dans la pile.
| Elle parcourt la pile en utilisant un pointeur temporaire et compare chaque
| élément avec la valeur recherchée. Elle renvoie la position de la valeur
| dans la pile, ou 0 si la valeur n'est pas trouvée.
*/
int Recherche_Val_Pile(Cellule *pile, int val)
{
  int i = 1, pos = 0;
  Cellule *pile2 = NULL;
  while (pile)
  {
    if (pile->info == val)
    {
      pos = i;
      break;
    }
    i++;
    pile2 = Empiler(pile2, pile->info);
    pile = Depiler(pile);
  }
  while (pile2)
  { // Récuperer la pile
    pile = Empiler(pile, pile2->info);
    pile2 = Depiler(pile2);
  }
  return ((int)pos);
}

/* ****************************************************************************
| Min_Pile
| Entrées : Cellule *pile - Pointeur vers la pile
|           int *Rang - Pointeur vers une variable qui contiendra le rang de la valeur minimale
| Sorties : int - Valeur minimale de la pile
| La fonction permet de trouver la valeur minimale dans la pile.
| Elle utilise un pointeur temporaire pour inverser la pile, parcourt les éléments un par un
| en maintenant le minimum trouvé jusqu'à présent, et renvoie la valeur minimale ainsi que son rang.
*/
int Min_Pile(Cellule *pile, int *Rang)
{
  Cellule *tmp = NULL;
  int min, rang, i = 1;
  if (!pile)
  {
    *Rang = 0;
    return ((int)0);
  }
  min = pile->info;
  rang = 1;
  while (pile->svt)
  {
    tmp = Empiler(tmp, pile->info);
    pile = Depiler(pile);
    i++;
    if (pile->info < min)
    {
      min = pile->info;
      rang = i;
    }
  }
  while (tmp)
  {
    pile = Empiler(pile, tmp->info);
    tmp = Depiler(tmp);
  }
  *Rang = rang;
  return ((int)min);
}

/* ****************************************************************************
| Supprimer_Repititions_Pile
| Entrées : Cellule *pile - Pointeur vers la pile
| Sorties : Cellule * - Nouveau pointeur vers la pile après la suppression des répétitions
| La fonction permet de supprimer toutes les répétitions dans la pile.
| Elle parcourt la pile en utilisant deux pointeurs temporaires et supprime les éléments
| qui sont identiques à ceux qui les précèdent.
*/
Cellule *Supprimer_Repititions_Pile(Cellule *pile)
{
  Cellule *tmpSD = NULL, *tmpAD = NULL;
  if (!pile) return ((Cellule *)pile);
  while (pile)
  {
    tmpSD = Empiler(tmpSD, pile->info);
    pile = Depiler(pile);
    while (pile)
    {
      if (pile->info != tmpSD->info) tmpAD = Empiler(tmpAD, pile->info);
      pile = Depiler(pile);
    }
    while (tmpAD)
    {
      pile = Empiler(pile, tmpAD->info);
      tmpAD = Depiler(tmpAD);
    }
  }
  while (tmpSD)
  {
    pile = Empiler(pile, tmpSD->info);
    tmpSD = Depiler(tmpSD);
  }
  return ((Cellule *)pile);
}
