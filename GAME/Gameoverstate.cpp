#include "Gameoverstate.h"

void Gameoverstate::initGui()
{
	this->gameovertext.setFont(this->font);
	this->gameovertext.setCharacterSize(60);
	this->gameovertext.setFillColor(sf::Color::Red);
	this->gameovertext.setString("Game Over!");
	this->gameovertext.setPosition(
		this->window->getSize().x / 2.f - this->gameovertext.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameovertext.getGlobalBounds().height / 2.f);

	this->returntomenu = new gui::Button(100.f, 100.f, 100.f, 100.f, &this->font, "Return", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

void Gameoverstate::initFont()
{
	if (!font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";
}

void Gameoverstate::resetGui()
{
	delete this->returntomenu;

	this->returntomenu = new gui::Button(100.f, 100.f, 100.f, 100.f, &this->font, "Return", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

Gameoverstate::Gameoverstate(StateData* statedata) : State(statedata)
{
	this->initFont();
	this->initGui();
	this->resetGui();
}

Gameoverstate::~Gameoverstate()
{
	delete this->returntomenu;
}

void Gameoverstate::updateInput(const float& dt)
{
}

void Gameoverstate::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->returntomenu->update(this->mousePosWindow);
	if (this->returntomenu->isPress())
	{
		this->endState();
	}
}

void Gameoverstate::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->window->draw(this->gameovertext);
	this->renderButton(*target);
}

void Gameoverstate::renderButton(RenderTarget& target)
{
	this->returntomenu->render(target);
}
