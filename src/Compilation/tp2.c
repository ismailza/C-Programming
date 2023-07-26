#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int line = 0; // line number
/**
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
/**
 * Prototypes des fonctions
*/
char *token_get_name(token);
token to_token(char *);
int match(FILE *, token);
token next_token(FILE *);
void syntax_error(token, int);
void system_goal(FILE *);
void program(FILE *);
void inst_List(FILE *);
void inst(FILE *);
void id_List(FILE *);
void expr(FILE *);
void expr_List(FILE *);
void add_op(FILE *);
void prim(FILE *);
void Syn();
/******************************************************************************
 * Open_File;
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
 * token_get_name;
 * Entrées: token tk - le type de token dont nous voulons le nom
 * Sorties: char * - le nom du token sous forme de chaîne de caractères
 * Cette fonction prend un token et renvoie son nom correspondant sous forme de chaîne de caractères.
 */
char *token_get_name(token tk)
{
  switch (tk)
  {
  case BEGIN: return ((char *)"BEGIN");
  case END: return ((char *)"END");
  case READ: return ((char *)"READ");
  case WRITE: return ((char *)"WRITE");
  case ID: return ((char *)"ID");
  case INTLETERAL: return ((char *)"INTLETERAL");
  case FLOATLETERAL: return ((char *)"FLOATLETERAL");
  case ASSIGNOP: return ((char *)"ASSIGNOP");
  case LPAREN: return ((char *)"LPAREN");
  case RPAREN: return ((char *)"RPAREN");
  case SEMICOLON: return ((char *)"SEMICOLON");
  case COMMA: return ((char *)"COMMA");
  case PLUSOP: return ((char *)"PLUSOP");
  case MINUSOP: return ((char *)"MINUSOP");
  case SCANEOF: return ((char *)"SCANEOF");
  default:
    printf("\nSomething is wrong");
    exit(0);
  }
}
/******************************************************************************
 * to_token;
 * Entrées: char *tok - le nom du token sous forme de chaîne de caractères
 * Sorties: token - le type de token correspondant
 * Cette fonction prend le nom d'un token sous forme de chaîne de caractères et renvoie le type de token correspondant.
 */
token to_token(char *tok)
{
  if (!strcmp(tok, "BEGIN"))        return BEGIN;
  if (!strcmp(tok, "END"))          return END;
  if (!strcmp(tok, "READ"))         return READ;
  if (!strcmp(tok, "WRITE"))        return WRITE;
  if (!strcmp(tok, "ID"))           return ID;
  if (!strcmp(tok, "INTLETERAL"))   return INTLETERAL;
  if (!strcmp(tok, "FLOATLETERAL")) return FLOATLETERAL;
  if (!strcmp(tok, "ASSIGNOP"))     return ASSIGNOP;
  if (!strcmp(tok, "LPAREN"))       return LPAREN;
  if (!strcmp(tok, "RPAREN"))       return RPAREN;
  if (!strcmp(tok, "SEMICOLON"))    return SEMICOLON;
  if (!strcmp(tok, "COMMA"))        return COMMA;
  if (!strcmp(tok, "PLUSOP"))       return PLUSOP;
  if (!strcmp(tok, "MINUSOP"))      return MINUSOP;
  if (!strcmp(tok, "SCANEOF"))      return SCANEOF;
  printf("\nSomething is wrong!");  
  exit(0);
}
/******************************************************************************
 * match;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 *          token tk - le type de token attendu
 * Sorties: int - 1 si le token correspond à celui attendu, sinon 0
 * Cette fonction vérifie si le token actuel dans le fichier correspond au token attendu.
 * Elle lit le prochain token du fichier et le compare à celui attendu.
 * Si le token correspond, la fonction retourne 1, sinon elle retourne 0.
 */
int match(FILE *file, token tk)
{
  char t[18],c;
  int l = ftell(file);
  if (c = fgetc(file) == '\n') line++;
  if (fscanf(file, "%18[^ ] ", t) != EOF)
  {
    if (!strcmp(token_get_name(tk), t)) return 1;
  }
  fseek(file, l, SEEK_SET);
  return 0;
}
/******************************************************************************
 * next_token;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: token - le prochain token du fichier
 * Cette fonction lit le prochain token du fichier source et le renvoie.
 */
token next_token(FILE *file)
{
  char t[18];
  int l = ftell(file);
  if (fscanf(file, "%18[^ ] ", t) != EOF)
  {
    fseek(file, l, SEEK_SET);
    return to_token(t);
  }
  return SCANEOF;
}
/******************************************************************************
 * syntax_error;
 * Entrées: token tk - le type de token associé à l'erreur
 *          int err_t - le type d'erreur (0, 1, 2, 3, etc.)
 * Sorties: aucune
 * Cette fonction affiche un message d'erreur de syntaxe en fonction du type d'erreur et du token associé.
 */
