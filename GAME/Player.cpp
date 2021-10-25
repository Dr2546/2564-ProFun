#include "Player.h"

//Private function
void Player::initVar()
{
	this->movespeed = 2.f;
	this->hpmax = 1;
	this->hp = this->hpmax;
	this->atkcooldownMax = 10.f;
	this->atkcooldown = this->atkcooldownMax;

	//Status 0 is idle 1 is attacking 2 is running
	this->status = 0;

	//1 is Right 0 is Left
	this->direction = 1;

	//Init hitbox
	this->createHitbox(this->sprite, 33.f, 13.f, 63.f, 100.f,Color::Green);
	this->createAtkboxR(this->sprite, 96.f, 27.f, 22.f, 18.f, Color::Yellow);
	this->createAtkboxL(this->sprite, 20.f, 30.f, 13.f, 12.f, Color::Yellow);
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->idleR.loadFromFile("Resources/Player/idleright.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->idleL.loadFromFile("Resources/Player/idleleft.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->attackR.loadFromFile("Resources/Player/attackright.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->attackL.loadFromFile("Resources/Player/attackleft.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->runR.loadFromFile("Resources/Player/runright.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
	if (!this->runL.loadFromFile("Resources/Player/runleft.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->idleR);
}

//Constructor && Destructor
Player::Player()
{
	//Initialize
	this->initVar();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

//Accessor
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBound() const
{
	return this->sprite.getGlobalBounds();
}

void Player::createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height,Color color)
{
	this->hitbox = new Hitbox(sprite, offsetX, offsetY, width, height,color);
}

void Player::createAtkboxR(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color)
{
	this->atkboxR = new Hitbox(sprite, offsetX, offsetY, width, height, color);
}

void Player::createAtkboxL(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color)
{
	this->atkboxL = new Hitbox(sprite, offsetX, offsetY, width, height, color);
}

FloatRect Player::getHitbox() const
{
	return this->hitbox->getGlobalBound();
}

FloatRect Player::getAtkboxR() const
{
	return this->atkboxR->getGlobalBound();
}

FloatRect Player::getAtkboxL() const
{
	return this->atkboxL->getGlobalBound();
}

//Modifier
void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

int Player::getHp()
{
	return this->hp;
}

int Player::getHpMax()
{
	return this->hpmax;
}

void Player::gethit()
{
	this->hp -= 1;
}


//Function
void Player::move(const float x, const float y)
{
	this->sprite.move(this->movespeed * x, this->movespeed * y);
}

void Player::setDirection(int d)
{
	this->direction = d;
}

void Player::setStatus(int s)
{
	this->status = s;
}

void Player::setSprite()
{
	if (this->status == 0)
	{
		if (this->direction == 0)
			this->sprite.setTexture(this->idleL);
		else
			this->sprite.setTexture(this->idleR);
	}
	else if (this->status == 1)
	{
		if (this->direction == 0)
		{
			this->sprite.setTexture(this->attackL);
		}
		else
		{
			this->sprite.setTexture(this->attackR);
		}
	}
	else if (this->status == 2)
	{
		if (this->direction == 0)
			this->sprite.setTexture(this->runL);
		else
			this->sprite.setTexture(this->runR);
	}

}

const bool Player::canAttack()
{
	if (this->atkcooldown >= this->atkcooldownMax)
	{
		this->atkcooldown = 0.f;
		return true;
	}
	return false;
}

int Player::getStatus()
{
	return this->status;
}


void Player::updateAttack()
{
	if (this->atkcooldown < this->atkcooldownMax)
		this->atkcooldown += 0.5f;
	else
		if(!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S))
			this->status = 0;
}

void Player::updateSprite()
{
	this->setSprite();
}

void Player::updateBox()
{
	this->hitbox->update();
	this->atkboxR->update();
	this->atkboxL->update();
}

void Player::update()
{
	this->updateAttack();
	this->updateSprite();
	this->updateBox();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitbox->render(target);
	if (this->status == 1)
	{
		if (this->direction == 1)
			this->atkboxR->render(target);
		else if (this->direction == 0)
			this->atkboxL->render(target);
	}
}
