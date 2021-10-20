#pragma once
#include "allheader.h"
#include "State.h"
//#include "Gameengine.h"
#include "Player.h"
#include "Enemy.h"

class GameState : public State
{
private:

	//Player
	Player* player;
	int score;

	//PlayerGUI
	RectangleShape hpbar;
	RectangleShape hpbarback;

	//Enemy 
	vector<Enemy*> enemies;
	float spawnTime;
	float spawnTimeMax;

	//GUI
	Font font;
	Text gameovertext;
	Text scoretext;


	//Function
	void initGUI();
	void initPlayer();
	void initEnemy();
public:
	GameState(StateData* statedata);
	virtual ~GameState();

	//Function
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);

	//Additional Function
	void updatePollevent();
	void updateMovement();
	void updateEnemy();
	void updateGUI();
	void renderGUI();
};