void syntax_error(token tk, int err_t)
{
  switch (err_t)
  {
  case 0:
    printf("\nSyntax error: \"%s\" not found", token_get_name(tk));
    break;
  case 1:
    printf("\nSyntax error before \"%s\": {ID, READ or WRITE} not found",
           token_get_name(tk));
    break;
  case 2:
    printf("\nSyntax error before \"%s\": {PLUSOP or MINUSOP} not found",
           token_get_name(tk));
    break;
  case 3:
    printf("\nSyntax error before \"%s\": {ID, LPARENT, INTLETERAL or FLOATLETERAL} not found",
           token_get_name(tk));
    break;
  }
}
/******************************************************************************
 * system_goal;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <systemgoal> -> <program> SCANEOF.
 * Elle appelle la fonction program pour analyser le code source et s'assurer qu'il est correctement structuré,
 * puis vérifie qu'il se termine avec le token SCANEOF, indiquant ainsi la fin du programme.
 */
void system_goal(FILE *file)
{ // <systemgoal> -> <program> SCANEOF
  program(file);
  if (!match(file, SCANEOF))
    syntax_error(SCANEOF, 0);
}
/******************************************************************************
 * program;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <program> -> begin <inst_List> end.
 * Elle s'assure que le code source commence par le token "BEGIN", puis appelle la fonction inst_List pour analyser la liste d'instructions,
 * et enfin vérifie que le code source se termine par le token "END".
 */
void program(FILE *file)
{ // <program> -> begin <inst_List> end
  if (!match(file, BEGIN))
    syntax_error(BEGIN, 0);
  inst_List(file);
  if (!match(file, END))
    syntax_error(END, 0);
}
/******************************************************************************
 * inst_List;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <inst_List> -> <inst> {<inst>}.
 * Elle appelle la fonction inst pour analyser chaque instruction dans la liste d'instructions,
 * jusqu'à ce qu'il n'y ait plus d'instructions à analyser.
 */
void inst_List(FILE *file)
{ // <inst_List> -> <inst> {<inst>}
  token tk;
  inst(file);
  while (1)
  {
    switch (tk = next_token(file))
    {
    case ID:
    case READ:
    case WRITE:
      inst(file);
      break;
    default:
      return;
    }
  }
}
/******************************************************************************
 * inst;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <inst> -> id := <expr>; | read(<id_List>); | write(<expr_List>);
 * Elle analyse l'instruction courante dans le code source en vérifiant quel type d'instruction est présent.
 * Si l'instruction est de type assignation, elle s'assure qu'elle est correctement formée avec le token d'assignation ":=" et appelle la fonction expr pour analyser l'expression associée.
 * Si l'instruction est de type lecture, elle s'assure qu'elle est correctement formée avec le token "READ" suivi d'une liste d'identifiants, et appelle la fonction id_List pour analyser cette liste.
 * Si l'instruction est de type écriture, elle s'assure qu'elle est correctement formée avec le token "WRITE" suivi d'une liste d'expressions, et appelle la fonction expr_List pour analyser cette liste.
 * Si l'instruction ne correspond à aucun des trois types attendus, elle signale une erreur de syntaxe.
 */
void inst(FILE *file)
{ // <inst> -> id := <expr>; | read(<id_List>); | write(<expr_List>);
  token tk = next_token(file);
  switch (tk)
  {
  case ID:
    match(file, ID);
    if (!match(file, ASSIGNOP))
      syntax_error(ASSIGNOP, 0);
    expr(file);
    if (!match(file, SEMICOLON))
      syntax_error(SEMICOLON, 0);
    break;
  case READ:
    match(file, READ);
    if (!match(file, LPAREN))
      syntax_error(LPAREN, 0);
    id_List(file);
    if (!match(file, RPAREN))
      syntax_error(RPAREN, 0);
    if (!match(file, SEMICOLON))
      syntax_error(SEMICOLON, 0);
    break;
  case WRITE:
    match(file, WRITE);
    if (!match(file, LPAREN))
      syntax_error(LPAREN, 0);
    expr_List(file);
    if (!match(file, RPAREN))
      syntax_error(RPAREN, 0);
    if (!match(file, SEMICOLON))
      syntax_error(SEMICOLON, 0);
    break;
  default:
    syntax_error(tk, 1);
  }
}
/******************************************************************************
 * id_List;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <id_List> -> id {, id}.
 * Elle analyse la liste d'identifiants présente dans une instruction de lecture (read) dans le code source.
 * Elle s'assure que la liste commence par un identifiant (ID) suivi éventuellement de virgules, et répète cette étape tant qu'il y a des virgules dans la liste d'identifiants.
 */
