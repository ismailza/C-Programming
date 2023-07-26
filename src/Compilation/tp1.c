#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/******************************************************************************
 * Enumeration des différents types de tokens possibles
*/
typedef enum
{
  BEGIN,
  END,
  READ,
  WRITE,
  ID,
  SCANEOF,
  INTLETERAL,
  LPAREN,
  RPAREN,
  SEMICOLON,
  COMMA,
  PLUSOP,
  ASSIGNOP,
  MINUSOP,
  EOL,
  ERROR,
  FLOATLETERAL
} token;
/******************************************************************************
 * Prototypes des fonctions
*/
FILE *Open_File(char *, char *);
token check_reserved(char[8]);
void lexical_error(int, int);
token Scanner(FILE *, int *);
void Transforme_Token(FILE *, token);
void Lex(FILE *);
/******************************************************************************
 * Open_File
 * Entrées: char *filename - le nom du fichier à ouvrir
 *          char *mode - le mode d'ouverture du fichier (par exemple, "r" pour lecture, "w" pour écriture)
 * Sorties: FILE * - un pointeur vers le fichier ouvert
 * Cette fonction ouvre un fichier avec le nom spécifié en utilisant le mode spécifié.
 * Si le fichier ne peut pas être ouvert, elle affiche un message d'erreur et termine le programme.
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
 * check_reserved
 * Entrées: char lexem[8] - le lexème (mot) à vérifier
 * Sorties: token - le type de token correspondant au mot réservé ou ID s'il s'agit d'un identifiant
 * Cette fonction vérifie si le lexème (mot) correspond à l'un des mots réservés prédéfinis.
 * Si le mot est réservé, elle renvoie le type de token correspondant.
 * Sinon, elle renvoie ID pour indiquer qu'il s'agit d'un identifiant.
 */
token check_reserved(char lexem[8])
{
  char *KeyWord[4] = {"BEGIN", "END", "READ", "WRITE"};
  int i;
  for (i = 0; i < 4; i++)
    if (stricmp(lexem, KeyWord[i]) == 0) break;
  switch (i)
  {
  case 0: return BEGIN;
  case 1: return END;
  case 2: return READ;
  case 3: return WRITE;
  default: return ID;
  }
}
/******************************************************************************
 * lexical_error
 * Entrées: int in_char - le caractère ayant provoqué l'erreur
 *          int line_n - le numéro de ligne où l'erreur s'est produite
 * Sorties: aucune
 * Cette fonction affiche un message d'erreur lexical indiquant le caractère qui a provoqué l'erreur et le numéro de ligne correspondant.
 */
void lexical_error(int in_char, int line_n)
{
  printf("\nLexical error at line %d : %c", line_n, (char)in_char);
}
/******************************************************************************
 * Scanner
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 *          int *err_char - pointeur vers une variable pour stocker le caractère en cas d'erreur
 * Sorties: token - le type de token correspondant au prochain élément analysé
 * Cette fonction effectue l'analyse lexicale réelle. Elle lit les caractères du fichier source et construit des tokens en fonction des règles définies dans le code.
 * La fonction reconnaît divers tokens tels que les identifiants, les littéraux (entiers et flottants), les parenthèses, les points-virgules, les virgules, les opérateurs arithmétiques, l'opérateur d'affectation, etc.
 * Elle gère également les erreurs lexicales, telles que les caractères invalides.
 */
