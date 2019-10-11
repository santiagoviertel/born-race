#include "Engine.h"
#include "SimpleAudioEngine.h"

HUDLayer* HUDLayer::sharedHUDLayer;
int HUDLayer::qtdCompetidores;
int HUDLayer::click[3];
float HUDLayer::escalas[2];
float HUDLayer::limitesPercurso[2];
float HUDLayer::tempoAnimacoes;
CCSprite* HUDLayer::btEsquerda;
CCSprite* HUDLayer::btDireita;
CCSprite* HUDLayer::btPause;
CCSprite* HUDLayer::percursoPista;
CCSprite** HUDLayer::posicoesCompetidores;
CCLabelTTF** HUDLayer::labels;
CCSprite* HUDLayer::cronometro;
CCSprite* HUDLayer::semaforo;
//Placas
CCSprite* HUDLayer::placas[4];

bool HUDLayer::init() {
	if(!CCLayer::init())
		return false;
	HUDLayer::sharedHUDLayer = this;
	HUDLayer::btEsquerda = CCSprite::createWithSpriteFrameName("botao_curva_esquerda.png");
	HUDLayer::escalas[0] = (0.2*CCDirector::sharedDirector()->getWinSize().height)/CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("botao_curva_esquerda.png")->getOriginalSize().height;
	HUDLayer::escalas[1] = 1.25*HUDLayer::escalas[0];
	HUDLayer::btEsquerda->setScale(HUDLayer::escalas[0]);
	HUDLayer::btEsquerda->retain();
	HUDLayer::btDireita = CCSprite::createWithSpriteFrameName("botao_curva_esquerda.png");
	HUDLayer::btDireita->setFlipX(true);
	HUDLayer::btDireita->setScale(HUDLayer::escalas[0]);
	HUDLayer::btDireita->retain();
	HUDLayer::btPause = CCSprite::createWithSpriteFrameName("botao_pause.png");
	HUDLayer::btPause->setScale(HUDLayer::escalas[0]);
	HUDLayer::btPause->retain();
	HUDLayer::percursoPista = CCSprite::createWithSpriteFrameName("PercursoPista.png");
	HUDLayer::percursoPista->setScale((0.45*CCDirector::sharedDirector()->getWinSize().height)/CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("PercursoPista.png")->getOriginalSize().height);
    HUDLayer::placas[0] = CCSprite::createWithSpriteFrameName("curva.gif");
    HUDLayer::placas[1] = CCSprite::createWithSpriteFrameName("curva.gif");
    HUDLayer::placas[2] = CCSprite::createWithSpriteFrameName("bifurcacao.gif");
    HUDLayer::placas[3] = CCSprite::createWithSpriteFrameName("contramao.gif");
    HUDLayer::placas[1]->setFlipX(true);

    float x = CCDirector::sharedDirector()->getWinSize().width*0.5 ;
    float y = CCDirector::sharedDirector()->getWinSize().height*0.9;

    for(int i=0;i<=3;i++){
        HUDLayer::placas[i]->setPosition(CCPoint(x,y));
        HUDLayer::placas[i]->retain();
        addChild(HUDLayer::placas[i]);
        HUDLayer::placas[i]->setVisible(false);
    }

    HUDLayer::semaforo = CCSprite::createWithSpriteFrameName("SemaforoVermelho.png");
    HUDLayer::semaforo->setPosition(CCPoint(x,CCDirector::sharedDirector()->getWinSize().height+HUDLayer::semaforo->getContentSize().height*0.5));
    HUDLayer::semaforo->retain();
    addChild(HUDLayer::semaforo);
	addChild(HUDLayer::btEsquerda);
	addChild(HUDLayer::btDireita);
	addChild(HUDLayer::btPause);
	addChild(HUDLayer::percursoPista);
	HUDLayer::qtdCompetidores = 0;
	HUDLayer::click[0] = -1;
	HUDLayer::click[1] = -1;
	HUDLayer::click[2] = -1;
	HUDLayer::limitesPercurso[0] = 0.022*HUDLayer::percursoPista->boundingBox().size.height;
	HUDLayer::limitesPercurso[1] = 0.978*HUDLayer::percursoPista->boundingBox().size.height;
	setTouchEnabled(false);
	return true;
}

