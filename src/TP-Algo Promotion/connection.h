
#define MOD4(a) a%4

FILE *Opern_File(char *filename, char *mode)
{
    FILE *file = fopen(filename,mode);
    if (!file) 
    {
        printf("\nErreur lors de l'ouverture du fichier %s",filename);
        exit(0);
    }
    return ((FILE *)file);
}

void View_File(FILE *file)
{
    char line[110];
    char *token;
    if (!file)
    {
        printf("\nErreur : Fichier n'existe pas !!");
        exit(0);
    }
    while (fgets(line, sizeof(line),file))
    {
        token = strtok(line,",");
        printf("\n");
        while (token)
        {
            printf("%16s",token);
            printf("\t");
            token = strtok(NULL,",");
        }
    }
}

int Est_Bessixtile(int a)
{
    if (a%100 == 0 && a%400 != 0) return ((int)0);
    return ((int)(MOD4(a)==0 ? 1:0));
}

int Date_Naiss_Valide(int j, int m, int a)
{
    int joursMois[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((a < 1996) || (a > 2004)) return ((int)-1);
    if ((m < 1) || (m > 12)) return ((int)-2);
    joursMois[1] += Est_Bessixtile(a);
    if ((j < 1) || (j > joursMois[m-1])) return ((int)-3);
    return ((int)1);
}

int CNE_Valide(char CNE[11])
{
    if ((CNE[0] < 'a' || CNE[0] > 'z') && (CNE[0] < 'A' || CNE[0] > 'Z')) return ((int)-2);
    for (int i = 1; i < 10; i++)
    {
        if (CNE[i] < '0' || CNE[i] > '9') return ((int)-1);
    }
    if (CNE[10] != '\0') return ((int)0);
    return ((int)1);
}

void Insert_File_Etudiant()
{
    FILE *etudiants;
    int rt;
    char CNE[11], NOM[26], Prenom[26], AdrMail[30], c;
    int j, m, a, ABac;
    do
    {
        printf("\nCNE : "); scanf("%s",&CNE);
        rt = CNE_Valide(CNE);
        if (rt == -2) printf("\n! Le premier caractere de CNE doit etre une lettre");
        else if (rt == -1) printf("\n! Le CNE doit contenir 10 caractere dont les 9 derniers caracteres sont des chiffres");
        else if (!rt) printf("\n! CNE doit contenir 10 caractere seulement");
    } while (rt != 1);
    printf("\nNOM : "); scanf("%s",&NOM);
    printf("\nPrenom : "); scanf("%s",&Prenom);
    do
    {
        printf("\nDate de naissance : ");
        printf("\nJour : "); scanf("%d",&j);
        printf("\nMois : "); scanf("%d",&m);
        printf("\nAnnee : "); scanf("%d",&a);
        rt = Date_Naiss_Valide(j,m,a);
        if (rt == -1) printf("\n! Annee non valide");
        else if (rt == -2) printf("\n! Mois non valide");
        else if (rt == -3) printf("\n! Jour non valide");
    } while (rt != 1);
    do 
    {
        rt = 1;
        printf("\nAnnee de baccalaureat : "); scanf("%d",&ABac);
        if (ABac < 2016 || ABac > 2020) 
        {
            printf("\n! Annee de bac entre 2016 et 2020");
            rt = 0;
        }
    } while (!rt);
    etudiants = Opern_File("Etudiants.csv","a");
    fprintf(etudiants,"%s,%s,%s,%d/%d/%d,%d,%c\n",CNE,NOM,Prenom,j,m,a,ABac,'0');
    fclose(etudiants);
}

int CNE_Existe(char CNE[10])
{
    char line[110];
    char *token;
    int rt;
    FILE *etudiants = Opern_File("Etudiants.csv","r");
    while (fgets(line, sizeof(line),etudiants))
    {
        token = strtok(line,",");
        rt = strcmp(token,CNE);
        if (rt == 1) 
        {
            fclose(etudiants);
            return ((int)1);
        }
    }
    fclose(etudiants);
    return ((int)0);
}

void Insert_File_Notes()
{
    FILE *notes;
    char CNE[11], Semestre, Phase;
    int Num_Mod, rt;
    float note;
    do
    {
        printf("\nCNE : "); scanf("%s",&CNE);
        rt = CNE_Valide(CNE);
        if (rt == -2) printf("\n! Le premier caractere de CNE doit etre une lettre");
        else if (rt == -1) printf("\n! Le CNE doit contenir 10 caractere dont les 9 derniers caracteres sont des chiffres");
        else if (!rt) printf("\n! CNE doit contenir 10 caractere seulement");
    } while (rt != 1);
    rt = CNE_Existe(CNE);
    if (rt) 
    {
        notes = Opern_File("Notes.csv","a");
        fprintf(notes,"%s,%d,%c,%c,%.2f,%d,%.2f,%d,%.2f,%d\n",CNE,Num_Mod,Semestre,Phase,note);
        fclose(notes);   
    }
    else printf("\nL'etudiant dont le CNE %s n'existe pas dans la base de donnees",CNE);
}