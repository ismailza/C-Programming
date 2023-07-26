#include<stdio.h>
#include<stdlib.h>

// Declaration de la structure de tableau
typedef struct
{
    int tab[3];
    int IdElem;
}Tab3;
// Declaration de la structure de l'arbre
typedef struct ND
{
    Tab3 MaTab;
    struct ND *fgc, *fdt;
}Noeud;
// Declaration de la structure de la liste
typedef struct CL
{
    Tab3 MaTab;
    struct CL *svt;
}Cellule;

Noeud *CreerNoeud(int val)
{
    Noeud *NE = (Noeud *)malloc(sizeof(Noeud));
    if (!NE) exit(0);
    NE->MaTab.tab[0] = val;
    NE->MaTab.IdElem = 0;
    NE->fgc = NE->fdt = NULL;
    return ((Noeud *)NE);
}

Cellule *CreerCellule(int val)
{
    Cellule *CE = (Cellule *)malloc(sizeof(Cellule));
    if (!CE) exit(0);
    CE->MaTab.tab[0] = val;
    CE->MaTab.IdElem = 0;
    CE->svt = NULL;
    return ((Cellule *)CE);
}

int Est_Sature(Tab3 *MaTab)
{
    if (!MaTab) return ((int)-1);
    return ((int)((MaTab->IdElem == 2) ? 1:0));
}

int Inserer_Bonne_Place(Tab3 *MaTab, int val)
{
    int ind;
    if (!MaTab) return ((int)-1);
    if (Est_Sature(MaTab)) return ((int)0);
    MaTab->IdElem++;
    ind = MaTab->IdElem;
    while ((ind > 0) && (val < MaTab->tab[ind-1]))
    {
        MaTab->tab[ind] = MaTab->tab[ind-1];
        ind--;
    }
    MaTab->tab[ind] = val;
    return ((int)1);
}

int Insertion_Tab3(Tab3 *MaTab, int val, int *recup)
{
    int rt;
    if (!MaTab) return ((int)-3);
    if (!Est_Sature(MaTab)) 
    {
        rt = Inserer_Bonne_Place(MaTab,val);
        return ((int)0);
    }
    if (val <= MaTab->tab[0]) return ((int)-1);
    if (MaTab->tab[2] <= val) return ((int)1);
    if (val < MaTab->tab[1])
    {
        *recup = MaTab->tab[0];
        MaTab->tab[0] = val;
        return ((int)-2);
    }
    *recup = MaTab->tab[2];
    MaTab->tab[2] = val;
    return ((int)2);
}

Noeud *Insertion_Arb_Tab3(Noeud *Arb, int val)
{
    int rt, recup;
    Noeud *NE;
    if (!Arb) return ((Noeud *)CreerNoeud(val));
    rt = Insertion_Tab3(&(Arb->MaTab),val,&recup);
    switch (rt)
    {
        case -2: 
            Arb->fgc = Insertion_Arb_Tab3(Arb->fgc,recup);
            break;
        case -1:
            Arb->fgc = Insertion_Arb_Tab3(Arb->fgc,val);
            break;
        case 0: break; 
        case 1:
            Arb->fdt = Insertion_Arb_Tab3(Arb->fdt,val);
            break;
        case 2:
            Arb->fdt = Insertion_Arb_Tab3(Arb->fdt,recup);
            break;        
        default: printf("\nErreur !!"); 
    }
    return ((Noeud *)Arb);
}

Cellule *Insertion_Liste_Tab3(Cellule *liste, int val)
{
    int rt, recup;
    Cellule *NC, *courant, *pred = NULL;
    if (!liste) return ((Cellule *)CreerCellule(val));
    courant = liste;
    while (courant)
    {
        if (!Est_Sature(&(courant->MaTab)) && courant->svt)
        {
            if (val > courant->svt->MaTab.tab[0])
            {
                pred = courant;
                courant = courant->svt;
                continue;
            }
        }
        rt = Insertion_Tab3(&(courant->MaTab),val,&recup);
        switch (rt)
        {
            case -2: val = recup;
            case -1:
                NC = CreerCellule(val);
                NC->svt = courant;
                if (!pred) liste = NC;
                else pred->svt = NC;
            case 0: return ((Cellule *)liste);
            case 2: val = recup;
            case 1: 
                pred = courant;
                courant = courant->svt; 
        }
    }
    pred->svt = CreerCellule(val);
    return ((Cellule *)liste);    
}

void AffichageInfixe(Noeud *Arb)
{
    if (Arb)
    {
        AffichageInfixe(Arb->fgc);
        for (int i = 0; i <= Arb->MaTab.IdElem; i++)
        {
            printf("%d\t",Arb->MaTab.tab[i]);
        }
        AffichageInfixe(Arb->fdt);
    }
}

void AfficherListe(Cellule *liste)
{
    Cellule *courant;
    // si la liste est vide
    if (!liste) printf("\nLa liste est vide");
    else
    {
        courant = liste; // initialiser courant par la tete de la liste
        printf("\nListe : ");
        while (courant)
        {   // tant qu'on a un element dans la liste
            for (int i = 0; i <= courant->MaTab.IdElem; i++)
            {
                printf("%d\t",courant->MaTab.tab[i]);
            }
            printf("|\t");
            courant = courant->svt; // passer au suivant
        }
    }
}

void main()
{
    Tab3 *MaTab = (Tab3 *)malloc(sizeof(Tab3));
    MaTab->IdElem = -1;
    Noeud *Arbre = NULL;
    Cellule *liste = NULL;

    // Arbre = Insertion_Arb_Tab3(Arbre,5);
    // Arbre = Insertion_Arb_Tab3(Arbre,2);
    // Arbre = Insertion_Arb_Tab3(Arbre,12);
    // Arbre = Insertion_Arb_Tab3(Arbre,3);
    // Arbre = Insertion_Arb_Tab3(Arbre,1);
    // AffichageInfixe(Arbre);
    
    liste = Insertion_Liste_Tab3(liste,5);
    liste = Insertion_Liste_Tab3(liste,-1);
    liste = Insertion_Liste_Tab3(liste,3); 
    liste = Insertion_Liste_Tab3(liste,2);
    liste = Insertion_Liste_Tab3(liste,8);
    liste = Insertion_Liste_Tab3(liste,12);
    liste = Insertion_Liste_Tab3(liste,14);
    liste = Insertion_Liste_Tab3(liste,9);
    liste = Insertion_Liste_Tab3(liste,13);
    liste = Insertion_Liste_Tab3(liste,25);
    liste = Insertion_Liste_Tab3(liste,17);
    liste = Insertion_Liste_Tab3(liste,3);
    liste = Insertion_Liste_Tab3(liste,1);
    liste = Insertion_Liste_Tab3(liste,18);
    AfficherListe(liste);
}