void HUDLayer::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent) {
	CCPoint ponto = (static_cast<CCTouch*>(pTouches->anyObject()))->getLocationInView();
	ponto.y = CCDirector::sharedDirector()->getWinSize().height - ponto.y;
	if(!Engine::getSharedEngine()->isAccelerometerEnabled()) {
		if(HUDLayer::btEsquerda->boundingBox().containsPoint(ponto)) {
			HUDLayer::btEsquerda->setScale(HUDLayer::escalas[1]);
			HUDLayer::click[0] = (static_cast<CCTouch*>(pTouches->anyObject()))->getID();
			Mundo::leftTurnPressed();
		}
		else if(HUDLayer::btDireita->boundingBox().containsPoint(ponto)) {
			HUDLayer::btDireita->setScale(HUDLayer::escalas[1]);
			HUDLayer::click[1] = (static_cast<CCTouch*>(pTouches->anyObject()))->getID();
			Mundo::rightTurnPressed();
		}
	}
	if(HUDLayer::btPause->boundingBox().containsPoint(ponto)) {
		HUDLayer::btPause->setScale(HUDLayer::escalas[1]);
		HUDLayer::click[2] = (static_cast<CCTouch*>(pTouches->anyObject()))->getID();
	}
}

void HUDLayer::ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent) {
	if(!Engine::getSharedEngine()->isAccelerometerEnabled()) {
		if((static_cast<CCTouch*>(pTouches->anyObject()))->getID()==HUDLayer::click[0]) {
			HUDLayer::btEsquerda->setScale(HUDLayer::escalas[0]);
			if(HUDLayer::click[1]!=-1)
				Mundo::rightTurnPressed();
			else
				Mundo::leftTurnReleased();
			HUDLayer::click[0] = -1;
		}
		else if((static_cast<CCTouch*>(pTouches->anyObject()))->getID()==HUDLayer::click[1]) {
			HUDLayer::btDireita->setScale(HUDLayer::escalas[0]);
			if(HUDLayer::click[0]!=-1)
				Mundo::leftTurnPressed();
			else
				Mundo::rightTurnReleased();
			HUDLayer::click[1] = -1;
		}
	}
	if((static_cast<CCTouch*>(pTouches->anyObject()))->getID()==click[2]) {
		HUDLayer::btPause->setScale(HUDLayer::escalas[0]);
		HUDLayer::click[2] = -1;
		Gameplay::getSharedGameplay()->setAccelerometer(!Gameplay::getSharedGameplay()->isAccelerometerEnabled(),0.4f);
	}
}

