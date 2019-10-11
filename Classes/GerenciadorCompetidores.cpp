#include "Engine.h"

#define RAIO_VISAO (CCDirector::sharedDirector()->getWinSize().height*CCDirector::sharedDirector()->getWinSize().height)/4

#define PORCENTAGEM_AFASTAMENTO 0.35
#define PORCENTAGEM_ATRAPALHAR_JOGADOR 0.15

int*** GerenciadorCompetidores::ckpPontos;
int** GerenciadorCompetidores::ckpNext;
int** GerenciadorCompetidores::ckpPrev;
int* GerenciadorCompetidores::ckpQtdNext;
int* GerenciadorCompetidores::ckpQtdPrev;
float* GerenciadorCompetidores::ckpPercursos;
int GerenciadorCompetidores::ckpQtd;
int* GerenciadorCompetidores::ckpQtdNextAtual;
int** GerenciadorCompetidores::ckpNextAtual;
int* GerenciadorCompetidores::ckpQtdPrevAtual;
int** GerenciadorCompetidores::ckpPrevAtual;
Competidor** GerenciadorCompetidores::comp;
float** GerenciadorCompetidores::pontosOtimosLocais;
int* GerenciadorCompetidores::ckpsVolta;
int* GerenciadorCompetidores::voltasComp;
float* GerenciadorCompetidores::porcentagemPistaComp;
int GerenciadorCompetidores::qtdComp;
int GerenciadorCompetidores::compInicial;

int* GerenciadorCompetidores::placas;
int GerenciadorCompetidores::placaAtual;

