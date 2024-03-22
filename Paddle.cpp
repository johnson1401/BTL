#include "Paddle.h"

Paddle::Paddle(SDL_Renderer* paddle_renderer)
{
    renderer = paddle_renderer;
    SDL_Surface* surface = IMG_Load("paddleRed.png");
    PaddleTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    paddleSpeed = 1000.0f;

    width = 104;
    height = 24;

    x = 0;
    y = 600 - 24;
}



void Paddle::Render()
{
    SDL_Rect paddlerect;
    paddlerect.x = x;
    paddlerect.y = y;
    paddlerect.w = width;
    paddlerect.h = height;
    SDL_RenderCopy(renderer, PaddleTexture, 0, &paddlerect);
}
// Định nghĩa phương thức MoveLeft()
void Paddle::MoveLeft() {
    movingLeft = true;
}

// Định nghĩa phương thức StopMovingLeft()
void Paddle::StopMovingLeft() {
    movingLeft = false;
}

// Định nghĩa phương thức MoveRight()
void Paddle::MoveRight() {
    movingRight = true;
}

// Định nghĩa phương thức StopMovingRight()
void Paddle::StopMovingRight() {
    movingRight = false;
}

