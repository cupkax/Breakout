#include "main.h"

int main(int argc, char* argv[])
{
	// Create breakout game object
	Breakout* breakout = new Breakout();

	// Initialize SDL and Breakout
	if (breakout->Init())
	{
		breakout->Run();
	}

	delete breakout;
	return 0;
}