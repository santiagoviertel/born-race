#include "WallManager.h"

#define PLACA_SEM 0
#define PLACA_DIREITA 1
#define PLACA_ESQUERDA 2
#define PLACA_BIFUCACAO 3
#define PLACA_CONTRAMAO 4

class GerenciadorCompetidores {

public:
	static void create(Competidor** comp,int qtdComp);
	static void release();
	static void update();
    static Competidor* retornaJogador();

private:
	static int*** ckpPontos;
	static int** ckpNext;
	static int** ckpPrev;
	static int* ckpQtdNext;
	static int* ckpQtdPrev;
	static float* ckpPercursos;
	static int ckpQtd;
	static int* ckpQtdNextAtual;
	static int** ckpNextAtual;
	static int* ckpQtdPrevAtual;
	static int** ckpPrevAtual;
	static Competidor** comp;
	static float** pontosOtimosLocais;
	static int* ckpsVolta;
	static int* voltasComp;
	static float* porcentagemPistaComp;
	static int qtdComp;
	static int compInicial;
    static int *placas;
    static int placaAtual;

	static void calculaPercursosCheckpoints();
	static void calculaPercursosCheckpointsRecursivo(int id);
	static void atualizaPontoOtimoLocal(int id);
	static void verificaCheckpointVoltaAdiante(int idJog,int idCkp);
	static void verificaCheckpointVoltaRetrocesso(int idJog,int idCkp);
	static void atualizaCheckpoints();
	static void calculaPorcentagensPista();
	static void calculaPosicao();
	static void decisaoVolante();
	static bool esquerdaInt(int *p0,int *p1,int *p2);
	static bool esquerdaFloat(float *p0,float *p1,float *p2);
    static bool retornaContraMao();
    static void retornaVetorDiretorCheckpoint(float* r);
};