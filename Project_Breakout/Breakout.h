#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<iostream>
#include <sstream>

#include "Ball.h"
#include "PlayField.h"
#include "Paddle.h"
#include "PlayerData.h"

#define FPS_DELAY 500

class Breakout
{
public:
	Breakout();
	~Breakout();

	bool Init();
	void Run();

private:
	// Breakout Game Window
	SDL_Window* breakoutWindow;

	// Breakout Game Renderer
	SDL_Renderer* breakoutRenderer;

	//// Breakout Texture
	//SDL_Texture* breakoutTexture; // Redundant

	// Timing
	unsigned int lastTick, fpsTick, framerate, framecount;

	// Assets
	PlayField* playfield;
	Ball* ball;
	Paddle* paddle;
	PlayerData* playerdata;

	// Flags
	bool ballStickToPaddle;
	bool isGameRunning;

	// Rendering 
	void DumpDestroy(); // Destroy Window/Renderer
	void Update(float dt); // Game Logic
	void Render(float dt); // Render Game Assets

	// To call when new game is created
	void NewGame(); // Create new game
	void ResetPaddle(); // Reset paddle position
	void BallStick(); // Reset ball position to paddle

	// Lose Life on dropping ball
	void LoseLife();

	// Game Asset states
	void SetPaddleX(float x); // Set paddle X-coordinate for input movement
	void CheckSidesCollision(); // Check ball to side collisions. Reflect ball when hit on window sides
	float BallPaddleReflection(float hitx); // Ball-Paddle reflection calculation
	void BallPaddleCollision(); // Check Ball-Paddle collision and call ball reflection
	void BallBrickReflection(int dirindex); // Calculate ball reflection based on brick hit location
	void CheckBallBrickCollision();// Check Ball-Brick Collision  
	int GetBricks(); // Returns the number of bricks in the level
};
#endif // !BREAKOUT_H