void GerenciadorCompetidores::create(Competidor** comp,int qtdComp) {
	int i,j;
	char ckpName[7],links[6];
	CCTMXTiledMap* tm = Pista::getTiledMap();
	CCTMXObjectGroup* ckps = tm->objectGroupNamed("CheckPoints");
	CCDictionary* d = ckps->getProperties();
	GerenciadorCompetidores::ckpQtd = d->valueForKey("qtdCkp")->intValue();
	GerenciadorCompetidores::ckpPontos = new int**[GerenciadorCompetidores::ckpQtd];
	GerenciadorCompetidores::ckpNext = new int*[GerenciadorCompetidores::ckpQtd];
	GerenciadorCompetidores::ckpPrev = new int*[GerenciadorCompetidores::ckpQtd];
	GerenciadorCompetidores::ckpQtdNext = new int[GerenciadorCompetidores::ckpQtd];
	GerenciadorCompetidores::ckpQtdPrev = new int[GerenciadorCompetidores::ckpQtd];
	GerenciadorCompetidores::ckpPercursos = new float[GerenciadorCompetidores::ckpQtd];
    //Placas
    GerenciadorCompetidores::placas = new int[GerenciadorCompetidores::ckpQtd];

    for(i=0;i<GerenciadorCompetidores::ckpQtd;i++) {
		GerenciadorCompetidores::ckpPontos[i] = new int*[2];
		GerenciadorCompetidores::ckpPontos[i][0] = new int[2];
		GerenciadorCompetidores::ckpPontos[i][1] = new int[2];

		sprintf(ckpName,"ckp%02i1",(i+1));
		d = ckps->objectNamed(ckpName);
		GerenciadorCompetidores::ckpPontos[i][0][0] = d->valueForKey("x")->intValue();
		GerenciadorCompetidores::ckpPontos[i][0][1] = d->valueForKey("y")->intValue();
		GerenciadorCompetidores::ckpQtdNext[i] = d->valueForKey("qtdNext")->intValue();
		GerenciadorCompetidores::ckpNext[i] = new int[GerenciadorCompetidores::ckpQtdNext[i]];
		for(j=0;j<GerenciadorCompetidores::ckpQtdNext[i];j++) {
			sprintf(links,"next%i",(j+1));
			GerenciadorCompetidores::ckpNext[i][j] = d->valueForKey(links)->intValue() - 1;
		}
		GerenciadorCompetidores::ckpQtdPrev[i] = d->valueForKey("qtdPrev")->intValue();
		GerenciadorCompetidores::ckpPrev[i] = new int[GerenciadorCompetidores::ckpQtdPrev[i]];
		for(j=0;j<GerenciadorCompetidores::ckpQtdPrev[i];j++) {
			sprintf(links,"prev%i",(j+1));
			GerenciadorCompetidores::ckpPrev[i][j] = d->valueForKey(links)->intValue() - 1;
		}
        //Placas
        GerenciadorCompetidores::placas[i] = d->valueForKey("placa")->intValue();
		sprintf(ckpName,"ckp%02i2",(i+1));
		d = ckps->objectNamed(ckpName);
		GerenciadorCompetidores::ckpPontos[i][1][0] = d->valueForKey("x")->intValue();
		GerenciadorCompetidores::ckpPontos[i][1][1] = d->valueForKey("y")->intValue();
		GerenciadorCompetidores::ckpPercursos[i] = 0;
	}
	GerenciadorCompetidores::calculaPercursosCheckpoints();
	GerenciadorCompetidores::qtdComp = qtdComp;
	GerenciadorCompetidores::ckpQtdNextAtual = new int[GerenciadorCompetidores::qtdComp];
	GerenciadorCompetidores::ckpNextAtual = new int*[GerenciadorCompetidores::qtdComp];
	GerenciadorCompetidores::ckpQtdPrevAtual = new int[GerenciadorCompetidores::qtdComp];
	GerenciadorCompetidores::ckpPrevAtual = new int*[GerenciadorCompetidores::qtdComp];
	GerenciadorCompetidores::pontosOtimosLocais = new float*[GerenciadorCompetidores::qtdComp];
	GerenciadorCompetidores::ckpsVolta = new int[GerenciadorCompetidores::qtdComp];
	GerenciadorCompetidores::voltasComp = new int[GerenciadorCompetidores::qtdComp];
	GerenciadorCompetidores::porcentagemPistaComp = new float[GerenciadorCompetidores::qtdComp];
	srand(time(NULL));
	for(i=0;i<GerenciadorCompetidores::qtdComp;i++) {
		GerenciadorCompetidores::ckpQtdNextAtual[i] = GerenciadorCompetidores::ckpQtdNext[GerenciadorCompetidores::ckpQtd-1];
		GerenciadorCompetidores::ckpNextAtual[i] = GerenciadorCompetidores::ckpNext[GerenciadorCompetidores::ckpQtd-1];
		GerenciadorCompetidores::ckpQtdPrevAtual[i] = GerenciadorCompetidores::ckpQtdPrev[0];
		GerenciadorCompetidores::ckpPrevAtual[i] = GerenciadorCompetidores::ckpPrev[0];
		GerenciadorCompetidores::pontosOtimosLocais[i] = new float[2];
		GerenciadorCompetidores::atualizaPontoOtimoLocal(i);
		GerenciadorCompetidores::ckpsVolta[i] = -1;
		GerenciadorCompetidores::voltasComp[i] = 1;
	}
	GerenciadorCompetidores::comp = comp;
	GerenciadorCompetidores::compInicial = 1;
	GerenciadorCompetidores::calculaPorcentagensPista();
    //Placa
    GerenciadorCompetidores::placaAtual = PLACA_SEM;
}

void GerenciadorCompetidores::update() {
	GerenciadorCompetidores::atualizaCheckpoints();
	GerenciadorCompetidores::calculaPorcentagensPista();
	GerenciadorCompetidores::calculaPosicao();
	GerenciadorCompetidores::decisaoVolante();
    if(retornaContraMao()){
        HUDLayer::ativarPlacaRetorno();
    }else{
        switch (GerenciadorCompetidores::placaAtual) {
            case PLACA_SEM:
                HUDLayer::desativarPlaca();
                break;
            case PLACA_ESQUERDA:
                HUDLayer::ativarPlacaEsquerda();
                break;
            case PLACA_DIREITA:
                HUDLayer::ativarPlacaDireita();
                break;
            case PLACA_BIFUCACAO:
                HUDLayer::ativarPlacaBifucacao();
                break;
            default:
                break;
        }
    }
}

