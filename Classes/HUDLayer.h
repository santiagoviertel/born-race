#include "SpriteSource.h"

class HUDLayer : public CCLayer {

private:
	static HUDLayer* sharedHUDLayer;
	static int qtdCompetidores;
	static int click[3];
	static float escalas[2];
	static float limitesPercurso[2];
	static float tempoAnimacoes;
	static CCSprite* btEsquerda;
	static CCSprite* btDireita;
	static CCSprite* btPause;
	static CCSprite* percursoPista;
	static CCSprite** posicoesCompetidores;
	static CCLabelTTF** labels;
	static CCSprite* cronometro;

	static void startInitialAnimation();
	static void startFinalAnimation();
	void endInitialAnimation();
	void endFinalAnimation();
    void semaforoON();
    //Placas
    static CCSprite* placas[4];
    static CCSprite* semaforo;

public:
	~HUDLayer();
	CREATE_FUNC(HUDLayer);

	virtual bool init();
	virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);

	static void atualizaPorcentagemCompetidor(int i,float p);
	static void atualizaPosicaoJogador(int posicao);
	static void atualizaVoltaJogador(int volta);
	static void atualizaTempoJogador(int min,int seg,int cent);
	static void beginGame(float tempoAnimacoes);
	static void endGame();
	static void start();
	static void pause();
	static void createCompetidores(int qtd);
	static void releaseCompetidores();
	static void enableAccelerometer();
	static void disableAccelerometer();
	static HUDLayer* getSharedHUDLayer();
  
    static void ativarPlacaEsquerda();
    static void ativarPlacaDireita();
    static void ativarPlacaBifucacao();
    static void ativarPlacaRetorno();
    static void desativarPlaca();
};