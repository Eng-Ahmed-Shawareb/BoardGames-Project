#include<iostream>
#include"BoardGame_Classes.h"
#include"FourInRow_UI.h"
#include"FourInRow_Board.h"

using namespace std;

FourInRow_UI::FourInRow_UI() : UI("Welcome to my Four In Row game!" , 3) {};

Move<char>* FourInRow_UI::get_move(Player<char>* player){
    int x = 0;
    int y;
    char symbol = player->get_symbol();
    if( player->get_type() == PlayerType::HUMAN ){
        cout << "Please enter your move column [0 to 6] : ";
        cin >> y;
    }
    else if( player->get_type() == PlayerType::COMPUTER ){
        /*int columns = player->get_board_ptr()->get_columns();

        y = rand() % columns;*/
        return get_AI_move(player);

    }
    return new Move<char>( x , y , symbol );
}

Player<char>* FourInRow_UI::create_player(string& name , char symbol , PlayerType type){
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player : " << name << " (" << symbol << ")" << endl;
    return new Player(name , symbol , type);
}

Player<char>** FourInRow_UI::setup_players(){
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, static_cast<char>('X'), typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, static_cast<char>('O'), typeO);

    return players;
}

int FourInRow_UI::min_max(Board<char>* current_board , bool is_max , int depth , int alpha , int beta , char AI_symbol , char human_symbol){
    //base case
    Player<char>AI_player("AI" , AI_symbol , PlayerType::COMPUTER);
    AI_player.set_board_ptr(current_board);
    Player<char>human_player("human" , human_symbol , PlayerType::HUMAN);
    human_player.set_board_ptr(current_board);

    if( current_board->is_win(&AI_player) ){
        return 10 + (100 - depth);
    }
    if( current_board->is_win(&human_player) ){
        return -10 - (100 - depth);
    }
    if( current_board->is_draw(&AI_player) ){
        return 0;
    }

    if( depth > 8 ) 
        return 0;

    //transition
    if( is_max ){
        int max_score = -1e5;

        for(int i = 0 ; i < current_board->get_columns() ; ++i){

        if( current_board->get_cell(0 , i) == '.' ){
            Move<char> current_move(0 , i , AI_symbol);
            current_board->update_board(&current_move);

            int score = min_max(current_board , false , depth + 1 , alpha , beta , AI_symbol , human_symbol);

            Move<char> undo_move(0 , i , 0);
            current_board->update_board(&undo_move);

            alpha = max(alpha , score);

            max_score = max(score , max_score);

            if( alpha >= beta ) 
                break;
            
        }
    }

        return max_score;

    }else{
        int min_score = 1e5;

        for(int i = 0 ; i < current_board->get_columns() ; ++i){

            if( current_board->get_cell(0 , i) == '.' ){
                Move<char> current_move(0 , i , human_symbol);
                current_board->update_board(&current_move);

                int score = min_max(current_board , true , depth + 1 , alpha , beta , AI_symbol , human_symbol);

                Move<char> undo_move(0 , i , 0);
                current_board->update_board(&undo_move);
                
                beta = min(beta , score);

                min_score = min(score , min_score);

                if( alpha >= beta )
                    break;

            }
        }

        return min_score;

    }
}

Move<char>* FourInRow_UI::get_AI_move(Player<char>* AI_player){

    Board<char>* test_board = new FourInRow_Board();
    *test_board = *AI_player->get_board_ptr();

    int best_score = -1e5;

    Move<char>* best_move = new Move<char>(0 , 0 , AI_player->get_symbol());

    int column_order[] = {3, 2, 4, 1, 5, 0, 6};

    for (int idx = 0; idx < 7; ++idx) {
        int i = column_order[idx];

        if( test_board->get_cell(0 , i) == '.' ){
            Move<char> current_move(0 , i , AI_player->get_symbol());
            test_board->update_board(&current_move);

            int score = min_max(test_board , false , 0 , best_score , 1e5 , AI_player->get_symbol() , ( AI_player->get_symbol() == 'X' ) ? 'O' : 'X');

            Move<char> undo_move(0 , i , 0);
            test_board->update_board(&undo_move);

            if( score > best_score ){
                best_score = score;
                delete best_move;
                best_move = new Move<char>(0 , i , AI_player->get_symbol());
            }
        }
    }

    delete test_board;
    return best_move;
}