void HUDLayer::startInitialAnimation() {
	int i;
	HUDLayer::sharedHUDLayer->setTouchEnabled(false);
	HUDLayer::btEsquerda->setAnchorPoint(ccp(-0.125,1.125));
	HUDLayer::btEsquerda->setRotation(90);
	HUDLayer::btEsquerda->setPosition(ccp(0,CCDirector::sharedDirector()->getWinSize().height));
	HUDLayer::btEsquerda->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,-90));
	HUDLayer::btDireita->setAnchorPoint(ccp(1.125,1.125));
	HUDLayer::btDireita->setRotation(-90);
	HUDLayer::btDireita->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height));
	HUDLayer::btDireita->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,90));
	HUDLayer::btPause->setAnchorPoint(ccp(-0.125,-0.125));
	HUDLayer::btPause->setRotation(-90);
	HUDLayer::btPause->setPosition(ccp(0,0));
	HUDLayer::btPause->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,90));
	HUDLayer::percursoPista->setAnchorPoint(ccp(1,0));
	HUDLayer::percursoPista->setRotation(90);
	HUDLayer::percursoPista->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width,0));
	HUDLayer::percursoPista->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,-90));
	for(i=0;i<HUDLayer::qtdCompetidores;i++)
		HUDLayer::posicoesCompetidores[i]->setVisible(false);
	if(HUDLayer::qtdCompetidores==1) {
		HUDLayer::cronometro->setPosition(ccp(-0.15*CCDirector::sharedDirector()->getWinSize().width,0.42*CCDirector::sharedDirector()->getWinSize().height));
		HUDLayer::cronometro->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.15*CCDirector::sharedDirector()->getWinSize().width,0.42*CCDirector::sharedDirector()->getWinSize().height)));
		HUDLayer::labels[2]->setPosition(ccp(HUDLayer::cronometro->getPositionX()-0.32*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY()));
		HUDLayer::labels[2]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.15*CCDirector::sharedDirector()->getWinSize().width-0.32*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY())));
		HUDLayer::labels[3]->setPosition(HUDLayer::cronometro->getPosition());
		HUDLayer::labels[3]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.15*CCDirector::sharedDirector()->getWinSize().width,0.42*CCDirector::sharedDirector()->getWinSize().height)));
		HUDLayer::labels[4]->setPosition(ccp(HUDLayer::cronometro->getPositionX()+0.31*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY()));
		HUDLayer::labels[4]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.15*CCDirector::sharedDirector()->getWinSize().width+0.31*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY())));
	}
	else {
		HUDLayer::labels[2]->setPosition(ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-HUDLayer::labels[2]->boundingBox().size.height));
		HUDLayer::labels[2]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-HUDLayer::labels[2]->boundingBox().size.height)));
		HUDLayer::labels[3]->setPosition(ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-2*HUDLayer::labels[2]->boundingBox().size.height));
		HUDLayer::labels[3]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-2*HUDLayer::labels[2]->boundingBox().size.height)));
	}
	HUDLayer::labels[0]->setPosition(ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+2*HUDLayer::labels[0]->boundingBox().size.height));
	HUDLayer::labels[0]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+2*HUDLayer::labels[0]->boundingBox().size.height)));
	HUDLayer::labels[1]->setPosition(ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+HUDLayer::labels[0]->boundingBox().size.height));
	HUDLayer::labels[1]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+HUDLayer::labels[0]->boundingBox().size.height)));

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/abertura.wav");
    HUDLayer::semaforo->runAction(CCSequence::createWithTwoActions(
                                            CCMoveTo::create(HUDLayer::tempoAnimacoes, ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
                                                                                        CCDirector::sharedDirector()->getWinSize().height*0.9)),
                                            CCCallFunc::create(HUDLayer::sharedHUDLayer,callfunc_selector(HUDLayer::semaforoON))));
}

void HUDLayer::semaforoON(){
    CCArray* frameSet = CCArray::create();
    frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SemaforoVermelho.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SemaforoAmarelo.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SemaforoVerde.png"));
    CCAnimation* anim = CCAnimation::createWithSpriteFrames(frameSet,1.0);
    CCAnimate *animacao = CCAnimate::create(anim);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/go.mp3");
    HUDLayer::semaforo->runAction(CCSequence::createWithTwoActions(animacao, CCCallFunc::create(HUDLayer::sharedHUDLayer,callfunc_selector(HUDLayer::endInitialAnimation))));
    
}

void HUDLayer::endInitialAnimation() {
	int i;
    HUDLayer::semaforo->runAction( CCMoveTo::create(HUDLayer::tempoAnimacoes,
                                            ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,
                                            CCDirector::sharedDirector()->getWinSize().height+HUDLayer::semaforo->getContentSize().height*0.5)));
	for(i=0;i<HUDLayer::qtdCompetidores;i++)
		HUDLayer::posicoesCompetidores[i]->setVisible(true);
	HUDLayer::btEsquerda->setAnchorPoint(ccp(0.5,0.5));
	HUDLayer::btEsquerda->setPosition(ccp(HUDLayer::escalas[1]*CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("botao_curva_esquerda.png")->getOriginalSize().width/2,CCDirector::sharedDirector()->getWinSize().height-HUDLayer::escalas[1]*CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("botao_curva_esquerda.png")->getOriginalSize().height/2));
	HUDLayer::btDireita->setAnchorPoint(ccp(0.5,0.5));
	HUDLayer::btDireita->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-HUDLayer::escalas[1]*CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("botao_curva_esquerda.png")->getOriginalSize().width/2,CCDirector::sharedDirector()->getWinSize().height-HUDLayer::escalas[1]*CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("botao_curva_esquerda.png")->getOriginalSize().height/2));
	HUDLayer::btPause->setAnchorPoint(ccp(0.5,0.5));
	HUDLayer::btPause->setPosition(ccp(HUDLayer::escalas[1]*CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("botao_pause.png")->getOriginalSize().width/2,HUDLayer::escalas[1]*CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("botao_pause.png")->getOriginalSize().height/2));
	HUDLayer::sharedHUDLayer->setTouchEnabled(true);
    Gameplay::getSharedGameplay()->startRace(0);
}

