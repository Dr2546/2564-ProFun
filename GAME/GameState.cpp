#include "GameState.h"

void GameState::initGUI()
{
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";

	this->scoretext.setFont(font);
	this->scoretext.setCharacterSize(30);
	this->scoretext.setFillColor(sf::Color::Red);
	this->scoretext.setString("score: 0");
	this->scoretext.setPosition(
		this->window->getSize().x / 2.f, 0.f);

	//PlayerGUI
	this->hpbar.setSize(Vector2f(50.f, 10.f));
	this->hpbar.setFillColor(Color::Red);
	this->hpbar.setPosition(Vector2f(player->getPos().x, player->getPos().y - 5.f));

	this->hpbarback = this->hpbar;
	this->hpbarback.setFillColor(Color::Transparent);

	this->gameovertext.setFont(this->font);
	this->gameovertext.setCharacterSize(60);
	this->gameovertext.setFillColor(sf::Color::Red);
	this->gameovertext.setString("Game Over!");
	this->gameovertext.setPosition(
		this->window->getSize().x / 2.f - this->gameovertext.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameovertext.getGlobalBounds().height / 2.f);

	this->returntomenu = new gui::Button(300.f, 100.f, 100.f, 100.f, &this->font, "Return", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

void GameState::resetGUI()
{
	delete this->returntomenu;

	this->returntomenu = new gui::Button(300.f, 100.f, 100.f, 100.f, &this->font, "Return", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

void GameState::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->score = 0;
	this->buff = "none";
}

void GameState::initEnemy()
{
	this->spawnTimeMax = 25.f;
	this->spawnTime = 20.f;
}

void GameState::initItem()
{
	this->itemspawnTimeMax = 25.f;
	this->itemspawnTime = 20.f;

	this->itemdurationMax = 3.f;
	this->itemduration = 0.f;
}

GameState::GameState(StateData* statedata,string name) : State(statedata)
{
	this->initPlayer();
	this->name = name;
	this->initEnemy();
	this->initItem();
	this->initGUI();
	this->resetGUI();
}

GameState::~GameState()
{
	delete this->player;

	for (auto* i : this->enemies)
		delete i;

	for (auto* ii : this->speedboost)
		delete ii;

	delete this->returntomenu;
}

void GameState::updateInput(const float& dt)
{
}

void GameState::updatePollevent()
{
	Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
			this->window->close();
	}
}

void GameState::updateMovement()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		if (this->player->getPos().x >= 0)
		{
			this->player->move(-1.f, 0.f);
			this->player->setDirection(0);
			this->player->setStatus(2);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		if (this->player->getPos().x <= 1800)
		{
			this->player->move(1.f, 0.f);
			this->player->setDirection(1);
			this->player->setStatus(2);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (this->player->getPos().y >= 0)
		{
			this->player->move(0.f, -1.f);
			this->player->setStatus(2);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		if (this->player->getPos().y <= 960)
		{
			this->player->move(0.f, 1.f);
			this->player->setStatus(2);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::J) && this->player->canAttack())
	{
		this->player->setStatus(1);
	}
}

void GameState::updateEnemy()
{
	//Spawning
	this->spawnTime += 0.5f;
	if (this->spawnTime >= this->spawnTimeMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, rand() % this->window->getSize().y - 20.f));
		this->spawnTime = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		//Move to player
		if (enemy->getPos().x <= player->getPos().x)
		{
			if (enemy->getPos().y >= player->getPos().y)
				enemy->move(1.f, -1.f);
			else if (enemy->getPos().y <= player->getPos().y)
				enemy->move(1.f, 1.f);
		}
		else if (enemy->getPos().x >= player->getPos().x)
		{
			if (enemy->getPos().y >= player->getPos().y)
				enemy->move(-1.f, -1.f);
			else if (enemy->getPos().y <= player->getPos().y)
				enemy->move(-1.f, 1.f);
		}

		//Intersect with player
		if (enemy->getHitbox().intersects(this->player->getHitbox()))
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			this->player->gethit();
		}
		else if ((enemy->getHitbox().intersects(this->player->getAtkboxL()) || enemy->getHitbox().intersects(this->player->getAtkboxR())) && player->getStatus() == 1)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			this->score++;
		}
		++counter;

	}
}

void GameState::updateButton()
{
	this->returntomenu->update(this->mousePosWindow);
}

void GameState::updateGUI()
{
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	float x = static_cast<float>(player->getBound().width);
	this->hpbar.setSize(Vector2f(x * hpPercent, this->hpbar.getSize().y));
	this->hpbar.setPosition(Vector2f(player->getPos().x, player->getPos().y - 3.f));

	stringstream ss;
	ss << this->score;
	string s = "score:" + ss.str();
	this->scoretext.setString(s);
}

void GameState::updateFile()
{
	this->scoreboard.open("Resources/scoreboard.txt", ios_base::out | ios_base::app);
	this->scoreboard << this->name << " ";
	this->scoreboard << this->score << endl;
	this->scoreboard.close();
}

void GameState::updateItem()
{
	//Spawning
	this->itemspawnTime += 0.1f;
	if (this->itemspawnTime >= this->itemspawnTimeMax)
	{
		this->speedboost.push_back(new Speedboost(rand() % this->window->getSize().x - 20.f, rand() % this->window->getSize().y - 20.f));
		this->itemspawnTime = 0.f;
	}

	unsigned counter = 0;
	//Intersect with player
	for (auto* boost : this->speedboost)
	{
		boost->update();
		if (boost->getHitbox().intersects(this->player->getHitbox()))
		{
			delete this->speedboost.at(counter);
			this->speedboost.erase(this->speedboost.begin() + counter);
			this->buff = "speed";
		}
		++counter;
	}
}

void GameState::updateBuff()
{
	if (this->buff == "speed")
	{
		this->player->setSpeed(4.f);
		this->itemduration += 0.01f;
		if (this->itemduration >= this->itemdurationMax)
		{
			this->player->setSpeed(2.f);
			this->buff = "none";
			this->itemduration = 0.f;
		}
	}
}

void GameState::renderGUI()
{
	this->window->draw(this->hpbarback);
	this->window->draw(this->hpbar);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updatePollevent();
	this->player->update();
	this->updateMovement();
	//this->updateEnemy();
	this->updateItem();
	this->updateBuff();
	this->updateGUI();
	this->updateButton();
	if (this->player->getHp() <= 0 && this->isSave == false)
	{
		this->updateFile();
		this->isSave = true;
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->gameovertext);
		this->returntomenu->render(*target);
		if(this->returntomenu->isPress())
			this->endState();
	}
	else
	{
		//Draw all the stuffs
		//Render player
		this->player->render(*this->window);

		for (auto* boost : this->speedboost)
			boost->render(*this->window);

		//Render enemies
		//for (auto* enemy : this->enemies)
			//enemy->render(*this->window);

		this->renderGUI();
		this->window->draw(this->scoretext);
	}
}