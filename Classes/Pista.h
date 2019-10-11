#include "ColisionListener.h"

#define EPIDIDYMIS 1
#define URETHRA 5
#define UTERUS 9
#define OVARY 13
#define CONDOM 17

#define EPIDIDYMIS_TRACK_1 1
#define EPIDIDYMIS_TRACK_2 2
#define EPIDIDYMIS_TRACK_3 3
#define EPIDIDYMIS_TRACK_4 4

#define URETHRA_TRACK_1 5
#define URETHRA_TRACK_2 6
#define URETHRA_TRACK_3 7
#define URETHRA_TRACK_4 8

#define UTERUS_TRACK_1 9
#define UTERUS_TRACK_2 10
#define UTERUS_TRACK_3 11
#define UTERUS_TRACK_4 12

#define OVARY_TRACK_1 13
#define OVARY_TRACK_2 14
#define OVARY_TRACK_3 15
#define OVARY_TRACK_4 16

#define CONDOM_TRACK_1 17
#define CONDOM_TRACK_2 18
#define CONDOM_TRACK_3 19
#define CONDOM_TRACK_4 20

class Pista {

public:
	static void create(int pista);
	static void release();

	static void setSpriteGroup(CCNode** compCorpo,int qtdComp);
	static CCPoint getStartingPosition(int i);
	static float getStartingOrientation();
	static CCTMXTiledMap* getTiledMap();
	static void update(float dt);
	static CCNode** getCompetidores();
	static int getQtdCompetidores();

private:
	static float camada1TempoTotal;
	static float camada1VelocidadePixelsSegundo;
	static CCTMXTiledMap* pista;
	static CCTMXLayer* camada1;
	static CCTMXLayer* camada4;
	static CCNode** competidores;
	static int qtdCompetidores;
	static CCArray* inimigos;
	static CCArray* itens;
	static void movimentaCamadaSangue(float dt,CCPoint centralPoint);
	static void movimentaCamadaProfundidade(CCPoint centralPoint);
	static void posicionaLargada(CCTMXLayer* largada);
};