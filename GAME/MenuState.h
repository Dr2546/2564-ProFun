#pragma once
#include "GameState.h"
#include "Leaderboard.h"
#include "Gui.h"

class MenuState : public State
{
private:

	Font font;
	string name;

	//GUI
	map<string, gui::Button*> buttons;
	map<string, gui::Textbox*> textboxes;

	void initGUI();
	void initFont();
	void resetGUI();

public:

	MenuState(StateData* state_data);
	virtual ~MenuState();

	//Function
	void updateState();
	void updateTextbox();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButton(RenderTarget& target);
	void renderTextbox(RenderTarget& target);
	void render(RenderTarget* target = NULL);
};

