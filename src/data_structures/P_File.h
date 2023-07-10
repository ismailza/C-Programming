/*                                  File                                     */

/* ****************************************************************************
| CreerFile
| Entrées : Aucune
| Sorties : File* - Un pointeur vers une nouvelle instance de File
| La fonction permet de créer une nouvelle instance de la structure File,
| alloue la mémoire nécessaire, initialise les pointeurs Tete et Queue à NULL
| et retourne le pointeur vers la nouvelle file.
*/
File *CreerFile()
{
  File *FL = (File *)malloc(sizeof(File));
  if (!FL)
  { // Erreur d'allocation de la memoire
    printf("\nErreur d'allocation de la memoire!");
    exit(0);
  }
  FL->Tete = FL->Queue = NULL;
  return ((File *)FL);
}
/* ****************************************************************************
| Enfiler
| Entrées : File* file - La file dans laquelle ajouter l'élément
|           int val   - La valeur à ajouter à la file
| Sorties : int        - Renvoie 1 si l'ajout est réussi, -1 si la file n'existe pas
| La fonction permet d'ajouter un nouvel élément à la fin de la file.
| Elle crée une cellule contenant la valeur spécifiée, l'ajoute à la fin de la file
| et met à jour les pointeurs Tete et Queue en conséquence.
*/
int Enfiler(File *file, int val)
{
  Cellule *CL;
  if (!file) return ((int)-1);     // tester si la file existe
  CL = CreerCellule(val); // creer l'element
  if (!file->Tete) file->Tete = CL;
  else file->Queue->svt = CL;
  file->Queue = CL;
  return ((int)1);
}
/* ****************************************************************************
| Defiler
| Entrées : File* file - La file à partir de laquelle supprimer l'élément en tête
| Sorties : int        - Renvoie 1 si la suppression est réussie, -1 si la file n'existe pas
| La fonction permet de supprimer l'élément en tête de la file.
| Elle met à jour les pointeurs Tete et Queue en conséquence et libère la mémoire
| de la cellule supprimée.
*/
int Defiler(File *file)
{
  Cellule *Supp;
  if (!file) return ((int)-1); // tester si la file existe
  if (!file->Tete) return ((int)0);            // tester si la file est vide
  Supp = file->Tete;            // pointer sur la tete de la file
  file->Tete = file->Tete->svt; // affecter au tete l'element suivant
  if (!file->Tete) file->Queue = NULL;
  free(Supp); // liberer la memoire
  return ((int)1);
}
/* ****************************************************************************
| Taille_File
| Entrées : File* file - La file dont on souhaite calculer la taille
| Sorties : int        - La taille de la file, -1 si la file n'existe pas,
|                        0 si la file est vide
| La fonction permet de calculer la taille de la file en comptant le nombre d'éléments.
| Elle utilise la méthode "défiler et réenfiler" pour parcourir tous les éléments de la file,
| en maintenant un compteur. La taille est ensuite retournée.
*/
int Taille_File(File *file)
{
  int taille = 0, rt;
  Cellule *DCL; // pour memoriser la derniere cellule
  if (!file) return ((int)-1); // tester si la file existe
  if (!file->Tete) return ((int)0); // si la file est vide
  DCL = file->Queue;
  while (file->Tete != DCL)
  {
    taille++;
    rt = Enfiler(file, file->Tete->info);
    rt = Defiler(file);
  }
  rt = Enfiler(file, file->Tete->info);
  rt = Defiler(file);
  return ((int)++taille);
}
/* ****************************************************************************
| Enfiler_File_Ordonnee
| Entrées : File* file - La file dans laquelle ajouter l'élément
|           int val   - La valeur à ajouter à la file
| Sorties : int        - Renvoie 1 si l'ajout est réussi, -1 si la file n'existe pas
| La fonction permet d'ajouter un nouvel élément dans la file de manière ordonnée.
| Si la file est vide ou si la valeur est supérieure ou égale à celle de l'élément en queue,
| l'élément est simplement ajouté à la fin de la file. Sinon, la fonction parcourt la file
| jusqu'à ce qu'elle trouve l'emplacement approprié pour insérer l'élément, en maintenant
| l'ordre croissant. Ensuite, les éléments sont réinsérés dans la file.
*/
int Enfiler_File_Ordonnee(File *file, int val)
{
  int rt;
  Cellule *ptr;
  if (!file) return ((int)-1);
  if (!file->Tete) rt = Enfiler(file, val);
  else if (val >= file->Queue->info) rt = Enfiler(file, val);
  else
  {
    ptr = file->Queue;
    while (file->Tete->info < val)
    {
      rt = Enfiler(file, file->Tete->info);
      rt = Defiler(file);
    }
    rt = Enfiler(file, val);
    while (file->Tete != ptr)
    {
      rt = Enfiler(file, file->Tete->info);
      rt = Defiler(file);
    }
    rt = Enfiler(file, file->Tete->info);
    rt = Defiler(file);
  }
  return ((int)1);
}
/* ****************************************************************************
| Defiler_Val
| Entrées : File* file - La file à partir de laquelle supprimer les occurrences de val
|           int val   - La valeur à supprimer de la file
| Sorties : int        - Le nombre d'éléments supprimés, -1 si la file n'existe pas
| La fonction permet de supprimer toutes les occurrences d'une valeur spécifiée dans la file.
| Elle parcourt la file, et si elle trouve une occurrence de la valeur, elle la supprime
| en utilisant la fonction "Defiler". Les éléments restants sont ensuite réinsérés dans la file.
| La fonction retourne le nombre d'éléments supprimés.
*/
int Defiler_Val(File *file, int val)
{
  int deleted = 0, rt;
  if (!file) return ((int)-1);
  Cellule *ptr = file->Queue;
  while (file->Tete != ptr)
  {
    if (!deleted && file->Tete->info == val)
    {
      rt = Defiler(file);
      deleted = 1;
    }
    rt = Enfiler(file, file->Tete->info);
    rt = Defiler(file);
  }
  if (file->Tete)
  {
    if (deleted || file->Tete->info != val) rt = Enfiler(file, file->Tete->info);
    rt = Defiler(file);
  }
  return ((int)deleted);
}
/* ****************************************************************************
| Affichage_File
| Entrées : File* file - La file à afficher
| Sorties : Aucune
| La fonction permet d'afficher les éléments de la file.
| Elle utilise la méthode "défiler et réenfiler" pour parcourir tous les éléments
| de la file et les afficher. Si la file est vide, un message approprié est affiché.
*/
void Affichage_File(File *file)
{
  int i, rt, taille = Taille_File(file);
  if (!file) // tester si la file existe
  {
    printf("\nFile inexistante !");
    exit(0);
  }
  if (!file->Tete) printf("\nLa file est vide.");
  else
  {
    printf("\nFile : ");
    for (i = 0; i < taille; i++)
    {
      printf("%d\t", file->Tete->info);
      rt = Enfiler(file, file->Tete->info);
      rt = Defiler(file);
    }
  }
}
/* ****************************************************************************
| Recherche_File
| Entrées : File* file - La file dans laquelle rechercher
|           int val   - La valeur à rechercher
| Sorties : int        - La position de l'élément dans la file (1-indexée) s'il existe,
|                        0 si l'élément n'est pas trouvé, -1 si la file n'existe pas
| La fonction permet de rechercher la première occurrence d'une valeur spécifiée dans la file.
| Elle parcourt la file, et si elle trouve une occurrence de la valeur, elle retourne la
| position de cette occurrence (1-indexée). Si la valeur n'est pas trouvée, elle retourne 0.
*/
int Recherche_File(File *file, int val)
{
  int i, rt, taille = Taille_File(file), pos = 0;
  if (!file) return ((int)-1); // tester si la file existe
  if (!file->Tete) return ((int)-2); // tester si la file est vide
  for (i = 0; i < taille; i++)
  { // on memorise la premiere occurence de l'element
    if ((file->Tete->info == val) && (pos == 0)) pos = i + 1;
    rt = Enfiler(file, file->Tete->info);
    rt = Defiler(file);
  }
  return ((int)pos); // retourne la position de l'element s'il existe, 0 sinon
}