void GerenciadorCompetidores::calculaPercursosCheckpoints() {
	int i;
	float p1[2],p2[2],vet[2];
	float percursoCompleto = 0,dist;
	GerenciadorCompetidores::calculaPercursosCheckpointsRecursivo(1);
	p1[0] = (GerenciadorCompetidores::ckpPontos[0][0][0]+GerenciadorCompetidores::ckpPontos[0][1][0])/2;
	p1[1] = (GerenciadorCompetidores::ckpPontos[0][0][1]+GerenciadorCompetidores::ckpPontos[0][1][1])/2;
	for(i=0;i<GerenciadorCompetidores::ckpQtdPrev[0];i++) {
		p2[0] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[0][i]][0][0]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[0][i]][1][0])/2;
		p2[1] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[0][i]][0][1]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[0][i]][1][1])/2;
		vet[0] = p1[0] - p2[0];
		vet[1] = p1[1] - p2[1];
		dist = sqrt(vet[0]*vet[0] + vet[1]*vet[1]) + GerenciadorCompetidores::ckpPercursos[GerenciadorCompetidores::ckpPrev[0][i]];
		if(dist>percursoCompleto)
			percursoCompleto = dist;
	}
	for(i=0;i<GerenciadorCompetidores::ckpQtd;i++)
		GerenciadorCompetidores::ckpPercursos[i] /= percursoCompleto;
}

void GerenciadorCompetidores::calculaPercursosCheckpointsRecursivo(int id) {
	int i;
	float maior = 0,dist;
	float p1[2],p2[2],vet[2];
	if(id!=0&&id<GerenciadorCompetidores::ckpQtd&&GerenciadorCompetidores::ckpPercursos[id]==0) {
		for(i=0;i<GerenciadorCompetidores::ckpQtdPrev[id];i++) {
			GerenciadorCompetidores::calculaPercursosCheckpointsRecursivo(GerenciadorCompetidores::ckpPrev[id][i]);
			p1[0] = (GerenciadorCompetidores::ckpPontos[id][0][0]+GerenciadorCompetidores::ckpPontos[id][1][0])/2;
			p1[1] = (GerenciadorCompetidores::ckpPontos[id][0][1]+GerenciadorCompetidores::ckpPontos[id][1][1])/2;
			p2[0] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[id][i]][0][0]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[id][i]][1][0])/2;
			p2[1] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[id][i]][0][1]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrev[id][i]][1][1])/2;
			vet[0] = p1[0] - p2[0];
			vet[1] = p1[1] - p2[1];
			dist = GerenciadorCompetidores::ckpPercursos[GerenciadorCompetidores::ckpPrev[id][i]] + sqrt(vet[0]*vet[0] + vet[1]*vet[1]);
			if(dist>maior)
				maior = dist;
		}
		GerenciadorCompetidores::ckpPercursos[id] = maior;
		GerenciadorCompetidores::calculaPercursosCheckpointsRecursivo(id+1);
	}
}

void GerenciadorCompetidores::atualizaPontoOtimoLocal(int id) {
	int i = 0;
	float por = ((float)rand())/RAND_MAX;
	if(GerenciadorCompetidores::ckpQtdNextAtual[id]!=1)
		i = rand()%GerenciadorCompetidores::ckpQtdNextAtual[id];
	GerenciadorCompetidores::pontosOtimosLocais[id][0] = GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[id][i]][0][0] + por*(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[id][i]][1][0] - GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[id][i]][0][0]);
	GerenciadorCompetidores::pontosOtimosLocais[id][1] = GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[id][i]][0][1] + por*(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[id][i]][1][1] - GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[id][i]][0][1]);
}

