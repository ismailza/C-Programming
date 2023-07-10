/*                  Fonctions de manipulation des structures                 */

/* ****************************************************************************
| Transfere_Liste_Pile_Ordonnee
| Entrées : Cellule *liste - un pointeur vers une liste chaînée
| Sorties : Cellule * - un pointeur vers une pile
| La fonction permet de transférer les éléments d'une liste chaînée dans une pile de manière ordonnée.
*/
Cellule *Transfere_Liste_Pile_Ordonnee(Cellule *liste)
{
  Cellule *pile = NULL, *courant[1], *tmp = NULL;
  if (!liste) return ((Cellule *)NULL);
  while (liste)
  {
    liste = Recuperer_Min_Liste(liste, courant);
    tmp = Empiler(tmp, courant[0]->info);
  }
  while (tmp)
  {
    pile = Empiler(pile, tmp->info);
    tmp = Depiler(tmp);
  }
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Transfere_TAB_Liste
| Entrées : TAB *T - un pointeur vers une structure TAB
| Sorties : Cellule * - un pointeur vers une liste chaînée
| La fonction permet de transférer les éléments d'un tableau dans une liste chaînée.
*/
Cellule *Transfere_TAB_Liste(TAB *T)
{
  Cellule *liste = NULL;
  if (!T) 
  {
    printf("\nErreur: La table n'existe pas!!");
    exit(0);
  }
  for (int i = 0; i <= T->IDE; i++) 
    liste = Inserer_Liste_Fin(liste, T->info[i]);
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Transfere_TAB_Pile
| Entrées : TAB *T - un pointeur vers une structure TAB
| Sorties : Cellule * - un pointeur vers une pile
| La fonction permet de transférer les éléments d'un tableau dans une pile.
*/
Cellule *Transfere_TAB_Pile(TAB *T)
{
  Cellule *pile = NULL;
  if (!T) 
  {
    printf("\nErreur: La table n'existe pas!!");
    exit(0);
  }
  for (int i = 0; i <= T->IDE; i++)
    pile = Empiler(pile, T->info[i]);
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Transfere_TAB_File
| Entrées : TAB *T - un pointeur vers une structure TAB
| Sorties : File * - un pointeur vers une file
| La fonction permet de transférer les éléments d'un tableau dans une file.
*/
File *Transfere_TAB_File(TAB *T)
{
  int rt;
  File *file = CreerFile();
  if (!T) 
  {
    printf("\nErreur: La table n'existe pas!!");
    exit(0);
  }
  for (int i = 0; i <= T->IDE; i++)
    rt = Enfiler(file, T->info[i]);
  return ((File *)file);
}
/* ****************************************************************************
| Transfere_Liste_Pile
| Entrées : Cellule *liste - un pointeur vers une liste chaînée
| Sorties : Cellule * - un pointeur vers une pile
| La fonction permet de transférer les éléments d'une liste chaînée dans une pile.
*/
Cellule *Transfere_Liste_Pile(Cellule *liste)
{
  Cellule *pile = NULL, *courant = liste;
  while (courant)
  {
    pile = Empiler(pile, courant->info);
    courant = courant->svt;
  }
  return ((Cellule *)pile);
}
/* ****************************************************************************
| Transfere_Pile_File
| Entrées : Cellule *pile - un pointeur vers une pile
| Sorties : File * - un pointeur vers une file
| La fonction permet de transférer les éléments d'une pile dans une file.
*/
File *Transfere_Pile_File(Cellule *pile)
{
  int rt;
  File *file = CreerFile();
  while (pile)
  {
    rt = Enfiler(file, pile->info);
    pile = Depiler(pile);
  }
  return ((File *)file);
}
/* ****************************************************************************
| Transfere_File_Arbre_Ordonne
| Entrées : File *file - un pointeur vers une file
| Sorties : Noeud * - un pointeur vers un arbre binaire ordonné
| La fonction permet de transférer les éléments d'une file dans un arbre binaire ordonné.
*/
Noeud *Transfere_File_Arbre_Ordonne(File *file)
{
  Noeud *Arbre = NULL;
  int rt;
  if (!file)
  {
    printf("\nErreur: La file n'existe pas!!");
    exit(0);
  }
  while (file->Tete)
  {
    Arbre = Inserer_ArbBin_Ordonne(Arbre, file->Tete->info);
    rt = Defiler(file);
  }
  return ((Noeud *)Arbre);
}
/* ****************************************************************************
| Transfere_ArbreBin_Ordonne_Liste_Rec
| Entrées : Noeud *Arb - un pointeur vers un arbre binaire ordonné
|           Cellule *liste - un pointeur vers une liste chaînée
| Sorties : Cellule * - un pointeur vers une liste chaînée
| La fonction permet de transférer les éléments d'un arbre binaire ordonné dans une liste chaînée récursivement.
*/
Cellule *Transfere_ArbreBin_Ordonne_Liste_Rec(Noeud *Arb, Cellule *liste)
{
  if (Arb)
  {
    liste = Inserer_Liste_Fin(liste, Arb->info);
    liste = Transfere_ArbreBin_Ordonne_Liste_Rec(Arb->fgc, liste);
    liste = Transfere_ArbreBin_Ordonne_Liste_Rec(Arb->fdt, liste);
  }
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Transfere_ArbreBin_Ordonne_Liste
| Entrées : Noeud *Arb - un pointeur vers un arbre binaire ordonné
| Sorties : Cellule * - un pointeur vers une liste chaînée
| La fonction permet de transférer les éléments d'un arbre binaire ordonné dans une liste chaînée.
*/
Cellule *Transfere_ArbreBin_Ordonne_Liste(Noeud *Arb)
{
  Cellule *liste = NULL;
  return ((Cellule *)Transfere_ArbreBin_Ordonne_Liste_Rec(Arb, liste));
}
