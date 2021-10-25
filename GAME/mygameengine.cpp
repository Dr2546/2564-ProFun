#include "mygameengine.h"

void mygameengine::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->gridsize = 64.f;
}

void mygameengine::initWindow()
{
	this->window = new RenderWindow(VideoMode(), "Game", Style::Titlebar | Style::Close | Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void mygameengine::initStateData()
{
	this->statedata.window = this->window;
	this->statedata.states = &this->states;
	this->statedata.gridsize = this->gridsize;
}

void mygameengine::initStates()
{
	this->states.push(new MenuState(&this->statedata));
}

mygameengine::mygameengine()
{
	this->initVariables();
	this->initWindow();
	this->initStateData();
	this->initStates();
}

mygameengine::~mygameengine()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void mygameengine::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}


void mygameengine::update()
{
	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
	{
		this->window->close();
	}
}

void mygameengine::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void mygameengine::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
