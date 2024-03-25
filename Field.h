#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 1072;
const int SCREEN_HEIGHT = 600;

// Dimension of the brick
const int BRICK_WIDTH = 38 * 2;
const int BRICK_HEIGHT = 26;

// The number of bricks 14x10
const int BRICK_NUM_WIDTH = 14;
const int BRICK_NUM_HEIGHT = 10;

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

    void Render()
    {
        int i = 0;
        int j = 0;

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

    void createBricks()
    {
        srand(time(0)); // Randomizer

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
};

#endif // FIELD_H_INCLUDED
