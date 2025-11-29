#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include"BoardGame_Classes.h"
#include"Numerical_Board.h"
#include"Numerical_UI.h"
#include"XO_Board.h"
#include"XO_UI.h"
#include"SUS_Board.h"
#include"SUS_UI.h"
#include"FourInRow_UI.h"
#include"FourInRow_Board.h"
#include"MemoryGame_Board.h"
#include"MemoryGame_UI.h"
#include"PlayGameFunctions.h"

using namespace std;

void PlayGameFunctions::playXOGame(){
    UI<char>* game_ui = new XO_UI();

    Board<char>* xo_board = new X_O_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> x_o_game(xo_board, players, game_ui);

    x_o_game.run();

    delete xo_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    delete game_ui;

    delete[] players;
}

void PlayGameFunctions::playNumericalGame(){

    UI<int>* game_ui = new Numerical_UI();

    Board<int>* NumericalBoard = new Numerical_Board();

    Player<int>** players = game_ui->setup_players();

    GameManager<int> NumericalGame(NumericalBoard, players, game_ui);

    NumericalGame.run();

    delete NumericalBoard;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    delete game_ui;
    
    delete[] players;
}

void PlayGameFunctions::playSUSGame(){

    UI<char>* game_ui = new SUS_UI();

    Board<char>* SUSBoard = new SUS_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> SUSGame(SUSBoard , players , game_ui);

    SUSGame.run();

    delete SUSBoard;

    for(int i = 0 ; i < 2 ; ++i){
        delete players[i];
    }

    delete game_ui;

    delete[] players;
}

void PlayGameFunctions::playFourInRowGame(){
    UI<char>* game_ui = new FourInRow_UI();

    Board<char>* FourInRowBoard = new FourInRow_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> FourInRowGame(FourInRowBoard , players , game_ui);

    FourInRowGame.run();

    delete FourInRowBoard;

    for(int i = 0 ; i < 2 ; ++i){
        delete players[i];
    }

    delete game_ui;

    delete[] players;
}

void PlayGameFunctions::playMemoryGame(){
    UI<char>* game_ui = new MemoryGame_UI();

    Board<char>* MemoryGameBoard = new MemoryGame_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> MemoryGame(MemoryGameBoard , players , game_ui);

    MemoryGame.run();

    delete MemoryGameBoard;
    
    for(int i = 0 ; i < 2 ; ++i){
        delete players[i];
    }

    delete game_ui;

    delete[] players;
}
