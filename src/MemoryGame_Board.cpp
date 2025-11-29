#include<iostream>
#include"BoardGame_Classes.h"
#include"MemoryGame_Board.h"

MemoryGame_Board::MemoryGame_Board() : Board(3, 3) , fact_board(3 , vector<char>(3)) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    for (auto& row : fact_board)
        for (auto& cell : row)
            cell = blank_symbol;

}

bool MemoryGame_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {
            n_moves++;
            fact_board[x][y] = toupper(mark);
            board[x][y] = '⊘';
        }
        return true;
    }
    return false;
}

bool MemoryGame_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    for (int i = 0; i < rows; ++i) {
        if ((all_equal(fact_board[i][0], fact_board[i][1], fact_board[i][2]) && fact_board[i][0] == sym) ||
            (all_equal(fact_board[0][i], fact_board[1][i], fact_board[2][i]) && fact_board[0][i] == sym))
            return true;
    }
    if ((all_equal(fact_board[0][0], fact_board[1][1], fact_board[2][2]) && fact_board[1][1] == sym) ||
        (all_equal(fact_board[0][2], fact_board[1][1], fact_board[2][0]) && fact_board[1][1] == sym))
        return true;

    return false;
}

bool MemoryGame_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool MemoryGame_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
