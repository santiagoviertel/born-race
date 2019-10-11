//
//  ExterminadorDourado.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 22/03/13.
//
//

#include "ExterminadorDourado.h"

ExterminadorDourado::ExterminadorDourado(CCDictionary* dados,CCTMXObjectGroup* destino):Exterminador(dados,destino) {
	//Cria o frameset da animacao do Diafragma
	CCArray* frameSet1 = CCArray::create();
	frameSet1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorDourado5.png"));
	frameSet1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorDourado4.png"));
	frameSet1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorDourado3.png"));
	CCArray* frameSet2 = CCArray::create();
	frameSet2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorDourado2.png"));
	frameSet2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorDourado1.png"));

	CCSpriteFrame* spr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExterminadorDourado4.png");

	CCDictionary* dadosEspermicida = destino->objectNamed(dados->valueForKey("espermicida")->getCString());
	ExterminadorDourado::iniciarExterminador(spr, frameSet1, frameSet2, new EspermicidaVerde(pontoInicial, dadosEspermicida));
}