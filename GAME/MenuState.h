#pragma once
#include "GameState.h"

class MenuState : public State
{
public:
	MenuState(StateData* state_data);
	virtual ~MenuState();

	//Function
	void updateState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

