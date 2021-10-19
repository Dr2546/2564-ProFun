#include "GameState.h"

/*void GameState::initVar()
{
}*/

GameState::GameState(StateData* statedata) : State(statedata)
{
}

GameState::~GameState()
{
}

void GameState::updateInput(const float& dt)
{
}

void GameState::update(const float& dt)
{
	this->gameengine.update();
}

void GameState::render(RenderTarget* target)
{
	this->gameengine.render();
}
