#include<stdio.h>
#include<stdlib.h>

#define Prc_op 0.05
#define Prc_etat 0.1
#define annee_crt 2023

typedef struct Mt
{
    int serie;
    char class[2];
    int province;
}Matricule;

typedef struct Vt
{
    Matricule matricule;
    char marque[20];
    int puissance;
    int type_carb; // 0: Essence / 1: Diesel
    int annee_service;
    int nb_place;
}Voiture;

typedef struct Qtts
{
    Voiture V;
    float histo_4Vtte[5]; // la 5e pour la courante
    struct Qtts *svt;
}Quittus;

void Base_Information(int T[2][4])
{
    T[0][0] = 350; T[1][0] = 750; 
    T[0][1] = 700; T[1][1] = 1500; 
    T[0][2] = 1500; T[1][2] = 3000; 
    T[0][3] = 3000; T[1][3] = 6000; 
}

int i_p(int puissance)
{
    if (puissance < 8) return ((int)0);
    if (puissance < 10) return ((int)1);
    if (puissance < 12) return ((int)2);
    return ((int)3)
}

// b- 
float Calcul_Facture(Voiture V, int T[2][4])
{
    float prix_tot, service_op;
    int i = i_p(V.puissance);
    prix_tot = (float)T[V.type_carb][i];
    service_op = prix_tot*Prc_op;
    if (service_op < 50) service_op = 50;
    prix_tot += prix_tot*Prc_etat + service_op;
    return ((float)prix_tot);
}
// c-
int Quittus_annees_precedentes(Quittus *Q, Matricule M)
{
    if (!Q) return ((int)-1);
    Quittus *crt = Q;
    while (crt)
    {
        
    }
    
    int i, vtte_np = 0, nb_y = annee_crt - V.annee_service;
    if (nb_y > 4) nb_y = 4;
    for (i = nb_y-1; i >= 0; i--)
    {
        if (!V.histo_4Vtte[i]) vtte_np++;
    }
    return ((int)vtte_np); // nombre de vignette non payer dans les derniers 4 ans
}
// d-
int Payement_Vignette(Voiture V, Recus)
{
    int rt = Quittus_annees_precedentes(V);
    float prix_vtte = Calcul_Facture(V);
    for (int i = rt-1; i >= 0; i--) V.histo_4Vtte[i] = prix_vtte;
    V.histo_4Vtte[4] = prix_vtte;
    return ((int)rt);
}
// e- 
void Impression_recu(Voiture V)
{

}

void main()
{
    int T[2][4];
    Base_Information(T);

}