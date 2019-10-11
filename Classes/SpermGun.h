//
//  SpermGun.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#include "SuperHero.h"

class SpermGun:public Item {

public:
	SpermGun(CCPoint pos);
	void aplicarEfeito(Competidor* comp);
	void removerEfeito(Competidor* comp);

private:
	bool desativado;
};