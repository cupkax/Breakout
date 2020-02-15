#ifndef COMMON_H_
#define COMMON_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>


class Common {
public:
	Common(SDL_Renderer* renderer);
	virtual ~Common();

	float posX, posY, width, height;

	virtual void Update(float delta);
	virtual void Render(float delta);

	bool Collides(Common* other);
protected:
	SDL_Renderer* renderer;

};

#endif // !COMMON_H_