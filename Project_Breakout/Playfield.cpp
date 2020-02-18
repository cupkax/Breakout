#include "Playfield.h"

PlayField::PlayField(SDL_Renderer* renderer) : Common(renderer)
{
	SDL_Surface* surface = IMG_Load("bricks.png");
	brickTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	posX = 16;
	posY = 50;
	width = 768;
	height = 768;


}
PlayField :: ~PlayField()
{
	SDL_DestroyTexture(brickTexture);
}

void PlayField::Update(float dt)
{

}

void PlayField::Render(float dt)
{
	// Bricks Rendering  [http://rembound.com/articles/porting-pong-from-flash-to-cpp]
	for (int i = 0; i < PLAYFIELD_WIDTH; i++)
	{
		for (int j = 0; j < PLAYFIELD_HEIGHT; j++)
		{
			Brick brick = bricks[i][j];

			// If the brick exists
			if (!brick.state)
			{
				continue;
			}

			SDL_Rect srcrect;

			srcrect.x = BRICK_WIDTH;
			srcrect.y = BRICK_HEIGHT;
			srcrect.w = BRICK_WIDTH;
			srcrect.h = BRICK_HEIGHT;

			SDL_Rect dstrect;
			dstrect.x = posX + (i * BRICK_WIDTH);
			dstrect.y = posY + (j * BRICK_HEIGHT);
			dstrect.w = BRICK_WIDTH;
			dstrect.h = BRICK_HEIGHT;

			SDL_RenderCopy(renderer, brickTexture, &srcrect, &dstrect);
		}
	}
}

void PlayField::NewLevel()
{
	// Populating the level
	for (int i = 0; i < PLAYFIELD_WIDTH; i++)
	{
		for (int j = 0; j < PLAYFIELD_HEIGHT; j++)
		{
			Brick brick;
			brick.state = true;
			bricks[i][j] = brick;
		}
	}
}