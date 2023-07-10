#include <stdio.h>
#include <stdlib.h>

#include "data_structures/structs.h"
#include "data_structures/Table.h"
#include "data_structures/P_Liste.h"
#include "data_structures/P_Pile.h"
#include "data_structures/P_File.h"
#include "data_structures/P_Arbre.h"
#include "data_structures/manip_functs.h"

int main()
{
  int rt;
  TAB *T = (TAB *)malloc(sizeof(TAB));
  rt = Init_TAB(T);
  Cellule *pile, *liste;
  File *file = CreerFile();
  Noeud *Arbre;
  // I- Traitement de tableau
  printf("\n*****  Traitement de tableau  *****");
  rt = Inserer_TAB(T,10);
  rt = Inserer_TAB(T,-1);
  rt = Inserer_TAB(T,5);
  rt = Inserer_TAB(T,10);
  rt = Inserer_TAB(T,12);
  rt = Inserer_TAB(T,4);
  rt = Inserer_TAB(T,3);
  rt = Inserer_TAB(T,6);
  rt = Inserer_TAB(T,9);
  rt = Inserer_TAB(T,15);
  rt = Inserer_TAB(T,2);
  rt = Inserer_TAB(T,0);
  printf("\nAffichage de tableau");
  Affichage_TAB(*T);
  printf("\n\nSuppression de la 1ere valeur");
  rt = Supprimer_TAB_Debut(T);
  Affichage_TAB(*T);
  printf("\n\nSuppression de la derniere valeur");
  rt = Supprimer_TAB(T);
  Affichage_TAB(*T);
  printf("\n\nSuppression de la valeur d'indice 4");
  rt = Supprimer_TAB_Pos(T,4);
  Affichage_TAB(*T);
  printf("\n\nInsertion de la valeur 5 au debut");
  rt = Inserer_TAB_Debut(T,5);
  Affichage_TAB(*T);
  printf("\n\nInsertion de la valeur 15 a fin");
  rt = Inserer_TAB(T,15);
  Affichage_TAB(*T);
  printf("\n\nInsertion de la valeur -5 a la 7eme Position");
  rt = Inserer_TAB_Pos(T,7,-5);
  Affichage_TAB(*T);
  // Traitement de pile
  printf("\n\n*****  Traitement de Pile  *****");
  pile = Transfere_TAB_Pile(T);
  printf("\nAffichage de la pile");
  Affichage_Pile(pile);
  printf("\n\nSuppresssion de sommet de la pile");
  pile = Depiler(pile);
  Affichage_Pile(pile);
  printf("\n\nSuppresssion de dernier element de la pile");
  pile = Depiler_Dernier_Elem(pile);
  Affichage_Pile(pile);
  printf("\n\nSuppresssion de 4eme element de la pile");
  pile = Depiler_Pos(pile,4,&rt);
  Affichage_Pile(pile);
  printf("\n\nInsertion de la valeur -2 en tete de la pile");
  pile = Empiler(pile,-2);
  Affichage_Pile(pile);
  printf("\n\nInsertion de la valeur 22 a la 5eme position de la pile");
  pile = Empiler_Pile_Pos(pile,5,22,&rt);
  Affichage_Pile(pile);
  printf("\n\nInsertion de la valeur 33 en bas de la pile");
  pile = Empiler_Pile_Fin(pile,33);
  Affichage_Pile(pile);
  // Traitement de File
  printf("\n\n*****  Traitement de File  *****");
  file = Transfere_Pile_File(pile);
  printf("\nAffichage de la file");
  Affichage_File(file);
  printf("\n\nSuppression dans la file");
  rt = Defiler(file);
  Affichage_File(file);
  printf("\n\nInsertion de la valeur -22 dans la file");
  rt = Enfiler(file,-22);
  Affichage_File(file);
  // Traitement d'un arbre
  printf("\n\n*****  Traitement d'un arbre  *****");
  Arbre = Transfere_File_Arbre_Ordonne(file);
  printf("\n\nAffichage Graphique");
  Affichage_Horizontal(Arbre,0);
  printf("\n\nAffichage Prefixe :\n");
  Affichage_Prefixe(Arbre);
  printf("\n\nAffichage Infixe :\n");
  Affichage_Infixe(Arbre);
  printf("\n\nAffichage Postfixe :\n");
  Affichage_Postfixe(Arbre);
  printf("\n\nSuppression de la valeur 9 dans l'arbre");
  Arbre = Supprimer_ArbBin_Ordonne(Arbre,9,&rt);
  printf("\n\nAffichage Infixe :\n");
  Affichage_Infixe(Arbre);
  printf("\n\nSuppression de la valeur 15 dans l'arbre");
  Arbre = Supprimer_ArbBin_Ordonne(Arbre,15,&rt);
  printf("\n\nAffichage Graphique");
  Affichage_Horizontal(Arbre,0);
  // Traitement de liste
  printf("\n\n*****  Traitement de Liste  *****");
  liste = Transfere_ArbreBin_Ordonne_Liste(Arbre);
  printf("\nAffichage de la liste ");
  Affichage_Liste(liste);
  printf("\n\nSuppression de la 1ere valeur de la liste");
  liste = Supprimer_Liste_Debut(liste);
  Affichage_Liste(liste);
  printf("\n\nSuppression de la derniere valeur de la liste");
  liste = Supprimer_Liste_Fin(liste);
  Affichage_Liste(liste);
  printf("\n\nSuppression de la 5eme valeur de la liste");
  liste = Supprimer_Liste_Pos(liste,5,&rt);
  Affichage_Liste(liste);
  return 0;
}