token Scanner(FILE *file, int *err_char)
{
  int in_char, c, i;
  char lexem[8]; // Pour vérifier les mots réservés
  if (!file)
    exit(0);
  while ((in_char = fgetc(file)) != EOF)
  {
    if (isspace(in_char))
    {
      if (in_char == (int)'\n') return EOL;
      continue;
    }
    if (isalpha(in_char))
    { // ID ::= LETTER | ID LETTER | ID DIGIT | ID UNDERSCORE
      lexem[0] = (char)in_char;
      for (i = 1; i < 7; i++)
      { // Vérifier les mots réservés
        c = fgetc(file);
        if ((isalnum(c) == 0) && (c != '_')) break;
        lexem[i] = (char)c;
      }
      if (i < 7)
      {
        lexem[i] = '\0';
        if (!feof(file)) fseek(file, -1, SEEK_CUR);
        return check_reserved(lexem);
      }
      while ((isalnum(c)) || (c == '_')) c = fgetc(file);
      if (!feof(file)) fseek(file, -1, SEEK_CUR);
      return ID;
    }
    if (isdigit(in_char))
    { // INTLETERAL ::= DIGIT | INTLETERAL DIGIT
      while (isdigit(c = fgetc(file)));
      if (c == '.')
      {
        while (isdigit(c = fgetc(file)));
        if (c == 'E' || c == 'e')
        {
          c = fgetc(file);
          if (c == '+' || c == '-')
          {
            if (!isdigit(c = fgetc(file)))
            {
              if (!feof(file)) fseek(file, -3, SEEK_CUR);
              else fseek(file, -2, SEEK_CUR);
            }
            else
            {
              while (isdigit(c = fgetc(file)));
              if (!feof(file)) fseek(file, -1, SEEK_CUR);
            }
          }
          else if (isdigit(c))
          {
            while (isdigit(fgetc(file)));
            if (!feof(file)) fseek(file, -1, SEEK_CUR);
          }
          else if (!feof(file)) fseek(file, -2, SEEK_CUR);
          else fseek(file, -1, SEEK_CUR);
        }
        return FLOATLETERAL;
      }
      if (!feof(file)) fseek(file, -1, SEEK_CUR);
      return INTLETERAL;
    }
    if (in_char == '.')
    {
      c = fgetc(file);
      if (!isdigit(c))
      {
        *err_char = c;
        if (!feof(file)) fseek(file, -1, SEEK_CUR);
        return ERROR;
      }
      while (isdigit(c = fgetc(file)));
      if (c == 'E' || c == 'e')
      {
        c = fgetc(file);
        if (c == '+' || c == '-')
        {
          if (!isdigit(c = fgetc(file)))
          {
            if (!feof(file)) fseek(file, -3, SEEK_CUR);
            else fseek(file, -2, SEEK_CUR);
          }
          else
          {
            while (isdigit(c = fgetc(file)));
            if (!feof(file)) fseek(file, -1, SEEK_CUR);
          }
        }
        else if (isdigit(c))
        {
          while (isdigit(fgetc(file)));
          if (!feof(file)) fseek(file, -1, SEEK_CUR);
        }
        else if (!feof(file)) fseek(file, -2, SEEK_CUR);
        else fseek(file, -1, SEEK_CUR);
      }
      return FLOATLETERAL;
    }
    if (in_char == '(') return LPAREN;
    if (in_char == ')') return RPAREN;
    if (in_char == ';') return SEMICOLON;
    if (in_char == ',') return COMMA;
    if (in_char == '+') return PLUSOP;
    if (in_char == ':') 
    { // look for :=
      c = fgetc(file);
      if (c == '=') return ASSIGNOP;
      if (!feof(file)) fseek(file, -1, SEEK_CUR);
      *err_char = in_char;
      return ERROR;
    }
    if (in_char == '-')
    { // is it --, comment start
      c = fgetc(file);
      if (c == '-')
      { // Ignore comment
        while ((c = fgetc(file)) != '\n');
        return EOL;
      }
      if (!feof(file)) fseek(file, -1, SEEK_CUR);
      return MINUSOP;
    }
    *err_char = in_char;
    return ERROR;
  } // fin while
  return SCANEOF;
}
/******************************************************************************
 * Transforme_Token
 * Entrées: FILE *file - un pointeur vers le fichier où écrire le token transformé
 *          token tk - le type de token à transformer et écrire dans le fichier
 * Sorties: aucune
 * Cette fonction prend un token et écrit son nom correspondant dans le fichier de sortie.
 */
void Transforme_Token(FILE *file, token tk)
{
  if (!file) exit(0);
  switch (tk)
  {
  case BEGIN:
    fprintf(file, "BEGIN ");
    break;
  case END:
    fprintf(file, "END ");
    break;
  case READ:
    fprintf(file, "READ ");
    break;
  case WRITE:
    fprintf(file, "WRITE ");
    break;
  case ID:
    fprintf(file, "ID ");
    break;
  case INTLETERAL:
    fprintf(file, "INTLETERAL ");
    break;
  case FLOATLETERAL:
    fprintf(file, "FLOATLETERAL ");
    break;
  case ASSIGNOP:
    fprintf(file, "ASSIGNOP ");
    break;
  case LPAREN:
    fprintf(file, "LPAREN ");
    break;
  case RPAREN:
    fprintf(file, "RPAREN ");
    break;
  case SEMICOLON:
    fprintf(file, "SEMICOLON ");
    break;
  case COMMA:
    fprintf(file, "COMMA ");
    break;
  case PLUSOP:
    fprintf(file, "PLUSOP ");
    break;
  case MINUSOP:
    fprintf(file, "MINUSOP ");
    break;
  case SCANEOF:
    fprintf(file, "SCANEOF ");
    break;
  default:
    printf("\nSomething is wrong");
  }
}
/******************************************************************************
 * Lex
 * Entrées: FILE *sourcefile - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction est le principal gestionnaire du processus d'analyse lexicale.
 * Elle appelle la fonction Scanner dans une boucle pour traiter l'intégralité du fichier source.
 * Elle écrit les tokens dans le fichier de sortie "codeUL.txt", en ignorant les espaces et en gérant les erreurs lexicales.
 */
void Lex(FILE *sourcefile)
{
  FILE *CodeULfile = Open_File("codeUL.txt", "w");
  int line_n = 1, err_char;
  token tk;
  do
  {
    tk = Scanner(sourcefile, &err_char);
    if (tk == EOL)
    {
      line_n++;
      fprintf(CodeULfile, "\n");
    }
    else if (tk == ERROR) lexical_error(err_char, line_n);
    else Transforme_Token(CodeULfile, tk);
  } while (tk != SCANEOF);
  fclose(CodeULfile);
}
/******************************************************************************
 * main
 * Entrées: aucune
 * Sorties: int - code de sortie du programme
 * La fonction principale main ouvre le fichier source "codesource.txt" en mode lecture, appelle la fonction Lex pour effectuer l'analyse lexicale, puis ferme le fichier source.
 */
int main()
{
  FILE *file = Open_File("codesource.txt", "r");
  Lex(file);
  fclose(file);
  return 0;
}