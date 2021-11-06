#pragma once
#include "allheader.h"
#include "Hitbox.h"

class Item
{
private:
	Sprite sprite;

	//Texture Item
	Texture speed;
	Texture heal;

	//Type
	string buff;

	void initVar();
	void initTexture();
	void initSprite(int id);

protected:
	Hitbox* hitbox;

public:
	Item(float x,float y,int id);
	virtual ~Item();

	//Accessor
	const FloatRect getBounds() const;
	const Vector2f& getPos() const;
	FloatRect getHitbox() const;
	string getBuff();

	void createHitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color);

	//Function
	void update();
	void render(RenderTarget& target);
};

