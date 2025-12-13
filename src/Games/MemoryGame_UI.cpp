#include<iostream>
#include<vector>
#include<algorithm>
#include"BoardGame_Classes.h"
#include"MemoryGame_UI.h"
#include"XO_Board.h"

MemoryGame_UI::MemoryGame_UI() : UI<char>("Welcome to my Memory-XO game!", 3) {}


int MemoryGame_UI::min_max(Board<char>* current_board , int depth , bool is_max , char AI_symbol , char human_symbol){
    
    //base case
    Player<char>AI_Player("AI" , AI_symbol , PlayerType::COMPUTER);
    Player<char>human_Player("human" , human_symbol , PlayerType::HUMAN);

    if( current_board->is_win(&AI_Player) ){
        return 10 - depth;
    }
    if( current_board->is_win(&human_Player) ){
        return -10 + depth;
    }
    if( current_board->is_draw(&AI_Player) ){
        return 0;
    }

    //transition
    if(is_max){
        int max_score = -1e5;

        for(int i = 0 ; i < current_board->get_rows() ; ++i)
            for(int j = 0 ; j < current_board->get_columns() ; ++j){
                if( current_board->get_cell(i , j) == '.' ){
                    Move<char> current_move(i , j , AI_symbol);
                    current_board->update_board(&current_move);
                    int score = min_max(current_board , depth+1 , false , AI_symbol , human_symbol);
                    Move<char> undo_move(i , j , 0);
                    current_board->update_board(&undo_move);
                    max_score = max(score , max_score);
                }
            }
        return max_score;
    }
    else{
        int min_score = 1e5;

        for(int i = 0 ; i < current_board->get_rows() ; ++i)
            for(int j = 0 ; j < current_board->get_columns() ; ++j){

                if( current_board->get_cell(i , j) == '.' ){
                    Move<char> current_move(i , j , human_symbol);
                    current_board->update_board(&current_move);
                    int score = min_max(current_board , depth+1 , true , AI_symbol , human_symbol);
                    Move<char> undo_move(i , j , 0);
                    current_board->update_board(&undo_move);
                    min_score = min(score , min_score);
                }
            }
        return min_score;
    }
}

Move<char>* MemoryGame_UI::get_AI_move(Player<char>* AI_player){
    Board<char>* test_board = new X_O_Board();

    *test_board = *AI_player->get_board_ptr();

    Move<char>* best_move = new Move<char>(-1 , -1 , AI_player->get_symbol());
    int best_score = -1e5;
    for(int i = 0 ; i < test_board->get_rows() ; ++i)
        for(int j = 0 ; j < test_board->get_columns() ; ++j){

            if( test_board->get_cell(i , j) == '.' ){

                Move<char> current_move(i , j , AI_player->get_symbol());
                test_board->update_board(&current_move);

                int score = min_max(test_board , 0 , false , AI_player->get_symbol() , ( AI_player->get_symbol() == 'X' ) ? 'O' : 'X');
                
                Move<char>undo_move(i , j , 0);
                test_board->update_board(&undo_move);
                
                if(score > best_score){
                    best_score = score;
                    delete best_move; 
                    best_move = new Move<char>(i, j, AI_player->get_symbol());
                }
                
            }
        }

    delete test_board;
    return best_move;
}

Player<char>* MemoryGame_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer");
    
    return new Player<char>(name, symbol, type);
}

Move<char>* MemoryGame_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        return get_AI_move(player);
    }
    return new Move<char>(x, y, player->get_symbol());
}

void MemoryGame_UI::display_board_matrix(const vector<vector<char>>& matrix) const{
    if (matrix.empty() || matrix[0].empty()) return;

        int rows = matrix.size();
        int cols = matrix[0].size();

        cout << "\n    ";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width + 1) << j;
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

        for (int i = 0; i < rows; ++i) {
            cout << setw(2) << i << " |";
            for (int j = 0; j < cols; ++j)
                cout << setw(cell_width) << ((matrix[i][j] == 'X' || matrix[i][j] == 'O') ? '?' : matrix[i][j]) << " |";
            cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        }
        cout << endl;
}