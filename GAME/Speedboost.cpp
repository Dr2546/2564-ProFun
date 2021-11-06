#include "Speedboost.h"

void Speedboost::initVar()
{
	this->createHitbox(this->sprite, 0.f, 0.f, 60.f, 56.f, Color::Magenta);
}

void Speedboost::initTexture()
{
	if (!this->texture.loadFromFile("Resources/speed.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void Speedboost::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.08f, 0.08f);
}

Speedboost::Speedboost(float x, float y)
{
	this->initVar();
	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(x, y);
}

Speedboost::~Speedboost()
{
}

const FloatRect Speedboost::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const Vector2f& Speedboost::getPos() const
{
	return this->sprite.getPosition();
}

FloatRect Speedboost::getHitbox() const
{
	return this->hitbox->getGlobalBound();
}

void Speedboost::createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color)
{
	this->hitbox = new Hitbox(sprite, offsetX, offsetY, width, height, color);
}

void Speedboost::update()
{
	this->hitbox->update();
}

void Speedboost::render(RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitbox->render(target);
}
