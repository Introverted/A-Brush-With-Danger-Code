///////////////// Jocelyn Cruz /////////////////
#ifndef __PLAYER_CONNECTION__
#define __PLAYER_CONNECTION__

#include "cocos2d.h"
#include <cstdlib>

#include "MenuScene.h"
#include "ClientDemoScene.h"
#include "ServerConnection.h"

USING_NS_CC;

class PlayerConnection : public cocos2d::Layer
{
private:
	Sprite* Directions;
	CCTMXTiledMap* playerScreen;
	cocos2d::MenuItemImage* begin_button;
	
	bool button1 = false;

public:
	static cocos2d::Scene* createPlayerConnection();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref * pSender);
	void beginGame(cocos2d::Ref* sSender);
	std::string IPAddress = "";
	CCLabelTTF* IPLabel;
	EventListenerKeyboard* keyboard;
	void KeyP(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyNP(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(PlayerConnection);

};


#endif // __PLAYER_CONNECTION__
