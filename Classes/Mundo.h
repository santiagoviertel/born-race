#include "Pista.h"

#define DIFICULDADE_FACIL 1
#define DIFICULDADE_MEDIO 2
#define DIFICULDADE_DIFICIL 3

class Mundo {

public:
	static void create();
	static void release();

	static void loadGame(int pista,int* competidores,int qtdCompetidores,int idJogador,int dificuldade,int vitaminas);
	static void startRace();
	static void update(float dt);
	static void updateAccelerometer(float p);
	static void disableAccelerometer();
	static void leftTurnPressed();
	static void leftTurnReleased();
	static void rightTurnPressed();
	static void rightTurnReleased();
	static CCPoint getCentralPoint();
	static b2World* getb2World();
	static float getPTMRatio();
	static Competidor** getCompetidor();
	static int retornaQtdCompetidor();
	static int getDificuldade();

private:
	static int dificuldade;
	static bool race;
	static float ptm_ratio;
	static b2World* world;
	static Competidor** competidores;
	static int qtdCompetidores;
	static struct timespec inicioCorrida;

	static void calculaTempoCorrida();
};