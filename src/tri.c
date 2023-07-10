#include <stdio.h>
#include <stdlib.h>



#define MaxElem 30

typedef struct
{
  int info[MaxElem];
  int NbElem;
} TAB;

typedef struct CL
{
  int cle;
  struct CL *svt;
} Cellule;

/* ****************************************************************************
| InsererTab
| Entrées : TAB *tab - pointeur vers une structure de tableau
|           int val - valeur à insérer dans le tableau
| Sorties : int - code de retour indiquant le succès ou l'échec de l'opération
| La fonction permet d'insérer une valeur dans un tableau.
*/
int InsererTab(TAB *tab, int val)
{
  if (!tab) return ((int)-1);
  if (tab->NbElem == MaxElem) return ((int)0);
  tab->info[tab->NbElem++] = val;
  return ((int)1);
}
/* ****************************************************************************
| AfficherTab
| Entrées : TAB tab - une structure de tableau
| Sorties : void
| La fonction permet d'afficher les éléments d'un tableau.
*/
void AfficherTab(TAB tab)
{
  printf("\nTAB :\t");
  for (int i = 0; i < tab.NbElem; i++) printf("%d\t", tab.info[i]);
}
/* ****************************************************************************
| CreerCellule
| Entrées : int cle - valeur à insérer dans la cellule
| Sorties : Cellule* - pointeur vers une cellule nouvellement créée
| La fonction permet de créer une nouvelle cellule et d'initialiser sa valeur.
*/
Cellule *CreerCellule(int cle)
{
  Cellule *NE = (Cellule *)malloc(sizeof(Cellule)); // Allocation de la memoire
  if (!NE)
  {
    printf("\nErreur d'allocation de la memoire!");
    exit(0);
  }
  NE->cle = cle;
  NE->svt = NULL; // Initialisation de pointeur suivant
  return ((Cellule *)NE);
}
/* ****************************************************************************
| InsererListeFin
| Entrées : Cellule *liste - pointeur vers une liste
|           int val - valeur à insérer dans la liste
| Sorties : Cellule* - pointeur vers la liste mise à jour
| La fonction permet d'insérer une valeur à la fin d'une liste.
*/
Cellule *InsererListeFin(Cellule *liste, int val)
{
  Cellule *CL, *courant;
  CL = CreerCellule(val); // Creer l'element
  if (!liste) return ((Cellule *)CL); // tester si la liste existe
  courant = liste;          // Initialiser courant a la tete de la liste
  while (courant->svt)      // tant que courant a un svt
    courant = courant->svt; // passer a l'element svt
  courant->svt = CL;        // Inserer l'element
  return ((Cellule *)liste);
}
/* ****************************************************************************
| AfficherListe
| Entrées : Cellule *liste - pointeur vers une liste
| Sorties : void
| La fonction permet d'afficher les éléments d'une liste.
*/
void AfficherListe(Cellule *liste)
{
  Cellule *courant;
  // si la liste est vide
  if (!liste) printf("\nLa liste est vide");
  else
  {
    courant = liste; // initialiser courant par la tete de la liste
    printf("\nListe : ");
    while (courant)
    {                               // tant qu'on a un element dans la liste
      printf("%d\t", courant->cle); // afficher l'element
      courant = courant->svt;       // passer au suivant
    }
  }
}
/* ********************************************************************************
| Echange
| Entrées : TAB *T - pointeur vers une structure de tableau
|           int ind1 - indice du premier élément à échanger
|           int ind2 - indice du deuxième élément à échanger
| Sorties : int - code de retour indiquant le succès ou l'échec de l'opération
| La fonction permet d'échanger deux valeurs dans un tableau.
*/
int Echange(TAB *T, int ind1, int ind2)
{
  int tmp;
  if (!T) return ((int)-1);
  if (((ind1 < 0) || (ind1 >= T->NbElem)) && ((ind2 < 0) || (ind2 >= T->NbElem)))
    return ((int)0);
  tmp = T->info[ind1];
  T->info[ind1] = T->info[ind2];
  T->info[ind2] = tmp;
  return ((int)1);
}
/* ********************************************************************************
| Echange_Adresse
| Entrées : int *add1 - adresse du premier élément à échanger
|           int *add2 - adresse du deuxième élément à échanger
| Sorties : int - code de retour indiquant le succès ou l'échec de l'opération
| La fonction permet d'échanger deux adresses passées en paramètres.
*/
int Echange_Adresse(int *add1, int *add2)
{
  int tmp;
  if (!add1 || !add2) return ((int)0);
  tmp = *add1;
  *add1 = *add2;
  *add2 = tmp;
  return ((int)1);
}

