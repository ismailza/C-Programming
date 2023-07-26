/* *****************************************************************************
Nom         : Import_Modules;
Entrees     : char Modules[42][45] : un tableau de chaine de caracteres
Sorties     : le tableau entre rempli 
Description : la fonction permet d'importer le nom des modules a partir du 
            fichier Modules.csv
***************************************************************************** */
void Import_Modules(char Modules[42][45])
{
    FILE *md_file = Opern_File("Modules.csv","r");
    int i = 0;
    char line[50], *token;   
    fgets(line, sizeof(line),md_file);
    while (fgets(line, sizeof(line),md_file))
    {
        token = strtok(line,",");
        token = strtok(NULL,",");
        strcpy(Modules[i++],token);
    }
    fclose(md_file);
}
/* *****************************************************************************
Nom         : Afficher_Notes_Annee;
Entrees     : Notes notes : les notes d'un etudiants
              int annee : l'annee pour afficher ses notes
              char Modules[42][45] : tableau des modules
Description : la fonction permet d'afficher les notes d'un etudiant pour une 
            annee donnee
***************************************************************************** */
void Afficher_Notes_Annee(Notes notes, int annee, char Modules[42][45])
{
    int i, n = 16, m = 16*(annee-1);
    if (annee == 3) n = 10; 
    for (i = 0; i < n; i++) printf("\n\t%.2f\t%s",notes.Notes[annee-1][i],Modules[m++]);
    printf("\n--> Moyenne de l'annee %d : %.2f",annee,notes.Notes[annee-1][16]);
}
/* *****************************************************************************
Nom         : Afficher_Notes_Semestre;
Entrees     : Notes notes : les notes d'un etudiants
              int sem : l'annee pour afficher ses notes
              char Modules[42][45] : tableau des modules
Description : La fonction permet d'afficher les notes d'un etudiant pour un
              semestre donne
***************************************************************************** */
void Afficher_Notes_Semestre(Notes notes, int sem, char Modules[42][45])
{
    int i = 0, n = 8, a = sem/2, m = 8*(sem-1);
    if (sem == 6) n = 2;
    if (sem%2 == 0) 
    {
        a--;
        i = 8;
    }
    n += i;
    for (; i < n; i++) printf("\n\t%.2f\t%s",notes.Notes[a][i],Modules[m++]);
    printf("\n--> Moyenne de semestre %d : %.2f",sem,Moyenne_Semestre(notes,sem));
}
/* *****************************************************************************
Nom         : Afficher_Toutes_Notes;
Entrees     : Notes notes : les notes d'un etudiants
              int classe : la classe de l'etudiant
              char Modules[42][45] : tableau des modules
Description : la fonction permet d'afficher toutes les notes d'un etudiant
***************************************************************************** */
void Afficher_Toutes_Notes(Notes notes, int classe, char Modules[42][45])
{
    for (int i = 1; i <= classe; i++) Afficher_Notes_Annee(notes,i,Modules);    
}

