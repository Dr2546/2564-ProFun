#include "Heal.h"

void Heal::initVar()
{
	this->createHitbox(this->sprite, 0.f, 0.f, 60.f, 56.f, Color::Magenta);
}

void Heal::initTexture()
{
	if (!this->texture.loadFromFile("Resources/heal.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void Heal::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.117f, 0.11f);
}

Heal::Heal(float x, float y)
{
	this->initVar();
	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(x, y);
}

Heal::~Heal()
{

}

const FloatRect Heal::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const Vector2f& Heal::getPos() const
{
	return this->sprite.getPosition();
}

FloatRect Heal::getHitbox() const
{
	return this->hitbox->getGlobalBound();
}

void Heal::createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color)
{
	this->hitbox = new Hitbox(sprite, offsetX, offsetY, width, height, color);
}

void Heal::update()
{
	this->hitbox->update();
}

void Heal::render(RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitbox->render(target);
}
