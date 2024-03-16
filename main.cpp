#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"


using namespace std;



void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void processClickAt(int x, int y, Tictactoe& game) {
    // chuyển tọa độ màn hình x, y thành tọa độ hàng cột của game
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
}




int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    Tictactoe game;
    game.init();
    graphics.render(game);


    int x, y;
    SDL_Event event;
    bool quit = false;
    while (! quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 quit = true;
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 SDL_GetMouseState(&x, &y);
                 processClickAt(x, y, game);
                 graphics.render(game);
                 if (game.checkWin()) {
                    cout << "Player win.";
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Chiến thắng!", "Bạn đã chiến thắng!", graphics.window);

                    // Xóa nội dung trước đó trên renderer
                    SDL_RenderClear(graphics.renderer);

                    // Vẽ lại màn hình
                    SDL_RenderPresent(graphics.renderer);

                   SDL_Quit();
                  return 0;
                }

                 break;
        }

    }

    graphics.quit();
    return 0;
}





