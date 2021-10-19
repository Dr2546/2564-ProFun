#include "Hitbox.h"

Hitbox::Hitbox(Sprite& sprite, float offset_X, float offset_Y, float width, float height, Color color) : sprite(sprite), offsetX(offset_X), offsetY(offset_Y), color(color)
{
	this->nextPos.left = 0.f;
	this->nextPos.top = 0.f;
	this->nextPos.width = width;
	this->nextPos.height = height;

	this->hitbox.setPosition(Vector2f(this->sprite.getPosition().x + offset_X, this->sprite.getPosition().y + offset_Y));
	this->hitbox.setSize(Vector2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineColor(color);
	this->hitbox.setOutlineThickness(4);
}

Hitbox::~Hitbox()
{
}

const Vector2f& Hitbox::getPos() const
{
	return this->hitbox.getPosition();
}

const FloatRect Hitbox::getGlobalBound() const
{
	return this->hitbox.getGlobalBounds();
}

const FloatRect Hitbox::getnextPos(Vector2f& velocity)
{
	this->nextPos.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPos.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPos;
}

void Hitbox::setPos(Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void Hitbox::setPos(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

bool Hitbox::intersect(const FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void Hitbox::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void Hitbox::render(RenderTarget& target)
{
	target.draw(this->hitbox);
}
