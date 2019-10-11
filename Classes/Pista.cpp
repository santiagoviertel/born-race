#include "Engine.h"
#include "Constantes.h"

//Medida em tiles por segundo
#define VELOCIDADE_CAMADA_1 0.2
#define RELACAO_CAMADA_4 0.25

float Pista::camada1TempoTotal;
float Pista::camada1VelocidadePixelsSegundo;
CCTMXTiledMap* Pista::pista;
CCTMXLayer* Pista::camada1;
CCTMXLayer* Pista::camada4;
CCNode** Pista::competidores;
int Pista::qtdCompetidores;
CCArray* Pista::inimigos;
CCArray* Pista::itens;

//Cria um pista. Recebe como parâmetro a id da pista
void Pista::create(int pista) {

	//Passo 1: Obter o diretório do arquivo em que está a pista de acordo com o tamanho
	//1.1 Pega o tamanho de tela
	char pacote[34] = "";
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		strcat(pacote,"tela1/pistas/");
		break;
	case TELA_2:
		strcat(pacote,"tela2/pistas/");
		break;
	case TELA_3:
		strcat(pacote,"tela3/pistas/");
		break;
	case TELA_4:
		strcat(pacote,"tela4/pistas/");
		break;
	}
	//1.2 Aqui pega as pista
	switch(pista) {
	case EPIDIDYMIS_TRACK_1:
		strcat(pacote,"epididimo_track1.tmx");
		break;
	case EPIDIDYMIS_TRACK_2:
		strcat(pacote,"epididimo_track2.tmx");
		break;
	}

	//2. Criando o mapa
	Pista::pista = CCTMXTiledMap::create(pacote);

	//3. Adiciona o mapa na Engine
	Gameplay::getSharedGameplay()->addChild(Pista::pista);

	//4. Organizar as camadas do Tiled
	//4.1 Cuidando da camada de sangue
	Pista::camada1 = Pista::pista->layerNamed("Camada 1");
	Pista::camada1->setAnchorPoint(ccp(0,1));
	Pista::camada1->_setZOrder(CAMADA_1);

	//4.2 Camadas das Paredes
	CCTMXLayer* camada2 = Pista::pista->layerNamed("Camada 2");
	camada2->_setZOrder(CAMADA_5);

	//4.2.1 Preenchendo os tiles de borda
	CCSize tamanho = camada2->getMapTileSize();
