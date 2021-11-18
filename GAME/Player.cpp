#include "Player.h"

//Private function
void Player::initVar()
{
	this->movespeedMax = 2.f;
	this->movespeed = this->movespeedMax;
	this->hpmax = 2;
	this->hp = this->hpmax;
	this->atkcooldownMax = 10.f;
	this->atkcooldown = this->atkcooldownMax;

	//Weapon
	this->weapon = "sword";

	//Status 0 is idle 1 is attacking 2 is running
	this->status = 0;

	//1 is Right 0 is Left
	this->direction = 1;

	//Init hitbox
	this->createHitbox(this->sprite, 19.f, 7.f, 73.f, 95.f,Color::Green);
	this->createAtkboxR(this->sprite, 75.f, 60.f, 22.f, 18.f, Color::Yellow,this->weapon);
	this->createAtkboxL(this->sprite, 15.f, 60.f, 22.f, 18.f, Color::Yellow,this->weapon);

	this->animation = NULL;
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
	if (!this->sheet.loadFromFile("Resources/Player/player.png"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->sheet);
	this->sprite.scale(1.75f, 1.75f);
}

void Player::initSword()
{
	this->sword = new Sword();
}

void Player::initAnimation()
{
	this->animation->addAnimation("LEFT", 30.f, 4, 1, 7, 1, 64, 64);
	this->animation->addAnimation("RIGHT", 30.f, 8, 1, 11, 1, 64, 64);
	this->animation->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animation->addAnimation("ATKR", 30.f, 11, 1, 11, 1, 64, 64);
	this->animation->addAnimation("ATKL", 30.f, 7, 1, 7, 1, 64, 64);
}

//Constructor && Destructor
Player::Player()
{
	//Initialize
	this->initVar();

	this->animation = new Animation(this->sprite, this->sheet);

	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initSword();
}

Player::~Player()
{
	delete this->animation;
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

const float Player::getSpeedMax() const
{
	return this->movespeedMax;
}

const int Player::getHpMax() const
{
	return this->hpmax;
}

const int Player::getDirection() const
{
	return this->direction;
}

bool Player::checkInside(float x, float y)
{
	float posx = this->hitbox->getPos().x - 100.f;
	float posy = this->hitbox->getPos().y - 100.f;
	if (posx < x && x < posx + this->hitbox->getWidth() + 200.f && posy < y && y < posy + this->hitbox->getHeight() + 200.f)
		return true;
	else
		return false;
}

void Player::setSpeed(float s)
{
	this->movespeed = s;
}

void Player::setHp(int s)
{
	this->hp = s;
}

string Player::getWeapon()
{
	return this->weapon;
}

void Player::createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height,Color color)
{
	this->hitbox = new Hitbox(sprite, offsetX, offsetY, width, height,color);
}

void Player::createAtkboxR(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color,string weapon)
{
	if (weapon == "none")
		this->atkboxR = new Hitbox(sprite, offsetX, offsetY, width, height, color);
	else if (weapon == "sword")
	{
		vector<float> data = this->sword->getHitboxR();
		this->atkboxR = new Hitbox(sprite,offsetX + data[0],offsetY+height/2, data[2], data[3], color);
	}
}

void Player::createAtkboxL(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color,string weapon)
{
	if (weapon == "none")
		this->atkboxL = new Hitbox(sprite, offsetX, offsetY, width, height, color);
	else if (weapon == "sword")
	{
		vector<float> data = this->sword->getHitboxL();
		this->atkboxL = new Hitbox(sprite,offsetX - data[2],offsetY+height/2, data[2], data[3], color);
	}
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


void Player::playAnimation(const float& dt)
{
	if (this->status == 0)
	{
		this->animation->play("IDLE", dt, this->movespeed,this->movespeedMax);
	}
	else if (this->status == 1)
	{
		if (this->direction == 1)
		{
			this->animation->play("ATKR", dt, this->movespeed, this->movespeedMax);
		}
		else if (this->direction == 0)
		{
			this->animation->play("ATKL", dt, this->movespeed, this->movespeedMax);
		}
	}
	else if (this->status == 2)
	{
		if (this->direction == 1)
		{
			this->animation->play("RIGHT", dt, this->movespeed, this->movespeedMax);
		}
		else if (this->direction == 0)
		{
			this->animation->play("LEFT", dt, this->movespeed, this->movespeedMax);
		}
	}
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

void Player::updateSword()
{
	if (this->direction == 1)
	{
		float x = this->atkboxR->getPos().x - 26.f;
		float y = this->atkboxR->getPos().y - 20.f;
		this->sword->setPos(x,y);
	}
	else if (this->direction == 0)
	{
		float x = this->atkboxL->getPos().x - 10.f;
		float y = this->atkboxL->getPos().y - 20.f ;
		this->sword->setPos(x, y);
	}
}

void Player::update()
{
	this->updateAttack();
	//this->updateSprite();
	this->updateBox();
	if(this->weapon == "sword")
		this->updateSword();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//this->hitbox->render(target);
	if (this->status == 1)
	{
		//if (this->direction == 1)
			//this->atkboxR->render(target);
		//else if (this->direction == 0)
			//this->atkboxL->render(target);
		if (this->weapon == "sword")
		{
			this->sword->render(target, this->direction);
		}
	}
}
