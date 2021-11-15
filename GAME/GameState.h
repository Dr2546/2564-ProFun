#pragma once
#include "allheader.h"
#include "State.h"
#include "Gameoverstate.h"
#include "Gui.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

class GameState : public State
{
private:

	//File
	fstream scoreboard;
	bool isSave = false;

	//Player
	string name;
	Player* player;
	int score;
	bool dead = true;
	string buff;

	//PlayerGUI
	RectangleShape hpbar;
	RectangleShape hpbarback;

	//Enemy 
	vector<Enemy*> enemies;
	float spawnTime;
	float spawnTimeMax;

	//Item
	vector<Item*> items;
	float itemspawnTime;
	float itemspawnTimeMax;
	float itemduration;
	float itemdurationMax;

	//GUI
	Font font;
	Text scoretext;
	Text gameovertext;
	gui::Button* returntomenu;

	//PauseMenu
	RectangleShape container;
	Text ptext;
	gui::Button* resume;
	gui::Button* quit;

	//Function
	void initGUI();
	void resetGUI();
	void initPlayer();
	void initEnemy();
	void initItem();
	void initPausemenu();
public:
	GameState(StateData* statedata,string name);
	virtual ~GameState();

	//Function
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);

	//Additional Function
	void updatePollevent();
	void updateMovement();
	void updateEnemy(const float& dt);
	void updateButton();
	void updateGUI();
	void updateFile();
	void updateItem();
	void updateBuff();
	void updatePausemenu();
	void renderGUI();
	void renderPausemenu();
};



