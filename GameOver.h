///////////////// Jocelyn Cruz /////////////////
#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer
{
private:
	Sprite* gameover;
	TMXTiledMap* titleScreen;
	MenuItemImage* menu_item;

	bool button1 = false;

public:
	static cocos2d::Scene* createGameOver();
	virtual bool init();
	void menuCloseCallback(Ref * pSender);
	void goToMainMenu(Ref* pSender);

	CREATE_FUNC(GameOver);

};


#endif // __GAME_OVER_H__
