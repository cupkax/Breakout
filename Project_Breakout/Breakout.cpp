#include "Breakout.h"

Breakout::Breakout()
{
	// Reset game window and renderer
	breakoutWindow = 0;
	breakoutRenderer = 0;

	// Game Running
	isGameRunning = true;
}

// Breakout Destructor
Breakout::~Breakout()
{

}

bool Breakout::Init()
{
	// Initialise SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Initialise TTF
	TTF_Init();

	// Create Breakout Window
	breakoutWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	// Window creation error reporting
	if (!breakoutWindow)
	{
		std::cout << "Failed to create game window" << SDL_GetError();
		return false;
	}

	// Create Breakout Renderer
	breakoutRenderer = SDL_CreateRenderer(breakoutWindow, -1, SDL_RENDERER_ACCELERATED);
	// Renderer creation error reporting
	if (!breakoutRenderer)
	{
		std::cout << "Failed to create game renderer" << SDL_GetError();
		return false;
	}

	// Initialise Timings
	lastTick = SDL_GetTicks();
	fpsTick = lastTick;
	framerate = 0;
	framecount = 0;

	return true;
}

// Destroy and free resources
void Breakout::DumpDestroy()
{
	SDL_DestroyWindow(breakoutWindow);
	SDL_DestroyRenderer(breakoutRenderer);
	SDL_DestroyTexture(breakoutTexture);
}

// Initialise game assets
void Breakout::Run()
{
	playfield = new PlayField(breakoutRenderer);
	ball = new Ball(breakoutRenderer);
	paddle = new Paddle(breakoutRenderer);
	playerdata = new PlayerData(breakoutRenderer);

	// Create new game instance
	NewGame();

	// Initialisation loop [ http://rembound.com/articles/porting-pong-from-flash-to-cpp]
	while (isGameRunning)
		// Events
	{
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				break;
			}
		}

		// Initialise delta and framerate
		unsigned int curtick = SDL_GetTicks();
		float dt = (curtick - lastTick) / 1000.0f;
		if (curtick - fpsTick >= FPS_DELAY)
		{
			framerate = framecount * (1000.0f / (curtick - fpsTick));
			fpsTick = curtick;
			framecount = 0;
		}
		else
		{
			framecount++;
		}
		lastTick = curtick;

		// Render Game
		Update(dt);
		Render(dt);
	}
	// Delete Assets
	delete playfield;
	delete ball;
	delete paddle;

	// Free Resources
	DumpDestroy();

	// Quit Game
	SDL_QUIT;
}

void Breakout::NewGame()
{
	// Create/Reset New Game and Reset Paddle position
	playfield->NewLevel();
	ResetPaddle();

}

// Reset Paddle state
void Breakout::ResetPaddle()
{
	ballStickToPaddle = true;
	BallStick();
}

// Stick Ball to Paddle center when paddle resets
void Breakout::BallStick()
{
	ball->posX = paddle->posX + paddle->width / 2 - ball->width / 2;
	ball->posY = paddle->posY - ball->height;
}

void Breakout::Update(float dt)
{

	// Mouse Input
	int mousex, mousey;
	Uint8 mousestate = SDL_GetMouseState(&mousex, &mousey);
	SetPaddleX(mousex - paddle->width / 2.0f);

	// Move paddle when moving mouse and shoot on left click
	if (mousestate & SDL_BUTTON(1))
	{
		// Shoot ball upwards if stuck to paddle
		if (ballStickToPaddle)
		{
			ballStickToPaddle = false;
			ball->BallMovement(-1, -1);
		}
	}

	if (ballStickToPaddle)
	{
		BallStick();
	}

	CheckSidesCollision();
	BallPaddleCollision();
	CheckBallBrickCollision();

	// Start new game if no bricks are left
	if (GetBricks() == 0)
	{
		SDL_QUIT;
	}


	// Pass deltatime value to level, paddle and ball (if ball is not sticking to paddle)
	playfield->Update(dt);
	paddle->Update(dt);
	playerdata->Update(breakoutRenderer);

	if (!ballStickToPaddle)
	{
		ball->Update(dt);
	}
}

// Decrement Life and terminate application if no lives left
void Breakout::LoseLife()
{
	if (playerdata->playerLives > 1)
	{
		playerdata->playerLives--; // Decrement player life
	}
	else
	{
		isGameRunning = false; // Set game running to false and close game window
	}
}

// Set paddle X-coordinate for input movement
void Breakout::SetPaddleX(float x)
{
	float newx;
	if (x < playfield->posX)
	{
		// Top Boundaries
		newx = playfield->posX;
	}
	else if (x + paddle->width > playfield->posX + playfield->width)
	{
		// Bottom Boundaries
		newx = playfield->posX + playfield->width - paddle->width;
	}
	else
	{
		newx = x;
	}
	paddle->posX = newx;
}

// Check ball to side collisions. Reflect ball when hit on window sides
void Breakout::CheckSidesCollision()
{
	// Top and Bot collisions
	if (ball->posY < playfield->posY)
	{
		// Top collision
		ball->posY = playfield->posY;
		ball->_dirY *= -1;
	}

	else if (ball->posY + ball->height > playfield->posY + playfield->height)
	{
		// When Bot hits bot border, reset paddle/ball and lose life
		ResetPaddle();
		LoseLife(); // Call lose life when ball hits bottom
	}

	// Side Collisions
	if (ball->posX <= playfield->posX)
	{
		// Left Side
		ball->posX = playfield->posX;
		ball->_dirX *= -1;
	}

	else if (ball->posX + ball->width >= playfield->posX + playfield->width)
	{
		// Right Side
		ball->posX = playfield->posX + playfield->width - ball->width;
		ball->_dirX *= -1;
	}
}

