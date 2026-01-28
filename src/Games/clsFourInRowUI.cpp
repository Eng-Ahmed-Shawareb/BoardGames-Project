#include "clsFourInRowUI.h"
#include "BoardGame_Classes.h"
#include "clsFourInRowAIPlayer.h"
#include "clsFourInRowBoard.h"
#include <iostream>

using namespace std;

clsFourInRowUI::clsFourInRowUI() : UI("Welcome to my Four In Row game!", 3){};

Move<char> *clsFourInRowUI::get_move(Player<char> *player) {
  int x = 0;
  int y;
  char symbol = player->get_symbol();
  if (player->get_type() == PlayerType::HUMAN) {
    cout << "Please enter your move column [0 to 6] : ";
    cin >> y;
  } else if (player->get_type() == PlayerType::COMPUTER) {
    clsFourInRowAIPlayer *AIPlayer =
        dynamic_cast<clsFourInRowAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }
  return new Move<char>(x, y, symbol);
}

Player<char> *clsFourInRowUI::create_player(string &name, char symbol,
                                            PlayerType type) {
  cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
       << " player : " << name << " (" << symbol << ")" << endl;
  if (type == PlayerType::COMPUTER) {
    return new clsFourInRowAIPlayer(name, symbol);
  }
  return new Player(name, symbol, type);
}

Player<char> **clsFourInRowUI::setup_players() {
  Player<char> **players = new Player<char> *[2];
  vector<string> vTypeOptions = {"Human", "Computer"};

  string nameX = get_player_name("Player X");
  PlayerType typeX = get_player_type_choice("Player X", vTypeOptions);
  players[0] = create_player(nameX, static_cast<char>('X'), typeX);

  string nameO = get_player_name("Player O");
  PlayerType typeO = get_player_type_choice("Player O", vTypeOptions);
  players[1] = create_player(nameO, static_cast<char>('O'), typeO);

  return players;
}