#include "Gameengine.h"

//Private Function
void Gameengine::initWindow()
{
	this->window = new RenderWindow(VideoMode(), "Game", Style::Titlebar | Style::Close | Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

/*void Gameengine::initStates()
{
	this->states.push(new GameState(this->window));
}*/

void Gameengine::initGUI()
{
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";

	this->gameovertext.setFont(font);
	this->gameovertext.setCharacterSize(60);
	this->gameovertext.setFillColor(sf::Color::Red);
	this->gameovertext.setString("Game Over!");
	this->gameovertext.setPosition(
		this->window->getSize().x / 2.f - this->gameovertext.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameovertext.getGlobalBounds().height / 2.f);

	this->scoretext.setFont(font);
	this->scoretext.setCharacterSize(30);
	this->scoretext.setFillColor(sf::Color::Red);
	this->scoretext.setString("score: 0");
	this->scoretext.setPosition(
		this->window->getSize().x / 2.f,0.f);

	//PlayerGUI
	this->hpbar.setSize(Vector2f(50.f, 10.f));
	this->hpbar.setFillColor(Color::Red);
	this->hpbar.setPosition(Vector2f(player->getPos().x,player->getPos().y - 5.f));

	this->hpbarback = this->hpbar;
	this->hpbarback.setFillColor(Color(25, 25, 25, 200));
}

void Gameengine::initPlayer()
{
	this->player = new Player();
	this->score = 0;
}

void Gameengine::initEnemy()
{
	this->spawnTimeMax = 25.f;
	this->spawnTime = this->spawnTimeMax;
}

//Constructor && Destructor
Gameengine::Gameengine()
{
	this->initWindow();
	//this->initStates();
	this->initPlayer();
	this->initEnemy();
	this->initGUI();
}

Gameengine::~Gameengine()
{
	delete this->window;
	delete this->player;

	/*while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}*/

	for (auto* i : this->enemies)
		delete i;
}

//Function
void Gameengine::run()
{
	while (this->window->isOpen())
	{
		this->updatePollevent();
		this->updatedt();
		if (this->player->getHp() > 0)
			this->update();
		this->render();
	}
}

void Gameengine::updatePollevent()
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

void Gameengine::updateMovement()
{
	//Move
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

void Gameengine::updateEnemy()
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
		else if ((enemy->getHitbox().intersects(this->player->getAtkboxL())|| enemy->getHitbox().intersects(this->player->getAtkboxR())) && player->getStatus() == 1)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			this->score++;
		}
		++counter;

	}
}

void Gameengine::updateGUI()
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

void Gameengine::updatedt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Gameengine::update()
{
	this->updatePollevent();

	
	/*if (!this->states.empty())
		this->states.top()->update(this->dt);*/
	

	this->player->update();
	this->updateMovement();
	this->updateEnemy();
	this->updateGUI();
}

//Render
void Gameengine::renderGUI()
{
	this->window->draw(this->hpbarback);
	this->window->draw(this->hpbar);
	cout << this->player->getPos().x << ',' << this->player->getPos().y << endl;
}

void Gameengine::render()
{
	this->window->clear();

	/*if (!this->states.empty())
		this->states.top()->render(this->window);*/

	//Draw all the stuffs
	//Render player
	this->player->render(*this->window);
	
	//Render enemies
	for (auto* enemy : this->enemies)
		enemy->render(*this->window);

	this->renderGUI();

	if (this->player->getHp() <= 0)
	{
		this->window->clear();
		this->window->draw(this->gameovertext);
	}
	this->window->draw(this->scoretext);

	this->window->display();
}