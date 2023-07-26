
typedef struct DT       // Structure d'une date
{
    int jour;           // Le jour
    int mois;           // Le mois 
    int annee;          // L'annee
}Date;
typedef struct ET       // Structure d'un etudiant
{
    char CNE[11];       // CNE d'un etudiant
    char Nom[26];       // Nom d'un etudiant
    char Prenom[26];    // Prenom d'un etudiant
    Date Date_naiss;    // Date de naissance d'un etudiant
    int AnneeBac;       // Annee du bacalaureat
    int Reserve;       // Annee de reserve (1 si en annee decreserve, 0 sinon)
    int Classe;        // La classe d'un etudiant (1 , 2 ou 3)
}Etudiant;
typedef struct NT       // Structure des notes
{
    float Notes[3][17]; // Les notes d'un etudiant
    float note_final;   // La note finale
}Notes;
typedef struct CL       // Structure de liste des etudiants
{
    Etudiant etu;       // Etudiant
    Notes note;         // Les notes d'etudiant
    struct CL *svt;     // Pointeur vers le suivant
}Cellule;

/* *****************************************************************************
Nom         : Init_Tab_Alpha_Promo;
Entrees     : Cellule *Promo[3][26] : un tableau de liste d'etudiants
Sorties     : le tableau passe en parametres initialise
Description : La fonction permet d'initialiser un tableau de liste d'etudiants 
***************************************************************************** */
void Init_Tab_Alpha_Promo(Cellule *Promo[3][26])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 26; j++) Promo[i][j] = NULL;
    }
}
/* *****************************************************************************
Nom         : CreerCellule;
Entrees     : Etudiant etu : les information d'un etudiant
              Notes notes : les notes de l'etudiant
Sorties     : La cellule cree
Description : La fonction permet de creer une cellule et de l'initialiser
***************************************************************************** */
Cellule *CreerCellule(Etudiant etu, Notes notes)
{
    Cellule *CL = (Cellule *)malloc(sizeof(Cellule));
    if (!CL)
    {
        printf("\nErreur lors de l'allocation memoire!!");
        exit(0);
    }
    CL->etu = etu;
    CL->note = notes;
    CL->svt = NULL;
    return ((Cellule *)CL);
}
/* *****************************************************************************
Nom         : Moyenne_Semestre;
Entrees     : Notes notes : les notes d'un etudiant
              int sem : le semestre
Sorties     : float result : la moyenne de semestre
Description : La fonction permet de calculer la moyenne d'un semestre pour un 
            etudiant.
***************************************************************************** */
float Moyenne_Semestre(Notes notes, int sem)
{
    float result = 0;      // pour stocker la moyenne
    int i, a, n;
    if (sem==6) return ((float)(notes.Notes[2][8]+notes.Notes[2][9])/2);
    i = sem%2;      // le premier semestre de l'annee ou le deuxieme
    a = (int)((i == 0)? sem/2-1 : sem/2);    // annee
    n = (i+1)*8;           // indice pour arreter la boucle
    for (i = i*8; i < n; i++) result += notes.Notes[a][i]; 
    return ((float)result/8);
}
/* *****************************************************************************
Nom         : Moyenne_Annee;
Entrees     : Notes *notes : les notes d'un etudiant
              int annee : l'annee
Sorties     : float result : la moyenne de l'annee
Description : La fonction permet de calculer la moyenne d'une annee pour un 
            etudiant et la sauvegarder.
***************************************************************************** */
float Moyenne_Annee(Notes *notes, int annee)
{
    float result = 0;
    int i;
    if (annee == 3)
    {
        for (i = 0; i < 8; i++) result += notes->Notes[annee-1][i];
        result /= 8;
        result += (notes->Notes[annee-1][8] + notes->Notes[annee-1][9])/2;
        result /= 2;
    }
    else
    {
        for (i = 0; i < 16; i++) result += notes->Notes[annee-1][i];
        result /= 16;
    }
    notes->Notes[annee-1][16] = result;
    return ((float)notes->Notes[annee-1][16]);    
}
/* *****************************************************************************
Nom         : Moyenne_Geeral;
Entrees     : Notes *notes : les notes d'un etudiant
Sorties     : La moyenne generale
Description : La fonction permet de calculer la moyenne generale d'un etudiant
            et la sauvegarder.
***************************************************************************** */
float Moyenne_Geeral(Notes *notes)
{
    float result;
    result = (notes->Notes[0][16] + notes->Notes[1][16])*0.34; // 1er & 2eme annee
    result += notes->Notes[2][16]*0.17;                       // Semestre 5
    result += notes->Notes[2][8]*0.09 +notes->Notes[2][9]*0.06;// PFE & PPI
    notes->note_final = result;
    return ((float)result);
}
/* *****************************************************************************
Nom         : Module_Valide;
Entrees     : Notes notes : les notes d'un etudiant
              int module : numero de module
Sorties     : entier : 1 si le module est validee, 0 sinon
Description : La fonction permet de verifier si un module est validee ou pas. 
***************************************************************************** */
int Module_Valide(Notes notes, int module)
{
    if (module <= 0 || module >= 42) return ((int)-1);
    int a = module/16, m = module%16 - 1;
    if (m == -1) m = 0;
    return ((int)(notes.Notes[a][m] >= 12)?1:0);
}
/* *****************************************************************************
Nom         : Annee_Validee;
Entrees     : Notes notes : les notes d'un etudiant
Sorties     : entier : 1 si l'annee est validee, 0 sinon
Description : La fonction permet de verifier si une annee est validee ou pas. 
***************************************************************************** */
int Annee_Validee(Notes notes, int annee)
{
    int i,nbcmp=0;
    if(notes.Notes[annee-1][16] >= 12) //Moyenne >= 12
    {
        for(i = 1; i < 17; i++)
        {   //note inferieure a 10
            if(notes.Notes[annee-1][i] < 10.0) return 0;
            //nbre des notes entre 10 et 12
            if(notes.Notes[annee-1][i] < 12.0) nbcmp++; 
        }
    } 
    return ((int)(nbcmp <= 4 ? 1:0));
}

