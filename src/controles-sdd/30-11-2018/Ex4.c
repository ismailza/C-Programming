#include"../structures.h"

Cellule *Trier_Pile_Liste_Par_File(Cellule *liste)
{
    Cellule *pile = NULL, *courant;
    File *file;
    int rt, i, cmp = 0;
    if (!liste) return ((Cellule *)NULL);
    courant = liste;
    while (courant)
    {
        if (!pile) pile = Empiler(pile, courant->info);
        else if (courant->info <= pile->info) pile = Empiler(pile, courant->info);
        else
        {
            while (pile)
            {
                if (courant->info <= pile->info) break;
                rt = EnfilerFile(file,pile->info);
                pile = Depiler(pile);
                cmp++;
            }
            pile = Empiler(pile,courant->info);
            for (i = 0; i < cmp; i++)
            {
                pile = Empiler(pile, file->Tete->info);
                rt = DefilerFile(file);
            }
            if (cmp > 1)
            {
                for (i = 0; i < cmp; i++)
                {
                    rt = EnfilerFile(file,pile->info);
                    pile = Depiler(pile);
                }
                for (i = 0; i < cmp; i++)
                {
                    pile = Empiler(pile, file->Tete->info);
                    rt = DefilerFile(file);
                }
            }
            cmp = 0;          
        }
        courant = courant->svt;
    }
    return ((Cellule *)pile);
}

File *Trier_File_Liste_Par_Pile(Cellule *liste)
{
    File *file = CreerFile();
    Cellule *pile = NULL, *courant;
    int rt, i, cmp = 1;
    if (!liste) return ((File *)file);
    courant = liste;
    while (courant)
    {
        if (!file->Tete) rt = EnfilerFile(file,courant->info);
        else if (courant->info < file->Queue->info) pile = Empiler(pile,courant->info);
        else
        {
            cmp++;
            rt = EnfilerFile(file,courant->info);
            while (pile)
            {
                if (pile->info < file->Queue->info) break;
                rt = EnfilerFile(file,pile->info);
                pile = Depiler(pile);
                cmp++;
            }
        }
        courant = courant->svt;
    }
    while (pile)
    {
        for (i = 0; i < cmp; i++)
        {
            if (pile->info <= file->Tete->info) break;
            rt = EnfilerFile(file,file->Tete->info);
            rt = DefilerFile(file);
        }
        rt = EnfilerFile(file,pile->info);
        pile = Depiler(pile);
        for (; i < cmp; i++)
        {
            rt = EnfilerFile(file,file->Tete->info);
            rt = DefilerFile(file);
        }
        cmp++;
    }
    return ((File *)file);    
}

void main()
{
    Cellule *liste = NULL, *pile;
    File *file;
    int rt;
    liste = Inserer_Liste_Fin(liste,8);
    liste = Inserer_Liste_Fin(liste,2);
    liste = Inserer_Liste_Fin(liste,4);
    liste = Inserer_Liste_Fin(liste,7);
    liste = Inserer_Liste_Fin(liste,0);
    liste = Inserer_Liste_Fin(liste,1);
    liste = Inserer_Liste_Fin(liste,19);
    liste = Inserer_Liste_Fin(liste,10);
    liste = Inserer_Liste_Fin(liste,5);
    AffichageListe(liste);
    printf("\nPile a l'aide d'une file");
    pile = Trier_Pile_Liste_Par_File(liste);
    AfficherPile(pile);
    printf("\nFile a l'aide d'une pile");
    file = Trier_File_Liste_Par_Pile(liste);
    AfficherFile(file);
}