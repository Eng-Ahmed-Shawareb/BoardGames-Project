
#include<iostream>
#include"Numerical_Board.h"
using namespace std;

Numerical_Board::Numerical_Board() : Board(3 , 3){
    for(auto& row : board){
        for(auto& element : row){
            element = Blank_Symbol;
        }
    }
};

bool Numerical_Board::update_board(Move<int>* move){
    int x = move->get_x();
    int y = move->get_y();
    int symbol = move->get_symbol();

    if(x < 0 || y < 0 || x >= rows || y >= columns || board[x][y] != Blank_Symbol)
        return false;
    if(symbol == 0){
        n_moves--;
        board[x][y] = Blank_Symbol;
    }else{
        n_moves++;
        board[x][y] = symbol;
    }
    return true;
}

bool Numerical_Board::is_win(Player<int>* player){
    for(int i = 0 ; i < rows ; ++i){
        
        int sum = board[i][0] + board[i][1] + board[i][2];

        if( board[i][0] == 0 || board[i][1] == 0 || board[i][2] == 0 ) sum = 0;

        if(sum == 15) 
            return true;
    }
    for(int i = 0 ; i < columns ; ++i){

        int sum = board[0][i] + board[1][i] + board[2][i];

        if( board[0][i] == 0 || board[1][i] == 0 || board[2][i] == 0 ) sum = 0;

        if(sum == 15)
            return true;
    }
    int sum_diagonal1 = board[0][0] + board[1][1] + board[2][2];

    if( board[0][0] == 0 || board[1][1] == 0 || board[2][2] == 0 ) sum_diagonal1 = 0;

    int sum_diagonal2 = board[0][2] + board[1][1] + board[2][0];

    if( board[0][2] == 0 || board[1][1] == 0 || board[2][0] == 0 ) sum_diagonal2 = 0;

    if(sum_diagonal1 == 15 || sum_diagonal2 == 15)
        return true;
    
    return false;

}

bool Numerical_Board::is_draw(Player<int>* player){
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player){
    return (is_win(player) || is_draw(player));
}
