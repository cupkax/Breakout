#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include"Common.h" 

// Playing Field and Brick Dimensions
constexpr auto PLAYFIELD_WIDTH = 12;
constexpr auto PLAYFIELD_HEIGHT = 9;
constexpr auto BRICK_WIDTH = 64;
constexpr auto BRICK_HEIGHT = 24;

class Brick
{
public:
	bool state;
};

class PlayField :public Common
{
public:
	PlayField(SDL_Renderer* renderer);
	~PlayField();

	void Update(float dt);
	void Render(float dt);
	void NewLevel();
	float brickPosX, brickPosY;

	// Bricks Position Array
	Brick bricks[PLAYFIELD_WIDTH][PLAYFIELD_HEIGHT];

private:
	SDL_Texture* brickTexture;
};
#endif // !PLAYFIELD_H