#include "Box2D/Box2D.h"
#include "HUDLayer.h"
#include "Sensorable.h"

#define VITAMINA_ACELERACAO 1
#define VITAMINA_VELOCIDADE 2

#define ANGULO_MAXIMO_VOLANTE M_PI/3

#define QTD_PERSONAGENS 5
#define TOMMY 0
#define SAMMY 1
#define RHINO 2
#define MIKE 3
#define BETH 4
#define YONG 5
#define BRIAN 6
#define CARLINHOS 7
#define MARY 8
#define JACK 9
#define KELLY 10
#define LEON 11
#define MONKY 12

const char NOMES[13][10] = {
		"Tommy",
		"Sammy",
		"Rhino",
		"Mike",
		"Beth",
		"Yong",
		"Brian",
		"Carlinhos",
		"Mary",
		"Jack",
		"Kelly",
		"Leon",
		"Monky"};

class Competidor {

public:
	Competidor(int personagem,CCPoint largada,float direction,int vitaminas);
	~Competidor();

	void update(float dt);
	CCSprite* getSprite();
	b2Body* getBody();
	b2Body* getFrontWheel();
	void getPontoNariz(int* p);
	void updateAccelerometer(float p);
	void turnRight();
	void turnLeft();
	void dontTurn();
	void startRace();
	void inicializaVariaveisFisicas();
	void aplicaForcasAtritoPerpendicularesDianteira();
	void aplicaForcasAtritoPerpendicularesTraseira();

	void aplicarEfeito_ReducaoVelocidade();
	void removerEfeito_ReducaoVelocidade();
	void aplicarEfeito_AumentoVelocidade();
	void removerEfeito_AumentoVelocidade();
	void aplicarEfeito_Invencibilidade();
	void removerEfeito_Invencibilidade();
	void aplicarEfeito_direcaoAutomatica();
	void removerEfeito_direcaoAutomatica();
	void aplicarEfeito_Paralisia();
	void removerEfeito_Paralisia();

	void removerColisao();
	void adicionarColisao();
	int pegarColisaoDeItem();
    void getVetorDiretor(float* p);

private:
	float aceleracao;
	float velocidade_maxima;
	int vitaminas;
	float desvioNariz;
	unsigned int status;
	float dnaTimer;
	float testosteronaTimer;
	float autoTimer;
	float paralisiaTimer;
	int colisao;
	float velocidadeRotacao;
	float velocidadePerpendicularAnteriorDianteira;
	float velocidadePerpendicularAnteriorTraseira;
	float velocidadePerpendicularMaximaDianteira;
	float velocidadePerpendicularMaximaTraseira;
	float impulsoPerpendicularMaximoDianteira;
	float impulsoPerpendicularMaximoTraseira;
	float forcaAceleracaoMaxima;
	float forcaAtritoDinamicoDianteira;
	float forcaAtritoDinamicoTraseira;
	CCSprite* spriteCorpo;
	CCSprite* spriteCauda;
	b2Body* geometriaCorpo;
	b2Body* rodaDianteira;
	b2Body* rodaTraseira;
	b2RevoluteJoint* juntaRodaDianteira;
	b2PrismaticJoint* juntaRodaTraseira;
	class VelocidadeAnimacao : public CCLayer {
	public:
		~VelocidadeAnimacao();
		virtual bool init();
		void setVars(CCSprite* spCorpo,CCSprite* spCauda,b2Body* corpo,CCArray* sequenciaFramesCorpo1,CCArray* sequenciaFramesCorpo2,CCArray* sequenciaFramesCorpo3);
		void startRace();
		CREATE_FUNC(VelocidadeAnimacao);

	private:
		float intervalo;
		CCSprite* spriteCorpo;
		CCSprite* spriteCauda;
		b2Body* geometriaCorpo;
		CCAnimate* animacaoCorpoVelBaixa;
		CCAnimate* animacaoCorpoVelNormal;
		CCAnimate* animacaoCorpoVelAlta;
		CCAnimate* animacaoCauda;

		void updateAnimacaoCorpo();
		void updateAnimacaoCauda();
	};
	VelocidadeAnimacao* velAnimacao;
};