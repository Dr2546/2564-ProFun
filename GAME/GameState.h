#pragma once
#include "allheader.h"
#include "State.h"
#include "Gameoverstate.h"
#include "Gui.h"
#include "Player.h"
#include "Enemy.h"

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

	//PlayerGUI
	RectangleShape hpbar;
	RectangleShape hpbarback;

	//Enemy 
	vector<Enemy*> enemies;
	float spawnTime;
	float spawnTimeMax;

	//GUI
	Font font;
	Text scoretext;
	Text gameovertext;
	gui::Button* returntomenu;

	//Function
	void initGUI();
	void resetGUI();
	void initPlayer();
	void initEnemy();
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
	void updateEnemy();
	void updateButton();
	void updateGUI();
	void updateFile();
	void renderGUI();
};