/* ********************************************************************************
                                TRI A BULLES
******************************************************************************** */
/* ********************************************************************************
| Tri_A_Bulles_Table
| Entrées : TAB *T - pointeur vers une structure de tableau à trier
| Sorties : int - code de retour indiquant le succès ou l'échec de l'opération
| La fonction permet de trier un tableau avec la méthode de tri à bulles.
*/
int Tri_A_Bulles_Table(TAB *T)
{
  int i, n, rt, trier = 0;
  if (!T) return ((int)0);
  n = T->NbElem;
  do
  {
    trier = 1;
    for (i = 0; i < n; i++)
    {
      if (T->info[i] > T->info[i + 1])
      {
        rt = Echange(T, i, i + 1);
        trier = 0;
      }
    }
    AfficherTab(*T);
    n--;
  } while (!trier && (n > 1));
  return ((int)1);
}
/* ********************************************************************************
| Tri_A_Bulles_Liste;
| Entrées     : Cellule *liste : une liste à trier
| Sorties     : la liste triée.
| La fonction permet de trier une liste avec la méthode de tri à bulles.
*/
Cellule *Tri_A_Bulles_Liste(Cellule *liste)
{
  Cellule *courant, *ptr = NULL;
  int rt, trier = 0;
  if (!liste) return ((Cellule *)NULL);
  do
  {
    courant = liste;
    trier = 1;
    while (courant->svt != ptr)
    {
      if (courant->cle > courant->svt->cle)
      {
        rt = Echange_Adresse(&courant->cle, &courant->svt->cle);
        trier = 0;
      }
      courant = courant->svt;
    }
    ptr = courant;
    AfficherListe(liste);
  } while (!trier && courant);
  return ((Cellule *)liste);
}

