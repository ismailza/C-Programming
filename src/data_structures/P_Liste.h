/*                                  Liste                                    */

/* ****************************************************************************
| CreerCellule
| Entrées : int val   - la valeur de la cellule à créer
| Sorties : Cellule * - un pointeur vers la cellule créée
| La fonction permet de créer une nouvelle cellule avec la valeur spécifiée et 
| renvoyer un pointeur vers celle-ci.
*/
Cellule *CreerCellule(int val)
{
  // Allocation mémoire pour une nouvelle cellule
  Cellule *CL = (Cellule *)malloc(sizeof(Cellule)); 
  if (!CL)  // Vérification si l'allocation a échouée
  {
    printf("\nErreur d'allocation memoire pour la cellule!"); 
    exit(0);
  }
  CL->info = val; // Initialisation de la valeur de la cellule avec val
  CL->svt = NULL; // Initialisation du pointeur suivant à NULL
  return ((Cellule *)CL);
}
/* ****************************************************************************
| Taille_Liste
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
| Sorties : int             - la taille de la liste
| La fonction permet de calculer et renvoyer la taille de la liste.
*/
int Taille_Liste(Cellule *liste)
{
  int taille = 0; // Variable pour stocker la taille de la liste
  Cellule *courant = liste; // Pointeur pour parcourir la liste
  while (courant)
  {                         
    taille++;               // Incrémenter la taille
    courant = courant->svt; // Passer à l'élément suivant
  }
  return ((int)taille);
}
/* ****************************************************************************
| Inserer_Liste_Debut
| Entrées : Cellule * liste - un pointeur vers la tête de la liste
|           int val         - la valeur à insérer
| Sorties : Cellule *       - un pointeur vers la nouvelle tête de la liste
| La fonction permet d'insèrer un nouvel élément contenant la valeur spécifiée 
| au début de la liste et renvoyer un pointeur vers la nouvelle tête de liste.
*/
Cellule *Inserer_Liste_Debut(Cellule *liste, int val)
{
  // Créer une nouvelle cellule avec la valeur val
  Cellule *CL = CreerCellule(val); 
  // Le pointeur suivant de la nouvelle cellule pointe vers l'ancienne liste
  CL->svt = liste; 
  return ((Cellule *)CL);
}
/* ****************************************************************************
| Inserer_Liste_Fin
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
|           int val         - la valeur à insérer
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonctio permet d'insèrer un nouvel élément contenant la valeur spécifiée à 
| la fin de la liste et renvoyer un pointeur vers la tête de liste.
*/
Cellule *Inserer_Liste_Fin(Cellule *liste, int val)
{
  Cellule *courant, *CL = CreerCellule(val); // Créer une nouvelle cellule avec la valeur val
  if (!liste) return ((Cellule *)CL); // Si la liste est vide, retourner la nouvelle cellule comme liste
  courant = liste;
  while (courant->svt) courant = courant->svt; // Parcourir la liste jusqu'au dernier élément
  courant->svt = CL; // Le pointeur suivant du dernier élément pointe vers la nouvelle cellule
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Inserer_Liste_Pos
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
|           int Pos         - la position à laquelle insérer l'élément
|           int val         - la valeur à insérer
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonction permet d'insèrer un nouvel élément contenant la valeur spécifiée 
| à la position spécifiée dans la liste et renvoyer un pointeur vers la tête de
| liste.
*/
Cellule* Inserer_Liste_Pos(Cellule* liste, int Pos, int val) 
{
  int i = 2;
  Cellule* courant, *CL;
  if (Pos <= 0) 
  {
    printf("\nPosition incorrecte!!"); // Vérifier si la position est valide
    return liste;
  }
  if (Pos == 1 || !liste) return Inserer_Liste_Debut(liste, val); // Insérer en début de liste si la position est 1 ou si la liste est vide
  courant = liste;
  while (courant->svt && i < Pos) 
  {
    courant = courant->svt; // Parcourir la liste jusqu'à la position souhaitée
    i++;
  }
  CL = CreerCellule(val); // Créer une nouvelle cellule avec la valeur val
  CL->svt = courant->svt; // Le pointeur suivant de la nouvelle cellule pointe vers l'élément suivant du courant
  courant->svt = CL; // Le pointeur suivant du courant pointe vers la nouvelle cellule
  return liste;
}
/* ****************************************************************************
| Inserer_Bonne_Place_Liste
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
|           int val         - la valeur à insérer
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonction permet d'insèrer un nouvel élément contenant la valeur spécifiée 
| à la bonne position dans une liste triée et renvoyer un pointeur vers la tête
| de liste.
*/
Cellule *Inserer_Bonne_Place_Liste(Cellule *liste, int val)
{
  Cellule *courant, *CL;
  CL = CreerCellule(val); // Créer une nouvelle cellule avec la valeur val
  if (!liste) return ((Cellule *)CL); // Si la liste est vide, retourner la nouvelle cellule comme liste
  // Insertion en tête
  if (val < liste->info)
  {
    CL->svt = liste; // Le pointeur suivant de la nouvelle cellule pointe vers l'ancienne liste
    return ((Cellule *)CL);
  }
  courant = liste;
  while (courant->svt)
  { 
    // Insertion en milieu
    if (val <= courant->svt->info)
    {
      CL->svt = courant->svt; // Le pointeur suivant de la nouvelle cellule pointe vers l'élément suivant du courant
      courant->svt = CL; // Le pointeur suivant du courant pointe vers la nouvelle cellule
      return ((Cellule *)liste);
    }
    courant = courant->svt;
  }
  // Insertion en queue
  courant->svt = CL; // Le pointeur suivant du dernier élément pointe vers la nouvelle cellule
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Supprimer_Liste_Debut
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
| Sorties : Cellule *       - un pointeur vers la nouvelle tête de la liste
| La fonction permet de supprimer le premier élément de la liste et renvoyer un
| pointeur vers la nouvelle tête de liste.
*/
Cellule *Supprimer_Liste_Debut(Cellule *liste)
{
  Cellule *Supp;
  if (!liste) return ((Cellule *)NULL); // Vérifier si la liste existe
  Supp = liste;               // Élément à supprimer
  liste = liste->svt;         // Passer à l'élément suivant
  free(Supp);                 // Libérer la mémoire
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Supprimer_Liste_Fin
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonction permet de supprimer le dernier élément de la liste et renvoyer un
| pointeur vers la tête de liste.
*/
Cellule *Supprimer_Liste_Fin(Cellule *liste)
{
  Cellule *courant, *Supp;
  if (!liste) return ((Cellule *)NULL); // Vérifier si la liste existe
  Supp = liste;               // Initialiser Supp avec la tête de la liste
  while (Supp->svt)
  { // Tant qu'on a le suivant de Supp
    courant = Supp;
    Supp = Supp->svt;
  }
  courant->svt = NULL;
  free(Supp); // Libérer la zone mémoire
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Supprimer_Liste_Pos
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
|           int Pos         - la position de l'élément à supprimer
|           int *isDeleted  - un pointeur vers un entier pour indiquer si 
|                             l'élément a été supprimé ou non
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonction permet de supprimer l'élément à la position spécifiée dans la 
| liste et renvoyer un pointeur vers la tête de liste.
| Met à jour la valeur de isDeleted pour indiquer si l'élément a été supprimé 
| (1) ou non (0).
*/
Cellule *Supprimer_Liste_Pos(Cellule *liste, int Pos, int *isDeleted)
{
  Cellule *courant, *Supp;
  int i;
  // Initialisation de la variable isDeleted à 0 (pas encore supprimé)
  *isDeleted = 0; 
  // Si la position est invalide ou négative, on retourne la liste inchangée
  if (Pos <= 0) return ((Cellule *)liste); 
  if (Pos == 1) 
  {
    *isDeleted = 1; // Marquer l'élément à la position 1 comme supprimé
    // Appeler la fonction Supprimer_Liste_Debut pour supprimer le premier élément
    return ((Cellule *)Supprimer_Liste_Debut(liste)); 
  }
  i = 2; // Commencer à la position 2
  courant = liste;
  // Parcourir la liste jusqu'à atteindre la position spécifiée
  while (courant->svt && (i < Pos)) 
  {
    courant = courant->svt;
    i++;
  }
  if (courant->svt) // Si on a atteint la position spécifiée dans la liste
  {
    Supp = courant->svt; // Element à supprimer
    // Mettre à jour les liens pour sauter l'élément à supprimer
    courant->svt = courant->svt->svt; 
    free(Supp); // Libérer la mémoire occupée par l'élément supprimé
    *isDeleted = 1; // Marquer l'élément comme supprimé
  }
  return ((Cellule *)liste); // Renvoyer la liste mise à jour
}
/* ****************************************************************************
| Supprimer_Liste_Val
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
|           int val         - la valeur de l'élément à supprimer
|           int *isDeleted  - un pointeur vers un entier pour indiquer si 
|                             l'élément a été supprimé ou non
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonction permet de supprimer l'élément contenant la valeur spécifiée de la
| liste et renvoyer un pointeur vers la tête de liste.
| Met à jour la valeur de isDeleted pour indiquer si l'élément a été supprimé 
| (1) ou non (0).
*/
Cellule *Supprimer_Liste_Val(Cellule *liste, int val, int *isDeleted)
{
  Cellule *courant, *Supp;
  *isDeleted = 0;
  if (!liste) return ((Cellule *)NULL); 
  if (liste->info == val)
  { // Suppression en tête
    Supp = liste;
    liste = liste->svt;
    free(Supp);
    *isDeleted = 1;
    return ((Cellule *)liste);
  }
  courant = liste; // Pointer courant vers la tête de la liste
  while (courant->svt)
  { // Tant que courant a un suivant
    if (courant->svt->info == val)
    { // Si on a trouvé un élément à supprimer
      Supp = courant->svt;
      courant->svt = courant->svt->svt;
      free(Supp); // Libérer la zone mémoire
      *isDeleted = 1;
      return ((Cellule *)liste);
    }
    courant = courant->svt;
  }
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Supprimer_Liste_Occurence
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
|           int val         - la valeur des éléments à supprimer
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonction permet de supprimer tous les éléments contenant la valeur spécifiée
| de la liste et renvoyer un pointeur vers la tête de liste.
*/
Cellule *Supprimer_Liste_Occurence(Cellule *liste, int val)
{
  Cellule *courant, *Supp;
  if (!liste) return ((Cellule *)NULL); // Vérifier si la liste existe
  while (liste->info == val)
  { // Suppression en tête
    Supp = liste;
    liste = liste->svt;
    free(Supp);
  }
  courant = liste; // Pointer courant vers la tête de la liste
  while (courant->svt)
  { // Tant que courant a un suivant
    if (courant->svt->info == val)
    { // Si on a trouvé un élément à supprimer
      Supp = courant->svt;
      courant->svt = courant->svt->svt;
      free(Supp); // Libérer la zone mémoire
      continue;   // Passer à l'élément suivant
    }
    courant = courant->svt;
  }
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Affichage_Liste
| Entrées : Cellule *liste - un pointeur vers la tête de la liste
| Sorties : void
| La fonction permet d'afficher les valeurs des éléments de la liste.
*/
void Affichage_Liste(Cellule *liste)
{
  Cellule *courant;
  if (!liste) printf("\nListe vide");
  else
  {
    printf("\nListe :  ");
    courant = liste;
    while (courant)
    {
      printf("%d\t", courant->info); // Afficher la valeur de la cellule
      courant = courant->svt; // Passer à l'élément suivant
    }
  }
}
/* ****************************************************************************
| Vider_Liste
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
| Sorties : Cellule *       - un pointeur vers la tête de la liste
| La fonction permet de vider la liste en libérant la mémoire occupée par tous 
| les éléments et renvoyer un pointeur vers la tête de liste (NULL).
*/
Cellule *Vider_Liste(Cellule *liste)
{
  Cellule *courant;
  while (liste) // Tant qu'il existe un élément
  {
    courant = liste;    // Affecter l'élément à courant
    liste = liste->svt; // Passer à l'élément suivant
    free(courant);      // Détruire l'élément courant
  }
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Recheche_Liste_Val
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
|           int val         - la valeur à rechercher
| Sorties : int             - la position de la valeur dans la liste 
|                             (-1 si non trouvée, -2 si la liste est vide)
| La fonction permet de chercher la valeur spécifiée dans la liste et renvoyer 
| sa position. Si la valeur n'est pas trouvée, renvoie -1. Si la liste est vide, 
| renvoie -2.
*/
int Recheche_Liste_Val(Cellule *liste, int val)
{
  Cellule *courant;
  int pos;
  if (!liste) return ((int)-1); // La liste est vide
  courant = liste;
  pos = 1;
  while (courant)
  {
    if (courant->info == val) return ((int)pos); // La valeur a été trouvée à la position pos
    pos++;
    courant = courant->svt; // Passer à l'élément suivant
  }
  return ((int)-2); // L'élément n'a pas été trouvé
}
/* ****************************************************************************
| Concatenation_2_Listes
| Entrées : Cellule *liste1 - un pointeur vers la tête de la première liste
|           Cellule *liste2 - un pointeur vers la tête de la deuxième liste
| Sorties : Cellule *       - un pointeur vers la tête de la liste résultante 
|                             de la concaténation
| La fonction permet de concatèner les deux listes spécifiées et renvoyer un 
| pointeur vers la tête de la liste résultante.
*/
Cellule *Concatenation_2_Listes(Cellule *liste1, Cellule *liste2)
{
  Cellule *courant;
  if (!liste1) return ((Cellule *)liste2);
  if (!liste2) return ((Cellule *)liste1);
  courant = liste1;
  while (courant->svt) courant = courant->svt; // Parcourir la liste1 jusqu'au dernier élément
  courant->svt = liste2; // Le pointeur suivant du dernier élément de liste1 pointe vers liste2
  return ((Cellule *)liste1);
}
/* ****************************************************************************
| Recuperer_Min_Liste
| Entrées : Cellule *liste      - un pointeur vers la tête de la liste
|           Cellule *AddMin[1]  - un tableau d'un élément pour stocker le pointeur
|                                 vers le minimum trouvé
| Sorties : Cellule *           - un pointeur vers la tête de la liste sans l'élément 
|                                 minimum
| La fonction permet de récupèrer l'élément minimum dans la liste et renvoyer un
| pointeur vers la tête de la liste sans cet élément.
| Stocke le pointeur vers l'élément minimum dans AddMin[0].
*/
Cellule *Recuperer_Min_Liste(Cellule *liste, Cellule *AddMin[1])
{
  Cellule *courant, *ptMin;
  if (!liste)
  {
    AddMin[0] = NULL;
    return ((Cellule *)NULL);
  }
  ptMin = liste;
  courant = liste->svt;
  while (courant)
  {
    if (courant->info < ptMin->info) ptMin = courant; // Rechercher le minimum dans la liste
    courant = courant->svt;
  }
  if (ptMin == liste) liste = liste->svt; // Si le minimum est en tête de liste, passer à l'élément suivant
  else
  {
    courant = liste;
    while (courant->svt != ptMin) courant = courant->svt; // Parcourir la liste jusqu'au précédent du minimum
    courant->svt = ptMin->svt; // Le pointeur suivant du précédent du minimum pointe vers l'élément suivant du minimum
  }
  ptMin->svt = NULL; // Le pointeur suivant du minimum est mis à NULL
  AddMin[0] = ptMin; // Ajouter le minimum au tableau AddMin
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Concatenation_Ordonnee_2_Listes
| Entrées : Cellule *liste1 - un pointeur vers la tête de la première liste triée
|           Cellule *liste2 - un pointeur vers la tête de la deuxième liste triée
| Sorties : Cellule *       - un pointeur vers la tête de la liste résultante de la 
|                             concaténation triée
| La fonction permet de concatèner les deux listes triées spécifiées et renvoyer 
| un pointeur vers la tête de la liste résultante triée.
*/
Cellule *Concatenation_Ordonnee_2_Listes(Cellule *liste1, Cellule *liste2)
{
  Cellule *liste = NULL, *courant;
  courant = liste1;
  while (courant)
  { // Insérer chaque élément de liste1 dans la liste de manière ordonnée
    liste = Inserer_Bonne_Place_Liste(liste, courant->info); 
    courant = courant->svt;
  }
  courant = liste2;
  while (courant)
  { // Insérer chaque élément de liste2 dans la liste de manière ordonnée
    liste = Inserer_Bonne_Place_Liste(liste, courant->info); 
    courant = courant->svt;
  }
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Supprimer_Repititions_Liste
| Entrées : Cellule *liste  - un pointeur vers la tête de la liste
| Sorties : Cellule *       - un pointeur vers la tête de la liste sans répétitions
| La fonction permet de supprimer toutes les répétitions dans la liste et renvoyer
| un pointeur vers la tête de la liste sans les répétitions.
*/
Cellule *Supprimer_Repititions_Liste(Cellule *liste)
{
  Cellule *courant, *ptr, *pred;
  if (!liste) return ((Cellule *)NULL); // Si la liste est vide, retourner NULL
  courant = liste; // Initialiser le pointeur courant à la tête de la liste
  while (courant)
  {
    ptr = courant->svt; // Pointeur vers l'élément suivant
    pred = courant; // Pointeur vers l'élément précédent
    while (ptr)
    {
      if (ptr->info == courant->info) // Si on trouve un doublon
      {
        pred->svt = pred->svt->svt; // Supprimer les doublons en modifiant les pointeurs suivants
        free(ptr); // Libérer la mémoire de l'élément en double
        ptr = pred; // Réinitialiser ptr pour vérifier l'élément suivant
      }
      pred = ptr; // Mettre à jour le pointeur précédent
      ptr = ptr->svt; // Passer à l'élément suivant
    }
    courant = courant->svt; // Passer à l'élément suivant dans la liste
  }
  return ((Cellule *)liste); // Renvoyer la liste modifiée
}

