#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <bits/stdc++.h>

struct Ball
{
   // Constructor của Ball, khởi tạo các thành viên và tải texture của quả bóng
   Ball(SDL_Renderer* ballRenderer) : renderer(ballRenderer)
   {
    x = 0; // Toa do x cua qua bong
    y = 0; // Toa do y cua qua bong
    width = 48; // Do rong cua qua bong
    height = 48; // Do cao cua qua bong
    speed = 500; // Toc do cua qua bong
    dirX = 0; // Huong di chuyen theo truc x
    dirY = 0; // Huong di chuyen theo truc y
    ballTexture = nullptr; // Khoi tao texture cua qua bong

    // Tai texture cua qua bong tu tep hinh anh
    ballTexture = IMG_LoadTexture(renderer,"ball1.png");
   }

   // Destructor của Ball, giải phóng bộ nhớ khi kết thúc
   ~Ball()
   {
        // Giải phóng tài nguyên của texture
        if (ballTexture != nullptr)
        {
            SDL_DestroyTexture(ballTexture);
        }
   }

    // Cap nhat vi tri cua qua bong dua tren delta time
    void Update(float delta)
    {
        x += dirX * delta; // Cap nhat toa do x
        y += dirY * delta; // Cap nhat toa do y
    }

    // Ve qua bong len man hinh
    void Render()
    {
        SDL_Rect src; // Source rect
        src.x = 0;
        src.y = 0;
        src.w = 200;
        src.h = 200;

        SDL_Rect dest; // Destination rect
        dest.x = x;
        dest.y = y;
        dest.w = width;
        dest.h = height;

        // Ve qua bong len renderer
        SDL_RenderCopy(renderer, ballTexture, &src, &dest);
    }

    // Thiet lap huong di chuyen cua qua bong
    void SetDirection(float _dirX, float _dirY)
    {
        // Chuan hoa vector huong sau do nhan voi toc do
        float length = std::sqrt(_dirX * _dirX + _dirY * _dirY);
        dirX = _dirX / length * speed;
        dirY = _dirY / length * speed;
    }

    SDL_Renderer* renderer; // Renderer
    SDL_Texture* ballTexture; // Texture cua qua bong
    float x, y, width, height; // Toa do va kich thuoc cua qua bong
    float speed; // Toc do cua qua bong
    float dirX, dirY; // Huong di chuyen cua qua bong
};

#endif // BALL_H_INCLUDED
