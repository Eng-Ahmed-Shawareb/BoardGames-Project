#ifndef FOUR_IN_ROW_AI_PLAYER_H
#define FOUR_IN_ROW_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "FourInRow_Board.h"

class FourInRow_AI_Player : public Player<char> {
private :
    int min_max(Board<char> *current_board, bool is_max, int depth,
                          int alpha, int beta);
public :
    FourInRow_AI_Player(string name , char symbol);

    Move<char>* get_best_move();
};

#endif