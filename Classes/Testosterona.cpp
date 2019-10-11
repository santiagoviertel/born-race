//
//  Testosterona.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "Testosterona.h"
#include "SimpleAudioEngine.h"

Testosterona::Testosterona(CCPoint pos):Item(pos) {
	CCArray* frameSet = CCArray::create();
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Testosterona1.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Testosterona2.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Testosterona1.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Testosterona3.png"));
	CCAnimation* anim = CCAnimation::createWithSpriteFrames(frameSet,TEMPO_DO_FRAME);
	CCAnimate *animacao = CCAnimate::create(anim);
	CCRepeatForever *animacaoForever = CCRepeatForever::create(animacao);
	Testosterona::inicializar(animacaoForever);
}

void Testosterona::aplicarEfeito(Competidor* comp) {
	if(comp->pegarColisaoDeItem()==0) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/testosterone.mp3");
	}
	comp->aplicarEfeito_Invencibilidade();
}

void Testosterona::removerEfeito(Competidor* comp) {
	comp->removerEfeito_Invencibilidade();
}