/* ********************************************************************************
                              TRI PAR INSERTION
******************************************************************************** */
/* ********************************************************************************
| Tri_Par_Insertion_Table
| Entrées : TAB *T - une structure de tableau à trier
| Sorties : int    - indique si le tri a été effectué ou non
| La fonction permet de trier un tableau avec la méthode de tri par insertion.
*/
int Tri_Par_Insertion_Table(TAB *T)
{
  int i, j, rt;
  if (!T)
    return ((int)0);
  for (i = 1; i < T->NbElem; i++)
  {
    j = i;
    while ((j > 0) && (T->info[j] < T->info[j - 1]))
    {
      rt = Echange(T, j - 1, j);
      j--;
    }
    AfficherTab(*T);
  }
  return ((int)1);
}
/* ********************************************************************************
| Tri_Par_Insertion_Liste
| Entrées : Cellule *liste - une liste à trier
| Sorties : Cellule*       - la liste triée
| La fonction permet de trier une liste avec la méthode de tri par insertion.
*/
Cellule *Tri_Par_Insertion_Liste(Cellule *liste)
{
  Cellule *courant, *ptr; // pointeur qui parcourt la liste
  int rt;
  if (!liste) return ((Cellule *)NULL);
  courant = liste->svt;
  while (courant)
  {
    ptr = liste;
    while (ptr != courant)
    {
      if (ptr->cle > courant->cle) rt = Echange_Adresse(&courant->cle, &ptr->cle);
      ptr = ptr->svt;
    }
    AfficherListe(liste);
    courant = courant->svt;
  }
  return (Cellule *)liste;
}
/* ********************************************************************************
                           TRI PAR SELECTION-ECHANGE
******************************************************************************** */
/* ********************************************************************************
| Min_Relatif_Table
| Entrées : TAB *T - une structure de tableau à trier
|           int indD - l'indice de départ pour la recherche du minimum
| Sorties : int     - l'indice du minimum
| La fonction permet de trouver l'indice du minimum dans un tableau à partir d'une position donnée.
*/
int Min_Relatif_Table(TAB *T, int indD)
{
  int i, idmin = indD;
  if ((indD < 0) || (indD >= T->NbElem)) return ((int)-1);
  for (i = indD; i < T->NbElem; i++)
  {
    if (T->info[i] < T->info[idmin]) idmin = i;
  }
  return ((int)idmin);
}
/* ********************************************************************************
| Tri_Par_Selection_Echange_Table
| Entrées : TAB *T - une structure de tableau à trier
| Sorties : int    - indique si le tri a été effectué ou non
| La fonction permet de trier un tableau avec la méthode de tri par sélection-échange.
*/
int Tri_Par_Selection_Echange_Table(TAB *T)
{
  int i, rt;
  if (!T) return ((int)0);
  for (i = 0; i < T->NbElem - 1; i++)
  {
    rt = Echange(T, i, Min_Relatif_Table(T, i));
    AfficherTab(*T);
  }
  return ((int)1);
}
/* ********************************************************************************
| Min_Relatif_Liste
| Entrées : Cellule *liste - une liste
| Sorties : int*           - l'adresse du minimum
| La fonction permet de trouver l'adresse du minimum dans une liste.
*/
int *Min_Relatif_Liste(Cellule *liste)
{
  int min, *add;
  Cellule *courant;
  if (!liste) return ((int *)NULL);
  courant = liste;
  add = &courant->cle;
  min = courant->cle;
  while (courant->svt)
  {
    if (courant->svt->cle < min)
    {
      min = courant->svt->cle;
      add = &courant->svt->cle;
    }
    courant = courant->svt;
  }
  return ((int *)add);
}
/* ********************************************************************************
| Tri_Par_Selection_Echange_Liste
| Entrées : Cellule *liste - une liste à trier
| Sorties : Cellule*       - la liste triée
| La fonction permet de trier une liste avec la méthode de tri par sélection-échange.
******************************************************************************** */
Cellule *Tri_Par_Selection_Echange_Liste(Cellule *liste)
{
  int rt;
  Cellule *courant;
  if (!liste) return ((Cellule *)NULL);
  courant = liste;
  while (courant->svt)
  {
    rt = Echange_Adresse(&courant->cle, Min_Relatif_Liste(courant->svt));
    AfficherListe(liste);
    courant = courant->svt;
  }
  return ((Cellule *)liste);
}

