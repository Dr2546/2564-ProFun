#pragma once
#include "allheader.h"
#include "MenuState.h"

class mygameengine
{
private:
	StateData statedata;
	RenderWindow* window;
	Event ev;

	Clock dtClock;
	float dt;

	stack<State*> states;

	float gridsize;

	void initVariables();
	void initWindow();
	void initStateData();
	void initStates();

public:
	mygameengine();
	virtual ~mygameengine();

	//Update function
	void updateDt();
	void updateSFMLEvent();
	void update();

	//Render
	void render();

	//Core
	void run();
};