void id_List(FILE *file)
{ // <id_List> -> id {, id}
  token tk;
  if (!match(file, ID))
    syntax_error(ID, 0);
  while ((tk = next_token(file)) == COMMA)
  {
    match(file, COMMA);
    if (!match(file, ID))
      syntax_error(ID, 0);
  }
}
/******************************************************************************
 * expr;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <expr> -> <prim> {<add_op> <prim>}.
 * Elle appelle la fonction prim pour analyser le premier terme de l'expression,
 * puis lit le prochain token pour vérifier s'il s'agit d'un opérateur d'addition ou de soustraction.
 * Si c'est le cas, elle appelle la fonction add_op pour analyser l'opérateur, puis la fonction prim pour analyser le deuxième terme de l'expression.
 * Elle répète ensuite cette étape pour les termes suivants tant qu'il y a des opérateurs d'addition ou de soustraction.
 */
void expr(FILE *file)
{ // <expr> -> <prim> {<add_op> <prim>}
  token tk;
  prim(file);
  for (tk = next_token(file); (tk == PLUSOP) || (tk == MINUSOP); tk = next_token(file))
  {
    add_op(file);
    prim(file);
  }
}
/******************************************************************************
 * expr_List;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <expr_List> -> <expr> {, <expr>}.
 * Elle appelle la fonction expr pour analyser la première expression,
 * puis lit le prochain token pour vérifier s'il s'agit d'une virgule.
 * Si c'est le cas, elle appelle à nouveau la fonction expr pour analyser la prochaine expression,
 * et répète cette étape tant qu'il y a des virgules dans la liste d'expressions.
 */
void expr_List(FILE *file)
{ // <expr_List> -> <expr> {, <expr>}
  token tk;
  expr(file);
  while ((tk = next_token(file)) == COMMA)
  {
    match(file, COMMA);
    expr(file);
  }
}
/******************************************************************************
 * add_op;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <add_op> -> plusop | minusop.
 * Elle analyse l'opérateur d'addition ou de soustraction (PLUSOP ou MINUSOP) présent dans une expression dans le code source.
 * Si l'opérateur est valide, elle avance dans le fichier en consommant le token correspondant, sinon elle signale une erreur de syntaxe.
 */
void add_op(FILE *file)
{ // <add_op> -> plusop | minusop
  token tk = next_token(file);
  if ((tk == PLUSOP) || (tk == MINUSOP))
    match(file, tk);
  else
    syntax_error(tk, 2);
}
/******************************************************************************
 * prim;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction représente la règle de grammaire <prim> -> id | (<expr>) | intleteral | floatleteral.
 * Elle analyse le premier terme (ou facteur) d'une expression dans le code source.
 * Selon le type de terme, elle appelle les fonctions correspondantes pour analyser l'identifiant (ID), l'expression entre parenthèses (<expr>),
 * l'entier littéral (INTLETERAL) ou le flottant littéral (FLOATLETERAL) présent dans le code source.
 * Si le terme ne correspond à aucun des types attendus, elle signale une erreur de syntaxe.
 */
void prim(FILE *file)
{ // <prim> -> id | (<expr>) | intleteral | floatleteral
  token tk = next_token(file);
  switch (tk)
  {
  case ID:
    match(file, ID);
    break;
  case LPAREN:
    match(file, LPAREN);
    expr(file);
    if (!match(file, RPAREN))
      syntax_error(RPAREN, 0);
    break;
  case INTLETERAL:
    match(file, INTLETERAL);
    break;
  case FLOATLETERAL:
    match(file, FLOATLETERAL);
    break;
  default:
    syntax_error(tk, 3);
  }
}
/******************************************************************************
 * Syn;
 * Entrées: FILE *file - un pointeur vers le fichier source à analyser
 * Sorties: aucune
 * Cette fonction est le point d'entrée du programme.
 * Elle vérifie si le fichier source existe, sinon elle affiche un message d'erreur et termine le programme.
 * Si le fichier source existe, elle appelle la fonction system_goal pour effectuer l'analyse syntaxique du code source.
 */
void Syn(FILE *file)
{
  if (!file)
  {
    printf("\nError: file not exist");
    exit(0);
  }
  system_goal(file);
}
