#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <cmath>

struct Ball
{

   Ball(SDL_Renderer* ballRenderer) : renderer(ballRenderer) {  // khoi tao thanh vien
    x = 0;
    y = 0;
    width = 48;
    height = 48;
    speed = 500;
    dirX = 0;
    dirY = 0;
    ballTexture = nullptr;

    ballTexture = IMG_LoadTexture(renderer, "ball1.png");
    }
    ~Ball() {
        // Clean resources
        if (ballTexture != nullptr) {
            SDL_DestroyTexture(ballTexture);
        }
    }

    void Update(float delta) {
        x += dirX * delta;
        y += dirY * delta;
    }

    void Render() {
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

    SDL_RenderCopy(renderer, ballTexture, &src, &dest);
    }

    void SetDirection(float _dirX, float _dirY) {
        // Normalize the direction vector then multiply speed
        float length = std::sqrt(_dirX * _dirX + _dirY * _dirY);
        dirX = _dirX / length * speed;
        dirY = _dirY / length * speed;
    }


    SDL_Renderer* renderer;
    SDL_Texture* ballTexture;
    float x, y, width, height;
    float speed;
    float dirX, dirY; // Direction vector
};

#endif // BALL_H_INCLUDED
