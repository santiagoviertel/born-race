//
//  DNA.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "Item.h"

class DNA:public Item {

public:
	DNA(CCPoint pos);
	void aplicarEfeito(Competidor* comp);
	void removerEfeito(Competidor* comp);
};