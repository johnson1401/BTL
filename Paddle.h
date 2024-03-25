#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

struct Paddle
{

  Paddle(SDL_Renderer* renderer) : renderer(renderer) {
      width = 108;
      height = 24;
      x = 0;
      y = 600 - height;

      paddleSpeed = 1000.0f ;
      movingLeft = false ;
      movingRight = false ;
      PaddleTexture= IMG_LoadTexture(renderer, "PaddleRed.png");

    if (PaddleTexture == nullptr) {
        // Xử lý lỗi nếu không tải được texture
        // Ví dụ: đóng ứng dụng hoặc ghi ra console
        SDL_Log("Failed to load paddle texture: %s", SDL_GetError());
        }
    }


    ~Paddle() {
        // Clean resources
        if (PaddleTexture != nullptr) {
            SDL_DestroyTexture(PaddleTexture);
        }
    }

    void Render() {
        SDL_Rect paddlerect;
        paddlerect.x = x;
        paddlerect.y = y;
        paddlerect.w = width;
        paddlerect.h = height;
        SDL_RenderCopy(renderer, PaddleTexture, nullptr, &paddlerect);
    }

    // Move left
    void MoveLeft() {
        movingLeft = true;
    }

    // Stop moving left
    void StopMovingLeft() {
        movingLeft = false;
    }

    // Move right
    void MoveRight() {
        movingRight = true;
    }

    // Stop moving right
    void StopMovingRight() {
        movingRight = false;
    }

    SDL_Renderer* renderer;
    SDL_Texture* PaddleTexture;
    float x, y, width, height;
    float paddleSpeed;
    bool movingLeft;
    bool movingRight;
};

#endif // PADDLE_H_INCLUDED
