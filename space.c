#include "space.h"
#include "vaisseau.h"
#include "missile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define Noir 30
#define Bleu 34
#define Jaune 33
#define Rouge 31
#define Vert 32
#define Magenta 35

//Fonction pour importer des fichier txt contenant les caractère vaisseau
void importVaisseau(char Carrosserie[12][40], char *filename)
{

	FILE *fichier = NULL;
	char caractereActuel;

	fichier = fopen(filename, "r+");

	if (fichier != NULL)
	{
		int i = 0, j = 0;
		while ((caractereActuel = fgetc(fichier)) != EOF)
		{
			if (caractereActuel == '\n')
			{
				i++;
				j = 0;
			}
			else
			{
				Carrosserie[i][j] = caractereActuel;

				j++;
			}
		}
	}
	else
	{
		// On affiche un message d'erreur si on veut
		printf("Impossible d'ouvrir le fichier test.txt");
	}
}

//Fonction pour ajouter les vaisseaux
void addVaisseau(SPACE *SI, char Direction, int PosX, int PosY, int Blindage, int Touches, int Type, int Couleur, int Etat)
{

	if (SI->Ennemis == NULL)
	{
		SI->Ennemis = (struct vaisseau *)malloc(sizeof(struct vaisseau));
		SI->Ennemis->Direction = Direction;
		SI->Ennemis->PosX = PosX;
		SI->Ennemis->PosY = PosY;
		SI->Ennemis->Blindage = Blindage;
		SI->Ennemis->Touches = Touches;
		SI->Ennemis->Couleur = Couleur;
		SI->Ennemis->Etat = Etat;
		SI->Ennemis->Type = Type;

		return;
	}
	struct vaisseau *tete = SI->Ennemis;

	while (tete->NXT != NULL)
	{
		tete = tete->NXT;
	}

	tete->NXT = (struct vaisseau *)malloc(sizeof(struct vaisseau));

	tete->NXT->Direction = Direction;
	tete->NXT->PosX = PosX;
	tete->NXT->PosY = PosY;
	tete->NXT->Blindage = Blindage;
	tete->NXT->Touches = Touches;
	tete->NXT->Type = Type;
	tete->NXT->Couleur = Couleur;

	tete->NXT->Etat = Etat;
	return;
}



//initialisation du jeu
void initialiser(SPACE *SI, int Mode)
{

	ETOILE *Ep;
	SI->Score = 0;
	for (int i = 0; i < 50; i++)
	{
		if (i == 0)
		{

			Ep = (ETOILE *)malloc(sizeof(ETOILE));
			SI->Etoiles = Ep;
		}
		else
		{
			Ep->next = (ETOILE *)malloc(sizeof(ETOILE));
			Ep = Ep->next;
		}

		Ep->PosX = rand() % 55;
		Ep->PosY = rand() % 199;
	}

	SI->Mode = Mode;
	SI->Joueur = (VAISSEAU *)malloc(sizeof(VAISSEAU));

	if(Mode==0)


	SI->Joueur->Direction = 'N';
	SI->Joueur->PosX = 53;
	SI->Joueur->PosY = 53;
	// SI->Joueur->Couleur="blanc";
	SI->Joueur->Etat = 1;

	importVaisseau(SI->Joueur->Carrosserie, "./Vaisseau/v1.txt");

	int inc;
	if(SI->Mode==0)
		inc=2;
	else
		inc=1;
	for (int i = 0; i < 3; i++ )
	{
		addVaisseau(SI, 'E', 18, 90 + i * 10, 1, 0, 'E', Vert, 1);
	}

	for (int i = 0; i < 5; i++)
	{
		addVaisseau(SI, 'E', 14, 80 + i * 10, 2, 0, 'E', Rouge, 1);
	}

	for (int i = 0; i < 9; i+=inc)
	{
		addVaisseau(SI, 'E', 10, 60 + i * 10, 3, 0, 'E', Jaune, 1);
	}

	for (int i = 0; i < 13; i+=inc)
	{
		addVaisseau(SI, 'E', 6, 40 + i * 10, 4, 0, 'E', Magenta, 1);
	}

	struct vaisseau *tete = SI->Ennemis;

	while (tete != NULL)
	{
		if (tete->Blindage == 1)
		{
			importVaisseau(tete->Carrosserie, "./Vaisseau/v2.txt");
		}
		else if (tete->Blindage == 2)
		{
			importVaisseau(tete->Carrosserie, "./Vaisseau/v3.txt");
		}
		else if (tete->Blindage == 3)
		{
			importVaisseau(tete->Carrosserie, "./Vaisseau/v4.txt");
		}
		else if (tete->Blindage == 4)
		{
			importVaisseau(tete->Carrosserie, "./Vaisseau/v5.txt");
		}
		tete = tete->NXT;
	}
}


//Fonction pour retirer les missiles du joueur de l'écran
void removeMissile(SPACE *SI, MISSILE *missileJ)
{

	if (SI->missileJ == missileJ)
	{
		SI->missileJ = missileJ->next;
		free(missileJ);
	}
	else
	{
		MISSILE *missileJJ = SI->missileJ;
		while (missileJJ->next != missileJ)
		{
			missileJJ = missileJJ->next;
		}
		missileJJ->next = missileJ->next;
		free(missileJ);
	}
}

//Fonction pour retirer les missiles ennemis de l'écran
void removeMissileE(SPACE *SI, MISSILE *missileE)
{

	if (SI->missileE == missileE)
	{
		SI->missileE = missileE->next;
		free(missileE);
	}
	else
	{
		MISSILE *missileEE = SI->missileE;
		while (missileEE->next != missileE)
		{
			missileEE = missileEE->next;
		}
		missileEE->next = missileE->next;
		free(missileE);
	}
}

