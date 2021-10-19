#pragma once

#include "Player.h"
#include "Enemy.h"
//#include "GameState.h";

class Gameengine
{
private:
	RenderWindow* window;

	//Time
	Clock dtClock;
	float dt;

	//States
	//stack<State*> states;

	//GUI
	Font font;
	Text gameovertext;
	Text scoretext;

	//Player
	Player* player;
	int score;

	//PlayerGUI
	RectangleShape hpbar;
	RectangleShape hpbarback;

	//Enemy
	float spawnTimeMax;
	float spawnTime;
	vector<Enemy*> enemies;

	//Private Function
	void initWindow();
	//void initStates();
	void initGUI();
	void initPlayer();
	void initEnemy();

public:

	//Constructor && Destructor
	Gameengine();
	virtual ~Gameengine();

	//Function
	void run();

	//Update function
	void updatePollevent();
	void updateMovement();
	void updateEnemy();
	void updateGUI();
	void updatedt();

	//Render function
	void renderGUI();

	void update();
	void render();

};

