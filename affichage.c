#include "vaisseau.h"
#include "missile.h"
#include "space.h"
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct missile MISSILE;


#define clear() printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", x,y);

#define Noir 30
#define Bleu 34
#define Jaune 33
#define Rouge 31
#define Vert 32
#define Magenta 35

#define couleur(param) printf("\033[%dm", param)

//affichage du vaisseau
void afficherVaisseau(VAISSEAU *v)
{
	int i = 0;

	while (strlen(v->Carrosserie[i]) > 0)
	{
		gotoxy((int)v->PosX + i, (int)v->PosY);
		printf("%s", v->Carrosserie[i]);
		i++;
	}
}
extern int MScore;



char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd;
	char c, result = 0;
	tcgetattr(STDIN_FILENO, &oldterm);
	newterm = oldterm;
	newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
	fcntl(STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF)
	{
		ungetc(c, stdin);
		result = getchar();
	}
	return result;
}

//Affichage du menu du jeu
void AfficherMenu(int choix)
{

	gotoxy(0, 0);
	couleur(Bleu);

	printf("╔");
	for (int i = 0; i < 25; i++)
		printf("════════");
	printf("╗");
	for (int i = 2; i < 60; i++)
	{
		gotoxy(i, 0);
		printf("║");
		gotoxy(i, 202);
		printf("║");
	}

	gotoxy(60, 0);
	printf("╚");
	for (int i = 0; i < 25; i++)
		printf("════════");
	printf("╝");

	gotoxy(20, 71);
	printf("               Facile               ");
	gotoxy(22, 71);
	printf("              Difficile             ");
	gotoxy(24, 71);
	printf("              Progressif            ");

	gotoxy(20 + choix * 2, 70);
	printf("║");

	gotoxy(20 + choix * 2, 106);
	printf("║\n");

	gotoxy(19 + choix * 2, 70);
	printf("╔═══════════════════════════════════╗\n");
	gotoxy(19 + (choix + 1) * 2, 70);
	printf("╚═══════════════════════════════════╝\n");

}

//Affichage du jeu
void AfficherGame(SPACE *SI)
{

	couleur(0);

	ETOILE *E = SI->Etoiles;

	while (E != NULL)
	{
		gotoxy((int)E->PosX, (int)E->PosY);
		printf("%s", ".");
		E = E->next;
	}

	couleur(Bleu);


	gotoxy(2, 2);
	printf("%s", "╔");
	for (int i = 0; i < 18; i++)
		printf("%s", "═");
	printf("%s", "╦");
	for (int i = 0; i < 15; i++)
		printf("%s", "═");
	printf("%s", "╗");
	gotoxy(3, 2);
	printf("%s", "║MODE : ");
	if (SI->Mode == 0)
	{
		couleur(Jaune);
		printf("%s", "Facile     ");
	}
	else if (SI->Mode == 1)
	{
		couleur(Rouge);

		printf("%s", "Difficile  ");
	}

	else if (SI->Mode == 2)
	{
		couleur(Vert);

		printf("%s", "Progressif ");
	}
	couleur(Bleu);

	gotoxy(3, 21);
	printf("%s", "║VIES :");

	if (SI->Joueur->Touches < 4)
	{
		couleur(Jaune);
		printf("%s", " |");
	}
	else
	{
		printf("%s", "  ");
	}

	if (SI->Joueur->Touches < 3)
	{
		couleur(Vert);
		printf("%s", " |");
	}
	else
	{
		printf("%s", "  ");
	}

	if (SI->Joueur->Touches < 2)
	{
		couleur(Rouge);
		printf("%s", " |");
	}
	else
	{
		printf("%s", "  ");
	}

	if (SI->Joueur->Touches < 1)
	{
		couleur(Magenta);
		printf("%s", " |");
	}
	else
	{
		printf("%s", "  ");
	}


	couleur(Bleu);

	printf("%s", " ║");
	gotoxy(4, 2);
	printf("%s", "╚");
	for (int i = 0; i < 18; i++)
		printf("═");
	printf("╩");
	for (int i = 0; i < 15; i++)
		printf("═");
	printf("╝\n");

	gotoxy(2, 161);
	printf("%s", "╔");
	for (int i = 0; i < 15; i++)
		printf("%s", "═");
	printf("%s", "╦");
	for (int i = 0; i < 20; i++)
		printf("%s", "═");
	printf("%s", "╗");
	gotoxy(3, 161);
	printf("%s", "║SCORE : ");
	printf("%6d ║", SI->Score);

	gotoxy(3, 179);
	printf("%s", "M . SCORE : ");
	printf("%6d ║", MScore);

	gotoxy(4, 161);
	printf("%s", "╚");
	for (int i = 0; i < 15; i++)
		printf("═");
	printf("╩");
	for (int i = 0; i < 20; i++)
		printf("═");
	printf("%s", "╝\n");

	couleur(0);

	afficherVaisseau(SI->Joueur);

	VAISSEAU *Ennemis = SI->Ennemis;

	while (Ennemis != NULL)
	{
		if (Ennemis->Etat == 1)
		{
			couleur(Ennemis->Couleur);
			afficherVaisseau(Ennemis);
			couleur(0);
		}
		Ennemis = Ennemis->NXT;
	}

	MISSILE *missileJ = SI->missileJ;

	while (missileJ != NULL)
	{
		if (missileJ->Actif)
		{
			gotoxy((int)missileJ->PosX, (int)missileJ->PosY);
			printf("%s", "║");
		}
		missileJ = missileJ->next;
	}

	MISSILE *missileE = SI->missileE;

	while (missileE != NULL)
	{
		if (missileE->Actif)
		{
			gotoxy((int)missileE->PosX, (int)missileE->PosY);
			printf("%s", "║");
		}
		missileE = missileE->next;
	}

	gotoxy(0, 0);
}


//Affichage de la fin du jeu avec la condition gagnante et perdante
void AfficherEnd(SPACE *SI){


	couleur(Bleu);

	gotoxy(30, 70);

	if(SI->Joueur->Touches==4)
	{
	printf("║           Vous avez perdu !        ║");
	}
	else{
	printf("║           Vous avez gagné !        ║");
	}
	gotoxy(29 , 70);
	printf("╔════════════════════════════════════╗\n");
	gotoxy(31 , 70);
	printf("╚════════════════════════════════════╝\n");



}
