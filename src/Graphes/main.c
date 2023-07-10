#include <stdio.h>
#include <stdlib.h>

#define __GRAPHE__ "graphe1.txt"

#include "algorithms.h"

void main()
{
  int choix, s, ps;
  Matrice *M;
  do 
  {
    M = remplirMatrice(__GRAPHE__);
    printf("\n********** Menu **********");
    printf("\n0\t| Arreter");
    printf("\n1\t| Tous les chemins a partir d'un sommet");
    printf("\n2\t| Detecter circuit");
    printf("\n--> "); scanf("%d",&choix);
    switch (choix)
    {
      case 1: // DFSRecursif
        printf("\nEntrer le sommet de depart : "); scanf("%d",&s);
        printf("\n\t1: Affichage Prefixe");
        printf("\n\t2: Affichage Sufixe");
        printf("\n\t--> "); scanf("%d",&ps);
        DFSR(M, s-1, ps);
        break;
      case 2: // 
        if (detecterCircuit(M)) printf("\n\t=> Le graphe contient un circuit");
        else printf("\n\t=> Le graphe ne contient pas aucun circuit");
        break;
    }
  } while (choix);
}