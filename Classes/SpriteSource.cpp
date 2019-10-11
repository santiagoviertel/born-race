#include "Engine.h"
#include "Constantes.h"

void SpriteSource::create() {
	char tela;
	char caminhoHUDs[28];
	char caminhoPersonagens[35];
	char caminhoItens[24];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		tela = '1';
		break;
	case TELA_2:
		tela = '2';
		break;
	case TELA_3:
		tela = '3';
		break;
	case TELA_4:
		tela = '4';
		break;
	}
	sprintf(caminhoHUDs,"tela%c/spriteSheetHUDs.plist",tela);
	sprintf(caminhoPersonagens,"tela%c/spriteSheetPersonagens.plist",tela);
	sprintf(caminhoItens,"tela%c/itens/itens.plist",tela);
	CCSpriteFrameCache::purgeSharedSpriteFrameCache();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(caminhoHUDs);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(caminhoPersonagens);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(caminhoItens);
}

void SpriteSource::addChild(CCSprite* camada,int zOrder) {
	Pista::getTiledMap()->addChild(camada,zOrder);
	Pista::getTiledMap()->sortAllChildren();
}

void SpriteSource::removeChild(CCSprite* camada) {
	Pista::getTiledMap()->removeChild(camada,true);
}