//	camada2->setTileGID(1, CCPoint(-1,-1));

	//4.3 Camada da linha de Chegada
	CCTMXLayer* camada3 = Pista::pista->layerNamed("Camada 3");
	camada3->_setZOrder(CAMADA_6);

	//4.4 Camada de fundo
	Pista::camada4 = Pista::pista->layerNamed("Camada 4");
	Pista::camada4->setAnchorPoint(ccp(0,1));
	Pista::camada4->_setZOrder(CAMADA_7);


	//5. Configurar o movimento do sangue
	Pista::camada1TempoTotal = 0;
	Pista::camada1VelocidadePixelsSegundo = VELOCIDADE_CAMADA_1*Pista::pista->getTileSize().height;

	//6. Posiciona a linha de chegada
	Pista::posicionaLargada(camada3);

	//7. Adicionar os inimigos na pista
	//7.1 Pegando o diretório
	int inim = 0;
	char caminho[16],arquivo[41];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		sprintf(caminho,"tela1/inimigos/");
		break;
	case TELA_2:
		sprintf(caminho,"tela2/inimigos/");
		break;
	case TELA_3:
		sprintf(caminho,"tela3/inimigos/");
		break;
	case TELA_4:
		sprintf(caminho,"tela4/inimigos/");
		break;
	}

	//7.2 Cria uma Array para adicionar os inimigos
	Pista::inimigos = CCArray::create();
	Pista::inimigos->retain();                 //WARNING: Lembrar de liberar ao destruir

	//7.3 Obter a lista de inimigos
	CCTMXObjectGroup *objects = Pista::pista->objectGroupNamed("Inimigos");
	CCArray *listaInimigo = objects->getObjects();

	//7.4 Para cada inimigo na lista
	CCObject *obj;
	CCARRAY_FOREACH(listaInimigo,obj) {
		//7.4.1 Cria um dicionário com os dados do inimigo a ser adicionado
		CCDictionary *dict = static_cast<CCDictionary*>(obj);
		CCTMXObjectGroup* destino = Pista::pista->objectGroupNamed("fInimigo");

		//7.4.2 Verifica o inimigo e instancia de acordo com o tipo de inimigo
		switch (dict->valueForKey("inimigo")->intValue()) {
		case DIAFRAGMA:
			if(!(inim&1)) {
				sprintf(arquivo,"%sdiafragma.plist",caminho);
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(arquivo);
				inim += 1;
			}
			Pista::inimigos->addObject(new Diafragma(dict,destino));
			break;
		case EXTERMINADOR_ROXO:
			if(!(inim&2)) {
				sprintf(arquivo,"%sexterminadorRoxo.plist",caminho);
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(arquivo);
				inim += 2;
			}
			Pista::inimigos->addObject(new ExterminadorRoxo(dict,destino));
			break;
		case EXTERMINADOR_DOURADO:
			if(!(inim&4)) {
				sprintf(arquivo,"%sexterminadorDourado.plist",caminho);
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(arquivo);
				inim += 4;
			}
			Pista::inimigos->addObject(new ExterminadorDourado(dict,destino));
			break;
		default:
			break;
		}
	}
	//8. Adicionando Itens
	{
		Pista::itens = CCArray::create();
		Pista::itens->retain();
		CCTMXObjectGroup *objects = Pista::pista->objectGroupNamed("Itens");
		CCArray *listaItens = objects->getObjects();
		CCObject *obj;
		CCARRAY_FOREACH(listaItens,obj) {
			CCDictionary *dict = static_cast<CCDictionary*>(obj);
			switch (dict->valueForKey("tipo")->intValue()) {
			case ITEM_DNA:
				Pista::itens->addObject(new DNA(ccp(dict->valueForKey("x")->floatValue(),
						dict->valueForKey("y")->floatValue())));
				break;
			case ITEM_TESTOSTERONA:
				Pista::itens->addObject(new Testosterona(ccp(dict->valueForKey("x")->floatValue(),
						dict->valueForKey("y")->floatValue())));
				break;
			case ITEM_SUPERHERO:
				Pista::itens->addObject(new SuperHero(ccp(dict->valueForKey("x")->floatValue(),
						dict->valueForKey("y")->floatValue())));
				break;
			case ITEM_SPERMGUN:
				Pista::itens->addObject(new SpermGun(ccp(dict->valueForKey("x")->floatValue(),
						dict->valueForKey("y")->floatValue())));
				break;
			default:
				CCLog("Pista.cpp: Item n‹o programado");
				break;
			}
		}
	}
	//9. Ordenar as camadas e os itens
	Pista::pista->sortAllChildren();
}

void Pista::setSpriteGroup(CCNode** compCorpo,int qtdComp) {
	int i;
	Pista::qtdCompetidores = qtdComp;
	Pista::competidores = new CCNode*[Pista::qtdCompetidores];
	for(i=0;i<Pista::qtdCompetidores;i++)
		Pista::competidores[i] = compCorpo[i];
	WallManager::create(Pista::pista->layerNamed("Camada 2"),Pista::qtdCompetidores);
}

