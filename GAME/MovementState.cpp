#include "MovementState.h"

MovementState::MovementState(Sprite& sprite, float speedMax) : sprite(sprite), speedMax(speedMax)
{
}

MovementState::~MovementState()
{
}

const float& MovementState::getspeedMax() const
{
	return this->speedMax;
}

const float& MovementState::getspeed() const
{
	return this->speed;
}

const bool MovementState::getState(const short unsigned state) const
{
	return false;
}

void MovementState::move()
{
}

void MovementState::update(const float& dt)
{
}
