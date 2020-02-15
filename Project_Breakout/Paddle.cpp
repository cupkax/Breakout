#include "Paddle.h"

Paddle::Paddle(SDL_Renderer* renderer) : Common(renderer)
{
	SDL_Surface* surface = IMG_Load("paddle.png");
	paddleTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	width = 128;
	height = 32;
	posX = 0;
	posY = 560;
}

Paddle::~Paddle()
{
	// Paddle Cleanup
	SDL_DestroyTexture(paddleTexture);
}

void Paddle::Update(float dt)
{

}

void Paddle::Render(float dt)
{
	// Paddle render attributes
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = width;
	rect.h = height;
	SDL_RenderCopy(renderer, paddleTexture, 0, &rect);
}