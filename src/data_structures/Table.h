/*                                  Table                                    */

/* ****************************************************************************
| Init_TAB
| Entrées : TAB *T  - pointeur vers une structure TAB
| Sorties : int     - indique si l'initialisation a réussi (1) ou échoué (0)
| La fonction permet d'initialiser une structure TAB en mettant l'indice à -1.
*/
int Init_TAB(TAB *T)
{
  if (!T) return ((int)0); // test si la zone memoire existe
  T->IDE = -1;       // la liste est vide
  return ((int)1);
}
/* ****************************************************************************
| Inserer_Bonne_Place_TAB
| Entrées : TAB *T  - pointeur vers une structure TAB
|           int val - valeur à insérer
| Sorties : int     - indique si l'insertion a réussi (1) ou échoué (0)
| La fonction permet d'insérer une valeur dans une structure TAB à la bonne place.
*/
int Inserer_Bonne_Place_TAB(TAB *T, int val)
{
  int i;
  if (!T) return ((int)-1);
  if (T->IDE == MaxElem - 1) return ((int)0);
  i = T->IDE;
  while ((i >= 0) && (val < T->info[i]))
  {
    T->info[i + 1] = T->info[i];
    i--;
  }
  T->info[i + 1] = val;
  ++T->IDE;
  return ((int)1);
}
/* ****************************************************************************
| EstVide_TAB
| Entrées : TAB T - structure TAB
| Sorties : int   - indique si la structure TAB est vide (1) ou non (0)
| La fonction permet de vérifier si une structure TAB est vide.
*/
int EstVide_TAB(TAB T)
{
  return ((int)(T.IDE == -1));
}
/* ****************************************************************************
| EstSaturee_TAB
| Entrées : TAB T - structure TAB
| Sorties : int - indique si la structure TAB est saturée (1) ou non (0)
| La fonction permet de vérifier si une structure TAB est saturée.
*/
int EstSaturee_TAB(TAB T)
{
  return ((int)(T.IDE == (MaxElem - 1)));
}
/* ****************************************************************************
| Affichage_TAB
| Entrées : TAB T - structure TAB
| Sorties : void
| La fonction permet d'afficher les éléments d'une structure TAB.
*/
void Affichage_TAB(TAB T)
{
  if (T.IDE == -1) printf("\nTAB vide");
  else
  {
    printf("\nTAB :\t");
    for (int i = 0; i <= T.IDE; i++) printf("%d\t", T.info[i]);
  }
}
/* ****************************************************************************
| Inserer_TAB_Debut
| Entrées : TAB *T - pointeur vers une structure TAB
|           int val - valeur à insérer
| Sorties : int - indique si l'insertion a réussi (1) ou échoué (0)
| La fonction permet d'insérer une valeur au début d'une structure TAB.
*/
int Inserer_TAB_Debut(TAB *T, int val)
{
  if (!T) return ((int)-1); // test si la zone memoire existe
  if (T->IDE == MaxElem - 1) return ((int)0); // test si la tab est saturee
  for (int i = T->IDE; i >= 0; i--) T->info[i + 1] = T->info[i];
  T->info[0] = val;
  T->IDE++;
  return ((int)1);
}
/* ****************************************************************************
| Inserer_TAB
| Entrées : TAB *T - pointeur vers une structure TAB
|           int val - valeur à insérer
| Sorties : int - indique si l'insertion a réussi (1) ou échoué (0)
| La fonction permet d'insérer une valeur à la fin d'une structure TAB.
*/
int Inserer_TAB(TAB *T, int val)
{
  if (!T) return ((int)-1); // test si la zone memoire existe
  if (T->IDE == MaxElem - 1) return ((int)0);       // test si la tab est saturee
  T->info[++T->IDE] = val; // Insertion a la fin de la liste
  return ((int)1);
}
/* ****************************************************************************
| Inserer_TAB_Pos
| Entrées : TAB *T - pointeur vers une structure TAB
|           int Pos - position d'insertion
|           int val - valeur à insérer
| Sorties : int - indique si l'insertion a réussi (1) ou échoué (0)
| La fonction permet d'insérer une valeur dans une structure TAB à une position donnée.
*/
int Inserer_TAB_Pos(TAB *T, int Pos, int val)
{
  int i;
  if (!T) return ((int)-1); // Tester si la zone memoire existe
  if (EstSaturee_TAB(*T)) return ((int)0); // Tester si la tab est sature
  if ((0 > Pos) || (Pos >= MaxElem)) return ((int)-2); // La position entree doit etre appartient a [0,MaxElem[
  i = ++T->IDE;       // incrementer IDE et l'affecter a i
  while (i > Pos) T->info[i--] = T->info[i];
  T->info[Pos] = val; // affecter Elem dans la position Pos
  return ((int)1);
}
/* ****************************************************************************
| Inserer_TAB_Ordonnee
| Entrées : TAB *T - pointeur vers une structure TAB
|           int Elem - valeur à insérer
| Sorties : int - indique si l'insertion a réussi (1) ou échoué (0)
| La fonction permet d'insérer une valeur dans une structure TAB triée par ordre croissant.
*/
int Inserer_TAB_Ordonnee(TAB *T, int Elem)
{
  int i;
  if (!T) return ((int)-1); // Tester si la zone memoire existe
  if (EstSaturee_TAB(*T)) return ((int)0); // Tester si la T est sature
  i = ++T->IDE;
  while ((0 <= i) && (T->info[--i] > Elem)) T->info[i + 1] = T->info[i];
  T->info[i + 1] = Elem; // Inserer l'element
  return ((int)1);
}
/* ****************************************************************************
| Supprimer_TAB_Debut
| Entrées : TAB *T - pointeur vers une structure TAB
| Sorties : int - indique si la suppression a réussi (1) ou échoué (0)
| La fonction permet de supprimer le premier élément d'une structure TAB.
*/
int Supprimer_TAB_Debut(TAB *T)
{
  if (!T) return ((int)-1); // Tester si la zone memoire existe
  for (int i = 0; i < T->IDE; i++) T->info[i] = T->info[i + 1];
  T->IDE--;
  return ((int)1);
}
/* ****************************************************************************
| Supprimer_TAB
| Entrées : TAB *T - pointeur vers une structure TAB
| Sorties : int - indique si la suppression a réussi (1) ou échoué (0)
| La fonction permet de supprimer le dernier élément d'une structure TAB.
*/
int Supprimer_TAB(TAB *T)
{
  if (!T) return ((int)-1); // Tester si la zone memoire existe
  T->IDE--;           // decrimenter l'indice du dernier element
  return ((int)1);
}
/* ****************************************************************************
| Supprimer_TAB_Pos
| Entrées : TAB *T  - pointeur vers une structure TAB
|           int Pos - La position de suppression
| Sorties : int - indique si la suppression a réussi (1) ou échoué (0)
| La fonction permet de supprimer un élément à une position donnée d'une structure TAB.
*/
int Supprimer_TAB_Pos(TAB *T, int Pos)
{
  if (!T) return ((int)-1); // Tester si la zone memoire existe
  if (Pos < 0 || Pos > T->IDE) return ((int)-2);
  for (int i = Pos; i < T->IDE; i++) T->info[i] = T->info[i + 1];
  T->IDE--;
  return ((int)1);
}
/* ****************************************************************************
| Supprimer_TAB_Val
| Entrées : TAB *T - pointeur vers une structure TAB
|           int val - valeur à supprimer
| Sorties : int - indique si la suppression a réussi (1) ou échoué (0)
| La fonction permet de supprimer la première occurrence d'une valeur dans une structure TAB.
*/
int Supprimer_TAB_Val(TAB *T, int val)
{
  int i = 0;
  if (!T) return ((int)-1);
  while ((T->info[i] != val) && (i <= T->IDE)) i++;
  if (T->info[i] != val) return ((int)0);
  while (i < T->IDE) 
  {
    T->info[i] = T->info[i + 1]; // tasser les elements apres l'element d'une case en arriere
    i++;
  }
  T->IDE--; // decrimenter l'indice du dernier element
  return ((int)1);
}
/* ****************************************************************************
| Supprimer_TAB_Occurence
| Entrées : TAB *T - pointeur vers une structure TAB
|           int val - valeur à supprimer
| Sorties : int - indique si la suppression a réussi (1) ou échoué (0)
| La fonction permet de supprimer toutes les occurrences d'une valeur dans une structure TAB.
*/
int Supprimer_TAB_Occurence(TAB *T, int val)
{
  int i = 0, tmpIDE = -1; // la variable occ pour stocker le nombre d'occurence
  if (!T) return ((int)-1);           // Tester si la zone memoire existe
  for (i = 0; i <= T->IDE; i++) // parcourir la T
  {
    if (T->info[i] != val) T->info[++tmpIDE] = T->info[i];
  }
  T->IDE = tmpIDE; // changer l'indice du dernier element
  return ((int)1);
}
/* ****************************************************************************
| Recherche_TAB
| Entrées : TAB *T - pointeur vers une structure TAB
|           int val - valeur à rechercher
| Sorties : int - position de l'élément recherché (-3 si non trouvé)
| La fonction permet de rechercher une valeur dans une structure TAB.
*/
int Recherche_TAB(TAB *T, int val)
{
  int i = 0;
  if (!T) return ((int)-1); // Tester si la zone memoire existe
  if (EstVide_TAB(*T)) return ((int)-2); // Tester si la T est vide
  while ((T->info[i] != val) && (i <= T->IDE)) i++;
  if (T->info[i] == val) return ((int)i); // retourner la position
  return ((int)-3);  // element non trouve
}
/* ****************************************************************************
| Recherche_TAB_Ordonnee
| Entrées : TAB *T - pointeur vers une structure TAB
|           int val - valeur à rechercher
| Sorties : int - position de l'élément recherché (-3 si non trouvé)
| La fonction permet de rechercher une valeur dans une structure TAB triée par ordre croissant.
*/
int Recherche_TAB_Ordonnee(TAB *T, int val)
{
  int gauche = 0, droite = T->IDE; // borne gauche et droite
  int i;
  if (!T) return ((int)-1); // Tester si la zone memoire existe
  if (EstVide_TAB(*T)) return ((int)-2); // Tester si la T est vide
  while (gauche < droite)
  {
    i = (gauche + droite) / 2;
    if (T->info[i] == val) return ((int)i); // Element trouve
    if (T->info[i] < val) gauche = i + 1; // changer la borne gauche
    else droite = i; // changer la borne droite
  }
  return ((int)-3); // element non trouve
}