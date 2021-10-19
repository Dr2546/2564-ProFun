#include "Enemy.h"

//Private Function
void Enemy::initVar()
{
	this->movespeed = 1.f;

	this->createHitbox(this->sprite, 0.f, 4.f, 65.f, 51.f,Color::Red);
}

void Enemy::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Resources/trump.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.25f, 0.25f);
}

//Constructor && Destructor
Enemy::Enemy(float x,float y)
{
	this->initVar();
	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(x, y);
}

Enemy::~Enemy()
{
}

//Accessor
const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f& Enemy::getPos() const
{
	return this->sprite.getPosition();
}

FloatRect Enemy::getHitbox() const
{
	return this->hitbox->getGlobalBound();
}

void Enemy::createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height,Color color)
{
	this->hitbox = new Hitbox(sprite, offsetX, offsetY, width, height,color);
}

//Function
void Enemy::move(const float x, const float y)
{
	this->sprite.move(this->movespeed * x, this->movespeed * y);
	this->hitbox->update();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitbox->render(target);
}