/* ********************************************************************************
                             TRI RAPIDE (QUICKSORT)
******************************************************************************** */
/* ********************************************************************************
| partitionner
| Entrées : TAB *T - une structure de tableau à partitionner
|           int debut - l'indice de début de la partition
|           int fin   - l'indice de fin de la partition
|           int pivot - la valeur de pivot
| Sorties : int       - l'indice de fin de la première partition
| La fonction permet de partitionner un tableau entre deux positions en deux partitions
| en mettant les valeurs inférieures au pivot dans la première et les autres dans la deuxième.
******************************************************************************** */
int partitionner(TAB *T, int debut, int fin, int pivot)
{
  int gauche = debut, droite = fin, rt;
  do
  {
    if (T->info[droite] < pivot) rt = Echange(T, gauche, droite);
    while (T->info[gauche] < pivot) gauche++;
    while (T->info[droite] >= pivot) droite--;
  } while (gauche <= droite);
  return ((int)gauche);
}
/* ****************************************************************************
| Tri_Par_Insertion_Table2
| Entrées : TAB *T - pointeur vers une structure de tableau à trier
|           int debut - indice de début de tri
|           int fin - indice de fin de tri
| Sorties : int - indique le résultat du tri (1 pour réussite, 0 pour échec)
| La fonction permet de trier une partition d'un tableau avec la méthode de tri par insertion.
*/
int Tri_Par_Insertion_Table2(TAB *T, int debut, int fin)
{
  int i, j, rt;
  if (!T) return ((int)0);
  for (i = debut; i <= fin; i++)
  {
    j = i;
    while ((j > 0) && (T->info[j] < T->info[j - 1]))
    {
      rt = Echange(T, j - 1, j);
      j--;
    }
    AfficherTab(*T);
  }
  return ((int)1);
}
/* ****************************************************************************
| Trouver_Pivot
| Entrées : TAB *T - pointeur vers une structure de tableau
|           int i - indice
|           int j - indice
| Sorties : int - indice du pivot
| La fonction permet de trouver le pivot en choisissant la valeur la plus grande
| des deux premiers éléments dans le tableau.
*/
int Trouver_Pivot(TAB *T, int i, int j)
{
  return ((int)(T->info[j] > T->info[i]) ? j : i);
}
/* ********************************************************************************
| Tri_Rapide_Table
| Entrées : TAB *T - une structure de tableau à trier
|           int debut - l'indice de début du tri
|           int fin   - l'indice de fin du tri
| Sorties : int       - indique si le tri a été effectué ou non
| La fonction permet de trier un tableau avec la méthode de tri rapide (quicksort).
*/
int Tri_Rapide_Table(TAB *T, int debut, int fin)
{
  int pivot, pos_pivot, k;
  if (!T) return ((int)0);
  pos_pivot = Trouver_Pivot(T, debut, debut + 1);
  if ((fin - debut) > 2)
  {
    pivot = T->info[pos_pivot];
    k = partitionner(T, pos_pivot, fin, pivot);
    AfficherTab(*T);
    Tri_Rapide_Table(T, debut, k - 1);
    Tri_Rapide_Table(T, k, fin);
  }
  else k = Tri_Par_Insertion_Table2(T, debut, fin);
  return ((int)1);
}
/* ********************************************************************************
| val_indice
| Entrées : Cellule *liste - une liste
|           int indice - l'indice recherché
| Sorties : Cellule*   - un pointeur vers l'élément de la liste correspondant à l'indice
| La fonction permet de trouver l'élément de la liste correspondant à un indice donné.
*/
Cellule *val_indice(Cellule *liste, int indice)
{
  while (liste && indice != 0)
  {
    liste = liste->svt;
    indice--;
  }
  return ((Cellule *)liste);
}
/* ********************************************************************************
| Trouver_pivot_liste
| Entrées : Cellule *liste - une liste
|           int i - indice 1
|           int j - indice 2
| Sorties : int - l'indice du pivot
| La fonction permet de trouver l'indice du pivot en choisissant la valeur la plus 
| grande des deux premiers éléments dans la liste.
*/
int Trouver_pivot_liste(Cellule *liste, int i, int j)
{
  if (val_indice(liste, i)->cle > val_indice(liste, i + 1)->cle)
    return ((int)i);
  else
    return ((int)i + 1);
}
/* ********************************************************************************
| partition_liste
| Entrées : Cellule *liste - une liste
|           int i - indice de début de la partition
|           int j - indice de fin de la partition
| Sorties : int - l'indice qui divise la liste en deux partitions
| La fonction permet de diviser la liste en deux partitions en utilisant un élément
| pivot. Elle place tous les éléments inférieurs au pivot dans la première partition
| et les autres dans la deuxième.
*/
int partition_liste(Cellule *liste, int i, int j)
{
  int compt = i; // indice de partition
  int premier;   // premier élément
  int indice;
  premier = val_indice(liste, i)->cle;
  for (indice = i + 1; indice <= j; indice++)
  {
    // comparer les éléments avec le premier
    if (val_indice(liste, indice)->cle < premier)
    {
      compt++;
      // échanger les valeurs des clés
      Echange_Adresse(&val_indice(liste, compt)->cle, &val_indice(liste, indice)->cle);
    }
  }
  // échanger le premier élément avec l'élément de partition
  Echange_Adresse(&val_indice(liste, compt)->cle, &val_indice(liste, i)->cle);
  return (int)compt;
}
/* ********************************************************************************
| Tri_Rapide_Liste
| Entrées : Cellule *liste - une liste à trier
|           int i - indice de début du tri
|           int j - indice de fin du tri
| Sorties : void
| La fonction permet de trier une liste avec la méthode de tri rapide (quicksort).
*/
void Tri_Rapide_Liste(Cellule *liste, int i, int j)
{
  int pivot, position_pivot, k;

  if (i >= j) return;                                  // condition d'arrêt
  position_pivot = Trouver_pivot_liste(liste, i, j);   // indice du pivot
  pivot = val_indice(liste, position_pivot)->cle;      // valeur du pivot
  k = partition_liste(liste, i, j);                    // obtenir l'indice qui divise la liste en deux partitions
  AfficherListe(liste);
  Tri_Rapide_Liste(liste, i, k - 1);                   // trier la première partition
  Tri_Rapide_Liste(liste, k + 1, j);                   // trier la deuxième partition
}
/* ********************************************************************************
                               TRI PAR EXTRACTION
******************************************************************************** */
/* ********************************************************************************
| Descente_tab
| Entrées : TAB *T - une structure de tableau
|           int N - le nombre d'éléments du tableau
|           int noeud - l'indice du nœud père
| Sorties : void
| La fonction permet de remplacer le nœud père par la plus grande valeur entre lui et ses fils.
*/
void Descente_tab(TAB *T, int N, int noeud)
{
  int max = noeud;         // indice pour la valeur max initialisé par l'indice du nœud
  int fgc = 2 * noeud;     // indice du fils gauche
  int fdt = 2 * noeud + 1; // indice du fils droit
  if (T)
  {
    // si le fils gauche est supérieur au nœud
    if ((fgc < N) && (T->info[fgc] > T->info[max])) max = fgc;
    // si le fils droit est supérieur au nœud
    if ((fdt < N) && (T->info[fdt] > T->info[max])) max = fdt;
    // si la valeur de max est l'un des deux fils
    if (max != noeud)
    {
      Echange(T, noeud, max); // échanger les valeurs des éléments
      Descente_tab(T, N, max);
    }
  }
}
/* ********************************************************************************
| Tri_Par_Extraction_Table
| Entrées : TAB *T - une structure de tableau à trier
| Sorties : int - indique si le tri a été effectué ou non
| Description : la fonction permet de trier un tableau avec la méthode de tri
|               par extraction (heapsort).
*/
int Tri_Par_Extraction_Table(TAB *T)
{
  int i;
  if (!T) return ((int)0);
  // construction de l'arbre tel que la valeur du nœud est supérieure à celle de ses fils
  for (i = (T->NbElem / 2 - 1); i >= 0; i--) Descente_tab(T, T->NbElem, i);
  for (i = T->NbElem - 1; i >= 1; i--)
  {
    Echange(T, 0, i);          // échanger le premier élément avec le dernier
    Descente_tab(T, i, 0);     // effectuer la descente du premier élément
    AfficherTab(*T);
  }
  return ((int)1);
}
/* ********************************************************************************
| Descente_ptr
| Entrées : Cellule *liste - une liste
|           int i - indice du nœud
|           int taille - taille de la liste
| Sorties : void
| La fonction permet de faire la descente d'un nœud à partir de l'indice spécifié
| jusqu'à la fin de la liste, en mettant à chaque étape le plus grand des fils à 
| la position de la racine.
*/

