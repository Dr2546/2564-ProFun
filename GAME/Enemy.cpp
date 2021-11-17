#include "Enemy.h"

//Private Function
void Enemy::initVar()
{
	this->movespeed = 1.f;
	this->direction = 1;

	this->createHitbox(this->sprite, 15.f, 8.f, 47.f, 88.f,Color::Red);

	this->animation = NULL;
}

void Enemy::initTexture()
{
	//Load a texture from file
	if (!this->textureSheetR.loadFromFile("Resources/enemy/enemyright.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->textureSheetL.loadFromFile("Resources/enemy/enemyleft.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->textureSheet.loadFromFile("Resources/enemy/enemysheet4.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->texture.loadFromFile("Resources/trump.png"))
	{
		cout << "Could not load texture file." << "\n";
	}

}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	//this->sprite.scale(0.25f, 0.25f);
}

void Enemy::initAnimation()
{
	this->animation->addAnimation("LEFT", 30.f, 0, 0, 2, 0, 78, 108);
	this->animation->addAnimation("RIGHT", 30.f, 0, 1, 2, 1, 78, 108);
}

//Constructor && Destructor
Enemy::Enemy(float x,float y)
{
	this->initVar();

	this->animation = new Animation(this->sprite, this->textureSheet);

	this->initTexture();
	this->initSprite();

	this->initAnimation();

	this->sprite.setPosition(x, y);
}

Enemy::~Enemy()
{
	delete this->animation;
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

const int Enemy::getDirection() const
{
	return this->direction;
}

void Enemy::setDirection(int d)
{
	this->direction = d;
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

void Enemy::playAnimation(const float& dt)
{
	if (this->direction == 1)
	{
		this->animation->play("LEFT", dt, this->movespeed, this->movespeed);
	}
	else if (this->direction == 0)
	{
		this->animation->play("RIGHT", dt, this->movespeed, this->movespeed);
	}
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//this->hitbox->render(target);
}
