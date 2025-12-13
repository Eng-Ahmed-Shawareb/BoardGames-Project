#include<iostream>
#include<vector>
#include"BoardGame_Classes.h"
#include"SUS_UI.h"
#include"SUS_Board.h"

SUS_UI::SUS_UI() : UI("Welcome to my SUS game!" , 3) {};

int SUS_UI::min_max(SUS_Board* current_board ,bool is_max , char AI_symbol , char human_symbol){
    //base case
    Player<char>AI_player("AI" , AI_symbol , PlayerType::COMPUTER);
    Player<char>human_player("human" , human_symbol , PlayerType::HUMAN);

    if( current_board->game_is_over(&AI_player) ){
        
        pair<int , int> scores = current_board->calculate_players_score();
        
        if( current_board->is_win(&AI_player) ){

            if( AI_symbol == 'U' ) 
                return scores.first - scores.second;
            else 
                return scores.second - scores.first;
        }
        if( current_board->is_win(&human_player) ){
            if( human_symbol == 'U' ) 
                return scores.second - scores.first;
            else 
                return scores.first - scores.second;
        } else 
            return 0;
    }
    //transition
    if( is_max ){
        int max_score = -1e5;

        for(int i = 0 ; i < current_board->get_rows() ; ++i)
            for(int j = 0 ; j < current_board->get_columns() ; ++j){

                if( current_board->get_cell(i , j) == '.' ){

                    Move<char> current_move(i , j , AI_symbol);
                    current_board->update_board(&current_move);

                    int score = min_max(current_board , false , AI_symbol , human_symbol);

                    Move<char> undo_move(i , j , 0);
                    current_board->update_board(&undo_move);

                    max_score = max(score , max_score);
                }
            }

        return max_score;

    }else{
        int min_score = 1e5;

        for(int i = 0 ; i < current_board->get_rows() ; ++i)
            for(int j = 0 ; j < current_board->get_columns() ; ++j){

                if( current_board->get_cell(i , j) == '.' ){

                    Move<char> current_move(i , j , human_symbol);
                    current_board->update_board(&current_move);

                    int score = min_max(current_board , true , AI_symbol , human_symbol);

                    Move<char> undo_move(i , j , 0);
                    current_board->update_board(&undo_move);

                    min_score = min(score , min_score);
                }
            }

        return min_score; 

    }
}

Move<char>* SUS_UI::get_AI_move(Player<char>* player){
    SUS_Board* test_board = new SUS_Board();
    SUS_Board* source_board = dynamic_cast<SUS_Board*>(player->get_board_ptr());
    if(source_board) {
        *test_board = *source_board; 
    }

    int best_score = -1e5;
    Move<char>* best_move = new Move<char>(-1 , -1 , player->get_symbol());

    for(int i = 0 ; i < test_board->get_rows() ; ++i)
        for(int j = 0 ; j < test_board->get_columns() ; ++j){

            if( test_board->get_cell(i , j) == '.' ){

                Move<char> current_move(i , j , player->get_symbol());
                test_board->update_board(&current_move);

                int score = min_max(test_board , false , player->get_symbol() , ( player->get_symbol() == 'S' ) ? 'U' : 'S');

                Move<char> undo_move(i , j , 0);
                test_board->update_board(&undo_move);

                if( score > best_score ){
                    best_score = score;
                    delete best_move;
                    best_move = new Move<char>(i , j , player->get_symbol());
                }
            }
        }

    delete test_board;
    return best_move;
}

Move<char>* SUS_UI::get_move(Player<char>* player){
    int x;
    int y; 
    char symbol = player->get_symbol();

    if(player->get_type() == PlayerType::HUMAN){

        cout << "Please enter your move x and y [0 to 2] : ";
        cin >> x >> y;

    }

    else if(player->get_type() == PlayerType::COMPUTER){

        return get_AI_move(player);

    }

    return new Move<char>( x , y , symbol );
}

Player<char>* SUS_UI::create_player(string& name , char symbol , PlayerType type){
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player : " << name << " (" << symbol << ")" << endl;
    return new Player(name , symbol , type);
}

Player<char>** SUS_UI::setup_players(){
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameS = get_player_name("Player S");
    PlayerType typeS = get_player_type_choice("Player S", type_options);
    players[0] = create_player(nameS, 'S', typeS);

    string nameU = get_player_name("Player U");
    PlayerType typeU = get_player_type_choice("Player U", type_options);
    players[1] = create_player(nameU, 'U', typeU);

    return players;
}