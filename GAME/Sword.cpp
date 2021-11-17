#include "Sword.h"

void Sword::initHitbox()
{
	this->hitboxR = new Hitbox(this->sprite, 26.f, 20.f, 50.f, 5.f, Color::Blue);
	this->hitboxL = new Hitbox(this->sprite, 0.f, 20.f, 50.f, 5.f, Color::Blue);
}

void Sword::initSword()
{
	if (!this->textureR.loadFromFile("Resources/Sword/swordR2.png"));
	{
		cout << "Error";
	}
	if (!this->textureL.loadFromFile("Resources/Sword/swordL2.png"));
	{
		cout << "Error";
	}
	this->sprite.setTexture(this->textureR);
	this->sprite.setScale(0.70f, 0.70f);
}

Sword::Sword()
{
	this->initSword();
	this->initHitbox();
}

Sword::~Sword()
{
}

vector<float> Sword::getHitboxR() const
{
	vector<float> v;
	v.push_back(26.f);
	v.push_back(20.f);
	v.push_back(50.f);
	v.push_back(5.f);
	return v;
}

vector<float> Sword::getHitboxL() const
{
	vector<float> v;
	v.push_back(0.f);
	v.push_back(26.f);
	v.push_back(50.f);
	v.push_back(5.f);
	return v;
}

void Sword::setPos(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Sword::render(RenderTarget& target,int direction)
{
	if (direction == 1)
	{
		this->sprite.setTexture(this->textureR);
		target.draw(this->sprite);
	}
	else if (direction == 0)
	{
		this->sprite.setTexture(this->textureL);
		target.draw(this->sprite);
	}
}
