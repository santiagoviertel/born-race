#include "Engine.h"

float Gameplay::sensibilidadeAcelerometro;
Gameplay* Gameplay::sharedGameplay;

bool Gameplay::init() {
	if(!CCLayer::init())
		return false;
	Gameplay::sharedGameplay = this;
	SpriteSource::create();
	Mundo::create();
	return true;
}

void Gameplay::loadGame(int pista,int* competidores,int qtdCompetidores,int idJogador,int dificuldade,int vitaminas) {
	Mundo::loadGame(pista,competidores,qtdCompetidores,idJogador,dificuldade,vitaminas);
}

void Gameplay::beginGame() {
	float tempoAnimacoes = 1.5;
	HUDLayer::beginGame(tempoAnimacoes);
	Gameplay::sharedGameplay->schedule(schedule_selector(Gameplay::update));
}

void Gameplay::startRace(float dt) {
	Mundo::startRace();
}

void Gameplay::start() {
	HUDLayer::getSharedHUDLayer()->start();
}

void Gameplay::pause() {
	HUDLayer::getSharedHUDLayer()->pause();
}

void Gameplay::setAccelerometer(bool flag,float sensibilidade) {
	if(flag) {
		Gameplay::sensibilidadeAcelerometro = sensibilidade;
		HUDLayer::getSharedHUDLayer()->enableAccelerometer();
	}
	else {
		HUDLayer::getSharedHUDLayer()->disableAccelerometer();
		Mundo::disableAccelerometer();
	}
	Gameplay::sharedGameplay->setAccelerometerEnabled(flag);
}

void Gameplay::didAccelerate(CCAcceleration *pAccelerationValue) {
	float porcentagem;
	porcentagem = pAccelerationValue->x;
	if(porcentagem<-Gameplay::sensibilidadeAcelerometro)
		porcentagem = -Gameplay::sensibilidadeAcelerometro;
	else if(porcentagem>Gameplay::sensibilidadeAcelerometro)
		porcentagem = Gameplay::sensibilidadeAcelerometro;
	porcentagem /= Gameplay::sensibilidadeAcelerometro;
	Mundo::updateAccelerometer(porcentagem);
}

void Gameplay::update(float dt) {
	Mundo::update(dt);
	Engine::getSharedEngine()->setPosition(ccp(-(Mundo::getCentralPoint().x-CCDirector::sharedDirector()->getWinSize().width/2),-(Mundo::getCentralPoint().y-CCDirector::sharedDirector()->getWinSize().height/2)));
}

Gameplay* Gameplay::getSharedGameplay() {
	return Gameplay::sharedGameplay;
}