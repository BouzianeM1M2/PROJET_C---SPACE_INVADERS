typedef struct vaisseau VAISSEAU;
typedef struct missile MISSILE;
typedef struct space SPACE;
typedef struct etoile ETOILE;

struct vaisseau{
	char Direction;		   /*N => Nord, S => Sud, E => EST, O => OUEST*/
	float PosX;		   /*Position courante coin gauche X du vaisseau*/
	float PosY;		   /*Position courante coin gauche Y du vaisseau*/
	int Blindage;		   /*Niveau de blindage en cours du vaisseau (0=>rien, 1=>blindé, 2=>ultra-blindé, etc.)*/
	int Touches;		   /*Nombre de fois que le vaisseau est touché par un missile*/
	char Carrosserie[12][40];   /*Carrosserie du vaisseau du joueur, servira pour l’affichage du vaisseau du joueur à tout moment*/
	char Type;		   /*’M’=> mon vaisseau, ’E’=> vaisseau ennemi*/
	int Couleur;	   /*Couleur du vaisseau*/
	int Etat;		   /*État du vaisseau 1=> actif, 2=> en destruction, 3 => inactif*/
	VAISSEAU *NXT;	   /*Pointeur vers un prochain vaisseau, servira pour la liste chaînée*/
	/*Vous pouvez rajouter d’autres variables si nécessaire */
};




struct etoile
{
	float PosX;		   /*Position courante coin gauche X du vaisseau*/
	float PosY;		   /*Position courante coin gauche Y du vaisseau*/
	struct etoile * next;
};





