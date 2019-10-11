#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Menu.h"
#include "debug/GLES-Render.h"

class Engine : public CCLayer {
private:
	static Engine* sharedEngine;
	static CCScene* sharedScene;

public:
	virtual bool init();
	static CCScene* scene();
	static Engine* getSharedEngine();
	static int getTamanhoTela();
	static void initMenu();
	static void changeToMenu();
	static void changeToGame(int pista,int* competidores,int qtdCompetidores,int idJogador,int dificuldade,int vitaminas);
	static void closeApp();
	CREATE_FUNC(Engine);
/*
	//Métodos e variaveis para debug
	GLESDebugDraw* debugDraw;
	void setupWorld();
	virtual void draw(void);
	void setupDebugDraw();
*/
};

#endif // __HELLOWORLD_SCENE_H__