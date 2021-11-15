#pragma once

#include "allheader.h"
#include "Hitbox.h"
#include "Animation.h"

using namespace sf;
using namespace std;

class Enemy
{
private:
	//Sprite and Texture
	Sprite sprite;
	Texture texture;
	Texture textureSheetR;
	Texture textureSheetL;
	Texture textureSheet;

	//Mecchanic

	//Movement
	float movespeed;
	int direction;

	//Private function
	void initVar();
	void initTexture();
	void initSprite();
	void initAnimation();

protected:
	Hitbox* hitbox;
	Animation* animation;

public:
	//Constructor && Destructor
	Enemy(float x,float y);
	virtual ~Enemy();

	//Accessor
	const FloatRect getBounds() const;
	const Vector2f& getPos() const;
	FloatRect getHitbox() const;
	const int getDirection() const;
	void setDirection(int d);
	void createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height,Color color);

	//Function
	void move(const float x, const float y);
	void playAnimation(const float& dt);
	void render(RenderTarget& target);
};

