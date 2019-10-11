//
//  Espermicida.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 03/04/13.
//
//

#include "Constantes.h"
#include "Mundo.h"

#define DESLOCAMENTO 0.25

Espermicida::Espermicida(CCSpriteFrame* tiro, CCSpriteFrame* area,CCPoint pontoInicial,CCDictionary* dadosEspermicida) {
	sprite = CCSprite::createWithSpriteFrame(tiro);
    municao = tiro;
	CCRect r;
	if(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo4.png"))
		r = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo4.png")->getRectInPixels();
	else
		r = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorDourado4.png")->getRectInPixels();
	posInicial= ccp(pontoInicial.x-(r.size.width*0.30),
			pontoInicial.y-(r.size.height*0.06));

	sprite->setPosition(posInicial);
	SpriteSource::addChild(Espermicida::sprite,CAMADA_5);

	//ANIMACAO
	animacoes = CCArray::create();
	animacoes->retain();
    

	//MOVE ATÉ O PONTO FINAL
	CCPoint pontoFinal = ccp(dadosEspermicida->valueForKey("x")->floatValue(),
			pontoInicial.y);
	CCMoveTo* paraPontoFinal = CCMoveTo::create(DESLOCAMENTO, pontoFinal);

	CCArray *array = CCArray::createWithObject(area);
//    array->retain();
	CCAnimation* anim = CCAnimation::createWithSpriteFrames(array,0.1);
	CCAnimate *animacao = CCAnimate::create(anim);
	CCSequence* seq = CCSequence::createWithTwoActions(paraPontoFinal,animacao);
	animacoes->addObject(seq);  //0

    //Desaparecer
    //Animacao do desaparecimento
	CCFadeTo *fadeIn =  CCFadeTo::create(0.2, 0);
    paraPontoFinal = CCMoveTo::create(0,posInicial);
    CCSequence* seq1 = CCSequence::createWithTwoActions(fadeIn, paraPontoFinal);
	CCCallFunc* andarF = CCCallFunc::create(this,callfunc_selector(Espermicida::Recarregar) );
    fadeIn =  CCFadeTo::create(0.2, 255);
	CCSequence* seq2 = CCSequence::createWithTwoActions(andarF, fadeIn);
    seq = CCSequence::createWithTwoActions(seq1, seq2);
	animacoes->addObject(seq); //1

	//Corpo para Box2D
	CCSize s = area->getRectInPixels().size;
	b2PolygonShape shape;
	shape.SetAsBox(0.8f,0.6f,b2Vec2(0.0,0.0),0);
	b2FixtureDef extShapeDef;
	extShapeDef.shape = &shape;
	extShapeDef.isSensor = true;
	b2Body* corpo;
	b2BodyDef corpoDef;
	float PTM = Mundo::getPTMRatio();
	corpoDef.userData = new Sensorable(SENSORABLE_ESPERMICIDA,this);
	corpoDef.position = b2Vec2(pontoFinal.x/PTM,
			pontoFinal.y/PTM);
	corpo = Mundo::getb2World()->CreateBody(&corpoDef);
	corpo->CreateFixture(&extShapeDef);
}
void Espermicida::Atirar() {
	sprite->runAction(static_cast<CCAction*>(animacoes->objectAtIndex(0)));
}

void Espermicida::Derreter(){
    sprite->runAction(static_cast<CCAction*>(animacoes->objectAtIndex(1)));
}

void Espermicida::Recarregar(){
    sprite->setDisplayFrame(municao);
}

//DESTRUTOR //Depois ajeito
/*
 animacoes->release();
 
 
 */

