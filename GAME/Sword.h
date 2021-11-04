#pragma once
#include "allheader.h"
#include "Hitbox.h"

class Sword
{
private:

	Sprite sprite;
	Texture textureR;
	Texture textureL;

	void initHitbox();
	void initSword();

protected:
	Hitbox *hitboxR;
	Hitbox *hitboxL;

public:
	Sword();
	virtual ~Sword();

	vector<float> getHitboxR() const;
	vector<float> getHitboxL() const;

	void setPos(float x, float y);

	void render(RenderTarget& target,int direction);
};

