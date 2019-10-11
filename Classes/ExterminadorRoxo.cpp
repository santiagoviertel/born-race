//
//  ExterminadorRoxo.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 19/03/13.
//
//

#include "ExterminadorRoxo.h"

ExterminadorRoxo::ExterminadorRoxo(CCDictionary* dados,CCTMXObjectGroup* destino):Exterminador(dados,destino) {
	//Cria o frameset da animacao do Diafragma
	CCArray* frameSet1 = CCArray::create();
	frameSet1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo5.png"));
	frameSet1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo4.png"));
	frameSet1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo3.png"));
	CCArray* frameSet2 = CCArray::create();
	frameSet2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo2.png"));
	frameSet2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo1.png"));

	CCSpriteFrame* spr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorRoxo4.png");

	CCDictionary* dadosEspermicida = destino->objectNamed(dados->valueForKey("espermicida")->getCString());
	ExterminadorRoxo::iniciarExterminador(spr, frameSet1, frameSet2, new EspermicidaBranco(pontoInicial,dadosEspermicida));
}