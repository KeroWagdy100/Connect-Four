#pragma once
#include <iostream>
#include <string>
using namespace std;

const int BOARD_RANK {6};
const char RED_CHAR{'R'}, BLUE_CHAR{'B'}, EMPTY_CHAR{' '};

enum dir    {LEFT = 0, LEFT_UP, UP, RIGHT_UP, RIGHT, RIGHT_DOWN, DOWN, LEFT_DOWN};
int r_dir[] { 0,       -1,      -1, -1,       0,     1,          1,    1};
int c_dir[] {-1,       -1,       0,  1,       1,     1,          0,   -1};


class Game {
public:
    Game() {
        Init();
        do {
            printBoard();
            int i{0}, j{0};
            update_board(i, j);
            check_board(i, j);
        } while(!over);

    }
    void Init() {
        initBoard();
        cout << "First Player Name: ";
        Input::stringInput(name1, "N/A");
        cout << "First Player Color (R for Red, B for Blue): ";
        Input::charInput(player1, 'R', 6);
        player2 = player1 == RED_CHAR ? BLUE_CHAR : RED_CHAR;
        cout << "Second Player Name: ";
        Input::stringInput(name2, "N/A");

        cout << "[Player 1: " << name1 << " - " << color_name(player1) << "]\n";
        cout << "[Player 2: " << name2 << " - " << color_name(player2) << "]\n";
        curr_player = player1;
    }
    void printBoard() const;
private:
    char board[BOARD_RANK][BOARD_RANK];
    string name1{""}, name2{""};
    char player1, player2;
    char curr_player {player1};
    char winner{player1};
    bool over{0};
    void initBoard();
    string color_name (char _color){
        return (_color == RED_CHAR ? "Red" : "Blue");
    }
    int validateCol(const int col) const; // returns empty row within this col
    void update_board(int& row, int& col);
    void check_board(const int row, const int col);
};

void Game::update_board(int& row, int& col) {
    cout << (curr_player == player1 ? name1 : name2) << " - " << color_name(curr_player) << "'s Turn --";
    
    while (true) { // taking player col
        cout << "Enter Col index: ";
        Input::intInput(col, 0, 5, 0, BOARD_RANK - 1);
        row = validateCol(col);
        if (row != -1)
            break;
        cout << "Invalid Col, Col " << col << " is not empty, Try again.\n";
    }
    board[row][col] = curr_player;
    curr_player = (curr_player == player1 ? player2 : player1);
}

void Game::initBoard() {
    for (int i = 0; i < BOARD_RANK; i++) {
        for (int j = 0; j < BOARD_RANK; j++)
            board[i][j] = EMPTY_CHAR;
    }
}

int Game::validateCol(const int col) const {
    if (col < 0 || col >= BOARD_RANK)
        return -1;
    for  (int i = BOARD_RANK; i >= 0; --i){
        if (board[i][col] == EMPTY_CHAR)
            return i;
    }
    return -1;
}




void Game::check_board(const int row, const int col){
    int curr_check_dir {dir::LEFT};
    int i{row}, j{col};
    char player{board[row][col]};
    int counter{1};
    while (curr_check_dir != (dir::LEFT_DOWN + 1) && !over) {
        i = row, j = col;
        counter = 0;
        while (true) {
            i += r_dir[curr_check_dir];
            j += c_dir[curr_check_dir];
            if (i < 0 || j < 0 || i >= BOARD_RANK || j >=  BOARD_RANK)
                break;
            else if(board[i][j] == player) {
                counter++;
            }
            else
                break;
            if (counter == 4) {
                winner = player;
                over = 1;
                cout << "Last Place [" << i << "][" << j << "]\n";
                int temp;
                cin >> temp;
            }
        }
        curr_check_dir++;
    }

    if (over) {
        printBoard();
        cout << (winner == player1 ? name1 : name2) << "(" << color_name(winner) << ") Won\n";
    }
}


void Game::printBoard() const {
    system("CLS");
    for (int i = 0; i < BOARD_RANK; i++)
        cout << i << " ";
    cout << "\n";
    
    for (int i = 0; i < BOARD_RANK; i++) {
        for (int j = 0; j < BOARD_RANK; j++)
            cout << board[i][j] << "|";
        cout << "\n";
    }
}