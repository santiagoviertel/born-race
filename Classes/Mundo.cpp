#include "Mundo.h"
#include "SimpleAudioEngine.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

int Mundo::dificuldade;
bool Mundo::race;
float Mundo::ptm_ratio;
b2World* Mundo::world;
Competidor** Mundo::competidores;
int Mundo::qtdCompetidores;
struct timespec Mundo::inicioCorrida;

void Mundo::create() {
	Mundo::ptm_ratio = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mike01.png")->getOriginalSize().width/1.92;
	b2Vec2 gravity = b2Vec2(0.0f,0.0f);
	Mundo::world = new b2World(gravity);
	Mundo::world->SetContactListener(new ColisionListener());
	Mundo::race = false;
}

void Mundo::loadGame(int pista,int* competidores,int qtdCompetidores,int idJogador,int dificuldade,int vitaminas) {
	Pista::create(pista);
	Mundo::dificuldade = dificuldade;
	Mundo::qtdCompetidores = qtdCompetidores;
	CCNode** compCorpo = new CCNode*[Mundo::qtdCompetidores];
	Mundo::competidores = new Competidor*[Mundo::qtdCompetidores];
	for(int i=0;i<Mundo::qtdCompetidores;i++) {
		Mundo::competidores[i] = new Competidor(competidores[i],Pista::getStartingPosition(i+1),Pista::getStartingOrientation(),i==idJogador?vitaminas:0);
		compCorpo[i] = Mundo::competidores[i]->getSprite();
		if(i==idJogador&&i!=0) {
			Competidor* aux1 = Mundo::competidores[0];
			CCNode* aux2 = compCorpo[0];
			Mundo::competidores[0] = Mundo::competidores[i];
			Mundo::competidores[i] = aux1;
			compCorpo[0] = compCorpo[i];
			compCorpo[i] = aux2;
			HUDLayer::atualizaPosicaoJogador(i+1);
		}
	}
	Pista::setSpriteGroup(compCorpo,Mundo::qtdCompetidores);
	GerenciadorCompetidores::create(Mundo::competidores,Mundo::qtdCompetidores);
	delete compCorpo;
}

void Mundo::startRace() {
#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	Mundo::inicioCorrida.tv_sec = mts.tv_sec;
	Mundo::inicioCorrida.tv_nsec = mts.tv_nsec;
#else
	clock_gettime(CLOCK_REALTIME_HR,&Mundo::inicioCorrida);
#endif

	//INICIA MUSICA DE CORRIDA
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sons/cups.mp3",true);

	for(int i=0;i<Mundo::qtdCompetidores;i++)
		Mundo::competidores[i]->startRace();
	Mundo::race = true;
}

void Mundo::update(float dt) {
	int i;
	if(Mundo::race) {
		Mundo::world->Step(dt,3,2);
		for(i=0;i<Mundo::qtdCompetidores;i++)
			Mundo::competidores[i]->update(dt);
		GerenciadorCompetidores::update();
		Mundo::calculaTempoCorrida();
	}
	Pista::update(dt);
}

void Mundo::calculaTempoCorrida() {
	if(Mundo::qtdCompetidores==1) {
		long cent;
		int seg,min;
		struct timespec tempoProcessadorAtual;
#ifdef __MACH__
		clock_serv_t cclock;
		mach_timespec_t mts;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
		clock_get_time(cclock, &mts);
		mach_port_deallocate(mach_task_self(), cclock);
		tempoProcessadorAtual.tv_sec = mts.tv_sec;
		tempoProcessadorAtual.tv_nsec = mts.tv_nsec;
#else
	clock_gettime(CLOCK_REALTIME_HR,&tempoProcessadorAtual);
#endif

	cent = tempoProcessadorAtual.tv_nsec;
	seg = tempoProcessadorAtual.tv_sec;
	if(tempoProcessadorAtual.tv_nsec<Mundo::inicioCorrida.tv_nsec) {
		cent += 1000000000l;
		seg -= 1;
	}
	cent -= Mundo::inicioCorrida.tv_nsec;
	cent /= 10000000l;
	seg -= Mundo::inicioCorrida.tv_sec;
	min = seg/60;
	seg %= 60;
	HUDLayer::atualizaTempoJogador(min,seg,cent);
	}
}

void Mundo::updateAccelerometer(float p) {
	Mundo::competidores[0]->updateAccelerometer(p);
}

void Mundo::disableAccelerometer() {
	Mundo::competidores[0]->dontTurn();
}

CCPoint Mundo::getCentralPoint() {
	return Mundo::competidores[0]->getSprite()->getPosition();
}

float Mundo::getPTMRatio() {
	return Mundo::ptm_ratio;
}

b2World* Mundo::getb2World() {
	return Mundo::world;
}

void Mundo::leftTurnPressed() {
	Mundo::competidores[0]->turnLeft();
}

void Mundo::leftTurnReleased() {
	Mundo::competidores[0]->dontTurn();
}

void Mundo::rightTurnPressed() {
	Mundo::competidores[0]->turnRight();
}

void Mundo::rightTurnReleased() {
	Mundo::competidores[0]->dontTurn();
}

void Mundo::release() {
	GerenciadorCompetidores::release();
	for(int i=Mundo::qtdCompetidores-1;i>=0;i--)
		delete Mundo::competidores[i];
	delete Mundo::competidores;
	Pista::release();
	delete Mundo::world;
}

Competidor** Mundo::getCompetidor() {
	return Mundo::competidores;
}

int Mundo::retornaQtdCompetidor() {
	return Mundo::qtdCompetidores;
}

int Mundo::getDificuldade() {
	return Mundo::dificuldade;
}