#include "Engine.h"
#include "Constantes.h"

/*
extern "C"
JNIEXPORT void JNICALL Java_com_ceugames_Born_Born_teste(JNIEnv *env,jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG,"Native Code","Teste");
}
 */

Engine* Engine::sharedEngine;
CCScene* Engine::sharedScene;

CCScene* Engine::scene() {
	Engine::sharedScene = CCScene::create();
	Engine::create();
	Engine::sharedScene->addChild(Engine::sharedEngine);
	Gameplay::create();
	Gameplay::getSharedGameplay()->retain();
	HUDLayer::create();
	HUDLayer::getSharedHUDLayer()->retain();
	Menu::create();
	Menu::getSharedMenu()->retain();

	Engine::initMenu();

	return Engine::sharedScene;
}

bool Engine::init() {
	if(!CCLayer::init())
		return false;
	Engine::sharedEngine = this;
	return true;
}

Engine* Engine::getSharedEngine() {
	return Engine::sharedEngine;
}

int Engine::getTamanhoTela() {
	if(CCDirector::sharedDirector()->getWinSize().height>=1080)
		return TELA_4;
	else if(CCDirector::sharedDirector()->getWinSize().height>=720)
		return TELA_3;
	else if(CCDirector::sharedDirector()->getWinSize().height>=480)
		return TELA_2;
	return TELA_1;
}

void Engine::initMenu() {
	Engine::sharedScene->addChild(Menu::getSharedMenu());
	Menu::getSharedMenu()->beginGame();
}

void Engine::changeToMenu() {
	Engine::sharedScene->removeChild(HUDLayer::getSharedHUDLayer());
	Engine::sharedEngine->removeChild(Gameplay::getSharedGameplay());
	Engine::sharedScene->addChild(Menu::getSharedMenu());
}

void Engine::changeToGame(int pista,int* competidores,int qtdCompetidores,int idJogador,int dificuldade,int vitaminas) {
	Engine::sharedScene->removeChild(Menu::getSharedMenu());
	Engine::sharedEngine->addChild(Gameplay::getSharedGameplay());
	Engine::sharedScene->addChild(HUDLayer::getSharedHUDLayer());
	HUDLayer::createCompetidores(qtdCompetidores);
	Gameplay::loadGame(pista,competidores,qtdCompetidores,idJogador,dificuldade,vitaminas);
	Gameplay::beginGame();
}

/*
bool Engine::init() {
	if(!CCLayer::init())
		return false;
	SpriteSource::create();
	Mundo::create(static_cast<CCNode*>(this));
	Engine::setupDebugDraw();
	Mundo::startRace();
	schedule(schedule_selector(Engine::update));
	return true;
}

void Engine::draw(void) {
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	Mundo::getb2World()->DrawDebugData();
	kmGLPopMatrix();
}

void Engine::setupDebugDraw() {
	Engine::debugDraw = new b2DebugDraw(PTM_RATIO);
	Mundo::getb2World()->SetDebugDraw(Engine::debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_centerOfMassBit;
	//flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	Engine::debugDraw->SetFlags(flags);
}
 */
void Engine::closeApp() {
	/*	delete Engine::debugDraw;
	Mundo::release();
	Menu::getSharedMenu()->release();
	Gameplay::getSharedGameplay()->release();
	 */	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	 exit(0);
#endif
}