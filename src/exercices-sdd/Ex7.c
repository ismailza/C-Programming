/* 
Soit une matrice de dimension NbLig * NbCol contient des element appartient a l'intervalle [0,255]
La matrice est deja initialiser
Donner une fonction qui recoit la matrice et retourne la frequence d'apparition pour toutes les valeurs de l'intervalle [0,255]
*/
// Declaration des bibliotheque
#include<stdio.h>
#include<stdlib.h>
// Declaration des constantes
#define NbLig 5
#define NbCol 6
#define NbElem 256
// Programme principale
void main()
{
    unsigned char Matrice[NbLig][NbCol];
    int histogramme[NbElem];
    for (int i = 0; i < NbLig; i++)
        for (int j = 0; j < NbCol; j++)
            scanf("%u",&Matrice[i][j]);
    frequenceApparition(Matrice,histogramme);
    for (int i = 0; i < NbElem; i++)
        printf("\n%d apparait %d dans la Matrice.",i,histogramme[i]);
    
}
void frequenceApparition(unsigned char Mat[NbLig][NbCol], int histogramme[NbElem])
{
    int i = 0, nbl, nbc;
    for (i = 0; i < NbElem; histogramme[i++] = 0);
    for (nbl = 0; nbl < NbLig; nbl++)
        for (nbc = 0; nbc < NbCol; nbc++)
            histogramme[(int)Mat[nbl][nbc]]++;
}
