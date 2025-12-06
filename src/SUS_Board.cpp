#include<iostream>
#include"BoardGame_Classes.h"
#include"SUS_Board.h"

SUS_Board::SUS_Board() : Board(3 , 3) , order_of_moves(3 , vector<int>(3)){
    for(auto& row : board){
        for(auto& element : row){
            element = Blank_Symbol;
        }
    }
    for(auto& row : order_of_moves)
        for(auto& element : row){
            element = 0;
        }
}

pair< int , int > SUS_Board::calculate_players_score(){
    pair < int , int > score = {0 , 0};

    for(int i = 0 ; i < 3 ; ++i){
        string s = "";
        for(int j = 0 ; j < 3 ; ++j){
            s += board[i][j];
        }
        if( s == "SUS" ){
            ( order_of_moves[i][1] > order_of_moves[i][0] &&  order_of_moves[i][1] > order_of_moves[i][2]) ? 
            score.first++ : score.second++;
        }
    }
    for(int i = 0 ; i < 3 ; ++i){
        string s = "";
        for(int j = 0 ; j < 3 ; ++j){
            s += board[j][i];
        }
        if( s == "SUS" ){
            ( order_of_moves[1][i] > order_of_moves[0][i] &&  order_of_moves[1][i] > order_of_moves[2][i]) ? 
            score.first++ : score.second++;
        }
    }
    string diagonal1 = "" , diagonal2 = "";
    for(int i = 0 ; i < 3 ; ++i){
        diagonal1 += board[i][i];
        diagonal2 += board[i][2 - i];
    }
    if( diagonal1 == "SUS" ){
        ( order_of_moves[1][1] > order_of_moves[0][0] && order_of_moves[1][1] > order_of_moves[2][2] ) ? 
        score.first++ : score.second++;
    }
    if( diagonal2 == "SUS" ){
        ( order_of_moves[1][1] > order_of_moves[2][0] && order_of_moves[1][1] > order_of_moves[2][0] ) ? 
        score.first++ : score.second++;
    }

    return score;
}

bool SUS_Board::valid_move( int x , int y ){
    return ( x >= 0 && x < rows && y >= 0 && y < columns );
}

bool SUS_Board::is_win( Player<char>* player ){
    if( n_moves < 9 ) return false;
    pair< int , int > players_score = calculate_players_score();
    char symbol = player->get_symbol();

    if( toupper(symbol) == 'S' ){
        if( players_score.second > players_score.first ) return true;
        else return false;
    }
    if( toupper(symbol) == 'U' ){
        if( players_score.second < players_score.first ) return true;
        else return false;
    }
}

bool SUS_Board::is_lose( Player<char>* player ){
    if( n_moves < 9 ) return false;
    pair< int , int > players_score = calculate_players_score();
    char symbol = player->get_symbol();

    if( toupper(symbol) == 'S' ){
        if( players_score.second < players_score.first ) return true;
        else return false;
    }
    if( toupper(symbol) == 'U' ){
        if( players_score.second > players_score.first ) return true;
        else return false;
    }
} 

bool SUS_Board::game_is_over( Player<char>* player ){ 
    return n_moves == 9; 
}

bool SUS_Board::is_draw( Player<char>* player ){
    if( n_moves < 9 ) return  false;
    pair< int , int > players_score = calculate_players_score();
    if( players_score.first == players_score.second ) return true;
    else return false;
} 

bool SUS_Board::update_board( Move<char>* move ){
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if( valid_move(x , y) ){
        if( symbol == 0 ){
            n_moves--;
            board[x][y] = Blank_Symbol;
            order_of_moves[x][y] = 0;
        }else{
            if( board[x][y] != Blank_Symbol )
                return false;  
            board[x][y] = toupper(symbol);
            n_moves++;
            order_of_moves[x][y] = n_moves;
        }
        return true;
    }
    return false;
}