void GerenciadorCompetidores::verificaCheckpointVoltaAdiante(int idJog,int idCkp) {
	int i;
	if(GerenciadorCompetidores::ckpsVolta[idJog]!=-1) {
		for(i=0;i<GerenciadorCompetidores::ckpQtdNext[GerenciadorCompetidores::ckpsVolta[idJog]];i++)
			if(GerenciadorCompetidores::ckpNext[GerenciadorCompetidores::ckpsVolta[idJog]][i]==idCkp) {
				GerenciadorCompetidores::ckpsVolta[idJog] = idCkp;
				if(idCkp==0) {
					GerenciadorCompetidores::voltasComp[idJog]++;
					if(idJog==0) {
						if(GerenciadorCompetidores::voltasComp[0]>=6) {
							if(GerenciadorCompetidores::compInicial==1) {
								HUDLayer::endGame();
								GerenciadorCompetidores::compInicial = 0;
							}
						}
						else
							HUDLayer::atualizaVoltaJogador(GerenciadorCompetidores::voltasComp[0]);
					}
				}
				break;
			}
	}
	else if(idCkp==0)
		GerenciadorCompetidores::ckpsVolta[idJog] = 0;
}

void GerenciadorCompetidores::verificaCheckpointVoltaRetrocesso(int idJog,int idCkp) {
	int i,flag = 1;
	if(GerenciadorCompetidores::ckpsVolta[idJog]!=-1) {
		for(i=0;i<GerenciadorCompetidores::ckpQtdPrev[GerenciadorCompetidores::ckpsVolta[idJog]];i++)
			if(GerenciadorCompetidores::ckpPrev[GerenciadorCompetidores::ckpsVolta[idJog]][i]==idCkp) {
				if(idCkp!=0)
					GerenciadorCompetidores::ckpsVolta[idJog] = idCkp;
				else
					GerenciadorCompetidores::ckpsVolta[idJog] = -1;
				flag = 0;
				break;
			}
		if(flag&&idCkp==0)
			GerenciadorCompetidores::ckpsVolta[idJog] = -1;
	}
}

void GerenciadorCompetidores::atualizaCheckpoints() {
	int i,j,mp,aux,id;
	int pontoNariz[2];
	for(i=0;i<GerenciadorCompetidores::qtdComp;i++) {
		GerenciadorCompetidores::comp[i]->getPontoNariz(pontoNariz);
		//Passou próximos checkpoints
		mp = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][0][0]-pontoNariz[0])*
				(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][0][0]-pontoNariz[0]) +
				(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][0][1]-pontoNariz[1])*
				(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][0][1]-pontoNariz[1]);
		id = GerenciadorCompetidores::ckpNextAtual[i][0];
		for(j=0;j<GerenciadorCompetidores::ckpQtdNextAtual[i];j++) {
			aux = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][0][0]-pontoNariz[0])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][0][0]-pontoNariz[0]) +
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][0][1]-pontoNariz[1])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][0][1]-pontoNariz[1]);
			if(aux<mp) {
				mp = aux;
				id = GerenciadorCompetidores::ckpNextAtual[i][j];
			}
			aux = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][1][0]-pontoNariz[0])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][1][0]-pontoNariz[0]) +
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][1][1]-pontoNariz[1])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][1][1]-pontoNariz[1]);
			if(aux<mp) {
				mp = aux;
				id = GerenciadorCompetidores::ckpNextAtual[i][j];
			}
		}
		if(!GerenciadorCompetidores::esquerdaInt(GerenciadorCompetidores::ckpPontos[id][0],GerenciadorCompetidores::ckpPontos[id][1],pontoNariz)) {
			GerenciadorCompetidores::verificaCheckpointVoltaAdiante(i,id);
			GerenciadorCompetidores::ckpQtdNextAtual[i] = GerenciadorCompetidores::ckpQtdNext[id];
			GerenciadorCompetidores::ckpNextAtual[i] = GerenciadorCompetidores::ckpNext[id];
			GerenciadorCompetidores::ckpQtdPrevAtual[i] = GerenciadorCompetidores::ckpQtdPrev[GerenciadorCompetidores::ckpNextAtual[i][0]];
			GerenciadorCompetidores::ckpPrevAtual[i] = GerenciadorCompetidores::ckpPrev[GerenciadorCompetidores::ckpNextAtual[i][0]];
            //Placa
            if(i==0)
                GerenciadorCompetidores::placaAtual = GerenciadorCompetidores::placas[id];
            GerenciadorCompetidores::atualizaPontoOtimoLocal(i);
		}
		//Passou checkpoints anteriores
		mp = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][0][0]-pontoNariz[0])*
				(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][0][0]-pontoNariz[0]) +
				(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][0][1]-pontoNariz[1])*
				(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][0][1]-pontoNariz[1]);
		id = GerenciadorCompetidores::ckpPrevAtual[i][0];
		for(j=0;j<GerenciadorCompetidores::ckpQtdPrevAtual[i];j++) {
			aux = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][0][0]-pontoNariz[0])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][0][0]-pontoNariz[0]) +
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][0][1]-pontoNariz[1])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][0][1]-pontoNariz[1]);
			if(aux<mp) {
				mp = aux;
				id = GerenciadorCompetidores::ckpPrevAtual[i][j];
			}
			aux = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][1][0]-pontoNariz[0])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][1][0]-pontoNariz[0]) +
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][1][1]-pontoNariz[1])*
					(GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][1][1]-pontoNariz[1]);
			if(aux<mp) {
				mp = aux;
				id = GerenciadorCompetidores::ckpPrevAtual[i][j];
			}
		}
		if(GerenciadorCompetidores::esquerdaInt(GerenciadorCompetidores::ckpPontos[id][0],GerenciadorCompetidores::ckpPontos[id][1],pontoNariz)) {
			GerenciadorCompetidores::verificaCheckpointVoltaRetrocesso(i,id);
			GerenciadorCompetidores::ckpQtdPrevAtual[i] = GerenciadorCompetidores::ckpQtdPrev[id];
			GerenciadorCompetidores::ckpPrevAtual[i] = GerenciadorCompetidores::ckpPrev[id];
			GerenciadorCompetidores::ckpQtdNextAtual[i] = GerenciadorCompetidores::ckpQtdNext[GerenciadorCompetidores::ckpPrevAtual[i][0]];
			GerenciadorCompetidores::ckpNextAtual[i] = GerenciadorCompetidores::ckpNext[GerenciadorCompetidores::ckpPrevAtual[i][0]];
            //Placa
            if(i==0)
                GerenciadorCompetidores::placaAtual = GerenciadorCompetidores::placas[id];
			GerenciadorCompetidores::atualizaPontoOtimoLocal(i);
		}
	}
}

