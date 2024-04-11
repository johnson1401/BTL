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
    SDL_Rect sourceRect;
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = 380;
    sourceRect.h = 125;

    SDL_Rect destinationRect;
    destinationRect.w = BRICK_WIDTH;
    destinationRect.h = BRICK_HEIGHT;

    // Render bricks
    if (level == 1) {
        for (int i = 0; i < BRICK_NUM_WIDTH; ++i) {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j) {
                if (bricks[i][j].isAlive) {
                    sourceRect.x = bricks[i][j].color1 * 380;
                    sourceRect.y = bricks[i][j].color2 * 125;
                    destinationRect.x = x + i * BRICK_WIDTH;
                    destinationRect.y = y + j * BRICK_HEIGHT;
                    SDL_RenderCopy(renderer, brickTexture, &sourceRect, &destinationRect);
                }
            }
        }
    }
    else if (level == 2) {
        float radius = RADIUS_OUTER * BRICK_WIDTH; // Convert the radius to pixel units
        float center_x_pixel = center_x * BRICK_WIDTH + x;
        float center_y_pixel = center_y * BRICK_HEIGHT + y;

        for (int i = 0; i < BRICK_NUM_WIDTH; ++i) {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j) {
                float brick_center_x = (i + 0.5) * BRICK_WIDTH + x;
                float brick_center_y = (j + 0.5) * BRICK_HEIGHT + y;
                float distance = sqrt((brick_center_x - center_x_pixel) * (brick_center_x - center_x_pixel) +
                                      (brick_center_y - center_y_pixel) * (brick_center_y - center_y_pixel));

                if (distance <= radius && bricks[i][j].isAlive) {
                    sourceRect.x = bricks[i][j].color1 * 380;
                    sourceRect.y = bricks[i][j].color2 * 125;
                    destinationRect.x = x + i * BRICK_WIDTH;
                    destinationRect.y = y + j * BRICK_HEIGHT;
                    SDL_RenderCopy(renderer, brickTexture, &sourceRect, &destinationRect);
                }
            }
        }
    }

    // Render sides
    SDL_Rect sideRect;
    sideRect.x = 0;                    // Left
    sideRect.y = 0;
    sideRect.w = 8;
    sideRect.h = 600;
    SDL_RenderCopy(renderer, sideTexture, &sourceRect, &sideRect);

    sideRect.x = SCREEN_WIDTH - 8;     // Right
    sideRect.y = 0;
    sideRect.w = 8;
    sideRect.h = 600;
    SDL_RenderCopy(renderer, sideTexture, &sourceRect, &sideRect);
}



void createBricks(int level)
{
    srand(time(0)); // Randomizer

    if (level == 1)
    {
        // Tạo các bricks theo hình chữ nhật
        for (int i = 0; i < BRICK_NUM_WIDTH; ++i)
        {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j)
            {
                bricks[i][j].color1 = rand() % 3;
                bricks[i][j].color2 = rand() % 3; // Random color
                bricks[i][j].isAlive = true;      // Brick is alive
            }
        }
    }
    else if (level == 2)
    {
        // Tạo các bricks theo hai vòng tròn đồng tâm
        for (int i = 0; i < BRICK_NUM_WIDTH; ++i)
        {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j)
            {
                float brick_center_x = i + 0.5;
                float brick_center_y = j + 0.5;
                float distance = sqrt((brick_center_x - center_x) * (brick_center_x - center_x) +
                                      (brick_center_y - center_y) * (brick_center_y - center_y));
                if (distance <= RADIUS_OUTER && distance >= RADIUS_INNER)
                {
                    bricks[i][j].color1 = rand() % 3;
                    bricks[i][j].color2 = rand() % 3;
                    bricks[i][j].isAlive = true;
                }
                else
                {
                    bricks[i][j].isAlive = false;
                }
            }
        }
    }
}

};


#endif // FIELD_H_INCLUDED
