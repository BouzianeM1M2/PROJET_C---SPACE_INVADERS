

typedef struct missile MISSILE;


struct missile
{
	char Direction;		   /*N => Nord, S => Sud, E => EST, O => OUEST*/
	float PosX;		   /*Position courante coin gauche X du vaisseau*/
	float PosY;		   /*Position courante coin gauche Y du vaisseau*/
	int Actif;
	struct missile * next;
};
