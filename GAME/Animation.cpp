#include "Animation.h"

Animation::Animation(Sprite& sprite, Texture& textureSheet) : sprite(sprite) , textureSheet(textureSheet) , last(NULL) , priorityAnimation(NULL)
{
}

Animation::~Animation()
{
	for (auto& i : this->animations)
		delete i.second;
}

const bool& Animation::isDone(const string key)
{
	return this->animations[key]->isDone();
}

void Animation::addAnimation(const string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animate(this->sprite, this->textureSheet, animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

const bool& Animation::play(const string key, const float& dt, const bool priority)
{
	if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->last != this->animations[key])
			{
				if (this->last == NULL)
					this->last = this->animations[key];
				else
				{
					this->last->reset();
					this->last = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->last != this->animations[key])
		{
			if (this->last == NULL)
				this->last = this->animations[key];
			else
			{
				this->last->reset();
				this->last = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& Animation::play(const string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->last != this->animations[key])
			{
				if (this->last == NULL)
					this->last = this->animations[key];
				else
				{
					this->last->reset();
					this->last = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->last != this->animations[key])
		{
			if (this->last == NULL)
				this->last = this->animations[key];
			else
			{
				this->last->reset();
				this->last = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier/modifier_max));
	}

	return this->animations[key]->isDone();
}

