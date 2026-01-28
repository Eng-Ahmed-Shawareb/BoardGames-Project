#include "clsSUSUI.h"
#include "BoardGame_Classes.h"
#include "clsSUSAIPlayer.h"
#include "clsSUSBoard.h"
#include <iostream>
#include <vector>

clsSUSUI::clsSUSUI() : UI("Welcome to my SUS game!", 3){};

Move<char> *clsSUSUI::get_move(Player<char> *player) {
  int x;
  int y;
  char symbol = player->get_symbol();

  if (player->get_type() == PlayerType::HUMAN) {

    cout << "Please enter your move x and y [0 to 2] : ";
    cin >> x >> y;

  }

  else if (player->get_type() == PlayerType::COMPUTER) {

    clsSUSAIPlayer *AIPlayer = dynamic_cast<clsSUSAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }

  return new Move<char>(x, y, symbol);
}

Player<char> *clsSUSUI::create_player(string &name, char symbol,
                                      PlayerType type) {
  cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
       << " player : " << name << " (" << symbol << ")" << endl;
  if (type == PlayerType::COMPUTER) {
    return new clsSUSAIPlayer(name, symbol);
  }
  return new Player(name, symbol, type);
}

Player<char> **clsSUSUI::setup_players() {
  Player<char> **players = new Player<char> *[2];
  vector<string> vTypeOptions = {"Human", "Computer"};

  string nameS = get_player_name("Player S");
  PlayerType typeS = get_player_type_choice("Player S", vTypeOptions);
  players[0] = create_player(nameS, 'S', typeS);

  string nameU = get_player_name("Player U");
  PlayerType typeU = get_player_type_choice("Player U", vTypeOptions);
  players[1] = create_player(nameU, 'U', typeU);

  return players;
}