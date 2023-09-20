/**
 * A.
 * 1. Ecrivez la structure cplx qui permet de représenter correctement un nombre complexe.
 * 2. Ecrivez la fonction complexe « saisie Complexe1 » qui permet la saisie au clavier d'un nombre complexe.
 * 3. Ecrivez une fonction nommée « saisie Complexe2 » qui fait le même travail en passage par adresse.
 * 4. Ecrivez une fonction nommée « affiche Complexe » qui permet d'afficher un nombre complexe à l'écran. 
 *    Vous passerez le nombre complexe à afficher par adresse.
 * 5. Ecrivez une fonction nommée « produitComplexe » qui permet d'effectuer le produit de deux nombres complexes fournis en paramètre.
 * 6. Ecrivez une fonction nommée «< sommeComplexe » qui permet de calculer la somme de deux nombres complexes fournis en paramètre.
 * B.
 * On souhaite gérer des matrices 2x2 de nombres complexes. On considère à partir de maintenant que toutes les fonctions, structures et types écrits lors de la question précédente sont déjà définies.
 * 1. Ecrivez la structure puis le type mat22cplx qui permet de gérer une matrice 2x2 de nombres complexes.
 * 2. Ecrivez la fonction « saisie Matrice Complexe » qui permet de faire la saisie au clavier d'une matrice 2x2 de nombres complexes.
 * 3. Ecrivez la fonction « affiche MatriceComplexe » qui permet de faire l'affichage d'une matrice 2x2 de nombres complexes.
 * 4. Ecrivez la fonction « produitMatrice Complexe » qui permet de calculer le produit de deux matrices de nombres complexes.
*/
#include <stdio.h>
#include <stdlib.h>

// * La structure d'un nombre complexe
typedef struct
{
  float reel;       // Partie réelle
  float imaginaire; // Partie imaginaire
} cplx;

cplx saisieComplexe1 ()
{
  cplx nb_cplx;
  printf("Saisir la partie reelle du nombre complexe : ");
  scanf("%f", &nb_cplx.reel);
  printf("Saisir la partie imaginaire du nombre complexe : ");
  scanf("%f", &nb_cplx.imaginaire);
  return nb_cplx;
}

int saisieComplexe2 (cplx *nb_cplx)
{
  if (!nb_cplx)
    return -1;
  printf("Saisir la partie reelle du nombre complexe : ");
  scanf("%f", &nb_cplx->reel);
  printf("Saisir la partie imaginaire du nombre complexe : ");
  scanf("%f", &nb_cplx->imaginaire);
  return 1;
}

void afficherComplexe (cplx *nb_cplx)
{
  if (!nb_cplx)
    printf("\nErreur: Le nombre complexe n'existe pas");
  else
    printf("%.2f + %.2f i", nb_cplx->reel, nb_cplx->imaginaire);
}

cplx produitComplexe (cplx num1, cplx num2)
{
  cplx result;
  result.reel = (num1.reel * num2.reel) - (num1.imaginaire * num2.imaginaire);
  result.imaginaire = (num1.reel * num2.imaginaire) + (num2.reel * num1.imaginaire);
  return result;
}

cplx sommeComplexe (cplx num1, cplx num2)
{
  cplx result;
  result.reel = num1.reel + num2.reel;
  result.imaginaire = num1.imaginaire + num2.imaginaire;
  return result;
}

void saisieMatriceComplexe (cplx matrice[2][2])
{
  int i, j;
  for (i = 0; i < 2; i++)
    for (j = 0; j < 2; j++)
      matrice[i][j] = saisieComplexe1();
}

void afficherMatriceComplexe (cplx matrice[2][2])
{
  int i, j;
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 2; j++)
    {
      afficherComplexe(&matrice[i][j]);
      printf("\t");
    }
    printf("\n");
  }
}

void produitMatriceComplexe(cplx result[2][2], cplx matrice1[2][2], cplx matrice2[2][2])
{
  int i, j, k;
  for (i = 0; i < 2; i++)
    for (j = 0; j < 2; j++)
      for (k = 0; k < 2; k++)
        result[i][j] = produitComplexe(matrice1[i][k], matrice2[k][j]);
}

