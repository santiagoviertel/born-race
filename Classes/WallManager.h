#include "Competidor.h"

class WallManager {

public:
	static void create(CCTMXLayer* p,int qtd);
	static void release();
	static void posicionaParedes(CCRect r,int jogador);

private:
	static int gid_branco;
	static int gid_completo;
	static int gid_esq_sup_meio;
	static int gid_dir_sup_meio;
	static int gid_esq_inf_meio;
	static int gid_dir_inf_meio;
	static int gid_dir_inf_inic;
	static int gid_esq_inf_inic;
	static int gid_dir_sup_inic;
	static int gid_esq_sup_inic;
	static int gid_dir;
	static int gid_esq;
	static int gid_sup;
	static int gid_inf;
	static b2Body** esq_sup_meio;
	static b2Body** dir_sup_meio;
	static b2Body** esq_inf_meio;
	static b2Body** dir_inf_meio;
	static b2Body** dir_inf_inic;
	static b2Body** esq_inf_inic;
	static b2Body** dir_sup_inic;
	static b2Body** esq_sup_inic;
	static b2Body** dir;
	static b2Body** esq;
	static b2Body** sup;
	static b2Body** inf;
	static int** paredesPosicionadas;
	static CCTMXLayer* pista;
	static int qtdJogadores;
	static int tileWidth;
	static int tileHeight;

	static void adicionaParede(CCPoint p1,CCPoint p2,CCPoint p,int jog);
	static bool buscaParede(CCPoint p,int jog,int posParedes);
	static void reposicionaParede(CCPoint p1,CCPoint p2,CCPoint p,int gid,int jog,int posParedes);
};