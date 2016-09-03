///////////////// Jocelyn Cruz /////////////////
#ifndef __SERVER_CONNECTION__
#define __SERVER_CONNECTION__

#include "cocos2d.h"
#include <cstdlib>
#include "HowToPlay.h"

USING_NS_CC;

class ServerConnection : public cocos2d::Layer
{
private:
	Sprite* Directions;
	CCTMXTiledMap* serverScreen;

	cocos2d::MenuItemImage* enter_button;
	EventListenerJoystick* joyListener;
	EventListenerKeyboard* keyListener;

	bool button1 = false;

public:
	static cocos2d::Scene* createServerConnection(char chosencharacters);

	static cocos2d::Scene* createServerConnection(std::string ipa, char chosencharacters); 

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref * pSender);
	void beginGame(cocos2d::Ref* sSender);

	void player1(cocos2d::Ref* sSender);
	void player2(cocos2d::Ref* sSender);
	void player3(cocos2d::Ref* sSender);
	void player4(cocos2d::Ref* sSender);

	bool aPlayerChosen = false;
	int playerNum = 1;

	void KeyDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(ServerConnection);

};


#endif // __SERVER_CONNECTION__
