//
//  Exterminador.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 22/02/13.
//
//

#include "EspermicidaVerde.h"

class Exterminador:public InimigoMovel {

public:
	Exterminador(CCDictionary* dados,CCTMXObjectGroup* destino);
	void update(float dt);

protected:
    float tempoRetorno;
    float tempo;
	void iniciarExterminador(CCSpriteFrame* spr,CCArray* frameSet1, CCArray* frameSet2, Espermicida* esp);

private:
	Espermicida *espermicida;
	int estado;
	void manterVigilancia(float dt);
	void andar();
	void desaparecer();
	void autoDestruir();
    void recarregar();
    void esperaRetorno(float dt);
    CCSpriteFrame* sprInicial;
};