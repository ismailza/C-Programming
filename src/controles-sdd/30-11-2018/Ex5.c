#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cellule
{
	int Donne;
	struct Cellule* Suivant;
} Cellule;

typedef struct
{
	struct Cellule* Tete;
	struct Cellule* Queue;
} File;

Cellule* Empiler(Cellule* Pile, int v)
{
	Cellule* p = (Cellule*)malloc(sizeof(Cellule));
	p->Suivant = Pile;
	p->Donne = v;
	return p;
}

Cellule* Depiler(Cellule* Pile, int* v)
{
	*v = Pile->Donne;
	Cellule* tmp = Pile;
	Pile = Pile->Suivant;
	free(tmp);
	return Pile;
}

void Enfiler(File* F, int v)
{
	Cellule* p = (Cellule*)malloc(sizeof(Cellule));
	p->Suivant = NULL;
	p->Donne = v;

	if (!F->Tete)
	{
		F->Queue = F->Tete = p;
	}
	else
	{
		F->Queue->Suivant = p;
		F->Queue = p;
	}
}

void Defiler(File* F, int* v)
{
	Cellule* p = F->Tete;
	*v = p->Donne;
	F->Tete = F->Tete->Suivant;
	free(p);
	if (!F->Tete)
		F->Queue = NULL;
}

int TailleF(File f)
{
	int taille = 0;
	Cellule* cur = f.Tete;
	while (cur)
	{
		cur = cur->Suivant;
		++taille;
	}
	return taille;
}

Cellule* TailleP(Cellule* p, int* taille)
{
	*taille = 0;
	Cellule* tmp = NULL;

	while (p)
	{
		*taille++;
		tmp = Empiler(tmp, p->Donne);
	}
	while (tmp)
	{
		*taille++;
		p = Empiler(p, tmp->Donne);
	}
	return p;
}

Cellule* Trieer_B(Cellule* liste)
{
	File file = { 0 };
	Cellule* pile = { 0 };

	int taille = 0;
	while (liste)
	{
		Enfiler(&file, liste->Donne);
		liste = liste->Suivant;
		taille++;
	}

	int tmp;
	while (file.Tete)
	{
		Defiler(&file, &tmp);
		pile = Empiler(pile, tmp);
		--taille;

		for (int i = 0; i < taille; i++)
		{
			if (file.Tete->Donne < pile->Donne)
			{
				pile = Depiler(pile, &tmp);
				Enfiler(&file, tmp);
				Defiler(&file, &tmp);
				pile = Empiler(pile, tmp);
			}
			else
			{
				Defiler(&file, &tmp);
				Enfiler(&file, tmp);
			}
		}
	}

	return pile;
}

void Trieer_C(Cellule* liste, File* file)
{
	file->Tete = file->Queue = NULL;
	Cellule* pile = NULL;

	while (liste)
	{
		pile = Empiler(pile, liste->Donne);
		liste = liste->Suivant;
	}

	int val, tmp;
	pile = Depiler(pile, &tmp);
	Enfiler(file, tmp);

	while (pile)
	{
		pile = Depiler(pile, &val);
		int i, taille = TailleF(*file);

		for (i = 0; i < taille; i++)
		{
			if (file->Tete->Donne >= val)
				break;
			Defiler(file, &tmp);
			Enfiler(file, tmp);
		}

		Enfiler(file, val);

		for (; i < taille; i++)
		{
			Defiler(file, &tmp);
			Enfiler(file, tmp);
		}
	}
}

void Afficher(Cellule* liste)
{
	while (liste)
	{
		printf("%i ", liste->Donne);
		liste = liste->Suivant;
	}
	printf("\n");
}

int main()
{
	Cellule* lst = NULL;
	File file;
	file.Tete = file.Queue = NULL;

	int V[] = { 8, 2, 4, 7, 0, 1, 19, 10, 5};
	for (int i = 0; i < _countof(V); i++)
		lst = Empiler(lst, V[i]);

	Trieer_C(lst, &file);
	Afficher(file.Tete);
	// lst = Trieer_B(lst);
    // Afficher(lst);
}