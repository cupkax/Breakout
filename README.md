# Breakout 
A C++ breakout clone developed using SDL2 library.




SDL

SDL_image

SDL_ttf

Application Loop:
Upon calling the update function:
1. Game Window and Renderer are initialised through Init () and Run() is called.
2. In Run(), game assets are initialised, framerate as well as deltatime loop are configured and NewGame(), Update() and Render() is called.
3. In Update(), once game application begins, the player is able to move the paddle (with the ball stuck to the centre) on the x-axis and shoot the ball on Mouse Click, sending initial coordinates to BallDirection().
4. As the ball moves within the playfield, upon encountering the Top/Left/Right boundaries of the game window. A collision is carried out and the ball is reflected with respect to initial direction vector via CheckSidesCollision(). When ball collides with bottom boundary, LoseLife() is called, decrementing player life by 1 and resetting the ball and paddle position through ResetPaddle().
4. When ball hits the paddle, BallPaddleCollision() performs a collision check is carried to inspect location of the collision on the paddle. While BallPaddleReflection() adjust the reflection angle of the ball of colliding with the paddle.
5. Furthermore, when the ball hits a brick, a collision check allows the program to calculate the reflection response of the ball while destroying the brick in process with the help of CheckBallBrickCollision().
6. This loop is maintained until either a) no bricks are left on the playfield b) player lives are equal 0. When either condition is fulfilled, SDL_Quit is called and the program is terminated. Alongside, DumpDestroy() is called to free the allocated resources.
