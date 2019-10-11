//
//  Diafragma.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 22/02/13.
//
//

#include "ExterminadorDourado.h"

class Diafragma:public InimigoMovel {

public:
	Diafragma(CCDictionary* dados,CCTMXObjectGroup* destino);
	void update(float dt);
	void tocarSom();
};