void Pista::posicionaLargada(CCTMXLayer* largada) {
	float dist,rot;
	int i,qtd;
	CCPoint p1,p2,vet;
	CCTMXObjectGroup *objects = Pista::pista->objectGroupNamed("CheckPoints");
	CCDictionary *dict = objects->objectNamed("ckp011");
	p1.setPoint(dict->valueForKey("x")->intValue(),dict->valueForKey("y")->intValue());
	dict = objects->objectNamed("ckp012");
	p2.setPoint(dict->valueForKey("x")->intValue(),dict->valueForKey("y")->intValue());
	vet.x = p1.x - p2.x;
	vet.y = p1.y - p2.y;
	//Preenchendo tiles para largada
	dist = sqrt(vet.x*vet.x + vet.y*vet.y);
	qtd = (dist/Pista::pista->getTileSize().width) + 2;
	for(i=1;i<qtd;i++)
		largada->setTileGID(largada->getTileSet()->m_uFirstGid,ccp(i,0));
	//Posicionando a camada corretamente
	largada->setAnchorPoint(ccp(qtd/(2*largada->getLayerSize().width),1 - (164/(216*largada->getLayerSize().height))));
	largada->setPosition((p1.x+p2.x)/2,(p1.y+p2.y)/2);
	//Rotacionando a camada corretamente
	vet.x /= dist;
	if(vet.y<0)
		rot = 2*M_PI - acos(vet.x);
	else
		rot = acos(vet.x);
	rot = -(rot*180.0f)/M_PI;
	largada->setRotation(rot);
}

CCPoint Pista::getStartingPosition(int i) {
	float mod,aux,ang = -M_PI/2;
	CCPoint p1,p2,pontoBase,vetBaseX,vetBaseY,ret;
	CCTMXObjectGroup *objects = Pista::pista->objectGroupNamed("CheckPoints");
	CCDictionary *dict = objects->objectNamed("ckp011");
	p1.setPoint(dict->valueForKey("x")->intValue(),dict->valueForKey("y")->intValue());
	dict = objects->objectNamed("ckp012");
	p2.setPoint(dict->valueForKey("x")->intValue(),dict->valueForKey("y")->intValue());
	pontoBase.x = (p1.x + p2.x)/2;
	pontoBase.y = (p1.y + p2.y)/2;
	vetBaseY.x = p1.x - p2.x;
	vetBaseY.y = p1.y - p2.y;
	mod = sqrt(vetBaseY.x*vetBaseY.x + vetBaseY.y*vetBaseY.y);
	vetBaseY.x /= mod;
	vetBaseY.y /= mod;
	aux = vetBaseY.x;
	vetBaseX.x = vetBaseY.x*cos(ang) - vetBaseY.y*sin(ang);
	vetBaseX.y = aux*sin(ang) + vetBaseY.y*cos(ang);
	if(i==1) {
		ret.x = pontoBase.x + vetBaseX.x*(0.8*Pista::pista->getTileSize().width);
		ret.y = pontoBase.y + vetBaseX.y*(0.8*Pista::pista->getTileSize().height);
	}
	else if(i==2) {
		ret.x = pontoBase.x + vetBaseX.x*(1.6*Pista::pista->getTileSize().width) - vetBaseY.x*(0.7*Pista::pista->getTileSize().width);
		ret.y = pontoBase.y + vetBaseX.y*(1.6*Pista::pista->getTileSize().height) - vetBaseY.y*(0.7*Pista::pista->getTileSize().height);
	}
	else if(i==3) {
		ret.x = pontoBase.x + vetBaseX.x*(1.6*Pista::pista->getTileSize().width) + vetBaseY.x*(0.7*Pista::pista->getTileSize().width);
		ret.y = pontoBase.y + vetBaseX.y*(1.6*Pista::pista->getTileSize().height) + vetBaseY.y*(0.7*Pista::pista->getTileSize().height);
	}
	else if(i==4) {
		ret.x = pontoBase.x + vetBaseX.x*(2.4*Pista::pista->getTileSize().width) - vetBaseY.x*(0.3*Pista::pista->getTileSize().width);
		ret.y = pontoBase.y + vetBaseX.y*(2.4*Pista::pista->getTileSize().height) - vetBaseY.y*(0.3*Pista::pista->getTileSize().height);
	}
	else {
		ret.x = pontoBase.x + vetBaseX.x*(2.4*Pista::pista->getTileSize().width) + vetBaseY.x*(0.3*Pista::pista->getTileSize().width);
		ret.y = pontoBase.y + vetBaseX.y*(2.4*Pista::pista->getTileSize().height) + vetBaseY.y*(0.3*Pista::pista->getTileSize().height);
	}
	return ret;
}

