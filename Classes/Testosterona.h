//
//  Testosterona.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "DNA.h"

class Testosterona:public Item {

public:
	Testosterona(CCPoint pos);
	void aplicarEfeito(Competidor* comp);
	void removerEfeito(Competidor* comp);
};