/* *****************************************************************************
Nom         : Affichage_Notes;
Entrees     : Notes notes : les notes d'un etudiants
              int an_sem : la classe de l'etudiant
              int type : type d'affichage 
Sorties     : 
Description : 
***************************************************************************** */
void Affichage_Notes(Notes notes, int an_sem, int type)
{
    int choix, i;
    char Modules[42][45];
    Import_Modules(Modules);
    switch (type)
    {
        case 0: Afficher_Toutes_Notes(notes,an_sem,Modules); break;
        case 1: Afficher_Notes_Annee(notes,an_sem,Modules); break;
        case 2: Afficher_Notes_Semestre(notes,an_sem,Modules); break;
        default : printf("\nErreur de type d'affichage");
    }
}
/* *****************************************************************************
Nom         : Insert_Tab_Alpha_Promo;
Entrees     : Cellule *Promo[3][26] : un tableau de liste des etudiants
              Etudiant etu : un etudiant
              Notes note : les notes de l'etudiant
Sorties     : entier : 1 si l'insertion effectuee, 0 sinon
Description : la fonction permet d'inserer un etudiant et leurs notes en ordre 
            alphabetique dans la table Promo
***************************************************************************** */
int Insert_Tab_Ordre_Alpha_Promo(Cellule *Promo[3][26],Etudiant etu, Notes note)
{
    int i, j, rt;
    Cellule *NS, *courant, *pred = NULL;
    if (!Promo) return ((int)-1);
    i = etu.Classe - 1;
    j = (int)etu.Nom[0] - 'A';
    NS = CreerCellule(etu,note);
    if (!Promo[i][j]) Promo[i][j] = NS;
    else
    {
        courant = Promo[i][j];
        while (courant)
        {
            rt = strcmp(etu.Nom,courant->etu.Nom);
            if (rt < 0) break;
            if (rt == 0) 
            {
                rt = strcmp(etu.Prenom,courant->etu.Prenom);
                if (rt <= 0) break;
            }
            pred = courant;
            courant = courant->svt;
        }
        if (!pred) 
        {
            NS->svt = Promo[i][j];
            Promo[i][j] = NS;
        }
        else
        {
            NS->svt = courant;
            pred->svt = NS;
        }
    }
    return ((int)1);
}
/* *****************************************************************************
Nom         : Insert_Tab_Ordre_Merite_Promo;
Entrees     : Cellule *Promo[3][26] : un tableau de liste des etudiants
              Etudiant etu : un etudiant
              Notes note : les notes de l'etudiant
Sorties     : entier : 1 si l'insertion effectuee, 0 sinon
Description : la fonction permet d'inserer un etudiant et leurs notes en ordre 
            de merite dans la table Promo
***************************************************************************** */
int Insert_Tab_Ordre_Merite_Promo(Cellule *Promo[3][26],Etudiant etu, Notes note)
{
    int i, j, rt;
    Cellule *NS, *courant, *pred = NULL;
    if (!Promo) return ((int)-1);
    i = etu.Classe - 1;
    j = (int)note.Notes[i][16];
    NS = CreerCellule(etu,note);
    if (!Promo[i][j]) Promo[i][j] = NS;
    else
    {
        courant = Promo[i][j];
        while (courant)
        {
            if (note.Notes[i][16] >= courant->note.Notes[i][16]) break;
            pred = courant;
            courant = courant->svt;
        }
        if (!pred) 
        {
            NS->svt = Promo[i][j];
            Promo[i][j] = NS;
        }
        else
        {
            NS->svt = courant;
            pred->svt = NS;
        }
    }
    return ((int)1);
}
/* *****************************************************************************
Nom         : Afficher_Date;
Entrees     : Date date : une date
Description : la fonction permet d'afficher une date sous forme "JJ/MM/AAAA"
***************************************************************************** */
void Afficher_Date(Date date)
{
    printf("%.2d/%.2d/%.4d",date.jour,date.mois,date.annee);
}
/* *****************************************************************************
Nom         : Afficher_Info_Etudiant;
Entrees     : Cellule *etudiant
Description : la fonction permet d'afficher les information d'un etudiant
***************************************************************************** */
void Afficher_Info_Etudiant(Etudiant etudiant)
{
    printf("\n%s\t %s\t %s\t ",etudiant.CNE,etudiant.Nom,etudiant.Prenom);
    Afficher_Date(etudiant.Date_naiss);
    printf("\t %d\t ",etudiant.AnneeBac);
    if (etudiant.Reserve == '1') printf("Oui");
    else printf("Non");
}
/* *****************************************************************************
Nom         : Afficher_Etudiants_Promo_Ordre;
Entrees     : Cellule *Promo[3][26]
              int classe
              int Ordre
Description : la fonction permet d'afficher les etudiants d'une classe selon 
            un ordre donne (alphabetique : 1 ou ordre de merite : 2)
***************************************************************************** */
void Afficher_Etudiants_Promo_Ordre(Cellule *Promo[3][26], int classe, int Ordre)
{
    int i;
    Cellule *courant;
    printf("\n********************************** I L I S I %d **********************************",classe);
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve\t Moyenne");
    printf("\n--------------------------------------------------------------------------------------------------------");
    if (Ordre == 1)
    {
        for (i = 0; i < 26; i++)
        {
            courant = Promo[classe-1][i];
            while (courant) 
            {
                Afficher_Info_Etudiant(courant->etu);
                printf("\t\t %.2f",courant->note.Notes[courant->etu.Classe-1][16]);
                printf("\n---------------------------------------------------------------------------------");
                courant = courant->svt;
            }
        }
    }
    else if (Ordre == 2)
    {
        for (i = 20; i >= 0; i--)
        {
            courant = Promo[classe-1][i];
            while (courant) 
            {
                Afficher_Info_Etudiant(courant->etu);
                printf("\t\t %.2f",courant->note.Notes[courant->etu.Classe-1][16]);
                printf("\n---------------------------------------------------------------------------------");
                courant = courant->svt;
            }
        }
    }
    else printf("\nOrdre d'affichage est incorrecte !!");
}
/* *****************************************************************************
Nom         : Import_Etudiants;
Entrees     : Cellule *Promo[3][26] : un tableau de liste des etudiants
Sorties     : Un tableau de listes des etudiants organiser en ordre alphabetique
Description : La fonction permet d'importer les informations des etudiants et 
            leurs notes.
***************************************************************************** */
void Import_Etudiants(Cellule *Promo[3][26], int Ordre)
{
    Etudiant etu;   // pour stocker les informations d'un etudiant
    Notes nt;       // pour stocker les notes de l'etudiant
    char CNE[11], t[30];
    int n_module, i, nb,rt;
    float note_m, note;
    FILE *st_file, *mk_file; // pointeurs sur les fichier (etudiants et notes)
    st_file = Opern_File("Etudiants.csv","r");  // fichiers des etudiants
    mk_file = Opern_File("Notes.csv","r");      // fichier des notes
    fscanf(st_file,"%s %s %s %s %s %s %s",t,t,t,t,t,t,t) != EOF; // L'en-tete
    // lire les informations des etudiants dans le fichier
    while (fscanf(st_file,"%s %s %s %d %d %d %d %d %d",etu.CNE,etu.Nom,etu.Prenom,
                &etu.Date_naiss.jour,&etu.Date_naiss.mois,&etu.Date_naiss.annee,
                &etu.AnneeBac,&etu.Reserve,&etu.Classe) != EOF)
    {
        rewind(mk_file);    // retourner le curseur au debut de fichier
        fscanf(mk_file,"%s %s %s",t,t,t);   // L'en-tete
        nb = etu.Classe*16; // nombre de module pour l'etudiant
        if (etu.Classe == 3) nb -= 6; // pour le 3eme annee 
        // Lire les notes dans le fichier
        while ((fscanf(mk_file,"%s %d %f",CNE,&n_module,&note_m) != EOF) && nb)
        {   // comparer le CNE lu dans le fichier et le CNE de l'etudiant 
            if (strcmp(CNE,etu.CNE) == 0) 
            {
                i = n_module/16;            // Indice de l'annee 
                if (n_module%16 == 0) i--;
                n_module = n_module%16 -1;  // Indice pour la note de module 
                if (n_module == -1) n_module = 15;
                nt.Notes[i][n_module] = note_m; // sauvegarder la notes
                nb--;
            }
        }
        // Calculer la moyenne de chaque annee pour l'etudiant courant
        for (int j = 1; j <= etu.Classe; j++) note = Moyenne_Annee(&nt,j); 
        // Calculer la moyenne generale d'obtention de diplome pour ILISI 3
        if (etu.Classe == 3) note = Moyenne_Geeral(&nt);
        // Inserer l'etudiant et leurs notes selon l'ordre donne
        if (Ordre == 1) rt = Insert_Tab_Ordre_Alpha_Promo(Promo,etu,nt);
        else rt = Insert_Tab_Ordre_Merite_Promo(Promo,etu,nt);
    }
    fclose(st_file);    // fermer le fichier des etudiants
    fclose(mk_file);    // fermer le fichier des notes
}
/* *****************************************************************************
Nom         : Recherche_Etudiant_Nom;
Entrees     : Cellule *Promo[3][26] : un tableau de liste des etudiants ordonne
            par ordre alphabetique
             int classe : classe de l'etudiant recherche
             char Nom[26] : nom recherche
Description : La fonction permet de chercher un etudiant par son nom et sa
            classe et afficher ses informations s'il le trouve.
***************************************************************************** */
void Recherche_Etudiant_Nom(Cellule *Promo[3][26], int classe, char Nom[26])
{
    int i = classe-1, j, rt, trouve = 0;
    Cellule *courant;
    strupr(Nom);    // 
    j = (int)Nom[0] - 'A';
    courant = Promo[i][j];
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve\t Moyenne");
    printf("\n--------------------------------------------------------------------------------------------------------");
    while (courant)
    {
        rt = strcmp(Nom,courant->etu.Nom);
        if (!rt)
        {
            trouve = 1;
            Afficher_Info_Etudiant(courant->etu);
            printf("\t\t %.2f",courant->note.Notes[classe-1][16]);
            printf("\n---------------------------------------------------------------------------------");
        }
        else if (rt < 0) break;
        courant = courant->svt;
    }
    if (!trouve) printf("\n\tEtudiant n'existe pas dans la base de donnees !\n");
}
/* *****************************************************************************
Nom         : Etudiants_Valides;
Entrees     : Cellule *Promo[3][26] : un tableau de liste des etudiants ordonne
            selon la variable Ordre
              int classe : la classe
              int annee : l'annee
              int Ordre : l'ordre d'affichage
Description : la fonction permet d'afficher les etudiants d'une classe donnee 
            qui sont valides une annee donnee en ordre donne
***************************************************************************** */
void Etudiants_Valides(Cellule *Promo[3][26], int classe, int annee, int Ordre)
{
    int i, j, nb_V = 0;
    float note;
    Cellule *courant;
    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve\t Moyenne");
    printf("\n--------------------------------------------------------------------------------------------------------");
    if (Ordre == 1)
    {
        for (i = 0; i < 26; i++)
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                if (Annee_Validee(courant->note,annee))
                {
                    nb_V++;
                    Afficher_Info_Etudiant(courant->etu);
                    printf("\t\t %.2f",courant->note.Notes[annee-1][16]);
                    printf("\n---------------------------------------------------------------------------------");
                }
                courant = courant->svt;
            }
        }
    }
    else if (Ordre == 2)
    {
        for (i = 20; i >= 12; i--) 
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                if (Annee_Validee(courant->note,annee))
                {
                    nb_V++;
                    Afficher_Info_Etudiant(courant->etu);
                    printf("\t\t %.2f",courant->note.Notes[annee-1][16]);
                    printf("\n---------------------------------------------------------------------------------");
                }
                courant = courant->svt;
            }   
        }
    }
    printf("\n*** Le total des etudiants valides : %d",nb_V);
}
/* *****************************************************************************
Nom         : Nombre_Etudiants_Annee;
Entrees     : Cellule *Promo[3][26] : un tableau de liste des etudiants ordonne
            en ordre alphabetique
              int classe : la classe
Sorties     : int : nombre d'etudiants dans la classe 
Description : la fonction permet de calculer le nombre d'etudiant dans une classe
***************************************************************************** */
int Nombre_Etudiants_Annee(Cellule *Promo[3][26], int classe)
{
    int i, nb_etud = 0;
    Cellule *courant;
    for (i = 0; i < 26; i++)
    {
        courant = Promo[classe-1][i];
        while (courant)
        {
            nb_etud++;
            courant = courant->svt;
        }
    }
    return ((int)nb_etud);
}
/* *****************************************************************************
Nom         : Etudiants_Non_Valides;
Entrees     : 
Sorties     : 
Description : 
***************************************************************************** */
void Etudiants_Non_Valides(Cellule *Promo[3][26], int classe, int annee, int ordre)
{
    int i, j, nb_m_10_12, nb = 0;
    float note;
    Cellule *courant;
    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve\t Moyenne");
    printf("\n--------------------------------------------------------------------------------------------------------");
    if (ordre ==1)
    {
        for (i = 0; i < 26; i++)
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                if (!Annee_Validee(courant->note,annee))
                {
                    nb++;
                    Afficher_Info_Etudiant(courant->etu);
                    printf("\t\t %.2f",courant->note.Notes[annee-1][16]);
                    printf("\n---------------------------------------------------------------------------------");
                }
                courant = courant->svt;
            }
        }
    }
    else if (ordre == 2)
    {
        for (i = 20; i >= 12; i--) 
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                if (!Annee_Validee(courant->note,annee))
                {
                    nb++;
                    Afficher_Info_Etudiant(courant->etu);
                    printf("\t\t %.2f",courant->note.Notes[annee-1][16]);
                    printf("\n---------------------------------------------------------------------------------");
                }
                courant = courant->svt;
            }   
        }
    }
    printf("\n*** Total : %d",nb);
}
/* *****************************************************************************
Nom         : ;
Entrees     : 
Sorties     : 
Description : 
***************************************************************************** */
void Etudiants_Note_Entre_10_12(Cellule *Promo[3][26], int classe, int annee, int ordre)
{
    int i;
    float note;
    Cellule *courant;
    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve\t Moyenne");
    printf("\n--------------------------------------------------------------------------------------------------------");
    if (ordre ==1)
    {
        for (i = 0; i < 26; i++)
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                note = courant->note.Notes[annee-1][16];
                if ((10 <= note) && (note < 12)) 
                {
                    Afficher_Info_Etudiant(courant->etu);
                    printf("\t\t %.2f",courant->note.Notes[annee-1][16]);
                    printf("\n---------------------------------------------------------------------------------");
                }    
                courant = courant->svt;
            }
        }
    }
    else if (ordre == 2)
    {
        for (i = 11; i >= 10; i--) 
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                Afficher_Info_Etudiant(courant->etu);
                printf("\t\t %.2f",courant->note.Notes[annee-1][16]);
                printf("\n---------------------------------------------------------------------------------");
                courant = courant->svt;
            }   
        }
    }
}
/* *****************************************************************************
Nom         : ;
Entrees     : 
Sorties     : 
Description : 
***************************************************************************** */
void Etudiants_Note_Inf_Note(Cellule *Promo[3][26], int classe, int annee, float max, int ordre)
{
    int i;
    float note;
    Cellule *courant;
    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve\t Moyenne");
    printf("\n--------------------------------------------------------------------------------------------------------");
    if (ordre ==1)
    {
        for (i = 0; i < 26; i++)
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                note = courant->note.Notes[annee-1][16];
                if (note <= max) 
                {
                    Afficher_Info_Etudiant(courant->etu);
                    printf("\t\t %.2f",courant->note.Notes[annee-1][16]);
                    printf("\n---------------------------------------------------------------------------------"); 
                }
                courant = courant->svt;
            }
        }
    }
    else if (ordre == 2)
    {
        courant = Promo[classe-1][(int)max];
        while (courant) 
        {
            if (courant->note.Notes[annee-1][16] <= max) 
            {
                Afficher_Info_Etudiant(courant->etu);
                printf("\t\t %.2f",courant->note.Notes[courant->etu.Classe-1][16]);
                printf("\n---------------------------------------------------------------------------------");
            }
            courant = courant->svt;
        }
        for (i = (int)max -1; i >= 0; i--) 
        {
            courant = Promo[classe-1][i];
            while (courant)
            {
                Afficher_Info_Etudiant(courant->etu);
                printf("\t\t %.2f",courant->note.Notes[courant->etu.Classe-1][16]);
                printf("\n---------------------------------------------------------------------------------");
                courant = courant->svt;
            }   
        }
    }
}
/* *****************************************************************************
Nom         : ;
Entrees     : 
Sorties     : 
Description : 
***************************************************************************** */
void Etudiants_Obtient_Diplome(Cellule *Promo[3][26], int Ordre)
{
    int i, j, nb;
    float note;
    Cellule *courant;
    printf("\n--------------------------------------------------------------------------------------------------------");
    printf("\nCNE\t\t NOM\t Prenom\t Date Naissance\t Bac\t Reserve\t Note");
    printf("\n--------------------------------------------------------------------------------------------------------");
    if (Ordre == 1)
    {
        for (i = 0; i < 26; i++)
        {
            courant = Promo[2][i];
            while (courant)
            {
                if (courant->note.note_final >= 12)
                {
                    nb = 0;
                    for (j = 0; j < 8; j++)
                    {
                        note = courant->note.Notes[2][j];
                        if ((10 <= note) && (note < 12)) nb++;
                        if (note < 10) break;
                    }
                    if ((j == 8) && (nb <= 4)) 
                    {
                        Afficher_Info_Etudiant(courant->etu);
                        printf("\t\t %.2f",courant->note.note_final);
                        printf("\n--------------------------------------------------------------------------------------------------------");
                    }
                }
                courant = courant->svt;
            }
        }
    }
    else if (Ordre == 2)
    {
        for (i = 20; i >= 12; i--)
        {
            courant = Promo[2][i];
            while (courant)
            {
                nb = 0;
                for (j = 0; j < 8; j++)
                {
                    note = courant->note.Notes[2][j];
                    if ((10 <= note) && (note < 12)) nb++;
                    if (note < 10) break;
                }
                if ((j == 8) && (nb <= 4)) 
                {
                    Afficher_Info_Etudiant(courant->etu);
                    printf("\t\t %.2f",courant->note.note_final);
                    printf("\n--------------------------------------------------------------------------------------------------------");
                }
                courant = courant->svt;
            }
        }
    }
}
/* *****************************************************************************
Nom         : ;
Entrees     : 
Sorties     : 
Description : 
***************************************************************************** */
int Nombre_Valider_Module(Cellule *Promo[3][26], int classe, int module)
{
    Cellule *courant;
    int i, nb = 0;
    for (i = 0; i < 26; i++)
    {
        courant = Promo[classe-1][i-1];
        while (courant)
        {
            if (courant->note.Notes[classe][module-1] >= 12) nb++;
            courant = courant->svt;
        }   
    }
    return ((int)nb);
}
