#include<iostream>
#include"BoardGame_Classes.h"
#include"FourInRow_Board.h"

using namespace std;

FourInRow_Board::FourInRow_Board() : Board( 6 , 7 ){
    for(auto& row : board){
        for(auto& element : row){
            element = Blank_Symbol;
        }
    }
}

bool FourInRow_Board::valid_move( int y ){
    if( y < 0 || y > 6 ) return false;
    
    for(int i = 0 ; i < 6 ; ++i){
        if(board[i][y] == Blank_Symbol) return true;
    }
    return false;
}

bool FourInRow_Board::update_board(Move<char>* move){
    int x = 0;
    int y = move->get_y();
    char symbol = move->get_symbol();
    if( valid_move( y ) ){
        for(int i = 5 ; i >= 0 ; --i){
            if( board[i][y] == Blank_Symbol ){
                board[i][y] = toupper(symbol);
                n_moves++;
                return true;
            }
        }
    }
    return false;
}

bool FourInRow_Board::is_win(Player<char>* player){
    int rows = player->get_board_ptr()->get_rows();
    int columns = player->get_board_ptr()->get_columns();
    char player_symbol = player->get_symbol();
    string four_symbol = "";
    for(int i = 0 ; i < 4 ; ++i){
        four_symbol += player_symbol;
    }
    for(int i = 0 ; i < rows ; ++i){
        for(int j = 0 ; j < columns ; ++j){
            if( board[i][j] == player_symbol ){
                string s = "";
                for(int u = j ; u < j + 4 ; ++u){
                    if( u < rows ){
                        s += board[i][u];
                    }
                }
                if( s == four_symbol ) 
                    return true;
                s = "";
                for(int u = i ; u >= i - 3 ; --u){
                    if( u >= 0 ){
                        s += board[u][j];
                    }
                }
                if( s == four_symbol ) 
                    return true;
                s = "";
                for(int u = i , v = j ; u >= i - 3 , v < j + 4 ; --u , ++v){
                    if( u >= 0 && v < columns ){
                        s += board[u][v];
                    }
                }
                if( s == four_symbol ) 
                    return true;
                s = "";
                for(int u = i , v = j ; u >= i - 3 , v >= j - 3 ; --u , --v){
                    if( u >= 0 && v >= 0){
                        s += board[u][v];
                    }
                }
                if( s == four_symbol ) 
                    return true;
            }
        }
    }
    return false;
}

bool FourInRow_Board::is_lose(Player<char>* player){
    return false;
}

bool FourInRow_Board::is_draw(Player<char>* player){
    return ( n_moves == 42 );
}

bool FourInRow_Board::game_is_over(Player<char>* player){
    return false;
}