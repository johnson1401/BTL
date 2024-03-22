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
    // Thêm phương thức để di chuyển paddle sang trái
    void MoveLeft();

    // Thêm phương thức để dừng di chuyển sang trái
    void StopMovingLeft();

    // Thêm phương thức để di chuyển paddle sang phải
    void MoveRight();

    // Thêm phương thức để dừng di chuyển sang phải
    void StopMovingRight();
    bool movingLeft = false;
    bool movingRight = false;
    float paddleSpeed;
};

#endif // PADDLE_H_INCLUDED
