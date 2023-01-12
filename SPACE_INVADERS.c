#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "vaisseau.h"
#include "space.h"
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define clrscr() printf("\033[H\033[2J")
#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))
#define couleur(param) printf("\033[%dm", param)

#define Noir 30
#define Bleu 34
#define Jaune 33
#define Rouge 31
#define Vert 32
#define Cyan 36
#define Magenta 35


int MScore = 0;

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
	struct timespec ts;
	int res;

	if (msec < 0)
	{
		errno = EINVAL;
		return -1;
	}

	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;

	do
	{
		res = nanosleep(&ts, &ts);
	} while (res && errno == EINTR);

	return res;
}

void afficherVaisseau(VAISSEAU *v);
char key_pressed();
void AfficherMenu(int choix);
void AfficherGame(SPACE *SI);
void AfficherEnd(SPACE *SI);

int main()
{
	//Effacer l'écran
	clrscr() ;

	// BOUCLE Du jeu
	while (1)
	{

		SPACE *SI = (SPACE *)malloc(sizeof(SPACE));
		int choix = 0;

		//Boucle pour le choix de la difficultée
		while (1)
		{
			//lecture de la touche tapé par le joueur
			char c = key_pressed();
			gotoxy(0, 250);
			couleur(Noir);
			if (c == '\033') // cas où la touche est un bouton de direction (droit , gauche,haut,bas )
			{
				c = key_pressed();
				c = key_pressed();
				switch (c)
				{
				case 'A':
					// code pour la flèche du haut
					if (choix == 0)
						choix = 2;
					else
						choix = choix - 1;
					break;
				case 'B':
					// code pour la flèche du bas
					choix = (choix + 1) % 3;
					break;
				}
			}
			else if (c == '\n')// cas où la touche est le bouton entrer
			{
				break;
			}

			clrscr() ;

			// affichage du menu avec l'option actif
			AfficherMenu(choix);
			fflush(stdout);
			gotoxy(0, 250);
			couleur(Noir);

			msleep(20);
			gotoxy(0, 250);
			couleur(Noir);
		}
		// initialisation de la strucutre SI
		initialiser(SI, choix);

		couleur(0);

		while (isFin(SI) == 0) // boucle de la partie
		{

			char c = key_pressed();

			if (c == '\033') // cas où le bouton tapé est une fléche (deplacment du vaisseau joueur)
			{
				c = key_pressed();
				c = key_pressed();
				switch (c)
				{
				case 'C':
					// code du mouvement à droit
					SI->Joueur->PosY++;
					if (SI->Joueur->PosY >= 200 - 6)
						SI->Joueur->PosY = 200 - 6;
					break;
				case 'D':
					// code du mouvement à gauche
					SI->Joueur->PosY--;
					if (SI->Joueur->PosY <= 2)
						SI->Joueur->PosY = 2;
					break;
				}
			}
			else if (c == ' ') // cas où le bouton tapé est le bouton espace (envoi d'une missile par le joueur)
			{
				addMissile(SI);
			}
			else if (c == 'q') // cas où le bouton tapé est 'q', pour quitter le jeu
			{
				system("clear");
				return 0;
			}
			gotoxy(0, 0);

			clrscr() ;

			fflush(stdout);

			// actualisation du jeu
			actualisation(SI);


			//acuallisation du meilleur score (si le score actuelle est superieur au M .score)
			if (SI->Score > MScore)
				MScore = SI->Score;

			// affichage du jeu
			AfficherGame(SI);
			fflush(stdout);
			gotoxy(0, 250);
			couleur(Noir);

			// suspension de l'écran pandant 15 ms
			msleep(15);
			gotoxy(0, 250);
			couleur(Noir);
		}
		clrscr() ;

		// affichage du status du jeu (gagné ou perdu!) 
		AfficherEnd(SI);
		fflush(stdout);

		msleep(5000);

	}

	system("clear");
	return 0;
}
