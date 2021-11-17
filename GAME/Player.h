#pragma once

#include "allheader.h"
#include "Hitbox.h"
#include "Sword.h"
#include "Animation.h"

using namespace sf;
using namespace std;

class Player
{
private:

	//Mechanics
	int hp;
	int hpmax;
	float atkcooldown;
	float atkcooldownMax;
	int direction;

	//Weapon
	string weapon;

	//Sprite and Texture
	Sprite sprite;
	Texture sheet;
	Texture idleR;
	Texture idleL;
	Texture attackR;
	Texture attackL;
	Texture runR;
	Texture runL;
	Texture swordR;
	Texture swordL;

	//Movement
	float movespeed;
	float movespeedMax;

	//Player Status
	int status;

	//Private function
	void initVar();
	void initTexture();
	void initSprite();
	void initSword();
	void initAnimation();
protected:
	//Hitbox
	Hitbox* hitbox;
	Hitbox* atkboxR;
	Hitbox* atkboxL;

	//Animation
	Animation* animation;

	//Sword
	Sword* sword;

public:
	//Constructor && Destructor
	Player();
	virtual ~Player();

	//Accessor
	const Vector2f& getPos() const;
	const FloatRect getBound() const;
	const float getSpeedMax() const;
	const int getHpMax() const;
	const int getDirection() const;
	void setSpeed(float s);
	void setHp(int s);
	string getWeapon();

	//Hitbox

	void createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height,Color color);
	void createAtkboxR(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color,string weapon);
	void createAtkboxL(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color, string weapon);
	FloatRect getHitbox() const;
	FloatRect getAtkboxR() const;
	FloatRect getAtkboxL() const;

	//Modifier
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	int getHp();
	int getHpMax();
	void gethit();

	//Function
	void move(const float x, const float y);
	void setDirection(int d);
	void setStatus(int s);
	void setSprite();
	const bool canAttack();
	int getStatus();

	void playAnimation(const float& dt);
	void updateAttack();
	void updateSprite();
	void updateBox();
	void updateSword();
	void update();
	void render(sf::RenderTarget& target);
};

