#pragma once
#include "allheader.h"
#include "Gui.h"
#include "State.h"
class Leaderboard : public State
{
private:
	//File
	ifstream scoreboard;
	map<string, int> score;

	//Gui
	Text board;
	Font font;
	RectangleShape line1;
	RectangleShape line2;

	//Button
	map<string, gui::Button*> buttons;

	void initScoreboard();
	void initGUI();
	void initFont();
	void initButtons();
	void resetButtons();

public:
	Leaderboard(StateData* statedata);
	virtual ~Leaderboard();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);

	void updateButtons();
	void renderGUI();
	void renderButtons();
};

