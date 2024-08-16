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
    /**
     * @brief Construct a new Game object that automatically starts.
     */
    Game() {
        Init();
        do {
            printBoard();
            int i{0}, j{0};
            update_board(i, j);
            check_board(i, j);
        } while(!over);
    }

    /**
     * @brief Initializes the game objects (players' data) by prompting using std::cin.
     *  first function call in Game() constructor. 
     */
    void Init() {
        initBoard();
        cout << "First Player Name: ";
        Input::stringInput(name1, "N/A");
        cout << "First Player Color (R for \033[0;31mRed\033[0m, B for \033[0;34mBlue\033[0m): ";
        Input::charInput(player1, 'R', 6);
        player2 = player1 == RED_CHAR ? BLUE_CHAR : RED_CHAR;
        cout << "Second Player Name: ";
        Input::stringInput(name2, "N/A");

        cout << "[Player 1: " << name1 << " - " << color_name(player1) << "]\n";
        cout << "[Player 2: " << name2 << " - " << color_name(player2) << "]\n";
        curr_player = player1;
    }

    /**
     * @brief Prints Game Board with an index-row on the top to help players select columns.
     */
    void printBoard() const;
private:
    /* Game Objects\Attributes */
    char board[BOARD_RANK][BOARD_RANK];
    string name1{""}, name2{""};
    char player1, player2;
    char curr_player {player1};
    char winner{player1};
    bool over{0}; // game terminator

    /* Game Priv. Functions*/

    /**
     * @brief initializes the board with EMPTY_CHAR ' '
     * called by Init() public function
     */
    void initBoard();

    /**
     * @brief takes the color char ['R' or 'B'] and returns ["Red" or "Blue"]
     * @param _color char ['R' or 'B']
     * @return string -- By Default returns "Blue" if _color char is not in the list
     */
    string color_name (char _color){
        return "\033[0;" + string(_color == RED_CHAR ? "31mRed" : "34mBlue") + "\033[0m";
    }

    /**
     * @brief takes a col index and returns the suitable empty cell row index in that column 
     * 
     * @param col column index that is required to be checked
     * @return int (-1 in case of column doesn't exist or column is filled, else returns the suitable empty row index)
     */
    int validateCol(const int col) const;

    /**
     * @brief Main Update function of the game
     * Takes current player input (col index) and validates it.
     * and updates the board
     * @param row passed by ref. to be edited and sent back to check_boad() func.
     * @param col passed by ref. because the user fills it
     */
    void update_board(int& row, int& col);

    /**
     * @brief updates the current state of the game 
     * 
     * @param row the last cell row filled by players
     * @param col the last cell col filled by players
     */
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
        counter = 1;
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
    

    // For coloring (bolded): "\033[1;" + (Blue? "34" : Red? "31") + "TEXT" + "\033[0m"
    for (int i = 0; i < BOARD_RANK; i++) {
        for (int j = 0; j < BOARD_RANK; j++)
        cout << "\033[1;" << (board[i][j] == RED_CHAR ? "31m" : "34m") << board[i][j] << "\033[0m|";
            // cout << board[i][j] << "|";
        cout << "\n";
    }
}
