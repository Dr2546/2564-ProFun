#pragma once
#include "allheader.h"
#include "State.h"
#include "Gameengine.h"

class GameState : public State
{
private:
	Gameengine gameengine;

	//Function
	//void initVar();
public:
	GameState(StateData* statedata);
	virtual ~GameState();

	//Function
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};