float Pista::getStartingOrientation() {
	float ret;
	CCPoint p1,p2,vet;
	CCTMXObjectGroup *objects = Pista::pista->objectGroupNamed("CheckPoints");
	CCDictionary *dict = objects->objectNamed("ckp011");
	p1.setPoint(dict->valueForKey("x")->intValue(),dict->valueForKey("y")->intValue());
	dict = objects->objectNamed("ckp012");
	p2.setPoint(dict->valueForKey("x")->intValue(),dict->valueForKey("y")->intValue());
	vet.x = p1.x - p2.x;
	vet.y = p1.y - p2.y;
	vet.x /= sqrt(vet.x*vet.x + vet.y*vet.y);
	if(vet.y<0)
		ret = 2*M_PI - acos(vet.x);
	else
		ret = acos(vet.x);
	return ret;
}

CCTMXTiledMap* Pista::getTiledMap() {
	return Pista::pista;
}

void Pista::update(float dt) {
	int i;
	Pista::movimentaCamadaSangue(dt,Pista::competidores[0]->getPosition());
	Pista::movimentaCamadaProfundidade(Pista::competidores[0]->getPosition());

	/*Reposiciona Paredes Logicas*/
	for(i=0;i<Pista::qtdCompetidores;i++)
		WallManager::posicionaParedes(Pista::competidores[i]->boundingBox(),i);

	/*Atualiza os inimigos */
	CCObject *obj;
	CCARRAY_FOREACH(Pista::inimigos,obj) {
		Inimigo *inimigo = static_cast<Inimigo*>(obj);
		inimigo->update(dt);
	}
}

void Pista::movimentaCamadaSangue(float dt,CCPoint centralPoint) {
	centralPoint.x -= CCDirector::sharedDirector()->getWinSize().width/2;
	Pista::camada1TempoTotal += dt;
	float deltaS = Pista::camada1VelocidadePixelsSegundo*Pista::camada1TempoTotal;
	if(deltaS>=3*Pista::pista->getTileSize().height) {
		deltaS -= 3*Pista::pista->getTileSize().height;
		Pista::camada1TempoTotal -= (3*Pista::pista->getTileSize().height)/Pista::camada1VelocidadePixelsSegundo;
	}
	centralPoint.y += CCDirector::sharedDirector()->getWinSize().height/2 + 3*Pista::pista->getTileSize().height - deltaS;
	Pista::camada1->setPosition(centralPoint);
}

void Pista::movimentaCamadaProfundidade(CCPoint centralPoint) {
	CCPoint pc3 = ccp(RELACAO_CAMADA_4*centralPoint.x,RELACAO_CAMADA_4*centralPoint.y);
	int deltaS;
	int wImg = 4*Pista::pista->getTileSize().width;
	int hImg = 4*Pista::pista->getTileSize().height;
	centralPoint.x -= CCDirector::sharedDirector()->getWinSize().width/2;
	centralPoint.y += CCDirector::sharedDirector()->getWinSize().height/2;
	if(pc3.x>centralPoint.x)
		deltaS = wImg - ((int)pc3.x-(int)centralPoint.x)%wImg;
	else
		deltaS = ((int)centralPoint.x-(int)pc3.x)%wImg;
	pc3.x = centralPoint.x - deltaS;
	if(pc3.y>=centralPoint.y)
		deltaS = ((int)pc3.y-(int)centralPoint.y)%hImg;
	else
		deltaS = hImg - ((int)centralPoint.y-(int)pc3.y)%hImg;
	pc3.y = centralPoint.y + deltaS;
	Pista::camada4->setPosition(pc3);
}

void Pista::release() {
	WallManager::release();
	delete Pista::competidores;
	Engine::getSharedEngine()->removeChild(Pista::pista,true);
	Pista::inimigos->release();
}

CCNode** Pista::getCompetidores() {
	return Pista::competidores;
}

int Pista::getQtdCompetidores() {
	return Pista::qtdCompetidores;
}