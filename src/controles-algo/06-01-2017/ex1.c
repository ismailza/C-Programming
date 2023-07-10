#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct V
{
    float a, b, c;
}Vecteur;

Vecteur *CreerVecteur(float a, float b, float c)
{
    Vecteur *V = (Vecteur *)malloc(sizeof(Vecteur));
    if (!V) exit(0);
    V->a = a;
    V->b = b;
    V->c = c;
    return ((Vecteur *)V);
}

float Norme_V(Vecteur V)
{
    return ((float)sqrt(pow(V.a,2)+pow(V.b,2)+pow(V.c,2)));
}

float Produit_Scalaire_2V(Vecteur V1, Vecteur V2)
{
    return ((float)(V1.a*V2.a)+(V1.b*V2.b)+(V1.c*V2.c));
}

Vecteur *Produit_Vectoriel_2V(Vecteur V1, Vecteur V2)
{
    return ((Vecteur *)CreerVecteur(V1.b*V2.c-V1.c*V2.b,V1.c*V2.a-V1.a*V2.c,V1.a*V2.b-V1.b*V2.a));
}

void main()
{
    Vecteur *V1 = CreerVecteur(4,8,2.5);
    Vecteur *V2 = CreerVecteur(4,5,2);
    printf("\nLa norme de V1 est %f",Norme_V(*V1));
    printf("\nLe produit scalaire de V1 et V2 est %f",Produit_Scalaire_2V(*V1,*V2));
    Vecteur *V = Produit_Vectoriel_2V(*V1,*V2); 
    printf("\nLe produit vectoriel de V1 et V2 est (%f, %f, %f)",V->a,V->b,V->c);
}