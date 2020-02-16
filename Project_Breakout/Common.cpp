#include "Common.h"

Common::Common(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	posX = 0;
	posY = 0;
	width = 1;
	height = 1;
}

Common::~Common()
{

}

void Common::Update(float delta)
{

}

void Common::Render(float delta)
{

}

// Collision
//bool Common::Collides(Common* other)
//{
//	if (posX + width > other->posX&& posX < other->posX + other->width &&
//		posY + height > other->posY&& posY < other->posY + other->height) {
//		return true;
//	}
//	return false;
//}