#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED


#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>


const int SCREEN_WIDTH = 1080;
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
    int color1, color2; // Mau sac
    bool isAlive;       // Gach duoc render hay k
};


struct Field
{
    float x, y, width, height; // Toa do, kich thuoc field

    Brick bricks[BRICK_NUM_WIDTH][BRICK_NUM_HEIGHT]; // Mang de render brick

    SDL_Texture* brickTexture; //
    SDL_Texture* sideTexture; // T
    SDL_Renderer* renderer; // Renderer

   Field(SDL_Renderer* rendererField)
{
    renderer = rendererField;

    brickTexture = IMG_LoadTexture(renderer, "Breakout_Tile_Free.png");
    sideTexture = IMG_LoadTexture(renderer, "side.png");
    if (sideTexture == NULL) std::cerr << "Errorrside";

    x = 8;
    y = 0;
    width = SCREEN_WIDTH - 2 * x;
    height = SCREEN_HEIGHT;
}
~Field()
   {
        SDL_DestroyTexture(brickTexture);
        SDL_DestroyTexture(sideTexture);
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
    SDL_Rect sideRect;
    sideRect.x = 0;                    // Left
    sideRect.y = 0;
    sideRect.w = 8;
    sideRect.h = 600;
    SDL_RenderCopy(renderer, sideTexture, &sourceRect, &sideRect);

    sideRect.x = SCREEN_WIDTH - 8;     // Rhight
    sideRect.y = 0;
    sideRect.w = 8;
    sideRect.h = 600;
    SDL_RenderCopy(renderer, sideTexture, &sourceRect, &sideRect);


    // Render
    if (level == 2) // render cac hinh anh theo theo 1 hinh chu nhat, sat nhau
    {
        for (int i = 0; i < BRICK_NUM_WIDTH; ++i)
         {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j)
            {
                if (bricks[i][j].isAlive)
                {
                    sourceRect.x = bricks[i][j].color1 * 380;   //380 = chieurong 1 texture gach trong anh
                    sourceRect.y = bricks[i][j].color2 * 125;   //125 = chieucao
                    destinationRect.x = x + i * BRICK_WIDTH;
                    destinationRect.y = y + j * BRICK_HEIGHT;
                    SDL_RenderCopy(renderer, brickTexture, &sourceRect, &destinationRect);
                }
            }
        }
    }
    else if (level == 3)
    {
        float radius = RADIUS_OUTER * BRICK_WIDTH; // Doi ban kinh sang pixel
        float center_x_pixel = center_x * BRICK_WIDTH + x; // Tính toạ độ x của tâm hình tròn trong pixel
        float center_y_pixel = center_y * BRICK_HEIGHT + y; // Tinh toa do y tam hinh tron

        for (int i = 0; i < BRICK_NUM_WIDTH; ++i)
        {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j)
            {
                float brick_center_x = (i + 0.5) * BRICK_WIDTH + x;         // tim tam cua tung vien gach
                float brick_center_y = (j + 0.5) * BRICK_HEIGHT + y;
                // khoanh cach tam vien gach den tam hinh tron
                float distance = sqrt((brick_center_x - center_x_pixel) * (brick_center_x - center_x_pixel) + (brick_center_y - center_y_pixel) * (brick_center_y - center_y_pixel));

                if (distance <= radius && bricks[i][j].isAlive)
                {
                    // neu vien gach nam trong hinh tron
                    sourceRect.x = bricks[i][j].color1 * 380;
                    sourceRect.y = bricks[i][j].color2 * 125;
                    destinationRect.x = x + i * BRICK_WIDTH;
                    destinationRect.y = y + j * BRICK_HEIGHT;
                    SDL_RenderCopy(renderer, brickTexture, &sourceRect, &destinationRect);
                }
            }
        }
    }
    else if (level == 1)
    {
        for (int i = 0; i < BRICK_NUM_WIDTH; i+=2)
         {
            for (int j = 0; j < BRICK_NUM_HEIGHT; j+=2)
            {
                if (bricks[i][j].isAlive)
                {
                    sourceRect.x = bricks[i][j].color1 * 380;
                    sourceRect.y = bricks[i][j].color2 * 125;
                    destinationRect.x = x + i * BRICK_WIDTH;
                    destinationRect.y = y + j * BRICK_HEIGHT;
                    SDL_RenderCopy(renderer, brickTexture, &sourceRect, &destinationRect);
                }
            }
        }

    }





}

void createBricks(int level)
{
    srand(time(0)); // Reset lich su

    if (level == 2)
    {
        // Tao hcn
        for (int i = 0; i < BRICK_NUM_WIDTH; ++i)
        {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j)
            {
                bricks[i][j].color1 = rand() % 3;
                bricks[i][j].color2 = rand() % 3; //
                bricks[i][j].isAlive = true;      //
            }
        }
    }
    else if (level == 3)
    {
        // Hinh tron
        for (int i = 0; i < BRICK_NUM_WIDTH; ++i)
        {
            for (int j = 0; j < BRICK_NUM_HEIGHT; ++j)
            {
                float brick_center_x = i + 0.5; // tim tam vien gach
                float brick_center_y = j + 0.5;
                float distance = sqrt((brick_center_x - center_x) * (brick_center_x - center_x) +
                                      (brick_center_y - center_y) * (brick_center_y - center_y)); // tim khoang cach tam gach den tam hinh tron
                if (distance <= RADIUS_OUTER && distance >= RADIUS_INNER)
                {
                    bricks[i][j].color1 = rand() % 3;   // color dung de lay vi tri hinh anh vien gach can duoc load o trong file source
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
    else if (level == 1)
    {
        for (int i = 0; i < BRICK_NUM_WIDTH; i+=2)
        {
            for (int j = 0; j < BRICK_NUM_HEIGHT; j+=2)
            {
                bricks[i][j].color1 = rand() % 3;
                bricks[i][j].color2 = rand() % 3; //
                bricks[i][j].isAlive = true;      //
            }
        }


    }
}

};

#endif // FIELD_H_INCLUDED
