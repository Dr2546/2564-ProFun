#include "MenuState.h"

void MenuState::initVar()
{
	this->animation = NULL;
}

void MenuState::initSprite()
{
	this->sprite.setTexture(this->sheet);
	this->sprite.scale(5.f, 5.f);

	this->sprite.setPosition(this->window->getSize().x / 4.f + 100.f, 300.f);
}

void MenuState::initTexture()
{
	if (!this->sheet.loadFromFile("Resources/Player/player.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void MenuState::initGUI()
{
	//Button
	this->buttons["GAME_STATE"] = new gui::Button(this->window->getSize().x / 2.f + 150.f, 300.f, 
		300.f, 50.f, &this->font, "Start", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50)
	);
	this->buttons["EXIT"] = new gui::Button(this->window->getSize().x / 2.f + 150.f, 700.f,
		300.f, 50.f, &this->font, "Exit", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50)
	);
	this->buttons["LEADERBOARD"] = new gui::Button(this->window->getSize().x / 2.f + 150.f, 500.f,
		300.f, 50.f, &this->font, "Leaderboard", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50)
	);

	//Textbox
	this->textboxes["TESTBOX"] = new gui::Textbox(this->window->getSize().x/4.f, 700.f, 500.f, 50.f, 30, 40, &this->font, false);

}

void MenuState::initBg()
{
	this->con1.setFillColor(Color(75, 75, 75));
	this->con1.setPosition(Vector2f(0.f, 100.f));
	this->con1.setSize(Vector2f(this->window->getSize().x, 100.f));

	this->con2.setFillColor(Color(75, 75, 75));
	this->con2.setPosition(Vector2f(0.f, this->window->getSize().y -50.f));
	this->con2.setSize(Vector2f(this->window->getSize().x, 50.f));

	this->gamename.setFont(font);
	this->gamename.setCharacterSize(50);
	this->gamename.setFillColor(Color::Black);
	this->gamename.setString("Not Yet Named");
	this->gamename.setOrigin(this->gamename.getLocalBounds().width / 2.f, this->gamename.getLocalBounds().height / 2.f);
	this->gamename.setPosition(
		this->con1.getPosition().x + this->con1.getSize().x/2.f,
		this->con1.getPosition().y + this->con1.getSize().y / 4.f);

	this->student.setFont(font);
	this->student.setCharacterSize(30);
	this->student.setFillColor(Color::Black);
	this->student.setString("64010272 Daniel Riyavong");
	this->student.setOrigin(this->student.getLocalBounds().width / 2.f, this->student.getLocalBounds().height / 2.f);
	this->student.setPosition(
		this->con2.getPosition().x + this->con2.getSize().x / 2.f,
		this->con2.getPosition().y + this->con2.getSize().y / 4.f);
}

void MenuState::initFont()
{
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";
}

void MenuState::initAnimation()
{
	this->animation->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
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
	this->initVar();

	this->animation = new Animation(this->sprite, this->sheet);

	this->initTexture();
	this->initSprite();
	this->initFont();
	this->initBg();
	this->initAnimation();
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

	delete this->animation;
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
				/*if (ev.Event::type == Event::Closed)
					this->window->close();
				else if (ev.Event::KeyPressed && ev.Event::key.code == Keyboard::Escape)
					this->window->close();*/
			}
		}
	}
}

void MenuState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		this->window->close();
}

void MenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateState();
	this->updateTextbox();
	this->playAnimation(dt);
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

void MenuState::renderBg(RenderTarget& target)
{
	target.draw(this->con1);
	target.draw(this->con2);
	target.draw(this->gamename);
	target.draw(this->student);
}

void MenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->window->draw(this->sprite);
	this->renderBg(*target);
	this->renderButton(*target);
	this->renderTextbox(*target);
}

void MenuState::playAnimation(const float& dt)
{
	this->animation->play("IDLE", dt, 2.f, 2.f);
}

