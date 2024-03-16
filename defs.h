#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "sugoidesune";
#define BOARD_X (SCREEN_WIDTH - BOARD_WIDTH)/2
#define BOARD_Y (SCREEN_HEIGHT - BOARD_HEIGHT)/2

#define BOARD_WIDTH  300 // Chiều rộng của bảng
#define BOARD_HEIGHT 300 // Chiều cao của bảng
#define CELL_SIZE  (BOARD_WIDTH / BOARD_SIZE) // Kích thước của mỗi ô, phụ thuộc vào số lượng ô trên bảng

#endif

