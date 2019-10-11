//
//  Espermicida.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 03/04/13.
//
//

#include "InimigoMovel.h"

class Espermicida:public CCObject{

public:
	Espermicida(CCSpriteFrame* tiro, CCSpriteFrame* area,CCPoint pontoInicial,CCDictionary* dadosEspermicida);
    virtual void Recarregar();
	virtual void Atirar();
    virtual void Derreter();
	virtual void aplicarEfeito(Competidor* competidor)=0;
	virtual void removerEfeito(Competidor* competidor)=0;

private:
	CCSprite *sprite;
	CCArray *animacoes;
    CCPoint posInicial;
    CCSpriteFrame* municao;
};