void Descente_ptr(Cellule *liste, int i, int taille)
{
  int left = 2 * i + 1;  // Indice du fils gauche
  int right = 2 * i + 2;  // Indice du fils droit
  int max;
  max = i;  // Indice initial du nœud
  // Comparaison des fils avec le nœud pour trouver le plus grand
  if (left < taille && val_indice(liste, left)->cle > val_indice(liste, i)->cle)
    max = left;
  if (right < taille && val_indice(liste, right)->cle > val_indice(liste, max)->cle)
    max = right;
  // Échange avec le fils ayant une plus grande valeur et appelle récursivement Descente_ptr sur le fils
  if (max != i)
  {
    Echange_Adresse(&val_indice(liste, i)->cle, &val_indice(liste, max)->cle);
    Descente_ptr(liste, max, taille);
  }
}
/* ****************************************************************************
| construction
| Entrées : Cellule *liste - pointeur vers la liste à construire en tas
|           int taille - taille de la liste
| La fonction construit un tas en appelant la fonction Descente_ptr à partir du
| dernier nœud interne jusqu'au nœud racine.
*/ 
void construction(Cellule *liste, int taille)
{
  int i = (taille - 2) / 2;  // Dernier nœud interne
  while (i >= 0) Descente_ptr(liste, i--, taille);
}
/* ****************************************************************************
| Tri_par_Extraction_Liste
| Entrées : Cellule *liste - pointeur vers la liste à trier
|           int taille - taille de la liste
| La fonction tri la liste avec la méthode de tri par extraction (Heapsort). 
| Elle commence par construire un tas à partir de la liste en appelant la fonction
| construction, puis elle effectue des extractions successives en échangeant le 
| premier noeud (le plus grand) avec le dernier nœud, puis en réduisant la taille du tas.
| Après chaque extraction, elle appelle Descente_ptr pour maintenir les propriétés du tas.
*/ 
void Tri_par_Extraction_Liste(Cellule *liste, int taille)
{
  construction(liste, taille);  // Construction du tas
  while (taille != 1)
  {
    Echange_Adresse(&val_indice(liste, 0)->cle, &val_indice(liste, taille - 1)->cle);  // Échange du premier nœud avec le dernier
    taille--;  // Réduction de la taille du tas
    Descente_ptr(liste, 0, taille);  // Maintien des propriétés du tas en appelant Descente_ptr
    AfficherListe(liste);  // Affichage de la liste après chaque extraction
  }
}
/* ****************************************************************************
| Remplir_Table
| Entrées : TAB *T - pointeur vers une structure de tableau
| Description : La fonction remplit le tableau avec des valeurs prédéfinies.
*/ 
void Remplir_Table(TAB *T)
{
  int rt;
  rt = InsererTab(T, 1);
  rt = InsererTab(T, 4);
  rt = InsererTab(T, 1);
  rt = InsererTab(T, 5);
  rt = InsererTab(T, 9);
  rt = InsererTab(T, 2);
  rt = InsererTab(T, 6);
  rt = InsererTab(T, 5);
  rt = InsererTab(T, 3);
}
/* ****************************************************************************
| Remplir_liste
| Entrées : Cellule *liste - pointeur vers la liste
| Sorties : Cellule* - pointeur vers la liste modifiée
| Description : La fonction remplit la liste avec des valeurs prédéfinies.
*/ 
Cellule *Remplir_liste(Cellule *liste)
{
  liste = InsererListeFin(liste, 1);
  liste = InsererListeFin(liste, 4);
  liste = InsererListeFin(liste, 1);
  liste = InsererListeFin(liste, 5);
  liste = InsererListeFin(liste, 9);
  liste = InsererListeFin(liste, 2);
  liste = InsererListeFin(liste, 6);
  liste = InsererListeFin(liste, 5);
  liste = InsererListeFin(liste, 3);
  return ((Cellule *)liste);
}
/* ****************************************************************************
| Taille_Liste
| Entrées : Cellule *liste - pointeur vers la liste
| Sorties : int - taille de la liste
| Description : La fonction calcule la taille de la liste en parcourant tous les éléments.
*/ 
int Taille_Liste(Cellule *liste)
{
  int t = 0;
  Cellule *courant = liste;
  while (courant)
  {
    t++;
    courant = courant->svt;
  }
  return ((int)t);
}

