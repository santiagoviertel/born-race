//
//  EspermicidaVerde.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 04/04/13.
//
//

#include "EspermicidaBranco.h"

class EspermicidaVerde:public Espermicida {

public:
	EspermicidaVerde(CCPoint pontoInicial,CCDictionary* dadosEspermicida);
	void aplicarEfeito(Competidor* competidor);
	void removerEfeito(Competidor* competidor);
};