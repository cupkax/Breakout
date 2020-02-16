#ifndef BALL_H
#define BALL_H

#include "Common.h"


// Ball speed
const float BALL_MOVESPEED = 500;

class Ball : public Common
{
public:
	Ball(SDL_Renderer* renderer);
	~Ball();

	float _dirX, _dirY;
	void Update(float dt);
	void Render(float dt);

	// Ball Movement Attributes
	void BallMovement(float dirX, float dirY);

	bool Collides(Common* other);


private:
	// Ball Render Attributes
	SDL_Texture* ballTexture;
};

#endif // !BALL_H
