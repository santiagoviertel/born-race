#define COCOS2D_DEBUG 1

#include "cocos2d.h"

USING_NS_CC;

class SpriteSource {

public:
	static void create();
	static void release();
	static void addChild(CCSprite* camada,int zOrder);
	static void removeChild(CCSprite* camada);
	static CCNode* getSpriteList();

private:
	static CCSpriteBatchNode* spriteList;
};