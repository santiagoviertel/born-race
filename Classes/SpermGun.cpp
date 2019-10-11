//
//  SpermGun.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "SimpleAudioEngine.h"
#include "Mundo.h"

SpermGun::SpermGun(CCPoint pos):Item(pos) {
	SpermGun::desativado = false;

	CCArray* frameSet = CCArray::create();
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sperm-Gun1.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sperm-Gun2.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sperm-Gun1.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sperm-Gun3.png"));

	CCAnimation* anim = CCAnimation::createWithSpriteFrames(frameSet,TEMPO_DO_FRAME);
	CCAnimate *animacao = CCAnimate::create(anim);
	CCRepeatForever *animacaoForever = CCRepeatForever::create(animacao);
	SpermGun::inicializar(animacaoForever);
}

void SpermGun::aplicarEfeito(Competidor* comp) {
	if(!desativado) {
		if(comp->pegarColisaoDeItem()==0) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/gun.mp3");
		}
		for(int i=0; i<Pista::getQtdCompetidores();i++) {
			Competidor* other = static_cast<Competidor*>(Mundo::getCompetidor()[i]);
			if(comp != other) {
				other->aplicarEfeito_Paralisia();
			}
		}
		SpermGun::desativado = true;
		SpermGun::removerItem();
	}
}

void SpermGun::removerEfeito(Competidor* comp) {
	CCLog("Remover Efeito: SpermGun");
}