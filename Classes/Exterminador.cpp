//
//  Exterminador.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 22/02/13.
//
//

#include "Mundo.h"
#include "SimpleAudioEngine.h"

#define MODO_ESPERA 0
#define MODO_ATIRAR 1
#define MODO_CAMINHAR 2
#define MODO_DESAPARECER 3
#define MODO_DESTRUIDO 4
#define MODO_REAPARECER 5

#define VISAO 49.0
#define TEMPO_DO_FRAME 0.15

Exterminador::Exterminador(CCDictionary* dados,CCTMXObjectGroup* destino):InimigoMovel(ccp(
		dados->valueForKey("x")->intValue(),
		dados->valueForKey("y")->intValue()),
		destino->objectNamed(dados->valueForKey("pontoFinal")->getCString())  ) {
	Exterminador::estado = MODO_ESPERA;
    tempoRetorno= dados->valueForKey("tempo")->floatValue();
}

void Exterminador::iniciarExterminador(CCSpriteFrame* spr,CCArray* frameSet1, CCArray* frameSet2, Espermicida* esp) {
	Exterminador::espermicida = esp;
    tempo = 0;
	//Inicializa o sprite
    sprInicial = spr;
	//Definicoes do Box2D
	CCSize s = spr->getRectInPixels().size;
	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 1.25f, b2Vec2(0.5,-0.45), 0);
	b2FixtureDef extShapeDef;
	extShapeDef.shape = &shape;
	extShapeDef.density = 1.0f;
	extShapeDef.friction = 0.0f;
	extShapeDef.restitution = 0.0f;
	Exterminador::setarSprite(spr,&extShapeDef);

	//Configurando a animacao do Sprite
	CCAnimation* anim = CCAnimation::createWithSpriteFrames(frameSet1,TEMPO_DO_FRAME);
	CCAnimate *animacao = CCAnimate::create(anim);
	CCCallFunc *andarF = CCCallFunc::create(this,callfunc_selector(Exterminador::andar));
	CCSequence* sequencia = CCSequence::createWithTwoActions(animacao, andarF);
	Exterminador::setarAnimacao(sequencia); //0

	//Adiciona as animacoes de movimento
	//Movimentacao para PontoFinal
	CCMoveTo* paraPontoFinal = CCMoveTo::create(Exterminador::tempoDeDeslocamento,Exterminador::pontoFinal);
	andarF = CCCallFunc::create(this,callfunc_selector(Exterminador::desaparecer));
	sequencia = CCSequence::createWithTwoActions(paraPontoFinal, andarF);
	Exterminador::setarAnimacao(sequencia);//1

	anim = CCAnimation::createWithSpriteFrames(frameSet2,TEMPO_DO_FRAME);
	animacao = CCAnimate::create(anim);
	CCRepeatForever *animacaoForever = CCRepeatForever::create(animacao);
	Exterminador::setarAnimacao(animacaoForever);//2

	//Animacao do desaparecimento
	CCFadeTo *fadeIn =  CCFadeTo::create(0.5, 0);
	andarF = CCCallFunc::create(this,callfunc_selector(Exterminador::autoDestruir));
	sequencia = CCSequence::createWithTwoActions(fadeIn, andarF);
	Exterminador::setarAnimacao(sequencia); //3
    
    //Animacao do reaparecimento
    fadeIn =  CCFadeTo::create(1.0, 255);
	andarF = CCCallFunc::create(this,callfunc_selector(Exterminador::recarregar));
	sequencia = CCSequence::createWithTwoActions(fadeIn, andarF);
	Exterminador::setarAnimacao(sequencia); //4
}

void Exterminador::update(float dt) {
	switch(estado) {
	case MODO_ESPERA:
		manterVigilancia(dt);
		break;
	case MODO_CAMINHAR:
		InimigoMovel::update(dt);
		break;
    case MODO_DESTRUIDO:
        esperaRetorno(dt);
        break;
	default:
		break;
	}
}

void Exterminador::esperaRetorno(float dt){
    tempo -=dt;
    if(tempo<=0){
        estado=MODO_REAPARECER;
        espermicida->Derreter();
        CCSprite* spr = Exterminador::pegarSprite();
        spr->setPosition(pontoInicial);
        spr->setDisplayFrame(sprInicial);
        iniciarAnimacao(4);
    }
}

void Exterminador::recarregar(){
    estado=MODO_ESPERA;
    tempo = 2;
}

void Exterminador::manterVigilancia(float dt) {
    if(tempo>0){
        tempo-=dt;
        if (tempo<=0) {
            tempo=0;
        }
        
    }else{
    
	CCSprite* spr = Exterminador::pegarSprite();
	CCPoint pos = ccp(spr->getPositionX()/Mundo::getPTMRatio(),
			spr->boundingBox().getMidY()/Mundo::getPTMRatio());
	Competidor** competidor = Mundo::getCompetidor();
	int qtd = Mundo::retornaQtdCompetidor();
	for(int i=0;i<qtd;i++) {
		CCSprite* spr2 = competidor[i]->getSprite();
		CCPoint pos2 = ccp(spr2->getPositionX()/Mundo::getPTMRatio(),
				spr2->getPositionY()/Mundo::getPTMRatio());
		if(((pow((pos2.x-pos.x), 2)+pow((pos2.y-pos.y), 2))<=VISAO)) { //Jogador chegou perto
			iniciarAnimacao(0);
            CCSprite* jog = competidor[0]->getSprite();
            CCPoint joP = ccp(jog->getPositionX(), jog->getPositionY());
            if(i==0 || ((pow((pos.x-joP.x), 2)+pow((pos.y-joP.y), 2))<pow(CCDirector::sharedDirector()->getWinSize().height,2)))
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sons/exterminador.wav");
			espermicida->Atirar();
			estado = MODO_ATIRAR;
		}
	 }
    }
}

void Exterminador::andar() {
	estado = MODO_CAMINHAR;
	iniciarAnimacao(2);
	iniciarAnimacao(1);
}

void Exterminador::desaparecer() {
	estado = MODO_DESAPARECER;
	pararTodasAnimacoes();
	iniciarAnimacao(3);
}

void Exterminador::autoDestruir() {
	estado = MODO_DESTRUIDO;
	tempo = tempoRetorno;
}