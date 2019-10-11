//
//  InimigoMovel.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 01/03/13.
//
//

#include "Inimigo.h"
class InimigoMovel:public Inimigo {

public:
    InimigoMovel(CCPoint posicaoInicial,CCDictionary* dados);
    virtual void update(float dt);
    
protected:
    float tempoDeDeslocamento;
    CCPoint pontoFinal;
};