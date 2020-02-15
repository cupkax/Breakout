#include "Common.h"



class PlayerData : public Common
{
public:
	PlayerData(SDL_Renderer* renderer);
	~PlayerData();

	void Update(SDL_Renderer* renderer);
	void Render(float dt);

	int playerLives;
	int texW, texH;

private:
	TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
	SDL_Color color = { 255, 255, 255 };
	SDL_Texture* texture;
	SDL_Surface* surface;
};