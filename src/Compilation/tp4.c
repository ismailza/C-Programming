#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
  SI,
  ALORS,
  SINON,
  NBINT,
  NBFLOAT,
  ID,
  OPRELINF,
  OPRELSUP,
  OPRELINFEGAL,
  OPRELSUPEGAL,
  OPRELEGAL,
  OPRELDIFF,
  FIN,
  ERROR
} token;

int state = 0;
int start = 0;
int line = 1;

/******************************************************************************
 * retract;
 * Entrées: int retr - le nombre de caractères à reculer dans le fichier
 *          FILE *file - un pointeur vers le fichier source
 * Sorties: aucune
 * Cette fonction recule le curseur de lecture dans le fichier source de "retr" caractères.
 * Elle est utilisée pour revenir en arrière dans le fichier lorsqu'une analyse de token échoue.
 */
void retract(int retr, FILE *file)
{
  if (!feof(file)) fseek(file, -retr, SEEK_CUR);
  else fseek(file, -retr + 1, SEEK_CUR);
}
/******************************************************************************
 * fail;
 * Entrées: int retr - le nombre de caractères à reculer dans le fichier
 *          FILE *file - un pointeur vers le fichier source
 * Sorties: int - la nouvelle valeur de l'état de la machine à états
 * Cette fonction est appelée lorsqu'une séquence de caractères ne correspond à aucun motif de token attendu.
 * Elle recule le curseur de lecture dans le fichier et change l'état de la machine à états pour recommencer l'analyse avec le prochain motif possible.
 * Si l'analyse a échoué à plusieurs reprises, elle retourne -1 pour signaler une erreur de syntaxe.
 */
int fail(int retr, FILE *file)
{
  retract(retr, file);
  switch (start)
  {
  case 0:
    start = 6;
    break;
  case 6:
    start = 12;
    break;
  case 12:
    start = 19;
    break;
  case 19:
    start = 21;
    break;
  case 21:
    start = 0;
    return (int)-1;
  default: printf("\nSomething else!!");
  }
  return (int)start;
}
/******************************************************************************
 * next_token;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: token - le prochain token identifié dans le fichier source
 * Cette fonction implémente la machine à états pour analyser le fichier source caractère par caractère.
 * Elle reconnaît les tokens définis dans l'énumération "token" et retourne le token correspondant lorsqu'il est identifié.
 * Si une erreur de syntaxe est détectée, la fonction retourne ERROR et signale l'erreur avec des informations sur la ligne et le caractère concerné.
 */
token next_token(FILE *file)
{
  if (!file) exit(0);
  {
    printf("\nError: file not existe!!");
  }
  int c;
  while (1)
  {
    c = fgetc(file);
    switch (state)
    {
    case -1:
      if (feof(file)) return FIN;
      printf("\nError at line %d :\"%c\"", line, c);
      return ERROR;
    case 0:
      if (feof(file)) return FIN;
      while (isspace(c))
      {
        if (c == '\n') line++;
        c = fgetc(file);
      }
      if (c == 's') state = 1;
      else state = fail(1, file);
      break;
    case 1:
      if (c == 'i') state = 2;
      else state = fail(2, file);
      break;
    case 2:
      if (c == 'n') state = 3;
      else if (isspace(c) || feof(file))
      {
        retract(1, file);
        return SI;
      }
      else state = fail(3, file);
      break;
    case 3:
      if (c == 'o') state = 4;
      else state = fail(4, file);
      break;
    case 4:
      if (c == 'n') state = 5;
      else state = fail(5, file);
      break;
    case 5:
      if (isspace(c) || feof(file))
      {
        retract(1, file);
        return SINON;
      }
      else state = fail(6, file);
      break;
    case 6:
      if (c == 'a') state = 7;
      else state = fail(1, file);
      break;
    case 7:
      if (c == 'l') state = 8;
      else state = fail(2, file);
      break;
    case 8:
      if (c == 'o') state = 9;
      else state = fail(3, file);
      break;
    case 9:
      if (c == 'r') state = 10;
      else state = fail(4, file);
      break;
    case 10:
      if (c == 's') state = 11;
      else state = fail(5, file);
      break;
    case 11:
      if (isspace(c) || feof(file))
      {
        retract(1, file);
        return ALORS;
      }
      else state = fail(6, file);
      break;
    case 12:
      if (c == '<') state = 13;
      else if (c == '>') state = 14;
      else if (c == '=') state = 15;
      else state = fail(1, file);
      break;
    case 13:
      if (c == '>') state = 16;
      else if (c == '=') state = 17;
      else 
      {
        retract(1, file);
        return OPRELINF;
      }
      break;
    case 14:
      if (c == '=') state = 18;
      else
      {
        retract(1, file);
        return OPRELSUP;
      }
      break;
    case 15:
      retract(1, file);
      return OPRELEGAL;
    case 16:
      retract(1, file);
      return OPRELDIFF;
    case 17:
      retract(1, file);
      return OPRELINFEGAL;
    case 18:
      retract(1, file);
      return OPRELSUPEGAL;
    case 19:
      if (!feof(file) && isalpha(c)) state = 20;
      else state = fail(1, file);
      break;
    case 20:
      if (!feof(file) && isalnum(c)) state = 20;
      else
      {
        retract(1, file);
        return ID;
      }
      break;
    case 21:
      if (isdigit(c)) state = 22;
      else state = fail(1, file);
      break;
    case 22:
      if (!feof(file) && isdigit(c)) state = 22;
      else if (c == 'E' || c == 'e') state = 23;
      else if (c == '.') state = 24;
      else
      {
        retract(1, file);
        return NBINT;
      }
      break;
    case 23:
      if (!feof(file) && isdigit(c)) state = 25;
      else if (c == '+' || c == '-') state = 26;
      else
      {
        retract(2, file);
        return NBINT;
      }
      break;
    case 24:
      if (!feof(file) && isdigit(c)) state = 27;
      else
      {
        retract(1, file);
        return NBINT;
      }
      break;
    case 25:
      if (!feof(file) && isdigit(c)) state = 25;
      else
      {
        retract(1, file);
        return NBFLOAT;
      }
      break;
    case 26:
      if (!feof(file) && isdigit(c)) state = 25;
      else
      {
        retract(3, file);
        return NBINT;
      }
      break;
    case 27:
      if (!feof(file) && isdigit(c)) state = 27;
      else if (c == 'E' || c == 'e') state = 23;
      else
      {
        retract(1, file);
        return NBFLOAT;
      }
      break;
    default:
      printf("\nSomething else");
    }
  }
}
/******************************************************************************
 * token_get_name;
 * Entrées: token tk - un token
 * Sorties: char* - le nom du token sous forme de chaîne de caractères
 * Cette fonction prend un token en entrée et retourne son nom sous forme de chaîne de caractères.
 * Elle est utilisée pour afficher les noms des tokens dans le fichier de sortie.
 */