void HUDLayer::startFinalAnimation() {
	int i;
	HUDLayer::sharedHUDLayer->setTouchEnabled(false);
	HUDLayer::btEsquerda->setAnchorPoint(ccp(-0.125,1.125));
	HUDLayer::btEsquerda->setPosition(ccp(0,CCDirector::sharedDirector()->getWinSize().height));
	HUDLayer::btEsquerda->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,90));
	HUDLayer::btDireita->setAnchorPoint(ccp(1.125,1.125));
	HUDLayer::btDireita->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height));
	HUDLayer::btDireita->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,-90));
	HUDLayer::btPause->setAnchorPoint(ccp(-0.125,-0.125));
	HUDLayer::btPause->setPosition(ccp(0,0));
	HUDLayer::btPause->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,-90));
	HUDLayer::percursoPista->setAnchorPoint(ccp(1,0));
	HUDLayer::percursoPista->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width,0));
	HUDLayer::percursoPista->runAction(CCRotateBy::create(HUDLayer::tempoAnimacoes,90));
	for(i=0;i<HUDLayer::qtdCompetidores;i++)
		HUDLayer::posicoesCompetidores[i]->setVisible(false);
	if(HUDLayer::qtdCompetidores==1) {
		HUDLayer::cronometro->setPosition(ccp(0.15*CCDirector::sharedDirector()->getWinSize().width,0.42*CCDirector::sharedDirector()->getWinSize().height));
		HUDLayer::cronometro->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-0.15*CCDirector::sharedDirector()->getWinSize().width,0.42*CCDirector::sharedDirector()->getWinSize().height)));
		HUDLayer::labels[2]->setPosition(ccp(0.15*CCDirector::sharedDirector()->getWinSize().width-0.32*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY()));
		HUDLayer::labels[2]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-HUDLayer::cronometro->getPositionX()-0.32*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY())));
		HUDLayer::labels[3]->setPosition(ccp(0.15*CCDirector::sharedDirector()->getWinSize().width,0.42*CCDirector::sharedDirector()->getWinSize().height));
		HUDLayer::labels[3]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-0.15*CCDirector::sharedDirector()->getWinSize().width,0.42*CCDirector::sharedDirector()->getWinSize().height)));
		HUDLayer::labels[4]->setPosition(ccp(0.15*CCDirector::sharedDirector()->getWinSize().width+0.31*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY()));
		HUDLayer::labels[4]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-HUDLayer::cronometro->getPositionX()+0.31*HUDLayer::cronometro->boundingBox().size.width,HUDLayer::cronometro->getPositionY())));
	}
	else {
		HUDLayer::labels[2]->setPosition(ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-HUDLayer::labels[2]->boundingBox().size.height));
		HUDLayer::labels[2]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-HUDLayer::labels[2]->boundingBox().size.height)));
		HUDLayer::labels[3]->setPosition(ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-2*HUDLayer::labels[2]->boundingBox().size.height));
		HUDLayer::labels[3]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2-2*HUDLayer::labels[2]->boundingBox().size.height)));
	}
	HUDLayer::labels[0]->setPosition(ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+2*HUDLayer::labels[0]->boundingBox().size.height));
	HUDLayer::labels[0]->runAction(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+2*HUDLayer::labels[0]->boundingBox().size.height)));
	HUDLayer::labels[1]->setPosition(ccp(0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+HUDLayer::labels[0]->boundingBox().size.height));
	HUDLayer::labels[1]->runAction(CCSequence::createWithTwoActions(CCMoveTo::create(HUDLayer::tempoAnimacoes,ccp(-0.08*CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height/2+HUDLayer::labels[0]->boundingBox().size.height)),CCCallFunc::create(HUDLayer::sharedHUDLayer,callfunc_selector(HUDLayer::endFinalAnimation))));
}

void HUDLayer::endFinalAnimation() {

}

void HUDLayer::beginGame(float tempoAnimacoes) {
	HUDLayer::tempoAnimacoes = tempoAnimacoes;
	HUDLayer::startInitialAnimation();
}

void HUDLayer::endGame() {
	HUDLayer::startFinalAnimation();
}

void HUDLayer::start() {
	HUDLayer::sharedHUDLayer->setTouchEnabled(true);
}

void HUDLayer::pause() {
	HUDLayer::sharedHUDLayer->setTouchEnabled(false);
}

