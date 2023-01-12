

typedef struct vaisseau VAISSEAU;
typedef struct missile MISSILE;
typedef struct space SPACE;
typedef struct etoile ETOILE;


struct space
{

	VAISSEAU *Ennemis;
	VAISSEAU *Joueur;
	MISSILE *missileJ;
	MISSILE *missileE;
	struct etoile * Etoiles;
	int Score;
	int Mode;
};


void addVaisseau(SPACE *SI, char Direction, int PosX, int PosY, int Blindage, int Touches,int Type,int Couleur,int Etat);



void removeMissile(SPACE *,MISSILE *missileJ);


void removeMissileE(SPACE *SI, MISSILE *missileE);


void initialiser(SPACE *SI, int Mode);

void addMissile(SPACE *SI);

void actualisation(SPACE *SI);

int isFin(SPACE *SI);


void addMissileEnnemi(SPACE *SI,VAISSEAU *v );
