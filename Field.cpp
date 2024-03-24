#include "Field.h"
#include "Game.h"

Field::Field(SDL_Renderer* field_renderer)
{
    renderer = field_renderer;      //Field::renderer = Game::renderer
    SDL_Surface* surface = IMG_Load("Breakout_Tile_Free.png");
    BrickTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("side.png");
    SideTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    x = 8;
    y = 0;
    width = SCREEN_WIDTH - 2*8;
    height = SCREEN_HEIGHT;
}

Field::~Field()
{};

void Field::Render() {
    // Render bricks
    for (int i=0; i < BRICK_NUM_WIDTH; i++)
    {
        for (int j=0; j < BRICK_NUM_HEIGHT; j++)
        {
            if (bricks[i][j].condition)
            {
                SDL_Rect srcrect;
                srcrect.x = bricks[i][j].color1 * 380 ;        //source rect
                srcrect.y = bricks[i][j].color2*125;
                srcrect.w = 380;
                srcrect.h = 125;













                SDL_Rect dstrect;
                dstrect.x = x + i * BRICK_WIDTH ;                    //destination rect
                dstrect.y = j * BRICK_HEIGHT ;
                dstrect.w = BRICK_WIDTH;
                dstrect.h = BRICK_HEIGHT;

                SDL_RenderCopy(renderer, BrickTexture, &srcrect, &dstrect);
            }
        }
    }

    // Render sides
    SDL_Rect realrect;
    realrect.x = 0;
    realrect.y = 0;
    realrect.w = 33;
    realrect.h = 128;

    SDL_Rect siderect;
    siderect.x = 0;                     //Left
    siderect.y = 0;
    siderect.w = 8;
    siderect.h = 600;
    SDL_RenderCopy(renderer, SideTexture, &realrect , &siderect);

    siderect.x = SCREEN_WIDTH-8;              //Right
    siderect.y = 0;
    siderect.w = 8;
    siderect.h = 600;
    SDL_RenderCopy(renderer, SideTexture, &realrect, &siderect);
}

void Field::CreateBricks()
{
    srand(time(0));         //Randomizer

    for (int i=0; i < BRICK_NUM_WIDTH; i++)
    {
        for (int j=0; j < BRICK_NUM_HEIGHT; j++)
        {
            bricks[i][j].color1 = rand() % 3;
            bricks[i][j].color2 = rand() % 3;    // Random color
            bricks[i][j].condition = true;       // Brick is born
        }
    }
}
