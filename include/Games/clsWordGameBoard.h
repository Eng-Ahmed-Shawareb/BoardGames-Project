#ifndef WORDGAME_BOARD_H
#define WORDGAME_BOARD_H

#include "BoardGame_Classes.h"
#include <string>
#include <unordered_set>
using namespace std;

class clsWordGameBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';
  unordered_set<string> _dictionary;

  void _loadDictionary();
  bool _isValidWord(const string &word);

public:
  clsWordGameBoard();

  bool updateBoard(clsMove<char> *move) override;

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;
};

#endif
