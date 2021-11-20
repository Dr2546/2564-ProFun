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

	//Background 
	RectangleShape con1;
	RectangleShape con2;
	Text gamename;
	Text student;

	Sprite sprite;
	Texture sheet;
	Sprite spritebg;
	Texture txtbg;

	void initVar();
	void initSprite();
	void initTexture();
	void initGUI();
	void initBg();
	void initFont();
	void initAnimation();
	void resetGUI();

protected:
	Animation* animation;

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
	void renderBg(RenderTarget& target);
	void render(RenderTarget* target = NULL);
	void playAnimation(const float& dt);
};

