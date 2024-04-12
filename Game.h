#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <sstream>

#include "Field.h"
#include "Paddle.h"
#include "Ball.h"



struct Game {
    bool Init();
    void Run();

    SDL_Texture* backgroundTexture;



    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Surface* screen;
    TTF_Font* font;
    Mix_Music* music;
    Mix_Chunk* sound;

    // Timing
    unsigned int curframe, lastframe;
    //unsigned int startframe, actualDelay;

    Field* field;
    Paddle* paddle;
    Ball* ball;
    bool Ball_on_Paddle;
    bool isRunning = true;

    int life = 1;
    int level = 2;
    int playerScore = 0;
    int HitSpot;

    void Update(float delta);
    void Render();
    void CleanUp();
    void StartGame();
    void ResetPaddle();
    void InitBall();

    void SetPaddlePosition(float x);
    float Reflection(float hitx);


    void FieldCollision();
    void PaddleCollision();
    void BrickCollision();
    void SideCollision(int sidehit);


    int BrickCount();
    void PlayMusic();
    void StopMusic();
    void PlaySoundEffect();
    void ShowScore();
    void GameLost();
    void GameWin();



    void HandleKeyboardEvent(SDL_Event& event);


    //score
    SDL_Texture *scoreTexture = nullptr;
    void UpdateScoreTexture();
};

#endif // GAME_H_INCLUDED

