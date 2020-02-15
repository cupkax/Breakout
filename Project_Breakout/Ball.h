#ifndef BALL_H_
#define BALL_H_

#include "Common.h"


// Ball speed
const float BALL_MOVESPEED = 500;

class Ball : public Common
{
public:
	Ball(SDL_Renderer* renderer);
	~Ball();

	void Update(float dt);
	void Render(float dt);

	// Ball Movement Attributes
	void BallMovement(float dirX, float dirY);
	float _dirX, _dirY;


private:
	// Ball Render Attributes
	SDL_Texture* ballTexture;
};

#endif // !BALL_H_