// Ball-Paddle reflection calculation
float Breakout::BallPaddleReflection(float hitx)
{
	// Check hitx less than paddle width
	if (hitx < 0)
	{
		hitx = 0;
	}
	else if (hitx > paddle->width)
	{
		hitx = paddle->width;
	}

	/* If ball hits left from the center, ball reflects to left.
	   If ball hits right from the center, ball reflects to right.
	*/
	hitx -= paddle->width / 2.0f;

	// Adjust reflection angle based on how far from the center the ball hits the paddle
	return 2.0f * (hitx / (paddle->width / 2.0f));
}

// Check Ball-Paddle collision and call ball reflection
void Breakout::BallPaddleCollision()
{
	// Get ball center x-coor
	float ballcenterx = ball->posX + ball->width / 2.0f;

	float paddlecenterx = paddle->posX + paddle->width / 2.0f;

	// Check if ball collided with paddle
	if (ball->Collides(paddle))
	{
		ball->posY = paddle->posY - ball->height;
		ball->BallMovement(BallPaddleReflection(ballcenterx - paddle->posX), -1);
		//ball->BallDirection(BallPaddleReflection(paddlecenterx - paddle->posx), -1); REFLECT BALLS STRIGHT UP

	}
}

// Calculate ball reflection based on brick hit location [ http://rembound.com/articles/porting-pong-from-flash-to-cpp]
void Breakout::BallBrickReflection(int dirindex)
{
	// Ball-Brick reflection direction factors
	int mulx = 1;
	int muly = 1;

	if (ball->_dirX > 0)
	{
		// Ball moving +ve x-direction
		if (ball->_dirY > 0)
		{
			// Ball moving +ve y-direction
			if (dirindex == 0 || dirindex == 3)
			{
				mulx = -1;
			}
			else
			{
				muly = -1;
			}
		}

		else if (ball->_dirY < 0)
		{
			// Ball moving -ve y-direction
			if (dirindex == 0 || dirindex == 1)
			{
				mulx = -1;
			}
			else
			{
				muly = -1;
			}
		}
	}

	else if (ball->_dirX < 0)
	{
		// Ball moving -ve x-direction
		if (ball->_dirY > 0)
		{
			if (dirindex == 2 || dirindex == 3)
			{
				mulx = -1;
			}
			else
			{
				muly = -1;
			}
		}

		else if (ball->_dirY < 0)
		{
			// Ball moving -ve y-direction
			if (dirindex == 1 || dirindex == 2)
			{
				mulx = -1;
			}
			else
			{
				muly = -1;
			}
		}
	}

	// Reflected direction is product of old direction with new factors
	ball->BallMovement(mulx * ball->_dirX, muly * ball->_dirY);


}


// Check Ball-Brick Collision  
void Breakout::CheckBallBrickCollision()
{
	for (int i = 0; i < PLAYFIELD_WIDTH; i++)
	{
		for (int j = 0; j < PLAYFIELD_HEIGHT; j++)
		{
			Brick brick = playfield->bricks[i][j];

			// Is brick present
			if (brick.state)
			{
				// Get brick position
				float brickx = playfield->brickPosX + playfield->posX + i * BRICK_WIDTH;
				float bricky = playfield->brickPosY + playfield->posY + j * BRICK_HEIGHT;

				// Check if ball collided with brick
				float w = (ball->width + BRICK_WIDTH) / 2.0f;
				float h = (ball->height + BRICK_HEIGHT) / 2.0f;
				float dx = (ball->posX + ball->width / 2.0f) - (brickx + BRICK_WIDTH / 2.0f);
				float dy = (ball->posY + ball->height / 2.0f) - (bricky + BRICK_HEIGHT / 2.0f);

				if (fabs(dx) <= w && fabs(dy) <= h)
				{
					// If Collision detected
					playfield->bricks[i][j].state = false;

					float wy = w * dy;
					float hx = h * dx;

					if (wy > hx)
					{
						if (wy > -hx)
						{
							// Bottom
							BallBrickReflection(3);
						}
						else
						{
							// Left
							BallBrickReflection(0);
						}
					}
					else
					{
						if (wy > -hx)
						{
							// Right
							BallBrickReflection(2);
						}
						else
						{
							// Top
							BallBrickReflection(1);
						}
					}
					return;
				}
			}
		}
	}
}

// Returns the number of bricks in the level
int Breakout::GetBricks()
{
	int brickcount = 0;
	for (int i = 0; i < PLAYFIELD_WIDTH; i++)
	{
		for (int j = 0; j < PLAYFIELD_HEIGHT; j++)
		{
			Brick brick = playfield->bricks[i][j];
			if (brick.state)
			{
				brickcount++;
			}
		}

	}
	return brickcount;
}

// Render game assets to screen
void Breakout::Render(float dt)
{
	SDL_RenderClear(breakoutRenderer);

	playfield->Render(dt);
	ball->Render(dt);
	paddle->Render(dt);
	playerdata->Render(dt);

	SDL_RenderPresent(breakoutRenderer);
}