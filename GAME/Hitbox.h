#pragma once
#include"allheader.h"

class Hitbox
{
private:
	Sprite& sprite;
	RectangleShape hitbox;
	FloatRect nextPos;
	float offsetX;
	float offsetY;
	float width, height;
	Color color;

public:
	Hitbox(Sprite& sprite, float offsetX, float offsetY, float width, float height, Color color);
	virtual ~Hitbox();

	const Vector2f& getPos() const;
	const FloatRect getGlobalBound() const;
	const FloatRect getnextPos(Vector2f& velocity);
	const float getWidth() const;
	const float getHeight() const;

	void setPos(Vector2f& position);
	void setPos(const float x, const float y);

	bool intersect(const FloatRect& frect);

	void update();
	void render(RenderTarget& target);
};

