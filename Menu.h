#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include<iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Game.h"

struct Menu {
    SDL_Renderer* grenderer;


    TTF_Font* font;
   // SDL_Texture* menuTexture;


    SDL_Texture* backgroundTexture;
    SDL_Texture* levelTexture;
   // SDL_Rect menuRect;

    bool showMenu;
    bool isRunning;

    Menu(SDL_Renderer* menurenderer)
    {
        grenderer = menurenderer;

        showMenu = true;
        backgroundTexture = nullptr;
    }

    void InitMenu() {
        // Initialize font
      //  if (TTF_Init() == -1) {
     //       std::cerr << "Failed to initialize SDL_ttf" << std::endl;
     //   }
     //   font = TTF_OpenFont("font.ttf", 24);
     //   if (font == nullptr) {
      //      std::cerr << "Failed to load font" << std::endl;
      //  }

        // Load and set color for menu texture
      //  SDL_Color textColor = {255, 255, 255};
     //   menuTexture = SDL_CreateTextureFromSurface(grenderer, TTF_RenderText_Solid(font, "Pha gach", textColor));




        // Load background texture from PNG
        backgroundTexture = IMG_LoadTexture(grenderer,"menukinhdi2.png");
        if (backgroundTexture == nullptr)
        {
            std::cerr << "Failed to load menu background image" << std::endl;
        }
    }



    void RenderMenu()
    {
        // Render background texture
        SDL_RenderCopy(grenderer, backgroundTexture, NULL, NULL);
        SDL_RenderPresent(grenderer);
    }



    void HandleMouseClick(SDL_Event& event, int &level1)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
             std::cerr << mouseX << " " << mouseY <<std::endl << level1;

            // Check if the mouse click is within specified ranges
            if (mouseX >= 130 && mouseX <= 250 && mouseY >= 130 && mouseY <= 200)
            {
                // Start the game
                isRunning = true;
                showMenu = false;
                return;
            }
            else if (mouseX >= 130 && mouseX <= 250 && mouseY >= 350 && mouseY <= 400)
            {
                // Stop the game
                isRunning = false;
                showMenu = true;

                SDL_Quit();

                return;
            }
            else if( mouseX >= 130 && mouseX <= 250 && mouseY >= 240 && mouseY <= 300)
            {
            levelTexture = IMG_LoadTexture(grenderer,"menukinhdi1.png");
            SDL_RenderCopy(grenderer, levelTexture, NULL, NULL);
            SDL_RenderPresent(grenderer);
            }



            else if (mouseX >= 380 && mouseX <= 538 && mouseY >=160 && mouseY <= 210)
                {
                level1 = 1;
                }


        }
    }


};

#endif // MENU_H_INCLUDED
