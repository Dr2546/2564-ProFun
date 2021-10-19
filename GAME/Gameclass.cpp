#include "Gameclass.h"


//Private Functions
void Gameclass::initVariable()
{
	this->window = nullptr;

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Gameclass::initWindow()
{
	this->video.height = 600;
	this->video.width = 800;
	this->window = new RenderWindow(this->video, "Game", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Gameclass::initEnemy()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(Vector2f(100.f, 100.f));
	this->enemy.setScale(Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(Color::Red);
	this->enemy.setOutlineColor(Color::Black);
	this->enemy.setOutlineThickness(1.f);


}

//----------------
//Destructor - Constructor
Gameclass::Gameclass()
{
	this->initVariable();
	this->initWindow();
	this->initEnemy();
}

Gameclass::~Gameclass()
{
	delete this->window;
}

//------------------
//Accessors
const bool Gameclass::running() const
{
	return this->window->isOpen();
}


void Gameclass::spawnEnemies()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	this->enemy.setFillColor(Color::Magenta);

	this->enemies.push_back(this->enemy);
}

//-------------------
//Function
void Gameclass::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Gameclass::updateMouse()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
}

void Gameclass::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	for (auto& e : this->enemies)
	{
		e.move(0.f, 5.f);
	}
}

void Gameclass::update()
{

	this->pollEvent();

	this->updateMouse();

	this->updateEnemies();
}

void Gameclass::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Gameclass::render()
{
	this->window->clear();
	this->renderEnemies();
	this->window->display();
}
