//
//  Inimigo.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 22/02/13.
//
//

#include "Constantes.h"
#include "Mundo.h"

Inimigo::Inimigo(CCPoint posicao) {
	Inimigo::pontoInicial = posicao;
	Inimigo::animacao = CCArray::create();
	Inimigo::animacao->retain();
}

void Inimigo::setarSprite(CCSpriteFrame* frame,b2FixtureDef* ballShapeDef) {
	Inimigo::sprite = CCSprite::createWithSpriteFrame(frame);
	Inimigo::sprite->setPosition(Inimigo::pontoInicial);
	SpriteSource::addChild(Inimigo::sprite,CAMADA_4);

	//Definicao do corpo
	float PTM = Mundo::getPTMRatio();
	Inimigo::corpoDef.position = b2Vec2(sprite->getPositionX()/PTM,
			sprite->getPositionY()/PTM);
	Inimigo::corpoDef.userData = ballShapeDef->userData;
	Inimigo::corpo = Mundo::getb2World()->CreateBody(&corpoDef);
	Inimigo::corpo->CreateFixture(ballShapeDef);
}

void Inimigo::iniciarAnimacao(unsigned int index) {
	Inimigo::sprite->runAction(static_cast<CCAction*>(animacao->objectAtIndex(index)));
}

void Inimigo::setarAnimacao(CCAction* acao) {
	Inimigo::animacao->addObject(acao);
}

b2Body* Inimigo::pegarCorpo() {
	return Inimigo::corpo;
}

b2BodyDef* Inimigo::pegarDefinicaoDoCorpo() {
	return &corpoDef;
}

void Inimigo::pararTodasAnimacoes() {
	Inimigo::sprite->stopAllActions();
}

CCSprite* Inimigo::pegarSprite() {
	return Inimigo::sprite;
}

void Inimigo::removerSprite() {
	SpriteSource::removeChild(Inimigo::sprite);
}