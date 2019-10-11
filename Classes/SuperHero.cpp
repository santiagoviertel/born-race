//
//  SuperHero.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "SuperHero.h"
#include "SimpleAudioEngine.h"

SuperHero::SuperHero(CCPoint pos):Item(pos) {
	CCArray* frameSet = CCArray::create();
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Super-Hero1.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Super-Hero2.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Super-Hero1.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Super-Hero3.png"));
	CCAnimation* anim = CCAnimation::createWithSpriteFrames(frameSet,TEMPO_DO_FRAME);
	CCAnimate *animacao = CCAnimate::create(anim);
	CCRepeatForever *animacaoForever = CCRepeatForever::create(animacao);
	SuperHero::inicializar(animacaoForever);
}

void SuperHero::aplicarEfeito(Competidor* comp) {
	if(comp->pegarColisaoDeItem()==0) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/hero.mp3");
	}
	comp->aplicarEfeito_Invencibilidade();
	comp->aplicarEfeito_direcaoAutomatica();
}

void SuperHero::removerEfeito(Competidor* comp) {
	CCLog("Remover Efeito: SuperHero");
}