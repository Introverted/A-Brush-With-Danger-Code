#include "ServerConnection.h" ///////////////// Jocelyn Cruz /////////////////

std::string IPAddress = ""; ///////////////// Jocelyn Cruz /////////////////
char pickedchars = 0; ///////////////// Jocelyn Cruz /////////////////


Scene* ServerConnection::createServerConnection(std::string ipa, char chosencharacters) ///////////////// Jocelyn Cruz /////////////////
{
	IPAddress = ipa;
	pickedchars = chosencharacters; // DID NOT DO THIS
	auto SCScene = Scene::create();
	auto SClayer = ServerConnection::create();

	SCScene->addChild(SClayer);

	return SCScene;
}

bool ServerConnection::init() 
{
	///////////////// Jocelyn Cruz /////////////////
	if (!Layer::init())
	{
		return false;
	}

	///////////////// Jocelyn Cruz /////////////////
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(ServerConnection::KeyDown, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);
	
	// DID NOT DO ANY OF THE P3MASK AND PICKED CHAR CODE
	char p1mask = 1;
	char p2mask = 2;
	char p3mask = 4;
	char p4mask = 8;
	char p1there = p1mask & pickedchars;
	char p2there = p2mask & pickedchars;
	char p3there = p3mask & pickedchars;
	char p4there = p4mask & pickedchars;

	///////////////// Jocelyn Cruz /////////////////
	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	///////////////// Jocelyn Cruz /////////////////
	enter_button = MenuItemImage::create("res//sprites//ui//EnterNP.png", "res//sprites//ui//EnterP.png", CC_CALLBACK_1(ServerConnection::beginGame, this));
	enter_button->setPosition(Vec2(winSizeWidth, winSizeHeight-120));
	enter_button->setScale(0.5f);

	///////////////// Jocelyn Cruz /////////////////
	auto p1_button = MenuItemImage::create("res//sprites//ui//p1NP.png", "res//sprites//ui//p1P.png", CC_CALLBACK_1(ServerConnection::player1, this));
	p1_button->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 20));
	p1_button->setScale(0.3f);

	///////////////// Jocelyn Cruz /////////////////
	//these button2s are so players can select the labels too.
	//selected image is the same as normal image for now, need selected version
	auto p1_button2 = MenuItemImage::create("res//sprites//ui//p1Label.png", "res//sprites//ui//p1Label.png", CC_CALLBACK_1(ServerConnection::player1, this));
	p1_button2->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 95));
	p1_button2->setScale(0.4f);

	///////////////// Jocelyn Cruz /////////////////
	auto p2_button = MenuItemImage::create("res//sprites//ui//p2NP.png", "res//sprites//ui//p2P.png", CC_CALLBACK_1(ServerConnection::player2, this));
	p2_button->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 20));
	p2_button->setScale(0.3f);

	///////////////// Jocelyn Cruz /////////////////
	auto p2_button2 = MenuItemImage::create("res//sprites//ui//p2Label.png", "res//sprites//ui//p2Label.png", CC_CALLBACK_1(ServerConnection::player2, this));
	p2_button2->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 95));
	p2_button2->setScale(0.4f);

	///////////////// Jocelyn Cruz /////////////////
	auto p3_button = MenuItemImage::create("res//sprites//ui//p3NP.png", "res//sprites//ui//p3P.png", CC_CALLBACK_1(ServerConnection::player3, this));
	p3_button->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 20));
	p3_button->setScale(0.3f);

	///////////////// Jocelyn Cruz /////////////////
	auto p3_button2 = MenuItemImage::create("res//sprites//ui//p3Label.png", "res//sprites//ui//p3Label.png", CC_CALLBACK_1(ServerConnection::player3, this));
	p3_button2->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 95));
	p3_button2->setScale(0.4f);

	///////////////// Jocelyn Cruz /////////////////
	auto p4_button = MenuItemImage::create("res//sprites//ui//p4NP.png", "res//sprites//ui//p4P.png", CC_CALLBACK_1(ServerConnection::player4, this));
	p4_button->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 20));
	p4_button->setScale(0.3f);

	///////////////// Jocelyn Cruz /////////////////
	auto p4_button2 = MenuItemImage::create("res//sprites//ui//p4Label.png", "res//sprites//ui//p4Label.png", CC_CALLBACK_1(ServerConnection::player4, this));
	p4_button2->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 95));
	p4_button2->setScale(0.4f);

	///////////////// Jocelyn Cruz /////////////////
	auto layer = Menu::create(enter_button, p1_button, p1_button2, p2_button, p2_button2, p3_button, p3_button2, p4_button, p4_button2, NULL);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 1);

	///////////////// Jocelyn Cruz /////////////////
	std::string file = "res//maps//server_connection.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	serverScreen = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	this->addChild(serverScreen, 0);

	///////////////// Jocelyn Cruz /////////////////
	Directions = Sprite::create("res//sprites//ui//choosePlayerDirections.png");
	Directions->setScale(0.25f);
	Directions->setPosition(Vec2((int)winSizeWidth - 10, (int)winSizeHeight + 120));
	this->addChild(Directions, 0);

	return true;
}


