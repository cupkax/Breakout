#include "Ball.h"

Ball::Ball(SDL_Renderer* renderer) : Common(renderer)
{
	SDL_Surface* surface = IMG_Load("ball.png");
	ballTexture = SDL_CreateTextureFromSurface(renderer, surface);

	width = 16;
	height = 16;
}

Ball::~Ball()
{
	SDL_DestroyTexture(ballTexture);
}

// Update the position of the ball
void Ball::Update(float dt)
{
	// Add ball's direction vector * deltatime 
	posX += _dirX * dt;
	posY += _dirY * dt;
}

void Ball::Render(float dt)
{
	// Ball render attributes
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = width;
	rect.h = height;

	SDL_RenderCopy(renderer, ballTexture, 0, &rect);
}

void Ball::BallMovement(float newDirX, float newDirY)
{
	// Normalise and multiply the direction vector with ball speed
	float length = sqrtf(newDirX * newDirX + newDirY * newDirY);
	_dirX = BALL_MOVESPEED * (newDirX / length);
	_dirY = BALL_MOVESPEED * (newDirY / length);
}

bool Ball::Collides(Common* other)
{
	if (posX + width > other->posX&& posX < other->posX + other->width &&
		posY + height > other->posY&& posY < other->posY + other->height) {
		return true;
	}
	return false;
}