void GerenciadorCompetidores::calculaPorcentagensPista() {
	int i,j,p[2],p1[2],p2[2],vet[2],pontoNariz[2],idPrev,idNext;
	float dist,dist1,dist2,distPerc;
	for(i=0;i<GerenciadorCompetidores::qtdComp;i++) {
		GerenciadorCompetidores::comp[i]->getPontoNariz(pontoNariz);
		p1[0] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][0][0]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][1][0])/2;
		p1[1] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][0][1]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][0]][1][1])/2;
		vet[0] = p1[0] - pontoNariz[0];
		vet[1] = p1[1] - pontoNariz[1];
		dist1 = vet[0]*vet[0] + vet[1]*vet[1];
		idPrev = GerenciadorCompetidores::ckpPrevAtual[i][0];
		for(j=1;j<GerenciadorCompetidores::ckpQtdPrevAtual[i];j++) {
			p[0] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][0][0]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][1][0])/2;
			p[1] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][0][1]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpPrevAtual[i][j]][1][1])/2;
			vet[0] = p[0] - pontoNariz[0];
			vet[1] = p[1] - pontoNariz[1];
			dist = vet[0]*vet[0] + vet[1]*vet[1];
			if(dist<dist1) {
				p1[0] = p[0];
				p1[1] = p[1];
				dist1 = dist;
				idPrev = GerenciadorCompetidores::ckpPrevAtual[i][j];
			}
		}
		p2[0] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][0][0]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][1][0])/2;
		p2[1] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][0][1]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][0]][1][1])/2;
		vet[0] = p2[0] - pontoNariz[0];
		vet[1] = p2[1] - pontoNariz[1];
		dist2 = vet[0]*vet[0] + vet[1]*vet[1];
		idNext = GerenciadorCompetidores::ckpNextAtual[i][0];
		for(j=1;j<GerenciadorCompetidores::ckpQtdNextAtual[i];j++) {
			p[0] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][0][0]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][1][0])/2;
			p[1] = (GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][0][1]+GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[i][j]][1][1])/2;
			vet[0] = p[0] - pontoNariz[0];
			vet[1] = p[1] - pontoNariz[1];
			dist = vet[0]*vet[0] + vet[1]*vet[1];
			if(dist<dist2) {
				p2[0] = p[0];
				p2[1] = p[1];
				dist2 = dist;
				idNext = GerenciadorCompetidores::ckpNextAtual[i][j];
			}
		}
		vet[0] = p1[0] - p2[0];
		vet[1] = p1[1] - p2[1];
		dist = sqrt(vet[0]*vet[0] + vet[1]*vet[1]);
		dist1 = sqrt(dist1);
		dist2 = sqrt(dist2);
		distPerc = (dist1 + dist2 - dist)/2 + dist1;
		distPerc /= dist;
		if(idNext!=0)
			GerenciadorCompetidores::porcentagemPistaComp[i] = GerenciadorCompetidores::ckpPercursos[idPrev] + distPerc*(GerenciadorCompetidores::ckpPercursos[idNext] - GerenciadorCompetidores::ckpPercursos[idPrev]);
		else
			GerenciadorCompetidores::porcentagemPistaComp[i] = GerenciadorCompetidores::ckpPercursos[idPrev] + distPerc*(1 - GerenciadorCompetidores::ckpPercursos[idPrev]);
		HUDLayer::atualizaPorcentagemCompetidor(i,GerenciadorCompetidores::porcentagemPistaComp[i]);
	}
}

