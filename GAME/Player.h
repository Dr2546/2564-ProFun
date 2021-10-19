#pragma once

#include "allheader.h"
#include "Hitbox.h"

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

	//Sprite and Texture
	Sprite sprite;
	Texture idleR;
	Texture idleL;
	Texture attackR;
	Texture attackL;
	Texture runR;
	Texture runL;

	//Movement
	float movespeed;

	//Player Status
	int status;

	//Private function
	void initVar();
	void initTexture();
	void initSprite();

protected:
	//Hitbox
	Hitbox* hitbox;
	Hitbox* atkboxR;
	Hitbox* atkboxL;

public:
	//Constructor && Destructor
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBound() const;

	//Hitbox

	void createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height,Color color);
	void createAtkboxR(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color);
	void createAtkboxL(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color);
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

	void updateAttack();
	void updateSprite();
	void updateBox();
	void update();
	void render(sf::RenderTarget& target);
};

