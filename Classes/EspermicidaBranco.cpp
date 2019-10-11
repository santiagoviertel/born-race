//
//  EspermicidaBranco.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 03/04/13.
//
//

#include "EspermicidaBranco.h"

EspermicidaBranco::EspermicidaBranco(CCPoint pontoInicial,CCDictionary* dadosEspermicida):Espermicida(
		CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("TirosExterminadorRoxo1.png"),
		CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("TirosExterminadorRoxo2.png"),
		pontoInicial,
		dadosEspermicida) {
}

void EspermicidaBranco::aplicarEfeito(Competidor* competidor) {
	competidor->aplicarEfeito_ReducaoVelocidade();
}

void EspermicidaBranco::removerEfeito(Competidor* competidor) {
	competidor->removerEfeito_ReducaoVelocidade();
}