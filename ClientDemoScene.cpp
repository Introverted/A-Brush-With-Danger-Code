#include "ClientDemoScene.h"

USING_NS_CC;
using boost::asio::ip::tcp;

int port = 10001; ///////////////// Jocelyn Cruz /////////////////
std::string ipaddress; ///////////////// Jocelyn Cruz /////////////////
int playerNumber; ///////////////// Jocelyn Cruz /////////////////


Scene* ClientDemo::createScene(std::string ipA, int playerNum) ///////////////// Jocelyn Cruz /////////////////
{
	ipaddress = ipA;
	playerNumber = playerNum;

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ClientDemo::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}





// on "init" you need to initialize your instance
bool ClientDemo::init()
{

	///////////////// Jocelyn Cruz /////////////////
	player1 = Player::create(1);
	addChild(player1, 0);
	player2 = Player::create(2);
	addChild(player2, 0);
	player3 = Player::create(3);
	addChild(player3, 0);
	player4 = Player::create(4);
	addChild(player4, 0);
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);


	tileHighlight = Sprite::create("res//sprites//select_tile.png"); ///////////////// Jocelyn Cruz /////////////////
	if (nullptr != tileHighlight) ///////////////// Jocelyn Cruz /////////////////
	{
		tileHighlight->setPosition(0, 0);
		tileHighlight->getTexture()->setAliasTexParameters();
		addChild(tileHighlight, -900);
	}
	

	//create Game Menu
	gameMenuLayer = GameMenu::createGameMenu(); ///////////////// Jocelyn Cruz /////////////////

	// Add the game menu to the screen 
	addChild(gameMenuLayer, 1000); ///////////////// Jocelyn Cruz /////////////////

	// Center the menu on the screen
	winSizeWidth = Director::getInstance()->getWinSize().width / 2; ///////////////// Jocelyn Cruz /////////////////
	winSizeHeight = Director::getInstance()->getWinSize().height / 2; ///////////////// Jocelyn Cruz /////////////////

	// Allows for the use of the keyboard keys
	auto keyListener = EventListenerKeyboard::create(); ///////////////// Jocelyn Cruz /////////////////
	keyListener->onKeyPressed = CC_CALLBACK_2(ClientDemo::KeyDown, this); ///////////////// Jocelyn Cruz /////////////////
	keyListener->onKeyReleased = CC_CALLBACK_2(ClientDemo::KeyRelease, this); ///////////////// Jocelyn Cruz /////////////////
	
	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);

	this->scheduleUpdate();

	return true;
}


void ClientDemo::update(float dt)
{

		// Have the tilehighlight be invisible until player walks over grid
		tileHighlight->setOpacity(0); ///////////////// Jocelyn Cruz /////////////////

		// Loop through each tile on the grid and compare it to the players position. 
		for (unsigned int i = 0; i < SPRITE_GRID.size(); i++) ///////////////// Jocelyn Cruz /////////////////
		{
			for (unsigned int j = 0; j < SPRITE_GRID[i].size(); j++)
			{
				// If the player is on the same position as the tile on the grid then have the tighlight be 
				// visible to indicate which tile the player is on
				if (players[playernum - 1]->getPositionX() > SPRITE_GRID[i][j]->getPositionX() - 12
					&& players[playernum - 1]->getPositionX() < SPRITE_GRID[i][j]->getPositionX() + 12
					&& players[playernum - 1]->getPositionY() > SPRITE_GRID[i][j]->getPositionY() - 12
					&& players[playernum - 1]->getPositionY() < SPRITE_GRID[i][j]->getPositionY() + 12)
				{
					tileHighlight->setOpacity(255);
					tileHighlight->setPosition(SPRITE_GRID[i][j]->getPositionX(), SPRITE_GRID[i][j]->getPositionY());
					gSound.pTrigs[playernum - 1].onGrid = true;
				}
			}
		}
	}


		//check if transition is over, timer begins at 9
		if (NotInTransition == false && transitionManager.timer_status())  ///////////////// Jocelyn Cruz /////////////////
		{
			NotInTransition = true;

			for (Sprite* ts : transitionManager.transitionSprite)
			{
				removeChild(ts);
			}
			villain->runAction(FadeIn::create(1.0f));
		}
}