char *token_get_name(token tk)
{
  switch (tk)
  {
  case SI:
    return ((char *)"SI");
  case ALORS:
    return ((char *)"ALORS");
  case SINON:
    return ((char *)"SINON");
  case OPRELINF:
    return ((char *)"OPRELINF");
  case OPRELINFEGAL:
    return ((char *)"OPRELINFEGAL");
  case OPRELSUP:
    return ((char *)"OPRELSUP");
  case OPRELSUPEGAL:
    return ((char *)"OPRELSUPEGAL");
  case OPRELEGAL:
    return ((char *)"OPRELEGAL");
  case OPRELDIFF:
    return ((char *)"OPRELDIFF");
  case ID:
    return ((char *)"ID");
  case NBINT:
    return ((char *)"NBINT");
  case NBFLOAT:
    return ((char *)"NBFLOAT");
  default:
    printf("\nSomething is wrong");
    exit(0);
  }
}
/******************************************************************************
 * Open_File;
 * Entrées: char *filename - le nom du fichier à ouvrir
 *          char *mode - le mode d'ouverture du fichier (lecture, écriture, etc.)
 * Sorties: FILE* - un pointeur vers le fichier ouvert
 * Cette fonction ouvre un fichier avec le nom et le mode spécifiés en entrée.
 * Si l'ouverture du fichier échoue, elle affiche un message d'erreur et termine le programme.
 * Elle retourne un pointeur vers le fichier ouvert si l'ouverture réussit.
 */
FILE *Open_File(char *filename, char *mode)
{
  FILE *file = fopen(filename, mode);
  if (!file)
  {
    printf("\nErreur lors de l'ouverture de fichier %s", filename);
    exit(0);
  }
  return ((FILE *)file);
}
/******************************************************************************
 * lex;
 * Entrées: aucune
 * Sorties: aucune
 * Cette fonction est le point d'entrée du programme d'analyseur lexical.
 * Elle ouvre le fichier source "testtp4.txt" en lecture et le fichier de sortie "testtp4res.txt" en écriture.
 * Elle appelle ensuite la fonction next_token pour analyser le fichier source et identifier les tokens.
 * Les tokens identifiés sont écrits dans le fichier de sortie sous forme de chaînes de caractères.
 */
void lex()
{
  FILE *filesource = Open_File("testtp4.txt", "r");
  FILE *fileUL = Open_File("testtp4res.txt", "w");
  token tk;
  line = 1;
  while ((tk = next_token(filesource)) != FIN)
  {
    start = 0;
    state = 0;
    if (tk != ERROR) fprintf(fileUL, "%s ", token_get_name(tk));
  }
  fprintf(fileUL, "FIN");
  fclose(filesource);
  fclose(fileUL);
}
/******************************************************************************
 * main;
 * Entrées: aucune
 * Sorties: int - code de sortie du programme
 * Cette fonction est le point d'entrée du programme principal.
 * Elle présente un menu à l'utilisateur avec les options "Analyseur lexical" et "Arreter le programme".
 * L'utilisateur peut choisir l'option "Analyseur lexical" pour lancer l'analyseur lexical sur le fichier source "testtp4.txt".
 * Le programme s'arrête lorsque l'utilisateur choisit l'option "Arreter le programme".
 */
int main()
{
  int x;
  do
  {
    printf("\n0: Arreter le programme");
    printf("\n1: Analyseur lexical");
    printf("\n==> ");
    scanf("%d", &x);
    if (x == 1)
      lex();
  } while (x);
  return 0;
}