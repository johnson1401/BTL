#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

struct Ball
{
public:
    Ball(SDL_Renderer* renderer);
    ~Ball();

    float x, y, width, height;
    float BALL_SPEED = 500;

    void Update(float delta);
    void Render();

    void SetDirection(float dirx, float diry);

    float dirx, diry; //direction vector

private:
    SDL_Texture* BallTexture;
    SDL_Renderer* renderer;
};

#endif