//Actualisation du jeu
void actualisation(SPACE *SI)
{

	MISSILE *missileJ = SI->missileJ;

	while (missileJ != NULL)
	{
		if(SI->Mode==0)
		{
			missileJ->PosX -= 0.4;

		}
		else if(SI->Mode==1)
		{
			missileJ->PosX -= 0.2;
		}
		else
		{
			missileJ->PosX -= 0.2;
		}
		if (missileJ->PosX <= 18)
		{
			 MISSILE *missileJ2 = missileJ->next;
			 removeMissile(SI, missileJ);
			 missileJ = missileJ2;
			//missileJ = missileJ->next;
		}
		else
		{
			missileJ = missileJ->next;
		}
	}

	MISSILE *missileE = SI->missileE;

	while (missileE != NULL)
	{
		missileE->PosX += 0.4;

		if (fabs(missileE->PosX - SI->Joueur->PosX) < 3 && fabs(missileE->PosY - SI->Joueur->PosY) < 3 && missileE->Actif)
		{
			SI->Joueur->Touches++;
			missileE->Actif=0;
		}

		if (missileE->PosX > 60)
		{
			 MISSILE *missileE2 = missileE->next;
			 removeMissileE(SI, missileE);
			 missileE = missileE2;
			//missileE = missileE->next;
		}
		else
		{
			missileE = missileE->next;
		}
	}






	ETOILE *E = SI->Etoiles;

	while (E != NULL)
	{

		E->PosX = E->PosX + 0.1;
		if (E->PosX >= 59)
			E->PosX = 2;
		E = E->next;
	}






	VAISSEAU *Ennemis = SI->Ennemis;

	int tmp = -1;
	while (Ennemis != NULL)
	{

		missileJ = SI->missileJ;

		while (missileJ != NULL)
		{
			if (fabs(Ennemis->PosX - missileJ->PosX) < 3 && fabs(Ennemis->PosY - missileJ->PosY) < 3 && missileJ->Actif && Ennemis->Etat == 1)
			{
				Ennemis->Touches++;
				missileJ->Actif = 0;
				if (Ennemis->Touches == Ennemis->Blindage)
				{
					Ennemis->Etat = 3;
					SI->Score += Ennemis->Blindage;
				}
			}
			missileJ = missileJ->next;
		}

		if (Ennemis->Etat == 1 && (tmp == -1 || tmp == Ennemis->Blindage))
		{
			if ((rand() % 200) % 199 == 0)
				addMissileEnnemi(SI, Ennemis);
			Ennemis->PosX = Ennemis->PosX + 0.01;
			Ennemis->PosY = Ennemis->PosY + 0.3;
			if (Ennemis->PosY > 199)
				Ennemis->PosY = 2;

			tmp = Ennemis->Blindage;
		}
		Ennemis = Ennemis->NXT;
	}
}

//Fonction pour ajouter les missiles tirés par le vaisseau Joueur
void addMissile(SPACE *SI)
{

	if (SI->missileJ == NULL)
	{
		SI->missileJ = (MISSILE *)malloc(sizeof(MISSILE));
		SI->missileJ->PosX = SI->Joueur->PosX;
		SI->missileJ->PosY = SI->Joueur->PosY + strlen(SI->Joueur->Carrosserie[0]) / 2;
		SI->missileJ->Actif = 1;
		SI->missileJ->next = NULL;
	}
	else
	{
		MISSILE *missileJ = SI->missileJ;

		while (missileJ->next != NULL)
		{
			missileJ = missileJ->next;
		}
		missileJ->next = (MISSILE *)malloc(sizeof(MISSILE));
		missileJ->next->PosX = SI->Joueur->PosX;
		missileJ->next->PosY = SI->Joueur->PosY + strlen(SI->Joueur->Carrosserie[0]) / 2;
		missileJ->next->Actif = 1;
		missileJ->next->next = NULL;
	}
}


//Fonction pour ajouter les missiles tirés par les vaisseaux ennemis
void addMissileEnnemi(SPACE *SI, VAISSEAU *v)
{

	if (SI->missileE == NULL)
	{
		SI->missileE = (MISSILE *)malloc(sizeof(MISSILE));
		SI->missileE->Direction = 1;
		SI->missileE->PosX = v->PosX + 1;
		SI->missileE->PosY = v->PosY + strlen(v->Carrosserie[0]) / 2;
		SI->missileE->Actif = 1;
		SI->missileE->next = NULL;
	}
	else
	{
		MISSILE *missileE = SI->missileE;

		while (missileE->next != NULL)
		{

			missileE = missileE->next;
		}
		missileE->next = (MISSILE *)malloc(sizeof(MISSILE));
		missileE->next->Direction = 1;
		missileE->next->PosX = v->PosX + 1;
		missileE->next->PosY = v->PosY + strlen(v->Carrosserie[0]) / 2;
		missileE->next->Actif = 1;
		missileE->next->next = NULL;
	}
}



int isFin(SPACE *SI)
{

	if (SI->Joueur->Touches == 4)
		return 1;

	VAISSEAU *Ennemis = SI->Ennemis;

	int Fin = 1;
	while (Ennemis != NULL)
	{
		if (Ennemis->Etat == 1 && Ennemis->PosX > 55)
		{
			return 1;
		}

		if (Ennemis->Etat == 1)
		{
			Fin = 0;
		}
		Ennemis = Ennemis->NXT;
	}

	return Fin;
}
