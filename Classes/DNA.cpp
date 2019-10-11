//
//  DNA.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "DNA.h"
#include "SimpleAudioEngine.h"

DNA::DNA(CCPoint pos):Item(pos) {
	CCArray* frameSet = CCArray::create();
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("DNA3.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("DNA2.png"));
	frameSet->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("DNA1.png"));

	CCAnimation* anim = CCAnimation::createWithSpriteFrames(frameSet,TEMPO_DO_FRAME);
	CCAnimate *animacao = CCAnimate::create(anim);
	CCRepeatForever *animacaoForever = CCRepeatForever::create(animacao);

	DNA::inicializar(animacaoForever);
}

void DNA::aplicarEfeito(Competidor* comp) {
    CCPoint pontoCompetidor = comp->getSprite()->getPosition();
    CCPoint pontoJogador = GerenciadorCompetidores::retornaJogador()->getSprite()->getPosition();
    float dist = sqrt((pontoJogador.x-pontoCompetidor.x)*(pontoJogador.x-pontoCompetidor.x)+(pontoJogador.y-pontoCompetidor.y)*(pontoJogador.y-pontoCompetidor.y));
	if(comp->pegarColisaoDeItem()==0 && dist<CCDirector::sharedDirector()->getWinSize().height)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/dna.mp3");
	comp->aplicarEfeito_AumentoVelocidade();
}

void DNA::removerEfeito(Competidor* comp) {
	comp->removerEfeito_AumentoVelocidade();
}