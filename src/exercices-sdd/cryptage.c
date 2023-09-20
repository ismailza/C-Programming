/**
 * Cryptage d'un texte composé de caractères minuscules
 * 1. Le codage de César
 * 2. Le cryptage affine
 */

#include <stdio.h>
#include <stdlib.h>

#define K 13 // clé de chiffrement affine

// 1. Le codage de César
// 1.1. Chiffrement
// Chiffrement d'un caractère
char chiffrementCesar(char c, int decalage)
{
  if ((c >= 'a') && (c <= 'z'))
    return ((c - 'a') + decalage) % 26 + 'a';
  else
    return c;
}
// Chiffrement d'une chaîne de caractères
void chiffrementCesar_chaine(char *T, int decalage)
{
  int i = 0;
  if (!T) // si T == NULL
    return;
  while (T[i] != '\0')
  {
    T[i] = chiffrementCesar(T[i], decalage);
    i++;
  }
}
// 1.2. Déchiffrement
// Déchiffrement d'un caractère
char dechiffrementCesar(char c, int decalage)
{
  if ((c >= 'a') && (c <= 'z'))
    return ((c - 'a') - decalage + 26) % 26 + 'a';
  else
    return c;
}
// Déchiffrement d'une chaîne de caractères
void dechiffrementCesar_chaine(char *T, int decalage)
{
  int i = 0;
  if (!T) // si T == NULL
    return;
  while (T[i] != '\0')
  {
    T[i] = dechiffrementCesar(T[i], decalage);
    i++;
  }
}
// 2. Le cryptage affine
// 2.1. Chiffrement
// Chiffrement d'un caractère
char chiffrementAffine(char c)
{
  if ((c >= 'a') && (c <= 'z'))
    return ((K * (c - 'a')) % 26) + 'a';
  else
    return c;
}
// Chiffrement d'une chaîne de caractères
void chiffrementAffine_chaine(char *T)
{
  int i = 0;
  if (!T) // si T == NULL
    return;
  while (T[i] != '\0')
  {
    T[i] = chiffrementAffine(T[i]);
    i++;
  }
}
// 2.2. Déchiffrement
