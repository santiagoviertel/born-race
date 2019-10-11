//
//  Diafragma.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 22/02/13.
//
//

#include "Constantes.h"
#include "Mundo.h"
#include "SimpleAudioEngine.h"

#define TEMPO_DO_FRAME 0.15

Diafragma::Diafragma(CCDictionary* dados,CCTMXObjectGroup* destino):InimigoMovel(ccp(
		dados->valueForKey("x")->intValue(),
		dados->valueForKey("y")->intValue()),
		destino->objectNamed(dados->valueForKey("pontoFinal")->getCString())) {
	//Cria o frameset da animacao do Diafragma
	CCArray* frameSet = CCArray::create();
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Diafragma1.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Diafragma2.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Diafragma3.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Diafragma2.png"));

	//Inicializa o sprite
	CCSpriteFrame* spr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Diafragma1.png");

	//Definicoes do Box2D
	b2CircleShape circle;
	circle.m_radius = 0.9;
	circle.m_p.Set(0,-0.1);
	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.0f;
	ballShapeDef.restitution = 10.0f;
	ballShapeDef.userData = new Sensorable(SENSORABLE_DIAFRAGMA,this);

	Diafragma::setarSprite(spr,&ballShapeDef);

	//Configurando a animacao do Sprite
	CCAnimation* anim = CCAnimation::createWithSpriteFrames(frameSet,TEMPO_DO_FRAME);
	CCAnimate *animacao = CCAnimate::create(anim);
	CCRepeatForever *animacaoForever = CCRepeatForever::create(animacao);
	setarAnimacao(animacaoForever);

	//Adiciona as animacoes de movimento
	//Movimentacao para PontoFinal
	CCMoveTo* paraPontoFinal = CCMoveTo::create(Diafragma::tempoDeDeslocamento,Diafragma::pontoFinal);
	//Movimentoacao para PontoInicial
	CCMoveTo* paraPontoInicial = CCMoveTo::create(Diafragma::tempoDeDeslocamento,Diafragma::pontoInicial);

	//Criar a sequencia para quando chegar ao ponto final, voltar ao inicial
	CCSequence* vaiVolta = CCSequence::createWithTwoActions(paraPontoFinal,paraPontoInicial);

	CCRepeatForever* vaiVoltaEternamente = CCRepeatForever::create(vaiVolta);
	Diafragma::setarAnimacao(vaiVoltaEternamente);

	//Iniciar as Animacao
	Diafragma::iniciarAnimacao(0);
	Diafragma::iniciarAnimacao(1);
}

void Diafragma::update(float dt) {
	InimigoMovel::update(dt);
}

void Diafragma::tocarSom() {
    Competidor** competidor = Mundo::getCompetidor();
    CCSprite* jog = competidor[0]->getSprite();
    CCPoint joP = ccp(jog->getPositionX(), jog->getPositionY());
    CCPoint pos = ccp(sprite->getPositionX(), sprite->getPositionY());
    if(((pow((pos.x-joP.x), 2)+pow((pos.y-joP.y), 2))<pow(CCDirector::sharedDirector()->getWinSize().height,2)))
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/diafragma.wav");
}