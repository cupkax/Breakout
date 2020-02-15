#include "Common.h"

class Paddle : public Common
{
public:
	Paddle(SDL_Renderer* renderer);
	~Paddle();

	void Update(float dt);
	void Render(float dt);

private:
	SDL_Texture* paddleTexture;
};
