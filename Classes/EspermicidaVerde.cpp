//
//  EspermicidaVerde.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 04/04/13.
//
//

#include "EspermicidaVerde.h"

EspermicidaVerde::EspermicidaVerde(CCPoint pontoInicial,CCDictionary* dadosEspermicida):Espermicida(
		CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("TirosExterminadorDourado1.png"),
		CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("TirosExterminadorDourado2.png"),
		pontoInicial,
		dadosEspermicida) {
}

void EspermicidaVerde::aplicarEfeito(Competidor* competidor){
	CCLog("Aplicar efeito verde");
}

void EspermicidaVerde::removerEfeito(Competidor* competidor){
	CCLog("remover efeito verde");
}