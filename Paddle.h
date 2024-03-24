#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

struct Paddle
{

    Paddle(SDL_Renderer* renderer);


    float x, y, width, height;

    void Render();


    SDL_Texture* PaddleTexture;
    SDL_Renderer* renderer;
    // sang trai
    void MoveLeft();


    void StopMovingLeft();

    // sang phai
    void MoveRight();


    void StopMovingRight();


    bool movingLeft = false;
    bool movingRight = false;
    float paddleSpeed;
};

#endif // PADDLE_H_INCLUDED