void ServerConnection::beginGame(cocos2d::Ref* pSender) ///////////////// Jocelyn Cruz /////////////////
{
	if (aPlayerChosen == true)
	{
		_eventDispatcher->removeEventListener(keyListener);
		//keyListener->release();
		//keyListener = nullptr;

		auto scene = HowToPlay::createHowToPlay(IPAddress, playerNum); 
		CCDirector::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	}
}

void ServerConnection::player1(cocos2d::Ref* sSender) ///////////////// Jocelyn Cruz /////////////////
{
	//this if block deals with de-selecting previously 
	//selected player
	if (aPlayerChosen == true)
	{
		if (playerNum == 2)
		{
			p2Chara->setOpacity(0);
		}
		else if (playerNum == 3)
		{
			p3Chara->setOpacity(0);
		}
		else if (playerNum == 4)
		{
			p4Chara->setOpacity(0);
		}
	}
	p1Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 1;
}

void ServerConnection::player2(cocos2d::Ref* sSender) ///////////////// Jocelyn Cruz /////////////////
{
	if (aPlayerChosen == true)
	{
		if (playerNum == 1)
		{
			p1Chara->setOpacity(0);
		}
		else if (playerNum == 3)
		{
			p3Chara->setOpacity(0);
		}
		else if (playerNum == 4)
		{
			p4Chara->setOpacity(0);
		}
	}
	p2Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 2;
}

void ServerConnection::player3(cocos2d::Ref* sSender) ///////////////// Jocelyn Cruz /////////////////
{
	if (aPlayerChosen == true)
	{
		if (playerNum == 1)
		{
			p1Chara->setOpacity(0);
		}
		else if (playerNum == 2)
		{
			p2Chara->setOpacity(0);
		}
		else if (playerNum == 4)
		{
			p4Chara->setOpacity(0);
		}
	}
	p3Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 3;
}

void ServerConnection::player4(cocos2d::Ref* sSender) ///////////////// Jocelyn Cruz /////////////////
{
	if (aPlayerChosen == true)
	{
		if (playerNum == 1)
		{
			p1Chara->setOpacity(0);
		}
		else if (playerNum == 2)
		{
			p2Chara->setOpacity(0);
		}
		else if (playerNum == 3)
		{
			p3Chara->setOpacity(0);
		}
	}
	p4Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 4;
}

void ServerConnection::menuCloseCallback(Ref* pSender) ///////////////// Jocelyn Cruz /////////////////
{

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void ServerConnection::KeyDown(EventKeyboard::KeyCode keyCode, Event* event) ///////////////// Jocelyn Cruz /////////////////
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_1:
		Director::getInstance()->getOpenGLView()->setFrameZoomFactor(1.0f);
		break;
	case EventKeyboard::KeyCode::KEY_2:
		Director::getInstance()->getOpenGLView()->setFrameZoomFactor(2.0f);
		break;
	case EventKeyboard::KeyCode::KEY_3:
		Director::getInstance()->getOpenGLView()->setFrameZoomFactor(3.0f);
		break;
	}
	event->stopPropagation();
}
