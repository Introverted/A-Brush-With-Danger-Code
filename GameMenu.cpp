///////////////// Jocelyn Cruz /////////////////
#include "GameMenu.h"

#define DEFAULT_OPACITY 220
#define SELECTED_OPACITY 255

GameMenu* GameMenu::createGameMenu()
{
	auto ptlayer = GameMenu::create();
	return ptlayer;
}


bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	float winSizeWidth = Director::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = Director::sharedDirector()->getWinSize().height / 2;

	background = Sprite::create("\\res\\sprites\\ui\\black_screen.png");
	background->getTexture()->setAliasTexParameters();
	background->setPosition(Vec2(winSizeWidth, winSizeHeight));
	background->setScale(1.5f);
	background->setOpacity(150);
	this->addChild(background, 1);

	menu = Menu::create(buttons[0], buttons[1], buttons[2], buttons[3], buttons[4], NULL);
	menu->alignItemsVerticallyWithPadding(5.0f);
	this->addChild(menu, 2);

	left_selector = Sprite::create("\\res\\sprites\\ui\\selection_arrow.png");
	left_selector->getTexture()->setAliasTexParameters();
	left_selector->setScale(0.5f);
	left_selector->setRotation(-180.0f);
	left_selector->setVisible(false);
	this->addChild(left_selector, 3);

	right_selector = Sprite::create("\\res\\sprites\\ui\\selection_arrow.png");
	right_selector->getTexture()->setAliasTexParameters();
	right_selector->setScale(0.5f);
	right_selector->setVisible(false);
	this->addChild(right_selector, 4);

	return true;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}



