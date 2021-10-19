#include "MenuState.h"

MenuState::MenuState(StateData* state_data) : State(state_data)
{
}

MenuState::~MenuState()
{
}

void MenuState::updateState()
{
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		this->states->push(new GameState(this->stateData));
	}
}

void MenuState::updateInput(const float& dt)
{
}

void MenuState::update(const float& dt)
{
	this->updateState();
}

void MenuState::render(RenderTarget* target)
{
}

