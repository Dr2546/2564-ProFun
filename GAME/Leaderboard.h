#pragma once
#include "allheader.h"
#include "Gui.h"
#include "State.h"
class Leaderboard : public State
{
private:
	//File
	fstream scoreboard;
	vector<pair<string,int>> score;

	//Gui
	Text board;
	Font font;
	RectangleShape line1;
	RectangleShape line2;
	RectangleShape line3;
	vector<Text> players;
	vector<Text> player_score;
	RectangleShape con1;
	RectangleShape con2;
	Text gamename;
	Text student;
	RectangleShape leaderbox;

	Sprite spritebg;
	Texture txtbg;

	//Button
	map<string, gui::Button*> buttons;

	void initScoreboard();
	void initSprite();
	void initTexture();
	void initGUI();
	void initFont();
	void initButtons();
	void resetButtons();
	void initScoreboardText();

	int get_rank(string input);
public:
	Leaderboard(StateData* statedata);
	virtual ~Leaderboard();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);

	void updateButtons();
	void renderGUI();
	void renderButtons();
	void renderScoreboardText();
};

