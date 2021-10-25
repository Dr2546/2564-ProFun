#pragma once
#include "allheader.h"
#include "Gui.h"
#include "State.h"

class Gameoverstate : public State
{
private:

	Text gameovertext;
	gui::Button* returntomenu;
	Font font;

	void initGui();
	void initFont();
	void resetGui();

public:
	Gameoverstate(StateData* statedata);
	virtual ~Gameoverstate();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
	void renderButton(RenderTarget& target);
};

