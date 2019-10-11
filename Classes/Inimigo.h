//
//  Inimigo.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 22/02/13.
//
//

#include "GerenciadorCompetidores.h"

#define DIAFRAGMA 0
#define EXTERMINADOR_ROXO 1
#define EXTERMINADOR_DOURADO 2

class Inimigo:public CCObject {

public:
	Inimigo(CCPoint posicao);
	virtual void update(float dt) = 0;
	CCSprite* pegarSprite();

protected:
	CCPoint pontoInicial;
    CCSprite* sprite;
	void setarSprite(CCSpriteFrame* frame,b2FixtureDef* ballShapeDef);
	void iniciarAnimacao(unsigned int index);
	void setarAnimacao(CCAction* acao);
	b2Body* pegarCorpo();
	b2BodyDef* pegarDefinicaoDoCorpo();
	void pararTodasAnimacoes();
	void removerSprite();

private:	
	CCArray* animacao;
	b2Body* corpo;
	b2BodyDef corpoDef;
};