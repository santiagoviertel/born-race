//
//  EspermicidaBranco.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 03/04/13.
//
//

#include "Espermicida.h"

class EspermicidaBranco:public Espermicida {

public:
	EspermicidaBranco(CCPoint pontoInicial,CCDictionary* dadosEspermicida);
	void aplicarEfeito(Competidor* competidor);
	void removerEfeito(Competidor* competidor);
};