void GerenciadorCompetidores::calculaPosicao() {
	if(GerenciadorCompetidores::qtdComp!=1) {
		int i,pos = 1;
		float somatorio[GerenciadorCompetidores::qtdComp];
		for(i=0;i<GerenciadorCompetidores::qtdComp;i++) {
			somatorio[i] = GerenciadorCompetidores::voltasComp[i];
			if(GerenciadorCompetidores::ckpsVolta[i]==-1)
				somatorio[i] -= 1.0 - GerenciadorCompetidores::porcentagemPistaComp[i];
			else
				somatorio[i] += GerenciadorCompetidores::porcentagemPistaComp[i];
			if(somatorio[i]>somatorio[0])
				pos++;
		}
		HUDLayer::atualizaPosicaoJogador(pos);
	}
}

void GerenciadorCompetidores::decisaoVolante() {
	int i,j,contAfastamento;
	float mod,distanciaTotal,porcentagemCurva,origem[2] = {0,0};
	float vetorOtimoGlobal[2],distanciaOG;
	float vetorOtimoLocal[2];
	float vetoresAfastamento[GerenciadorCompetidores::qtdComp][2],distanciaAf[GerenciadorCompetidores::qtdComp];
	float vetorRoda[2];
	float vetorDirecao[2];
	b2Vec2 vetorRodaDianteira;
	for(i=GerenciadorCompetidores::compInicial;i<GerenciadorCompetidores::qtdComp;i++) {
		distanciaTotal = 0;
		if(i!=0) {
			vetorOtimoGlobal[0] = GerenciadorCompetidores::comp[0]->getSprite()->getPositionX() - GerenciadorCompetidores::comp[i]->getSprite()->getPositionX();
			vetorOtimoGlobal[1] = GerenciadorCompetidores::comp[0]->getSprite()->getPositionY() - GerenciadorCompetidores::comp[i]->getSprite()->getPositionY();
			distanciaOG = vetorOtimoGlobal[0]*vetorOtimoGlobal[0] + vetorOtimoGlobal[1]*vetorOtimoGlobal[1];
			mod = sqrt(distanciaOG);
			vetorOtimoGlobal[0] /= mod;
			vetorOtimoGlobal[1] /= mod;
			if(distanciaOG<=RAIO_VISAO) {
				distanciaOG = RAIO_VISAO - distanciaOG;
				distanciaTotal += distanciaOG;
			}
			else
				distanciaOG = -1;
		}
		else
			distanciaOG = -1;
		vetorOtimoLocal[0] = GerenciadorCompetidores::pontosOtimosLocais[i][0] - GerenciadorCompetidores::comp[i]->getSprite()->getPositionX();
		vetorOtimoLocal[1] = GerenciadorCompetidores::pontosOtimosLocais[i][1] - GerenciadorCompetidores::comp[i]->getSprite()->getPositionY();
		mod = sqrt(vetorOtimoLocal[0]*vetorOtimoLocal[0] + vetorOtimoLocal[1]*vetorOtimoLocal[1]);
		vetorOtimoLocal[0] /= mod;
		vetorOtimoLocal[1] /= mod;
		contAfastamento = 0;
		for(j=1;j<GerenciadorCompetidores::qtdComp;j++) {
			if(j!=i) {
				vetoresAfastamento[j][0] = GerenciadorCompetidores::comp[i]->getSprite()->getPositionX() - GerenciadorCompetidores::comp[j]->getSprite()->getPositionX();
				vetoresAfastamento[j][1] = GerenciadorCompetidores::comp[i]->getSprite()->getPositionY() - GerenciadorCompetidores::comp[j]->getSprite()->getPositionY();
				distanciaAf[j] = vetoresAfastamento[j][0]*vetoresAfastamento[j][0] + vetoresAfastamento[j][1]*vetoresAfastamento[j][1];
				mod = sqrt(distanciaAf[j]);
				vetoresAfastamento[j][0] /= mod;
				vetoresAfastamento[j][1] /= mod;
				if(distanciaAf[j]<=RAIO_VISAO) {
					distanciaAf[j] = RAIO_VISAO - distanciaAf[j];
					distanciaTotal += distanciaAf[j];
					contAfastamento++;
				}
				else
					distanciaAf[j] = -1;
			}
			else
				distanciaAf[j] = -1;
		}
		if(distanciaTotal!=0) {
			vetorDirecao[0] = 0;
			vetorDirecao[1] = 0;
			porcentagemCurva = 0;
			if(distanciaOG!=-1) {
				distanciaOG = PORCENTAGEM_ATRAPALHAR_JOGADOR*(distanciaOG/distanciaTotal);
				vetorDirecao[0] += distanciaOG*vetorOtimoGlobal[0];
				vetorDirecao[1] += distanciaOG*vetorOtimoGlobal[1];
				porcentagemCurva += distanciaOG;
			}
			for(j=1;j<GerenciadorCompetidores::qtdComp;j++)
				if(distanciaAf[j]!=-1) {
					distanciaAf[j] = (PORCENTAGEM_AFASTAMENTO*distanciaAf[j])/(contAfastamento*distanciaTotal);
					vetorDirecao[0] += distanciaAf[j]*vetoresAfastamento[j][0];
					vetorDirecao[1] += distanciaAf[j]*vetoresAfastamento[j][1];
					porcentagemCurva += distanciaAf[j];
				}
			porcentagemCurva = 1.0 - porcentagemCurva;
			vetorDirecao[0] = porcentagemCurva*vetorOtimoLocal[0];
			vetorDirecao[1] = porcentagemCurva*vetorOtimoLocal[1];
			mod = sqrt(vetorDirecao[0]*vetorDirecao[0] + vetorDirecao[1]*vetorDirecao[1]);
			if(mod!=0) {
				vetorDirecao[0] /= mod;
				vetorDirecao[1] /= mod;
			}
		}
		else {
			vetorDirecao[0] = vetorOtimoLocal[0];
			vetorDirecao[1] = vetorOtimoLocal[1];
		}
		vetorRodaDianteira = GerenciadorCompetidores::comp[i]->getFrontWheel()->GetWorldVector(b2Vec2(0,1));
		vetorRoda[0] = vetorRodaDianteira.x;
		vetorRoda[1] = vetorRodaDianteira.y;
		porcentagemCurva = acos(vetorRoda[0]*vetorDirecao[0] + vetorRoda[1]*vetorDirecao[1]);
		if(porcentagemCurva>ANGULO_MAXIMO_VOLANTE)
			porcentagemCurva = ANGULO_MAXIMO_VOLANTE;
		porcentagemCurva /= ANGULO_MAXIMO_VOLANTE;
		if(GerenciadorCompetidores::esquerdaFloat(origem,vetorRoda,vetorDirecao))
			porcentagemCurva = -porcentagemCurva;
		if(porcentagemCurva>0.1f)
			GerenciadorCompetidores::comp[i]->turnRight();
		else if(porcentagemCurva<-0.1f)
			GerenciadorCompetidores::comp[i]->turnLeft();
		else
			GerenciadorCompetidores::comp[i]->dontTurn();
	}
}

