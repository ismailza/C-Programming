#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    unsigned int csmt;  // consommation en m^3
    float prix;         // le pris de la consommation
}Consommation;

Consommation *TableCsmt[12];

float Prix_Consommation(unsigned int csmt)
{
    float prix;
    int control = csmt/5;
    switch (control)
    {
        case 0: prix = (float)(0.2950*csmt); break;
        case 1: prix = (float)(0.2950*5 + 0.3245*(csmt-5)); break;
        case 2: prix = (float)((0.2950 + 0.3245)*5 + 0.4568*(csmt-10)); break;
        default : prix = (float)((0.2950 + 0.3245 + 0.4568)*5 + 0.6895*(csmt-15)); break;
    }
    prix += prix*0.07;
    return ((float)prix+15);
}

float Consommation_Moyenne(Consommation *TableCsmt[12])
{
    int i;
    unsigned int total = 0;
    for (i = 0; i < 12; i++) total += TableCsmt[i]->csmt;
    return ((float)total/12);    
}
float Facture_Moyenne(Consommation *TableCsmt[12])
{
    int i;
    float total = 0;
    for (i = 0; i < 12; i++) total += TableCsmt[i]->prix;
    return ((float)total/12); 
}
