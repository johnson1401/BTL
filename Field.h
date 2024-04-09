#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED


#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>


const int SCREEN_WIDTH = 1072;
const int SCREEN_HEIGHT = 600;

// Dimension of the brick
const int BRICK_WIDTH = 38 * 2;
const int BRICK_HEIGHT = 26;

// The number of bricks 14x10
const int BRICK_NUM_WIDTH = 14;
const int BRICK_NUM_HEIGHT = 10;


const float center_x = BRICK_NUM_WIDTH / 2.0;
const float center_y = BRICK_NUM_HEIGHT / 2.0;
const int RADIUS_OUTER = 7;
const int RADIUS_INNER = 3;

struct Brick
{
    int color1, color2; // Color
    bool isAlive;       // Whether the brick is alive or dead
};

struct Field
{
    float x, y, width, height;

    Brick bricks[BRICK_NUM_WIDTH][BRICK_NUM_HEIGHT];

    SDL_Texture* brickTexture;
    SDL_Texture* sideTexture;
    SDL_Renderer* renderer;

   Field(SDL_Renderer* fieldRenderer)
{
    renderer = fieldRenderer;

    brickTexture = IMG_LoadTexture(renderer, "Breakout_Tile_Free.png");
    sideTexture = IMG_LoadTexture(renderer, "side.png");

    x = 8;
    y = 0;
    width = SCREEN_WIDTH - 2 * x;
    height = SCREEN_HEIGHT;
}

    void Render(int level)
    {
        int i = 0;
        int j = 0;
       if (level == 1)
       {


        // Render bricks using while loop
        while (i < BRICK_NUM_WIDTH)
        {
            j = 0;
            while (j < BRICK_NUM_HEIGHT)
            {
                if (bricks[i][j].isAlive)
                {
                    SDL_Rect sourceRect;
                    sourceRect.x = bricks[i][j].color1 * 380; // Source rect
                    sourceRect.y = bricks[i][j].color2 * 125;
                    sourceRect.w = 380;
                    sourceRect.h = 125;

                    SDL_Rect destinationRect;
                    destinationRect.x = x + i * BRICK_WIDTH; // Destination rect
                    destinationRect.y = j * BRICK_HEIGHT;
                    destinationRect.w = BRICK_WIDTH;
                    destinationRect.h = BRICK_HEIGHT;

                    SDL_RenderCopy(renderer, brickTexture, &sourceRect, &destinationRect);
                }
                ++j;
            }
            ++i;
        }




       }


       if (level == 2)
       {



        // Render bricks using while loop
        while (i < BRICK_NUM_WIDTH)
        {
            j = 0;
            while (j < BRICK_NUM_HEIGHT)
            {
            float distance = sqrt((i - center_x) * (i - center_x) + (j - center_y) * (j - center_y));
             if (distance <= RADIUS_OUTER && distance >= RADIUS_INNER)
             {


                if (bricks[i][j].isAlive)
                {
                    SDL_Rect sourceRect;
                    sourceRect.x = bricks[i][j].color1 * 380; // Source rect
                    sourceRect.y = bricks[i][j].color2 * 125;
                    sourceRect.w = 380;
                    sourceRect.h = 125;

                    SDL_Rect destinationRect;
                    destinationRect.x = x + i * BRICK_WIDTH; // Destination rect
                    destinationRect.y = j * BRICK_HEIGHT;
                    destinationRect.w = BRICK_WIDTH;
                    destinationRect.h = BRICK_HEIGHT;

                    SDL_RenderCopy(renderer, brickTexture, &sourceRect, &destinationRect);
                }
             }
                ++j;
            }
            ++i;
        }
       }

        // Render sides
        SDL_Rect realRect;
        realRect.x = 0;
        realRect.y = 0;
        realRect.w = 33;
        realRect.h = 128;

        SDL_Rect sideRect;
        sideRect.x = 0;                    // Left
        sideRect.y = 0;
        sideRect.w = 8;
        sideRect.h = 600;
        SDL_RenderCopy(renderer, sideTexture, &realRect, &sideRect);

        sideRect.x = SCREEN_WIDTH - 8;     // Right
        sideRect.y = 0;
        sideRect.w = 8;
        sideRect.h = 600;
        SDL_RenderCopy(renderer, sideTexture, &realRect, &sideRect);
    }
void createBricks(int level)

    {
        srand(time(0)); // Randomizer


        // Tạo các bricks theo hình tròn đồng tâm
    if (level == 1)
    {


        int i = 0;
        int j = 0;

        // Generate bricks using while loop
        while (i < BRICK_NUM_WIDTH)
        {
            j = 0;
            while (j < BRICK_NUM_HEIGHT)
            {
                bricks[i][j].color1 = rand() % 3;
                bricks[i][j].color2 = rand() % 3; // Random color
                bricks[i][j].isAlive = true;      // Brick is alive
                ++j;
            }
            ++i;
        }
    }
    else if (level == 2)
    {

        int i = 0;
        int j = 0;
        while (i < BRICK_NUM_WIDTH)
        {
            j = 0;
            while (j < BRICK_NUM_HEIGHT)
            {
                // Tính khoảng cách từ brick hiện tại đến tâm
                float distance = sqrt((i - center_x) * (i - center_x) + (j - center_y) * (j - center_y));

                // Kiểm tra xem brick có thuộc vào hình tròn không
                if (distance <= RADIUS_OUTER && distance >= RADIUS_INNER)
                {
                    // Gán màu sắc và trạng thái sống cho brick
                    bricks[i][j].color1 = rand() % 3;
                    bricks[i][j].color2 = rand() % 3;
                    bricks[i][j].isAlive = true;
                }
                else
                {
                    // Nếu không thuộc hình tròn, đặt trạng thái sống của brick là false
                    bricks[i][j].isAlive = false;
                }

                ++j;
            }
            ++i;
        }
      }
    }
};


#endif // FIELD_H_INCLUDED
