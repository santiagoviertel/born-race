//
//  Item.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "Constantes.h"
#include "Mundo.h"

Item::Item(CCPoint pos) {
	Item::posicao = pos;
}

void Item::inicializar(CCAction* animacao) {
	Item::sprite = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("DNA1.png"));
	Item::sprite->setPosition(Item::posicao);
	Item::sprite->runAction(static_cast<CCAction*>(animacao));
	SpriteSource::addChild(Item::sprite,CAMADA_4);

	b2PolygonShape shape;
	shape.SetAsBox(0.4f,0.9f,b2Vec2(0.0,0.0),0);
	b2FixtureDef extShapeDef;
	extShapeDef.shape = &shape;
	extShapeDef.isSensor = true;
	b2Body* corpo;
	b2BodyDef corpoDef;

	float PTM = Mundo::getPTMRatio();
	corpoDef.userData = new Sensorable(SENSORABLE_ITEM,this);
	corpoDef.position = b2Vec2(posicao.x/PTM,
			posicao.y/PTM);
	corpo = Mundo::getb2World()->CreateBody(&corpoDef);
	fixture =  corpo->CreateFixture(&extShapeDef);
}

void Item::removerItem() {
	SpriteSource::removeChild(Item::sprite);
}