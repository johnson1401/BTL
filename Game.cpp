#include "Game.h"
#include <math.h>

bool Game::Init()   //Initialize SDL
{
    bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
	else
	{

		//Create window
		window = SDL_CreateWindow(".><.",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window==NULL)
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}

        //Create renderer for window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }

        // Load background texture từ tệp hình ảnh
        backgroundTexture = IMG_LoadTexture(renderer, "background.jpg");
        if (backgroundTexture == NULL) {
        printf("Failed to load background texture! SDL Error: %s\n", SDL_GetError());
        success = false;
        }

        //create music
        music = Mix_LoadMUS( "kinhdi.mp3" );
        if( music == NULL)
        {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
        }

        //create sound effect
        sound = Mix_LoadWAV("sword.mp3");
        if( sound == NULL )
        {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
        }

    }
    lastframe = SDL_GetTicks();
    return success;
}


void Game::HandleKeyboardEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
                paddle->MoveLeft(); // Bắt đầu di chuyển paddle sang trái
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                paddle->MoveRight(); // Bắt đầu di chuyển paddle sang phải
                break;
            default:
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
                paddle->StopMovingLeft(); // Dừng di chuyển sang trái khi nhả phím
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                paddle->StopMovingRight(); // Dừng di chuyển sang phải khi nhả phím
                break;
            default:
                break;
        }
    }
}


void Game::Run() //How the game works
{
    field = new Field(renderer);
    paddle = new Paddle(renderer);
    ball = new Ball(renderer);

    StartGame();

    // Game loop
    while (1)
    {

        // Handler events
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                {
                break;          // break from while
                }
                else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            HandleKeyboardEvent(e);
            }
        }

        // delta timing
        curframe = SDL_GetTicks();
        float delta = (curframe - lastframe) / 1000.0f;
        lastframe = curframe;

        // Update and render the game
        Update(delta);
        Render();
        SDL_Delay(10);

        //Delay frame rates
        /*actualDelay = SDL_GetTicks() - startframe;
        if(FRAME_DELAY > actualDelay)
            SDL_Delay(FRAME_DELAY - actualDelay);*/

        if(isRunning == false)  // Game stops by a condition somewhere
            break;
    }

    delete paddle;          // Clean up if the game ended
    delete ball;
    delete field;

    CleanUp();
}

void Game::CleanUp()        // Clean up when the game ended
{
    Mix_FreeMusic(music);
    Mix_FreeChunk(sound);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    Mix_Quit();
}

void Game::StartGame()
{
    field->createBricks();
    ResetPaddle();
    PlayMusic();
}

void Game::ResetPaddle()
{
    Ball_on_Paddle = true;
    InitBall();
}

void Game::InitBall()
{
    ball->x = paddle->x + paddle->width/2 - ball->width/2;
    ball->y = paddle->y - ball->height;
}

void Game::Update(float delta)
{
    // Game logic

    // mouse handling
    int mouse_x, mouse_y;
    Uint32 mousestate = SDL_GetMouseState(&mouse_x, &mouse_y);
    //keyboard
    if (paddle->movingLeft) {
        SetPaddlePosition(paddle->x - paddle->paddleSpeed * delta);
    }
    else if (paddle->movingRight) {
        SetPaddlePosition(paddle->x + paddle->paddleSpeed * delta);
    }

    if ( mousestate == SDL_BUTTON(1) )   // click to start game
    {
        if (Ball_on_Paddle)         // ball leaves paddle
        {
            Ball_on_Paddle = false;
            ball->SetDirection(1, -1);
        }
    }

    if (Ball_on_Paddle)
    {
        InitBall();     // hold the ball on the paddle when move paddle
    }

    FieldCollision();       // handling collisions
    PaddleCollision();
    BrickCollision();
    BrickCollision();

    if (BrickCount() == BRICK_NUM_WIDTH * BRICK_NUM_HEIGHT)
    {
        GameWin();
        if(level < 3)
        {
            level++;
            ball->speed += 150;        // Ball go faster
            StartGame();
        }
    }

    if (!Ball_on_Paddle)
    {
        ball->Update(delta);
    }
    ShowScore();
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    field->Render();
    paddle->Render();
    ball->Render();
    SDL_RenderPresent(renderer);
}

void Game::SetPaddlePosition(float x)       // Set the x rect of paddle
{
    float out_x;   // x for the output wanted

    // keep the paddle inside of the field
    if (x < field->x)
    {
        // Left
        out_x = field->x;
                }
        else if (x + paddle->width > field->x + field->width)
        {
            // Right
            out_x = field->x + field->width - paddle->width;
        }
        else
        {
            out_x = x;
        }
        paddle->x = out_x;
    }
void Game::SetPaddlePositionFromKeyboard() {
    if (paddle->movingLeft) {
        paddle->MoveLeft();
    }
    else if (paddle->movingRight) {
        paddle->MoveRight();
    }
}

void Game::FieldCollision()
{
    if (ball->y < field->y)     // Hit top wall
    {
        // Top
        ball->y = field->y;
        ball->dirY *= -1;
    }
    else if (ball->y + ball->height > field->y + field->height)
    {
        // Reach the void

        // Bottom
        if(life > 0)
        {
            ResetPaddle(); //GameOver();
            life--;
        }
        else
            GameLost();
    }

    if (ball->x < field->x)
    {
        // Left
        ball->x = field->x;
        ball->dirX *= -1;
    }
    else if (ball->x + ball->width > field->x + field->width)
    {
        // Right
        ball->x = field->x + field->width - ball->width;
        ball->dirX *= -1;
    }
}

