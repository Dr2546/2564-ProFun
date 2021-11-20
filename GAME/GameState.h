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
	int wave;

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
	RectangleShape gameoverbox;
	gui::Button* returntomenu;
	RectangleShape scorebox;

	//Background
	Sprite bgsprite;
	Texture bg1;
	Texture bg2;
	Texture bg3;
	Texture bg4;
	float playareaup, playareadown, playarealeft, playarearight;

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
	void initBackground();
public:
	GameState(StateData* statedata,string name);
	virtual ~GameState();

	//Function
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);

	//Additional Function
	void updatePollevent();
	void updateMovement(const float& dt);
	void updateEnemy(const float& dt);
	void updateButton();
	void updateGUI();
	void updateFile();
	void updateItem();
	void updateBuff();
	void updateWave();
	void updateRate();
	void updatePausemenu();
	void renderGUI();
	void renderPausemenu();
};



