#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

#include"BoardGame_Classes.h"

class MemoryGame_UI : public UI<char> {
public:
    MemoryGame_UI();

    ~MemoryGame_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    int min_max(Board<char>* current_board , int depth , bool is_max , char AI_symbol , char human_symbol);

    Move<char>* get_AI_move(Player<char>* AI_player);

    Move<char>* get_move(Player<char>* player);

    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};


#endif