bool GerenciadorCompetidores::esquerdaInt(int *p0,int *p1,int *p2) {
	return (p1[0]-p0[0])*(p2[1]-p0[1])-(p2[0]-p0[0])*(p1[1]-p0[1])>0?true:false;
}

bool GerenciadorCompetidores::esquerdaFloat(float *p0,float *p1,float *p2) {
	return (p1[0]-p0[0])*(p2[1]-p0[1])-(p2[0]-p0[0])*(p1[1]-p0[1])>0?true:false;
}

void GerenciadorCompetidores::retornaVetorDiretorCheckpoint(float* r){
    int pontoNariz[2];
    GerenciadorCompetidores::comp[0]->getPontoNariz(pontoNariz);
    r[0]=GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[0][0]][0][0]-pontoNariz[0];
    r[1]=GerenciadorCompetidores::ckpPontos[GerenciadorCompetidores::ckpNextAtual[0][0]][0][1]-pontoNariz[1];
    float m = sqrt(r[0]*r[0]+r[1]*r[1]);
    r[0]/=m;
    r[1]/=m;
}

bool GerenciadorCompetidores::retornaContraMao(){
    float direcaoCheckpoint[2];
    float direcaoCompetidor[2];
    retornaVetorDiretorCheckpoint(direcaoCheckpoint);
    GerenciadorCompetidores::comp[0]->getVetorDiretor(direcaoCompetidor);
    return (sqrt(((direcaoCompetidor[0]+direcaoCheckpoint[0])*(direcaoCompetidor[0]+direcaoCheckpoint[0]))+
                 ((direcaoCompetidor[1]+direcaoCheckpoint[1])*(direcaoCompetidor[1]+direcaoCheckpoint[1])))<1.0);
}

