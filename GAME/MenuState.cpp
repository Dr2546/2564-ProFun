#include "MenuState.h"

void MenuState::initGUI()
{
	//Button
	this->buttons["GAME_STATE"] = new gui::Button(100.f, 100.f, 100.f, 100.f, &this->font, "Start", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
	this->buttons["EXIT"] = new gui::Button(100.f, 500.f, 100.f, 100.f, &this->font, "Exit", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
	this->buttons["LEADERBOARD"] = new gui::Button(100.f, 300.f, 100.f, 100.f, &this->font, "Leaderboard", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);

	//Textbox
	this->textboxes["TESTBOX"] = new gui::Textbox(100.f, 800.f, 500.f, 50.f, 30, 40, &this->font, false);

}

void MenuState::initFont()
{
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";
}

void MenuState::resetGUI()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto its = this->textboxes.begin();
	for (its = this->textboxes.begin(); its != this->textboxes.end(); ++its)
	{
		delete its->second;
	}
	this->textboxes.clear();

	this->initGUI();
}

MenuState::MenuState(StateData* state_data) : State(state_data)
{
	this->initFont();
	this->initGUI();
	this->resetGUI();
}

MenuState::~MenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto its = this->textboxes.begin();
	for (its = this->textboxes.begin(); its != this->textboxes.end(); ++its)
	{
		delete its->second;
	}
}

void MenuState::updateState()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosWindow);

	if (this->buttons["GAME_STATE"]->isPress() && this->textboxes["TESTBOX"]->getText() != "")
	{
		this->name = this->textboxes["TESTBOX"]->getText();
		this->states->push(new GameState(this->stateData,this->name));
		auto its = this->textboxes.begin();
		for (its = this->textboxes.begin(); its != this->textboxes.end(); ++its)
		{
			its->second->clearbox();
		}
	}

	if (this->buttons["LEADERBOARD"]->isPress())
	{
		this->states->push(new Leaderboard(this->stateData));
		auto its = this->textboxes.begin();
		for (its = this->textboxes.begin(); its != this->textboxes.end(); ++its)
		{
			its->second->clearbox();
		}
	}

	if (this->buttons["EXIT"]->isPress())
	{
		this->endState();
	}
}

void MenuState::updateTextbox()
{
	Event ev;

	for (auto& its : this->textboxes)
	{
		its.second->update(this->mousePosWindow);
		if (its.second->isSelected())
		{
			while (this->window->pollEvent(ev))
			{
				if (ev.type == Event::TextEntered)
				{
					its.second->type(ev);
				}
			}
		}
	}
}

void MenuState::updateInput(const float& dt)
{
}

void MenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateState();
	this->updateTextbox();
}

void MenuState::renderButton(RenderTarget& target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void MenuState::renderTextbox(RenderTarget& target)
{
	for (auto& it : this->textboxes)
	{
		it.second->render(target);
	}
}

void MenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButton(*target);
	this->renderTextbox(*target);
}

