#pragma once
#include "allheader.h"
#include "Hitbox.h"

class Speedboost
{
private:

	Sprite sprite;
	Texture texture;

	void initVar();
	void initTexture();
	void initSprite();

protected:

	Hitbox* hitbox;

public:
	//Constructor && Destructor
	Speedboost(float x, float y);
	virtual ~Speedboost();

	//Accessor
	const FloatRect getBounds() const;
	const Vector2f& getPos() const;
	FloatRect getHitbox() const;

	void createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color);

	//Function
	void update();
	void render(RenderTarget& target);
};