void HUDLayer::atualizaPorcentagemCompetidor(int i,float p) {
	HUDLayer::posicoesCompetidores[i]->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-HUDLayer::percursoPista->boundingBox().size.width/2,HUDLayer::limitesPercurso[0] + p*(HUDLayer::limitesPercurso[1] - HUDLayer::limitesPercurso[0])));
}

void HUDLayer::atualizaPosicaoJogador(int posicao) {
	char texto[6];
	sprintf(texto,"%i - 5",posicao);
	HUDLayer::labels[3]->setString(texto);
}

void HUDLayer::atualizaVoltaJogador(int volta) {
	char texto[6];
	sprintf(texto,"%i - 5",volta);
	HUDLayer::labels[1]->setString(texto);
}

void HUDLayer::atualizaTempoJogador(int min,int seg,int cent) {
	char texto[3];
	sprintf(texto,"%2i",min);
	HUDLayer::labels[2]->setString(texto);
	sprintf(texto,"%02i",seg);
	HUDLayer::labels[3]->setString(texto);
	sprintf(texto,"%02i",cent);
	HUDLayer::labels[4]->setString(texto);
}

void HUDLayer::createCompetidores(int qtd) {
	int i;
	HUDLayer::qtdCompetidores = qtd;
	HUDLayer::posicoesCompetidores = new CCSprite*[HUDLayer::qtdCompetidores];
	for(i=HUDLayer::qtdCompetidores-1;i>0;i--) {
		HUDLayer::posicoesCompetidores[i] = CCSprite::createWithSpriteFrameName("PosicaoAdversarios.png");
		HUDLayer::posicoesCompetidores[i]->setScale((0.058*CCDirector::sharedDirector()->getWinSize().height)/HUDLayer::posicoesCompetidores[i]->boundingBox().size.height);
		HUDLayer::sharedHUDLayer->addChild(HUDLayer::posicoesCompetidores[i]);
	}
	HUDLayer::posicoesCompetidores[0] = CCSprite::createWithSpriteFrameName("PosicaoJogador.png");
	HUDLayer::posicoesCompetidores[0]->setScale((0.058*CCDirector::sharedDirector()->getWinSize().height)/HUDLayer::posicoesCompetidores[0]->boundingBox().size.height);
	HUDLayer::sharedHUDLayer->addChild(HUDLayer::posicoesCompetidores[0]);

	ccColor3B cor;
	cor.r = 100;
	cor.g = 255;
	cor.b = 100;

#ifdef __MACH__
	float tamanhoFonte1 = 0.08*0.50*CCDirector::sharedDirector()->getWinSize().height;
	float tamanhoFonte2 = 0.07*0.50*CCDirector::sharedDirector()->getWinSize().height;
	float tamanhoFonteDigital = 0.15*0.50*CCDirector::sharedDirector()->getWinSize().height;
	char digital7[14] = "Digital-7Mono";
	char myriadProBold[15] = "MyriadPro-Bold";
#else
	float tamanhoFonte1 = 0.08*0.75*CCDirector::sharedDirector()->getWinSize().height;
	float tamanhoFonte2 = 0.07*0.75*CCDirector::sharedDirector()->getWinSize().height;
	float tamanhoFonteDigital = 0.15*0.75*CCDirector::sharedDirector()->getWinSize().height;
	char digital7[25] = "fontes/Digital-7Mono.ttf";
	char myriadProBold[26] = "fontes/MyriadPro-Bold.ttf";
#endif
	if(HUDLayer::qtdCompetidores!=1) {
		HUDLayer::labels = new CCLabelTTF*[4];
		HUDLayer::labels[2] = CCLabelTTF::create("Posicao",myriadProBold,tamanhoFonte1);
		HUDLayer::labels[2]->setColor(cor);
		HUDLayer::labels[3] = CCLabelTTF::create("1 - 5",myriadProBold,tamanhoFonte2);
		HUDLayer::labels[3]->setColor(cor);
		HUDLayer::sharedHUDLayer->addChild(HUDLayer::labels[2]);
		HUDLayer::sharedHUDLayer->addChild(HUDLayer::labels[3]);
	}
	else {
		HUDLayer::labels = new CCLabelTTF*[5];
		HUDLayer::cronometro = CCSprite::createWithSpriteFrameName("Cronometro.png");
		HUDLayer::cronometro->setScale((0.15*CCDirector::sharedDirector()->getWinSize().height)/HUDLayer::cronometro->boundingBox().size.height);
		HUDLayer::labels[2] = CCLabelTTF::create(" 0",digital7,tamanhoFonteDigital);
		HUDLayer::labels[3] = CCLabelTTF::create("00",digital7,tamanhoFonteDigital);
		HUDLayer::labels[4] = CCLabelTTF::create("00",digital7,tamanhoFonteDigital);
		HUDLayer::sharedHUDLayer->addChild(HUDLayer::cronometro);
		HUDLayer::sharedHUDLayer->addChild(HUDLayer::labels[2]);
		HUDLayer::sharedHUDLayer->addChild(HUDLayer::labels[3]);
		HUDLayer::sharedHUDLayer->addChild(HUDLayer::labels[4]);
	}
	HUDLayer::labels[0] = CCLabelTTF::create("Volta",myriadProBold,tamanhoFonte1);
	HUDLayer::labels[0]->setColor(cor);
	HUDLayer::labels[1] = CCLabelTTF::create("1 - 5",myriadProBold,tamanhoFonte2);
	HUDLayer::labels[1]->setColor(cor);
	HUDLayer::sharedHUDLayer->addChild(HUDLayer::labels[0]);
	HUDLayer::sharedHUDLayer->addChild(HUDLayer::labels[1]);
}