Competidor* GerenciadorCompetidores::retornaJogador(){
    return comp[0];
}

void GerenciadorCompetidores::release() {
	int i;
	delete GerenciadorCompetidores::porcentagemPistaComp;
	delete GerenciadorCompetidores::voltasComp;
	delete GerenciadorCompetidores::ckpsVolta;
	for(i=0;i<GerenciadorCompetidores::qtdComp;i++)
		delete GerenciadorCompetidores::pontosOtimosLocais[i];
	delete GerenciadorCompetidores::pontosOtimosLocais;
	delete GerenciadorCompetidores::ckpPrevAtual;
	delete GerenciadorCompetidores::ckpQtdPrevAtual;
	delete GerenciadorCompetidores::ckpNextAtual;
	delete GerenciadorCompetidores::ckpQtdNextAtual;
	for(i=0;i<GerenciadorCompetidores::ckpQtd;i++) {
		delete GerenciadorCompetidores::ckpPrev[i];
		delete GerenciadorCompetidores::ckpNext[i];
		delete GerenciadorCompetidores::ckpPontos[i][0];
		delete GerenciadorCompetidores::ckpPontos[i][1];
		delete GerenciadorCompetidores::ckpPontos[i];
	}
	delete GerenciadorCompetidores::ckpPercursos;
	delete GerenciadorCompetidores::ckpQtdPrev;
	delete GerenciadorCompetidores::ckpQtdNext;
	delete GerenciadorCompetidores::ckpPrev;
	delete GerenciadorCompetidores::ckpNext;
	delete GerenciadorCompetidores::ckpPontos;
}