void Game::BrickCollision() {
    for (int i=0; i<BRICK_NUM_WIDTH; i++) {
        for (int j=0; j<BRICK_NUM_HEIGHT; j++) {

            // Check if brick is present
            if (field->bricks[i][j].isAlive) {
                // Brick x and y coordinates
                float brickx = field->x + i*BRICK_WIDTH;
                float bricky = field->y + j*BRICK_HEIGHT;

                float w = 0.5f * (ball->width + BRICK_WIDTH); // Ball width + Brick width
                float h = 0.5f * (ball->height + BRICK_HEIGHT);
                float dx = (ball->x + 0.5f*ball->width) - (brickx + 0.5f*BRICK_WIDTH);    // Ball center - Brick center
                float dy = (ball->y + 0.5f*ball->height) - (bricky + 0.5f*BRICK_HEIGHT);

                if (fabs(dx) <= w && fabs(dy) <= h) {
                    // Collision detected
                    PlaySoundEffect();
                    field->bricks[i][j].isAlive = false;

                    float wy = w * fabs(dy);
                    float hx = h * fabs(dx);

                    if (wy > hx)
                    {
                        if (dy < 0)
                        {
                            // Top (axis reversed)
                            SideCollision(1);
                        }
                        else
                        {
                            // Bottom
                            SideCollision(3);
                        }
                    }
                    else
                    {
                        if (dx < 0)
                        {
                            // Left
                            SideCollision(0);
                        }
                        else
                        {
                            // Right
                            SideCollision(2);
                        }
                    }
                    return;
                }
            }
        }
    }
}

void Game::SideCollision(int sidehit)       //Solving bugs involving hitting the intersection of 2 bricks
{
    // sidehit 0: Left, 1: Top, 2: Right, 3: Bottom

    // coeficient factor
    int cx = 1;
    int cy = 1;

    if (ball->dirX > 0)
    {
        if (ball->dirY > 0)
        {
            // +1 +1
            if (sidehit == 0 || sidehit == 3)
            {
                cx = -1;
            }
            else
            {
                cy = -1;
            }
        }
        else if (ball->dirY <= 0)
        {
            // +1 -1
            if (sidehit == 0 || sidehit == 1)
            {
                cx = -1;
            }
            else
            {
                cy = -1;
            }
        }
    }
    else if (ball->dirX <= 0)
    {
        if (ball->dirY > 0)
            {
            // -1 +1
            if (sidehit == 2 || sidehit == 3)
            {
                cx = -1;
            }
            else
            {
                cy = -1;
            }
        }
        else if (ball->dirY <= 0)
        {
            // -1 -1
            if (sidehit == 1 || sidehit == 2)
            {
                cx = -1;
            }
            else
            {
                cy = -1;
            }
        }
    }
    // Set the new direction by multiplying the coefficient
    ball->SetDirection(cx*ball->dirX, cy*ball->dirY);
}

void Game::PaddleCollision()
{
    // center of the ball
    float ballcenterx = ball->x + ball->width / 2.0f;

    // Check paddle collision
    if (ball->x + ball->width > paddle->x &&
        ball->x < paddle->x + paddle->width &&
        ball->y + ball->height > paddle->y &&
        ball->y < paddle->y + paddle->height)
    {
        ball->y = paddle->y - ball->height;
        ball->SetDirection(Reflection(ballcenterx - paddle->x), -1);
    }
}

float Game::Reflection(float x) // range of x from 0 to paddle->width
{

    // Everything to the left of the center of the paddle is reflected to the left and vice versa
    x -= paddle->width / 2.0f;

    // range of -1 to 1
    return  x / (paddle->width / 2.0f);
}


int Game::BrickCount()  //count the destroyed bricks
{
    int brickcount = 0;
    for (int i=0; i<BRICK_NUM_WIDTH; i++)
    {
        for (int j=0; j<BRICK_NUM_HEIGHT; j++)
        {
            if (field->bricks[i][j].isAlive == false)
                brickcount++;
        }
    }

    return brickcount;
}

void Game::PlayMusic()
{
    if( Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_PlayMusic(music, -1);
    }
}

void Game::PlaySoundEffect()
{
    Mix_PlayChannel(-1, sound, 0);
}

void Game::StopMusic()
{
    Mix_HaltMusic();
}

void Game::ShowScore()
{
    int score = BrickCount() * 100;
    std::stringstream textscore;
    textscore << "BrickBreaker                                                                            SCORE: " << score <<"       ||        LIFE: "<<life;

    SDL_SetWindowTitle( window, textscore.str().c_str());       //Put score on window title
}

void Game::GameLost()
{
    StopMusic();
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game over", "You lose! Restart the game to try again!", window);
    isRunning = false;
}

void Game::GameWin()
{
    if(level == 1)
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "LEVEL 1 PASSED!", "You finished level 1! Hit OK to try the next level", window);
    else if(level == 2)
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "LEVEL 2 PASSED!", "You finished level 2! Hit OK to try the next level", window);
    else
    {
        StopMusic();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You win", "You win! Restart the game to try again!", window);
        isRunning = false;
    }
}

/*void Game::ShowHitSpot()
{
    std::cout<<HitSpot<<" ";
}*/

