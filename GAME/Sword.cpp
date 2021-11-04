#include "Sword.h"

void Sword::initHitbox()
{
	this->hitboxR = new Hitbox(this->sprite, 24.5f, 24.7f, 71.3f, 4.7f, Color::Blue);
	this->hitboxL = new Hitbox(this->sprite, 0.f, 24.7f, 71.3f, 4.7f, Color::Blue);
}

void Sword::initSword()
{
	if (!this->textureR.loadFromFile("Resources/Sword/swordR.png"));
	{
		cout << "Error";
	}
	if (!this->textureL.loadFromFile("Resources/Sword/swordL.png"));
	{
		cout << "Error";
	}
	this->sprite.setTexture(this->textureR);
	this->sprite.setScale(0.05f, 0.05f);
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
	v.push_back(24.5f);
	v.push_back(24.7f);
	v.push_back(71.3f);
	v.push_back(4.7f);
	return v;
}

vector<float> Sword::getHitboxL() const
{
	vector<float> v;
	v.push_back(0.f);
	v.push_back(24.7f);
	v.push_back(71.3f);
	v.push_back(4.7f);
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
