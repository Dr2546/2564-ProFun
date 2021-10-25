#pragma once
#include "allheader.h"
#include "Player.h"

class Player;
class State;

class StateData
{
public:
	StateData() {};

	//Variable
	float gridsize;
	RenderWindow* window;
	stack<State*>* states;
};

class State
{
protected:
	StateData* stateData;
	stack<State*>* states;
	RenderWindow* window;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;

	//Resources
	map<string, Texture> textures;

	//Functions
	

public:
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions	
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};