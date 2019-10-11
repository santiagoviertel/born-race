//
//  Item.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 24/04/13.
//
//

#define ITEM_DNA 1
#define ITEM_TESTOSTERONA 2
#define ITEM_SUPERHERO 3
#define ITEM_SPERMGUN 4

#define TEMPO_DO_FRAME 0.15

#include "Diafragma.h"

class Item:public CCObject {

public:
	Item(CCPoint pos);
	virtual void aplicarEfeito(Competidor* comp)=0;

private:
	CCPoint posicao;
	CCSprite* sprite;
	b2Fixture* fixture;

protected:
	void inicializar(CCAction* animacao);
	void removerItem();
};