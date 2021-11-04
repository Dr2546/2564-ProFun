#pragma once

#include "allheader.h"
#include "Hitbox.h"

using namespace sf;
using namespace std;

class Enemy
{
private:
	//Sprite and Texture
	Sprite sprite;
	Texture texture;

	//Mecchanic

	//Movement
	float movespeed;

	//Private function
	void initVar();
	void initTexture();
	void initSprite();

protected:
	Hitbox* hitbox;

public:
	//Constructor && Destructor
	Enemy(float x,float y);
	virtual ~Enemy();

	//Accessor
	const FloatRect getBounds() const;
	const Vector2f& getPos() const;
	FloatRect getHitbox() const;

	void createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height,Color color);

	//Function
	void move(const float x, const float y);
	void render(RenderTarget& target);
};

