#include "Leaderboard.h"

void Leaderboard::initScoreboard()
{
	this->scoreboard.open("Resources/scoreboard.txt");
	string name;
	int playerscore;
	while (this->scoreboard >> name >> playerscore)
	{
		score[name] = playerscore;
	}
	this->scoreboard.close();
}

void Leaderboard::initGUI()
{
	this->board.setString("Leaderboard");
	this->board.setCharacterSize(50);
	this->board.setFillColor(Color::White);
	this->board.setPosition(
		this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f,
		100.f);
	this->board.setFont(this->font);

	this->line1.setSize(Vector2f(this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f, 5.f));
	this->line1.setPosition(Vector2f(this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f, 160.f));
	this->line1.setFillColor(Color::White);

	this->line2.setSize(Vector2f(this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f, 5.f));
	this->line2.setPosition(Vector2f(this->board.getGlobalBounds().width / 2.f, 160.f));
	this->line2.setFillColor(Color::White);
	this->line2.setRotation(90.f);
}

void Leaderboard::initFont()
{
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";
}

void Leaderboard::initButtons()
{
	this->buttons["BACK"] = new gui::Button(100.f, 200.f, 100.f, 100.f, &this->font, "Back", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
	this->buttons["CLEAR"] = new gui::Button(100.f, 400.f, 100.f, 100.f, &this->font, "Clear Board", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
}

void Leaderboard::resetButtons()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initButtons();
}

Leaderboard::Leaderboard(StateData* statedata) : State(statedata)
{
	this->initFont();
	this->initGUI();
	this->initScoreboard();
	this->initButtons();
	this->resetButtons();
}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::updateInput(const float& dt)
{
}

void Leaderboard::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void Leaderboard::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderGUI();
	this->renderButtons();
}

void Leaderboard::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosWindow);

	if (this->buttons["BACK"]->isPress())
	{
		this->endState();
	}

	if (this->buttons["CLEAR"]->isPress())
	{
		if (remove("Resources/scoreboard.txt"))
		{
			;
		}
	}
}

void Leaderboard::renderGUI()
{
	this->window->draw(this->board);
	this->window->draw(this->line1);
	this->window->draw(this->line2);
}

void Leaderboard::renderButtons()
{
	for (auto& it : this->buttons)
		it.second->render(*this->window);
}