void main()
{
  int rt, choix, choixT;
  Cellule *liste;
  TAB *T = (TAB *)malloc(sizeof(TAB));
  T->NbElem = 0;
  liste = NULL;
  Remplir_Table(T);
  liste = Remplir_liste(liste);
  printf("\n ********************************************************************************");
  AfficherTab(*T);
  do
  {
    printf("\n ********************************************************************************");
    printf("\n 0 : pour arreter le programme");
    printf("\n 1 : pour travaillez a l'aide de tableau");
    printf("\n 2 : pour travaillez a l'aide de liste");
    printf("\n--> Choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 0: break;
    case 1:
      do
      {
        T->NbElem = 0;
        Remplir_Table(T);
        AfficherTab(*T);
        printf(" \n --------------TRI A L'AIDE D'UN TABLEAU --------------------------\n");
        printf("\n 0 : Retour au Menu principal");
        printf("\n 1 : pour le tri a bulles");
        printf("\n 2 : pour le tri par insertion");
        printf("\n 3 : pour le tri par selection echange");
        printf("\n 4 : pour le tri rapide");
        printf("\n 5 : pour le tri par extraction");
        printf("\n--> Choix : ");
        scanf("%d", &choixT);
        switch (choixT)
        {
        case 0:
          break;
        case 1:
          rt = Tri_A_Bulles_Table(T);
          break;
        case 2:
          rt = Tri_Par_Insertion_Table(T);
          break;
        case 3:
          rt = Tri_Par_Selection_Echange_Table(T);
          break;
        case 4:
          rt = Tri_Rapide_Table(T, 0, T->NbElem - 1);
          break;
        case 5:
          rt = Tri_Par_Extraction_Table(T);
          break;
        default:
          printf("\nChoix invalide\n");
        }
        AfficherTab(*T);
        printf("\n ********************************************************************************");
      } while (choixT);
      break;
    case 2:
      do
      {
        liste = NULL;
        liste = Remplir_liste(liste);
        printf(" \n --------------TRI A L'AIDE D'UNE LISTE --------------------------\n");
        printf("\n 0 : Retour au Menu Principal");
        printf("\n 1 : pour le tri a bulles");
        printf("\n 2 : pour le tri par insertion");
        printf("\n 3 : pour le tri par selection echange");
        printf("\n 4 : pour le tri rapide");
        printf("\n 5 : pour le tri par extraction");
        printf("\n--> Choix : ");
        scanf("%d", &choixT);
        switch (choixT)
        {
        case 0:
          break;
        case 1:
          printf("\nListe initiale");
          AfficherListe(liste);
          liste = Tri_A_Bulles_Liste(liste);
          break;
        case 2:
          printf("\nListe initiale");
          AfficherListe(liste);
          liste = Tri_Par_Insertion_Liste(liste);
          break;
        case 3:
          printf("\nListe initiale");
          AfficherListe(liste);
          liste = Tri_Par_Selection_Echange_Liste(liste);
          break;
        case 4:
          printf("\nListe initiale");
          AfficherListe(liste);
          Tri_Rapide_Liste(liste, 0, Taille_Liste(liste) - 1);
          break;
        case 5:
          printf("\nListe initiale");
          AfficherListe(liste);
          Tri_par_Extraction_Liste(liste, Taille_Liste(liste));
          break;
        default:
          printf("\nChoix invalide!");
        }
        AfficherListe(liste);
        printf("\n ********************************************************************************");
      } while (choixT);
      break;
    default:
      printf("\nChoix invalide");
    }
  } while (choix);
}