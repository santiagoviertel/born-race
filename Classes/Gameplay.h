#include "Mundo.h"

class Gameplay : public CCLayer {

private:
	static float sensibilidadeAcelerometro;
	static Gameplay* sharedGameplay;

public:
	virtual bool init();
	static void loadGame(int pista,int* competidores,int qtdCompetidores,int idJogador,int dificuldade,int vitaminas);
	static void beginGame();
	static void start();
	static void pause();
	static void setAccelerometer(bool flag,float sensibilidade);
	static Gameplay* getSharedGameplay();
	virtual void didAccelerate(CCAcceleration *pAccelerationValue);
	void startRace(float dt);
	void update(float dt);
	CREATE_FUNC(Gameplay);
};