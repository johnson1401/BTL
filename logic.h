#ifndef _LOGIC__H
#define _LOGIC__H
#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'



struct Tictactoe {
    char board[BOARD_SIZE][BOARD_SIZE];
    char next_move   = O_CELL;
    bool isCellOccupied(int row, int col) {
        return (board[row][col] != EMPTY_CELL);
    }
    bool checkWin() {
    // Kiểm tra hàng ngang
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][0] != EMPTY_CELL && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return true; // Người chơi chiến thắng
        }
    }

    // Kiểm tra hàng dọc
    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[0][j] != EMPTY_CELL && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return true; // Người chơi chiến thắng
        }
    }

    // Kiểm tra đường chéo chính
    if (board[0][0] != EMPTY_CELL && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return true; // Người chơi chiến thắng
    }

    // Kiểm tra đường chéo phụ
    if (board[0][2] != EMPTY_CELL && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return true; // Người chơi chiến thắng
    }

    return false; // Chưa có người chơi nào chiến thắng
    }

    void init(){
        for (int i = 0; i < BOARD_SIZE;i++)
        {

            for (int j = 0; j<BOARD_SIZE; j++)
            {
                board[i][j]=EMPTY_CELL;
            }
        }

    }
    void move(int row,int col) {

        if (row >= 0 && row < BOARD_SIZE
            && col >= 0 && col < BOARD_SIZE)
        {
            if (!isCellOccupied(row,col) ){
            board[row][col] = next_move;

            next_move = (next_move == O_CELL) ? X_CELL : O_CELL;
            }

        }



    }

};



#endif // _LOGIC_H