// Will update the tiles on the grid with colors that have been put down by players 
void ClientDemo::updateTilesFromPacket(ServerPositionPacket p) ///////////////// Jocelyn Cruz /////////////////
{

	for (unsigned int i = 0; i < p.tilevector.size(); i++)
	{
		for (unsigned int j = 0; j < p.tilevector[i].size(); j++)
		{
			if (CURRENT_GRID[i][j] != p.tilevector[i][j])
			{
				CURRENT_GRID[i][j] = p.tilevector[i][j];
				if (CURRENT_GRID[i][j] == 1)
				{
					SPRITE_GRID[i][j]->setColor("clear");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 2)
				{
					SPRITE_GRID[i][j]->setColor("red");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 3)
				{
					SPRITE_GRID[i][j]->setColor("blue");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 4)
				{
					SPRITE_GRID[i][j]->setColor("yellow");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 5)
				{
					SPRITE_GRID[i][j]->setColor("orange");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 6)
				{
					SPRITE_GRID[i][j]->setColor("black");
					SPRITE_GRID[i][j]->refreshColor();
				}

				else if (CURRENT_GRID[i][j] == 7)
				{
					SPRITE_GRID[i][j]->setColor("blue2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 8)
				{
					SPRITE_GRID[i][j]->setColor("blue3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 9)
				{
					SPRITE_GRID[i][j]->setColor("green1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 10)
				{
					SPRITE_GRID[i][j]->setColor("green2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 11)
				{
					SPRITE_GRID[i][j]->setColor("green3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 12)
				{
					SPRITE_GRID[i][j]->setColor("white");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 13)
				{
					SPRITE_GRID[i][j]->setColor("grey1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 14)
				{
					SPRITE_GRID[i][j]->setColor("grey2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 15)
				{
					SPRITE_GRID[i][j]->setColor("red2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 16)
				{
					SPRITE_GRID[i][j]->setColor("purple1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 17)
				{
					SPRITE_GRID[i][j]->setColor("red1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 20)
				{
					SPRITE_GRID[i][j]->setColor("Xred1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 30)
				{
					SPRITE_GRID[i][j]->setColor("Xblue");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 40)
				{
					SPRITE_GRID[i][j]->setColor("Xyellow");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 50)
				{
					SPRITE_GRID[i][j]->setColor("Xorange");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 60)
				{
					SPRITE_GRID[i][j]->setColor("Xblack");
					SPRITE_GRID[i][j]->refreshColor();
				}

				else if (CURRENT_GRID[i][j] == 70)
				{
					SPRITE_GRID[i][j]->setColor("Xblue2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 71)
				{
					SPRITE_GRID[i][j]->setColor("Xblue3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 72)
				{
					SPRITE_GRID[i][j]->setColor("Xgreen1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 73)
				{
					SPRITE_GRID[i][j]->setColor("Xgreen2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 74)
				{
					SPRITE_GRID[i][j]->setColor("Xgreen3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 75)
				{
					SPRITE_GRID[i][j]->setColor("Xwhite");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 76)
				{
					SPRITE_GRID[i][j]->setColor("Xgrey1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 77)
				{
					SPRITE_GRID[i][j]->setColor("Xgrey2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 78)
				{
					SPRITE_GRID[i][j]->setColor("Xred2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 79)
				{
					SPRITE_GRID[i][j]->setColor("Xpurple1");
					SPRITE_GRID[i][j]->refreshColor();
				}
			}
		}
	}

}

void ClientDemo::processServerMessage(ServerMessage msg)
{
	/*character messagechar, float xpos, float ypos, char status
	0. Assign Player Number, unused, unused, new player number
	1. Player 1 pos, xpos, ypos, animation #
	2. Player 2 pos, xpos, ypos, animation #
	3. Player 3 pos, xpos, ypos, animation #
	4. Player 4 pos, xpos, ypos, animation #
	5. Sam pos, xpos, ypos, animation #
	6. Ptera pos, xpos, ypos, animmation #
	7. Candy spawned, xpos, ypos, unused
	8. Got candy, unused, unused, player #
	9. Candy wore off, unused, unused, player #
	10. Change Level, unused, unused, new level #
	11. Drop Player, unused, unused, player #
	12. Player Joined, unused, unused, player #
	13. Sam hit player, unused, unused, player #
	14. Ptero hit player, unused, unused, player #
	15. Go to win game, unused, unused, unused	
	16. Player got bucket, player number, unused, color #
	17. Player already taken, unused, unused, player #
	18. Puzzle completed, unused, unused, unused
	19. Event change, event #, phase #, event status
	*/

	// This will change the colors of the labels of the characters indicating what colors they are currently holding
	else if (msg.messagechar == 16) ///////////////// Jocelyn Cruz /////////////////
	{
		auto labelcolor(Color3B(255, 255, 255));
		switch (msg.status)
		{
		case 2: // red
			labelcolor = Color3B(247, 52, 47);
			break;
		case 3: // blue
			labelcolor = Color3B(49, 58, 197);
			break;
		case 4: // yellow 
			labelcolor = Color3B(236, 250, 85);
			break;
		case 5: // orange
			labelcolor = Color3B(234, 152, 26);
			break;
		case 6: // black
			labelcolor = Color3B(36, 33, 25);
			break;
		case 7: 
			labelcolor = Color3B(4, 31, 131);
			break;
		case 8: 
			labelcolor = Color3B(1, 16, 73);
			break;
		case 9: 
			labelcolor = Color3B(2, 123, 36);
			break;
		case 10: 
			labelcolor = Color3B(11, 187, 60);
			break;
		case 11: 
			labelcolor = Color3B(47, 247, 145);
			break;
		case 12: 
			labelcolor = Color3B(255, 255, 255);
			break;
		case 13: 
			labelcolor = Color3B(101, 141, 186);
			break;
		case 14: 
			labelcolor = Color3B(203, 216, 229);
			break;
		case 15: // red2
			labelcolor = Color3B(187, 11, 44);
			break;
		case 16:  // purple1
			labelcolor = Color3B(148, 55, 122);
			break;
		case 17: 
			labelcolor = Color3B(247, 52, 47);
			break;


		}
		// These will change the appropriate characters label color
		if (msg.xpos == 1) ///////////////// Jocelyn Cruz /////////////////
		{
			//player1->getLabel()->setFontFillColor(labelcolor);
			player1->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}
		if (msg.xpos == 2) ///////////////// Jocelyn Cruz /////////////////
		{
			//player2->getLabel()->setFontFillColor(labelcolor);
			player2->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}
		if (msg.xpos == 3) ///////////////// Jocelyn Cruz /////////////////
		{
			//player3->getLabel()->setFontFillColor(labelcolor);
			player3->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}
		if (msg.xpos == 4) ///////////////// Jocelyn Cruz /////////////////
		{
			//player4->getLabel()->setFontFillColor(labelcolor);
			player4->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}

	}
}


// Moves the character depending on which key is pressed
void ClientDemo::KeyDown(EventKeyboard::KeyCode keyCode, Event* event) ///////////////// Jocelyn Cruz /////////////////
{

	
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			ymove += 2;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			ymove -= 2;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			xmove -= 2;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			xmove += 2;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			ymove += 2;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			xmove -= 2;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			xmove += 2;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			button1 = true;
			//space(); - handled server-side now
			break;
		case EventKeyboard::KeyCode::KEY_CTRL:
			button2 = true;
			break;

		}
	
	event->stopPropagation();
}

// Will do nothing when a key is released 
void ClientDemo::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event) ///////////////// Jocelyn Cruz /////////////////
{

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (!button2)
			ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		button1 = false;
		break;
	case EventKeyboard::KeyCode::KEY_CTRL:
		button2 = false;
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		if (isPaused == false)
		{
			PauseGame();
		}
		else
		{
			ResumeGame();
		}
		break;
	}

	event->stopPropagation();

}


// This will convert the players coordinates into tile coordinates
Point ClientDemo::plyrCoordToTileCoord(int playerNum) ///////////////// Jocelyn Cruz /////////////////
{
	int newx = players[playerNum - 1]->getPositionX() + xmove;
	int newy = (levelmanager.levelmap->getMapSize().height*levelmanager.levelmap->getTileSize().height) - (players[playerNum - 1]->getPositionY() + ymove);
  	int tilex = newx / (levelmanager.levelmap->getTileSize().width);
	int tiley = newy / (levelmanager.levelmap->getTileSize().height);
	return(Point(tilex,tiley));
}

// Will get the tile ID to be used 
int ClientDemo::getTileProperties(TMXLayer* mapLayer, Point tileCoord) ///////////////// Jocelyn Cruz /////////////////
{
	if (tileCoord.x >= 0 && tileCoord.x <= levelmanager.levelmap->getMapSize().width && tileCoord.y >= 0 && tileCoord.y <= levelmanager.levelmap->getMapSize().height)
	{
		return (mapLayer->getTileGIDAt(tileCoord));
	}
}


void ClientDemo::loadLevel(int level)
{

	//if not in transition and centercamera() has been called before (not new game, not player joining game in progress)
	if (transitionManager.start_timer == 60) ///////////////// Jocelyn Cruz ///////////////// 
	{
		NotInTransition = false;

		transitionManager.loadTransition(level);
		for (Sprite* ts : transitionManager.transitionSprite)
		{
			addChild(ts, 10);
		}
	}

	// Load the new level
	levelmanager.setLevel(level); ///////////////// Jocelyn Cruz ///////////////// 

	// Add the level to the map
	addChild(levelmanager.levelmap, -1000); ///////////////// Jocelyn Cruz ///////////////// 

	// Make the collision blocks invisible so that you can't see them
	blockage = levelmanager.levelmap->getLayer("Collision"); ///////////////// Jocelyn Cruz ///////////////// 
	if (blockage != NULL)
	{
		blockage->setVisible(false);
	}
	
	// Get bucket layer from the tiled map
	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets"); ///////////////// Jocelyn Cruz ///////////////// 

}




