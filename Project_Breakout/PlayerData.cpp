#include "PlayerData.h"

PlayerData::PlayerData(SDL_Renderer* renderer) : Common(renderer)
{
	playerLives = 3;
}
PlayerData::~PlayerData()
{
	SDL_DestroyTexture(texture);
}

void PlayerData::Update(SDL_Renderer* renderer)
{
	// Convert int to string
	std::stringstream ssPlayerLives;
	ssPlayerLives << playerLives;

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(font, (std::string("Paddles: ") + std::to_string(playerLives)).c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void PlayerData::Render(float dt)
{
	texW = 32;
	texH = 32;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 325,10, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}