void HUDLayer::releaseCompetidores() {
	int i;
	if(HUDLayer::qtdCompetidores==1) {
		HUDLayer::sharedHUDLayer->removeChild(HUDLayer::labels[4],true);
		HUDLayer::sharedHUDLayer->removeChild(HUDLayer::cronometro,true);
	}
	HUDLayer::sharedHUDLayer->removeChild(HUDLayer::labels[3],true);
	HUDLayer::sharedHUDLayer->removeChild(HUDLayer::labels[2],true);
	HUDLayer::sharedHUDLayer->removeChild(HUDLayer::labels[1],true);
	HUDLayer::sharedHUDLayer->removeChild(HUDLayer::labels[0],true);
	delete HUDLayer::labels;
	for(i=0;i<HUDLayer::qtdCompetidores;i++)
		HUDLayer::sharedHUDLayer->removeChild(HUDLayer::posicoesCompetidores[i],true);
	HUDLayer::qtdCompetidores = 0;
	delete HUDLayer::posicoesCompetidores;
}

void HUDLayer::enableAccelerometer() {
	HUDLayer::sharedHUDLayer->removeChild(HUDLayer::btEsquerda,true);
	HUDLayer::sharedHUDLayer->removeChild(HUDLayer::btDireita,true);
}

void HUDLayer::disableAccelerometer() {
	HUDLayer::click[0] = -1;
	HUDLayer::click[1] = -1;
	HUDLayer::btEsquerda->setScale(HUDLayer::escalas[0]);
	HUDLayer::btDireita->setScale(HUDLayer::escalas[0]);
	HUDLayer::sharedHUDLayer->addChild(HUDLayer::btEsquerda);
	HUDLayer::sharedHUDLayer->addChild(HUDLayer::btDireita);
}

HUDLayer* HUDLayer::getSharedHUDLayer() {
	return HUDLayer::sharedHUDLayer;
}

void HUDLayer::ativarPlacaEsquerda(){
    HUDLayer::desativarPlaca();
    placas[0]->setVisible(true);
}
void HUDLayer::ativarPlacaDireita(){
    HUDLayer::desativarPlaca();
    placas[1]->setVisible(true);
}
void HUDLayer::ativarPlacaBifucacao(){
    HUDLayer::desativarPlaca();
    placas[2]->setVisible(true);
}
void HUDLayer::ativarPlacaRetorno(){
    HUDLayer::desativarPlaca();
    placas[3]->setVisible(true);
}
void HUDLayer::desativarPlaca(){
    placas[0]->setVisible(false);
    placas[1]->setVisible(false);
    placas[2]->setVisible(false);
    placas[3]->setVisible(false);
}

HUDLayer::~HUDLayer() {
	HUDLayer::btPause->release();
	HUDLayer::btDireita->release();
	HUDLayer::btEsquerda->release();
    HUDLayer::placas[0]->release();
    HUDLayer::placas[1]->release();
    HUDLayer::placas[2]->release();
    HUDLayer::placas[3]->release();
}