#pragma once
#include "allheader.h"

enum movement_state { IDLE = 0 , MOVING, MOVING_LEFT , MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

using namespace std;
using namespace sf;

class MovementState
{
private:

	Sprite& sprite;

	float speed;
	float speedMax;

public:
	MovementState(Sprite& sprite,float speedMax);
	virtual ~MovementState();

	//Accessor
	const float& getspeedMax() const;
	const float& getspeed() const;

	//Function
	const bool getState(const short unsigned state) const;

	void move();
	void update(const float& dt);

};

