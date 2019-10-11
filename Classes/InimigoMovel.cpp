//
//  InimigoMovel.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 01/03/13.
//
//

#include "Mundo.h"

InimigoMovel::InimigoMovel(CCPoint posicaoInicial, CCDictionary* dados):Inimigo(posicaoInicial) {
	InimigoMovel::tempoDeDeslocamento = dados->valueForKey("tempo")->floatValue();
	InimigoMovel::pontoFinal = ccp(dados->valueForKey("x")->intValue(),dados->valueForKey("y")->intValue());
}

void InimigoMovel::update(float dt) {
	b2Body* corpo = InimigoMovel::pegarCorpo();
	CCSprite* spr = InimigoMovel::pegarSprite();
	corpo->SetTransform(b2Vec2(spr->getPositionX()/Mundo::getPTMRatio(),
			spr->boundingBox().getMidY()/Mundo::getPTMRatio()), 0.0f);
}