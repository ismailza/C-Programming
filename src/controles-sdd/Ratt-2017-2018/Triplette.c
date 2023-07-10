#include<stdio.h>
#include<stdlib.h>

typedef struct TR
{
    int info;   // information
    struct TR *svt; 
}Triplette;

typedef struct CL
{
    Triplette *Tr; // Liste de 3 elements
    struct CL *svt;
}Cellule;

Triplette *CreerTriplette(int val)
{
    Triplette *tr = (Triplette *)malloc(sizeof(Triplette));
    if (!tr) exit(0);
    tr->info = val;
    tr->svt = NULL;
    return ((Triplette *)tr);
}
Cellule *CreerCellule(Triplette *Tr)
{
    Cellule *NE = (Cellule *)malloc(sizeof(Cellule));
    if (!NE) exit(0);
    NE->Tr = Tr;
    NE->svt = NULL;
    return ((Cellule *)NE);
}
int Taille_Triplette(Triplette *Tr)
{
    Triplette *ptr = Tr;
    int n = 0;
    while (ptr)
    {
        n++;
        ptr = ptr->svt;
    }
    return ((int)n);    
}

Triplette *Inserer_Triplette(Triplette *Tr, int val, int *ret, int *rec)
{
    Triplette *NT, *ptr;
    if (!Tr)
    {
        *ret = 0;
        return ((Triplette *)CreerTriplette(val));
    }
    if (Taille_Triplette(Tr) < 3)
    {
        NT = CreerTriplette(val);
        *ret = 0;
        if (val <= Tr->info) 
        {
            NT->svt = Tr;
            return ((Triplette *)NT);
        }
        ptr = Tr;
        while (ptr->svt)
        {
            if (val < ptr->svt->info)
            {
                NT->svt = ptr->svt;
                ptr->svt = NT;
                return ((Triplette *)Tr);
            }
            ptr = ptr->svt;
        }
        ptr->svt = NT;
        return ((Triplette *)Tr);        
    }
    if (val <= Tr->info) *ret = -1;
    else if (Tr->svt->svt->info <= val) *ret = 1;
    else if (val <= Tr->svt->info) 
    {
        *rec = Tr->info;
        Tr->info = val;
        *ret = -2;
    }
    else
    {
        *rec = Tr->svt->svt->info;
        Tr->svt->svt->info = val;
        *ret = 2;
    }
    return ((Triplette *)Tr);
}

Cellule *Inserer_Liste_Triplette(Cellule *liste, int val)
{
    Cellule *courant, *pred = NULL, *NC;
    int ret, rec;
    if (!liste) return ((Cellule *)CreerCellule(CreerTriplette(val)));
    courant = liste;
    while (courant)
    {
        if ((Taille_Triplette(courant->Tr) < 3) && (courant->svt))
        {
            if (val > courant->svt->Tr->info)
            {
                pred = courant;
                courant = courant->svt;
                continue;
            }
        }
        courant->Tr = Inserer_Triplette(courant->Tr,val,&ret,&rec);
        switch (ret)
        {
            case -2: val = rec;
            case -1: 
                NC = CreerCellule(CreerTriplette(val));
                NC->svt = courant;
                if (!pred) liste = NC;
                else pred->svt = NC;
            case 0: return ((Cellule *)liste);
            case 2: val = rec;
            case 1: 
                pred = courant;
                courant = courant->svt;
        }
    }
    pred->svt = CreerCellule(CreerTriplette(val));
    return ((Cellule *)liste);
}

void AfficherListe(Cellule *liste)
{
    Cellule *courant;
    Triplette *ptr;
    // si la liste est vide
    if (!liste) printf("\nLa liste est vide");
    else
    {
        courant = liste; 
        printf("\nListe : ");
        while (courant)
        {   
            ptr = courant->Tr;
            while (ptr)
            {
                printf("%d\t",ptr->info);
                ptr = ptr->svt;
            }
            printf("|\t");
            courant = courant->svt; 
        }
    }
}

void main()
{
    Cellule *liste = NULL;
    liste = Inserer_Liste_Triplette(liste,5);
    liste = Inserer_Liste_Triplette(liste,-1);
    liste = Inserer_Liste_Triplette(liste,3);
    liste = Inserer_Liste_Triplette(liste,2);
    liste = Inserer_Liste_Triplette(liste,8);
    liste = Inserer_Liste_Triplette(liste,12);
    liste = Inserer_Liste_Triplette(liste,14);
    liste = Inserer_Liste_Triplette(liste,9);
    liste = Inserer_Liste_Triplette(liste,13);
    liste = Inserer_Liste_Triplette(liste,25);
    liste = Inserer_Liste_Triplette(liste,17);
    liste = Inserer_Liste_Triplette(liste,3);
    liste = Inserer_Liste_Triplette(liste,1);
    liste = Inserer_Liste_Triplette(liste,18);

    AfficherListe(liste);
}