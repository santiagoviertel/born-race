//
//  SuperHero.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "Testosterona.h"

class SuperHero:public Item {

public:
	SuperHero(CCPoint pos);
	void aplicarEfeito(Competidor* comp);
	void removerEfeito(Competidor* comp);
};