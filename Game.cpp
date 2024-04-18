#include "Game.h"
#include <math.h>
#include "Menu.h"



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
     if (TTF_Init() == -1)
            {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
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
       font = TTF_OpenFont("font.ttf",24);
       if (font == nullptr)
        {
            std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
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

    Menu* menu = new Menu(renderer);
    menu->InitMenu();
    menu->RenderMenu();
    while (!isRunning) {
        // Handle events for the menu
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
                CleanUp();
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                menu->HandleMouseClick(e,level);
                if (!menu->showMenu) {
                    isRunning = true; // Start the game loop if menu is no longer active
                    std::cerr << level ;
                }
            }
        }
        if (isRunning) StartGame();


        SDL_Delay(10); // Delay frame rates
    }

    // Clean up menu after exiting loop
    delete menu;






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
                else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
                    {
                            HandleKeyboardEvent(e);
                    }
        }

        // delta timing
        curframe = SDL_GetTicks();
        float delta = (curframe - lastframe) / 800.0f;
        lastframe = curframe;

        // Update and render the game

        Update(delta);

        Render();

        SDL_Delay(10);



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
    field->createBricks(level);
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
            ball->SetDirection(1, 10);
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
    UpdateHUDTextures();

}
void Game::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    field->Render(level);
    paddle->Render();
    ball->Render();

    ShowHUD(); // showscore

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
    // Left and right collisions
    if (ball->x < field->x)
    {
        // Left
        ball->x = field->x;
        ball->dirX *= -1;
    }
    else if (ball->x + ball->width >= field->x + field->width)
    {
        // Right
        ball->x = field->x + field->width - ball->width;
        ball->dirX *= -1;
    }
}

void Game::BrickCollision()
{
    bool continueChecking = true; // Flag to continue checking collisions

    for (int i = 0; i < BRICK_NUM_WIDTH && continueChecking; i++)
    {
        for (int j = 0; j < BRICK_NUM_HEIGHT && continueChecking; j++)
        {
            if (field->bricks[i][j].isAlive)
            {
                // Brick x and y coordinates
                float brickx = field->x + i * BRICK_WIDTH;
                float bricky = field->y + j * BRICK_HEIGHT;

                float w = 0.5f * (ball->width + BRICK_WIDTH); // Ball width + Brick width
                float h = 0.5f * (ball->height + BRICK_HEIGHT);
                float dx = (ball->x + 0.5f * ball->width) - (brickx + 0.5f * BRICK_WIDTH); // Ball center - Brick center
                float dy = (ball->y + 0.5f * ball->height) - (bricky + 0.5f * BRICK_HEIGHT);

                if (fabs(dx) <= w && fabs(dy) <= h)
                {
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
                    continueChecking = false; // Stop checking collisions
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
    // tam bong
    float ballcenterx = ball->x + ball->width / 1.9f;

    // Check paddle collision
        float bongx = ball->x + ball->width;
        float vanx = paddle->x + paddle->width;
        float bongy = ball->y + ball->height;
        float vany = paddle->y + paddle->height;


    if (bongx > paddle->x &&  ball->x < vanx && bongy > paddle->y && ball->y < vany)
    {
        ball->y = paddle->y - ball->height;
        ball->SetDirection(Reflection(ballcenterx - paddle->x), -1);
    }
}

float Game::Reflection(float x)
{

    // phan lai dua tren duong di toi
    x -= paddle->width / 2.0f;

    // range tu -1.5 den 1.5
    return  x / (paddle->width / 2.0f) * 1.5f;
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

// score

void Game::UpdateHUDTextures() {
    // Update score texture
    std::stringstream scoreText;
    SDL_Color scoreColor = {0, 255, 255}; // Màu xanh dương cho điểm số

    int totalBricks = 0;
    int destroyedBricks = 0;

    for (int i = 0; i < BRICK_NUM_WIDTH; ++i) {
        for (int j = 0; j < BRICK_NUM_HEIGHT; ++j) {
            if (field->bricks[i][j].isAlive)
                totalBricks++;

            if (!field->bricks[i][j].isAlive)
                destroyedBricks++;
        }
    }

    playerScore = destroyedBricks * 100;
    if (level == 2) playerScore -= 4400;

    scoreText << "SCORE: " << playerScore ;

    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), scoreColor);

    if (scoreSurface == nullptr) {
        std::cerr << "Failed to create score surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    if (scoreTexture != nullptr) {
        SDL_DestroyTexture(scoreTexture);
    }

    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);

    // Update life texture
    std::stringstream lifeText;
    SDL_Color lifeColor = {255, 0, 0}; // Màu đỏ cho mạng số lượt chơi

    lifeText << "LIFE: " << life;

    SDL_Surface *lifeSurface = TTF_RenderText_Solid(font, lifeText.str().c_str(), lifeColor);

    if (lifeSurface == nullptr) {
        std::cerr << "Failed to create life surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    if (lifeTexture != nullptr) {
        SDL_DestroyTexture(lifeTexture);
    }

    lifeTexture = SDL_CreateTextureFromSurface(renderer, lifeSurface);
    SDL_FreeSurface(lifeSurface);
}
void Game::ShowHUD() {
    // Kiểm tra xem texture điểm số và mạng số lượt chơi đã được cập nhật chưa
    if (scoreTexture == nullptr || lifeTexture == nullptr) {
        // Nếu chưa, cập nhật texture điểm số và mạng số lượt chơi
        UpdateHUDTextures();
    }

    // Kiểm tra lại sau khi cập nhật
    if (scoreTexture != nullptr && lifeTexture != nullptr) {
        // Lấy kích thước của texture điểm số và mạng số lượt chơi
        int scoreTextureWidth, scoreTextureHeight;
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreTextureWidth, &scoreTextureHeight);

        int lifeTextureWidth, lifeTextureHeight;
        SDL_QueryTexture(lifeTexture, NULL, NULL, &lifeTextureWidth, &lifeTextureHeight);

        // Vị trí để vẽ texture điểm số và mạng số lượt chơi
        int scoreTextureX = 10; // X coordinate
        int scoreTextureY = SCREEN_HEIGHT - scoreTextureHeight - 10; // Y coordinate

        int lifeTextureX = SCREEN_WIDTH - lifeTextureWidth - 15; // X coordinate
        int lifeTextureY = SCREEN_HEIGHT - lifeTextureHeight - 10; // Y coordinate

        // Vẽ texture điểm số và mạng số lượt chơi lên màn hình
        SDL_Rect scoreDestRect = {scoreTextureX, scoreTextureY, scoreTextureWidth, scoreTextureHeight};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreDestRect);

        SDL_Rect lifeDestRect = {lifeTextureX, lifeTextureY, lifeTextureWidth, lifeTextureHeight};
        SDL_RenderCopy(renderer, lifeTexture, NULL, &lifeDestRect);
    } else
     {
        std::cerr << "Failed to render HUD!" << std::endl;
     }
}
