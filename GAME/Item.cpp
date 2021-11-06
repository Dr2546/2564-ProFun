#include "Item.h"

void Item::initVar()
{
	this->createHitbox(this->sprite, 0.f, 0.f, 50.f, 50.f, Color::Magenta);
	this->buff = "";
}

void Item::initTexture()
{
	if (!this->speed.loadFromFile("Resources/speed.png"))
	{
		cout << "Could not load texture file." << "\n";
	}

	if (!this->heal.loadFromFile("Resources/heal.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void Item::initSprite(int id)
{
	switch (id)
	{
	case 0:
		this->sprite.setTexture(this->speed);
		this->buff = "speed";
		break;
	case 1:
		this->sprite.setTexture(this->heal);
		this->buff = "heal";
		break;
	default:
		break;
	}
	this->sprite.scale(0.125f, 0.125f);
}

Item::Item(float x, float y,int id)
{
	this->initVar();
	this->initTexture();
	this->initSprite(id);

	this->sprite.setPosition(x, y);
}

Item::~Item()
{
}

const FloatRect Item::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const Vector2f& Item::getPos() const
{
	return this->sprite.getPosition();
}

FloatRect Item::getHitbox() const
{
	return this->hitbox->getGlobalBound();
}

string Item::getBuff()
{
	return this->buff.c_str();
}

void Item::createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color)
{
	this->hitbox = new Hitbox(sprite, offsetX, offsetY, width, height, color);
}

void Item::update()
{
	this->hitbox->update();
}

void Item::render(RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitbox->render(target);
}
