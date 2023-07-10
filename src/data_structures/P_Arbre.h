/*                                  Arbre                                    */

/* ****************************************************************************
| CreerNoeud
| Entrées : int val - valeur du noeud à créer
| Sorties : Noeud * - pointeur vers le nouveau noeud créé
| La fonction permet de créer un nouveau noeud avec la valeur spécifiée.
*/
Noeud *CreerNoeud(int val)
{
  Noeud *NE = (Noeud *)malloc(sizeof(Noeud)); // Allocation de la memoire
  if (!NE)
  {
    printf("\nErreur d'allocation de la memoire!");
    exit(0);
  }
  NE->info = val;           // Affectation de la valeur du noeud
  NE->fgc = NE->fdt = NULL; // Initialiser les fils au NULL
  return ((Noeud *)NE);
}
/* ****************************************************************************
| Affichage_Prefixe
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
| Sorties : void
| La fonction permet d'afficher les noeuds de l'arbre en parcours préfixe.
*/
void Affichage_Prefixe(Noeud *Arb)
{
  if (Arb)
  {
    printf("%d\t", Arb->info);
    Affichage_Prefixe(Arb->fgc);
    Affichage_Prefixe(Arb->fdt);
  }
}
/* ****************************************************************************
| Affichage_Infixe
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
| Sorties : void
| La fonction permet d'afficher les noeuds de l'arbre en parcours infixe.
*/
void Affichage_Infixe(Noeud *Arb)
{
  if (Arb)
  {
    Affichage_Infixe(Arb->fgc);
    printf("%d\t", Arb->info);
    Affichage_Infixe(Arb->fdt);
  }
}
/* ****************************************************************************
| Affichage_Postfixe
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
| Sorties : void
| La fonction permet d'afficher les noeuds de l'arbre en parcours postfixe.
*/
void Affichage_Postfixe(Noeud *Arb)
{
  if (Arb)
  {
    Affichage_Postfixe(Arb->fgc);
    Affichage_Postfixe(Arb->fdt);
    printf("%d\t", Arb->info);
  }
}
/* ****************************************************************************
| Affichage_Horizontal
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
|           int n - niveau actuel de l'arbre
| Sorties : void
| La fonction permet d'afficher les noeuds de l'arbre horizontalement avec
| indentation selon leur niveau.
*/
void Affichage_Horizontal(Noeud *Arb, int n)
{
  if (Arb)
  {
    if (Arb->fdt) Affichage_Horizontal(Arb->fdt, n + 1);
    printf("\n");
    for (int i = 0; i < n; i++) printf("\t");
    printf("%d", Arb->info);
    if (Arb->fgc) Affichage_Horizontal(Arb->fgc, n + 1);
  }
}
/* ****************************************************************************
| Taille_Arbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
| Sorties : int - taille de l'arbre
| La fonction permet de calculer le nombre de noeuds dans l'arbre.
*/
int Taille_Arbre(Noeud *Arb)
{
  if (!Arb) return ((int)0); // Arbre vide
  // 1 de la racine plus nombre de noeuds gauches et droits de la racine
  return ((int)(1 + Taille_Arbre(Arb->fgc) + Taille_Arbre(Arb->fdt)));
}
/* ****************************************************************************
| Hauteur_Arbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
| Sorties : int - hauteur de l'arbre
| La fonction permet de calculer la hauteur de l'arbre.
*/
int Hauteur_Arbre(Noeud *Arb)
{
  int HG = 0, HD = 0; // Hauteur gauche et Hauteur droite
  if (!Arb) return ((int)0); // Arbre vide
  if (Arb->fgc) HG = 1 + Hauteur_Arbre(Arb->fgc);
  if (Arb->fdt) HD = 1 + Hauteur_Arbre(Arb->fdt);
  return ((int)((HG < HD) ? HD : HG));
}
/* ****************************************************************************
| ViderArbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
| Sorties : Noeud * - pointeur vers la racine de l'arbre vide
| La fonction permet de vider complètement l'arbre et libérer la mémoire.
*/
Noeud *ViderArbre(Noeud *Arb)
{
  if (!Arb) return ((Noeud *)NULL);// Arbre Vide
  Arb->fgc = ViderArbre(Arb->fgc); // Vider sous arbre gauche
  Arb->fdt = ViderArbre(Arb->fdt); // Vider sous arbre droit
  free(Arb);                       // Liberer la memoire
  return ((Noeud *)NULL);
}
/* ****************************************************************************
| Min_Arbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
|           int *Min - pointeur vers la variable de stockage du minimum
| Sorties : int - valeur booléenne indiquant si le minimum a été trouvé
| La fonction permet de trouver la valeur minimale dans l'arbre.
*/
int Min_Arbre(Noeud *Arb, int *Min)
{
  int rt, min;
  if (!Arb) return ((int)0);
  *Min = Arb->info;
  if (Arb->fgc)
  {
    rt = Min_Arbre(Arb->fgc, &min);
    if (min < *Min) *Min = min;
  }
  if (Arb->fdt)
  {
    rt = Min_Arbre(Arb->fdt, &min);
    if (min < *Min) *Min = min;
  }
  return ((int)1);
}
/* ****************************************************************************
| Max_Arbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
|           int *Max - pointeur vers la variable de stockage du maximum
| Sorties :int - valeur booléenne indiquant si le maximum a été trouvé
| La fonction permet de trouver la valeur maximale dans l'arbre.
*/
int Max_Arbre(Noeud *Arb, int *Max)
{
  int rt, max;
  if (!Arb) return ((int)0);
  *Max = Arb->info;
  if (Arb->fgc)
  {
    rt = Max_Arbre(Arb->fgc, &max);
    if (*Max < max) *Max = max;
  }
  if (Arb->fdt)
  {
    rt = Max_Arbre(Arb->fdt, &max);
    if (*Max < max) *Max = max;
  }
  return ((int)1);
}
/* ****************************************************************************
| Inserer_Arbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
|           int val - valeur à insérer dans l'arbre
| Sorties : Noeud * - pointeur vers la racine de l'arbre mis à jour
| La fonction permet d'insérer une valeur dans l'arbre en respectant les règles
| d'ordre.
*/
Noeud *Inserer_Arbre(Noeud *Arb, int val)
{
  Noeud *NE;
  int dir;
  if (!Arb)
  {
    NE = CreerNoeud(val);
    return ((Noeud *)NE);
  }
  do
  {
    printf("\nTaper 1 si vous voulez inserer a gauche, 2 si a droit : ");
    scanf("%d", &dir);
    if (dir == 1) Arb->fgc = Inserer_Arbre(Arb->fgc, val);
    else if (dir == 2) Arb->fdt = Inserer_Arbre(Arb->fdt, val);
    else printf("\nChoix invalide !");
  } while (dir != 1 && dir != 2);
  return ((Noeud *)Arb);
}
/* ****************************************************************************
| Recherche_Val_Arbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
|           int val - valeur à rechercher dans l'arbre
| Sorties : int - valeur booléenne indiquant si la valeur a été trouvée
| La fonction permet de rechercher une valeur dans l'arbre.
*/
int Recherche_Val_Arbre(Noeud *Arb, int val)
{
  int rt;
  if (!Arb) return ((int)-1);
  if (Arb->info == val) return ((int)1);
  if (Arb->fgc)
  {
    rt = Recherche_Val_Arbre(Arb->fgc, val);
    if (rt == 1) return ((int)1);
  }
  if (Arb->fdt)
  {
    rt = Recherche_Val_Arbre(Arb->fdt, val);
    if (rt == 1) return ((int)1);
  }
  return ((int)0);
}
/* ****************************************************************************
| Supprimer_Val_Arbre
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre
|           int val - valeur à supprimer de l'arbre
|           int *supp - pointeur vers la variable de stockage de l'état de suppression
| Sorties : Noeud * - pointeur vers la racine de l'arbre mis à jour
| La fonction permet de supprimer une valeur de l'arbre.
*/
Noeud *Supprimer_Val_Arbre(Noeud *Arb, int val, int *supp)
{
  int rt;
  Noeud *pred, *courant, *tmp;
  *supp = 0;
  if (!Arb) return ((Noeud *)NULL);
  if (Arb->info == val)
  {
    tmp = Arb;
    if (!Arb->fgc) Arb = Arb->fdt;
    else if (!Arb->fdt) Arb = Arb->fgc;
    else
    {
      courant = Arb->fgc;
      if (courant->fdt)
      {
        pred = Arb;
        while (courant->fdt)
        {
          pred = courant;
          courant = courant->fdt;
        }
        pred->fdt = courant->fgc;
        courant->fgc = Arb->fgc;
      }
      courant->fdt = Arb->fdt;
      Arb = courant;
    }
    free(tmp);
    *supp = 1;
  }
  else
  {
    Arb->fgc = Supprimer_Val_Arbre(Arb->fgc, val, supp);
    if (*supp == 0) Arb->fdt = Supprimer_Val_Arbre(Arb->fdt, val, supp);
  }
  return ((Noeud *)Arb);
}
/* ****************************************************************************
| Min_Arbre_Ordonne
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre ordonné
|           int *Min - pointeur vers la variable de stockage du minimum
| Sorties : int - valeur booléenne indiquant si le minimum a été trouvé
| La fonction permet de trouver la valeur minimale dans un arbre ordonné.
*/
int Min_Arbre_Ordonne(Noeud *Arb, int *Min)
{
  int rt;
  if (!Arb) return ((int)0);
  *Min = Arb->info;
  if (Arb->fgc) rt = Min_Arbre_Ordonne(Arb->fgc, Min);
  return ((int)1);
}
/* ****************************************************************************
| Max_Arbre_Ordonne
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre ordonné
|           int *Max - pointeur vers la variable de stockage du maximum
| Sorties : int - valeur booléenne indiquant si le maximum a été trouvé
| La fonction permet de trouver la valeur maximale dans un arbre ordonné.
*/
int Max_Arbre_Ordonne(Noeud *Arb, int *Max)
{
  int rt;
  if (!Arb) return ((int)0);
  *Max = Arb->info;
  if (Arb->fdt) rt = Max_Arbre_Ordonne(Arb->fdt, Max);
  return ((int)1);
}
/* ****************************************************************************
| Inserer_ArbBin_Ordonne
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre ordonné
|           int val - valeur à insérer dans l'arbre ordonné
| Sorties : Noeud * - pointeur vers la racine del'arbre ordonné mis à jour
| La fonction permet d'insérer une valeur dans un arbre ordonné en respectant
| l'ordre croissant des valeurs.
*/
Noeud *Inserer_ArbBin_Ordonne(Noeud *Arb, int val)
{
  Noeud *NE;
  if (!Arb) // Arbre vide
  {
    NE = CreerNoeud(val); // Creer un noued
    return ((Noeud *)NE);
  }
  // Insertion dans la partie gauche
  if (val < Arb->info) Arb->fgc = Inserer_ArbBin_Ordonne(Arb->fgc, val);
  // Insertion dans la partie droite
  else Arb->fdt = Inserer_ArbBin_Ordonne(Arb->fdt, val);
  return ((Noeud *)Arb);
}
/* ****************************************************************************
| Recherche_ArbBin_Ordonne
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre ordonné
|           int val - valeur à rechercher dans l'arbre ordonné
| Sorties : int - valeur booléenne indiquant si la valeur a été trouvée
| La fonction permet de rechercher une valeur dans un arbre ordonné.
*/
int Recherche_ArbBin_Ordonne(Noeud *Arb, int val)
{
  if (!Arb) return ((int)-1); // Arbre vide
  if (Arb->info == val) return ((int)1); // Element trouve
  if (val < Arb->info)
  {
    if (!Arb->fgc) return ((int)0);
    return ((int)Recherche_ArbBin_Ordonne(Arb->fgc, val));
  }
  if (!Arb->fdt) return ((int)0);
  return ((int)Recherche_ArbBin_Ordonne(Arb->fdt, val));
}
/* ****************************************************************************
| Supprimer_ArbBin_Ordonne
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre ordonné
|           int val - valeur à supprimer de l'arbre ordonné
|           int *supp - pointeur vers la variable de stockage de l'état de suppression
| Sorties : Noeud * - pointeur vers la racine de l'arbre ordonné mis à jour
| La fonction permet de supprimer une valeur de l'arbre ordonné.
*/
Noeud *Supprimer_ArbBin_Ordonne(Noeud *Arb, int val, int *supp)
{
  Noeud *pred, *courant, *tmp;
  *supp = 0;
  if (!Arb) return ((Noeud *)NULL); // Arbre vide
  if (val < Arb->info)      // Recherche dans la sous arbre gauche
  {
    if (!Arb->fgc) return ((Noeud *)Arb); // Pas de fils gauche
    Arb->fgc = Supprimer_ArbBin_Ordonne(Arb->fgc, val, supp);
  }
  else
  {
    if (Arb->info < val) // Recherche dans la sous arbre droit
    {
      if (!Arb->fdt) return ((Noeud *)Arb); // Pas de fils droit
      Arb->fdt = Supprimer_ArbBin_Ordonne(Arb->fdt, val, supp);
    }
    else // Valeur trouvee
    {
      tmp = Arb; // pour liberer la memoire
      if (!Arb->fgc) Arb = Arb->fdt; // Pas de fils gauche
      else
      {
        if (!Arb->fdt) Arb = Arb->fgc; // Pas de fils droit
        else
        {
          courant = Arb->fgc;
          if (courant->fdt) // si le fils gauche a un fils droit
          {
            pred = Arb;
            while (courant->fdt) // Tant qu'on a un fils droit
            {
              pred = courant;
              courant = courant->fdt;
            }
            pred->fdt = courant->fgc;
            courant->fgc = Arb->fgc;
          }
          courant->fdt = Arb->fdt;
          Arb = courant;
        }
      }
      free(tmp); // liberer la memoire
      *supp = 1; // Suppression effectuee
    }
  }
  return ((Noeud *)Arb);
}
/* ****************************************************************************
| Affichage_Infixe_Bornee
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre ordonné
|           int Inf - valeur minimale de la borne
|           int Sup - valeur maximale de la borne
| Sorties : void
| La fonction permet d'afficher les noeuds de l'arbre ordonné qui se trouvent
| entre les bornes spécifiées.
*/
void Affichage_Infixe_Bornee(Noeud *Arb, int Inf, int Sup)
{
  if (Arb)
  {
    if (Inf <= Arb->info) Affichage_Infixe_Bornee(Arb->fgc, Inf, Sup);
    if (Inf <= Arb->info && Arb->info <= Sup) printf("%d\t", Arb->info);
    if (Arb->info <= Sup) Affichage_Infixe_Bornee(Arb->fdt, Inf, Sup);
  }
}
/* ****************************************************************************
| Recherche_Doubles_ArbBin_Ordonne
| Entrées : Noeud *Arb - pointeur vers la racine de l'arbre ordonné
|           int val - valeur à rechercher dans l'arbre ordonné
| Sorties : int - valeur booléenne indiquant si des doubles ont été trouvés
| La fonction permet de rechercher des doubles dans un arbre ordonné à partir
| d'une valeur spécifique.
*/
int Recherche_Doubles_ArbBin_Ordonne(Noeud *Arb, int val)
{
  int rt;
  rt = Recherche_ArbBin_Ordonne(Arb, val);
  if (rt == 1)
  {
    printf("\n%d", val);
    rt = Recherche_Doubles_ArbBin_Ordonne(Arb, 2 * val);
    return ((int)1);
  }
  return ((int)0);
}
