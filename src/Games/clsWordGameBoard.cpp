#include "clsWordGameBoard.h"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

clsWordGameBoard::clsWordGameBoard() : clsBoard(3, 3) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      vBoard[i][j] = _blankSymbol;
    }
  }
  _loadDictionary();
}

void clsWordGameBoard::_loadDictionary() {
  ifstream file("../include/Core/dic.txt");
  if (!file.is_open()) {
    file.open("include/Core/dic.txt");
  }
  if (!file.is_open()) {
    cout << "Error: Could not open dic.txt" << endl;
    return;
  }
  string word;
  while (file >> word) {
    _dictionary.insert(word);
  }
}

bool clsWordGameBoard::_isValidWord(const string &word) {
  if (word.length() != 3)
    return false;
  for (char c : word) {
    if (c == _blankSymbol)
      return false;
  }
  return _dictionary.find(word) != _dictionary.end();
}

bool clsWordGameBoard::updateBoard(clsMove<char> *move) {
  int x = move->getX();
  int y = move->getY();
  char mark = move->getSymbol();

  if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
      (vBoard[x][y] == _blankSymbol || mark == 0)) {

    if (mark == 0) {
      nMoves--;
      vBoard[x][y] = _blankSymbol;
    } else {
      nMoves++;
      vBoard[x][y] = toupper(mark);
    }
    return true;
  }
  return false;
}

bool clsWordGameBoard::isWin(clsPlayer<char> *player) {
  // Check rows
  for (int i = 0; i < rows; ++i) {
    string word = "";
    word += vBoard[i][0];
    word += vBoard[i][1];
    word += vBoard[i][2];
    if (_isValidWord(word))
      return true;
  }

  // Check columns
  for (int i = 0; i < columns; ++i) {
    string word = "";
    word += vBoard[0][i];
    word += vBoard[1][i];
    word += vBoard[2][i];
    if (_isValidWord(word))
      return true;
  }

  // Check diagonals
  string word1 = "";
  word1 += vBoard[0][0];
  word1 += vBoard[1][1];
  word1 += vBoard[2][2];
  if (_isValidWord(word1))
      return true;

  string word2 = "";
  word2 += vBoard[0][2];
  word2 += vBoard[1][1];
  word2 += vBoard[2][0];
  if (_isValidWord(word2))
      return true;

  return false;
}

bool clsWordGameBoard::isDraw(clsPlayer<char> *player) {
  return (nMoves == 9 && !isWin(player));
}

bool clsWordGameBoard::isLose(clsPlayer<char> *player) {
  // Can't lose on your own turn in Word Tic-Tac-Toe, winning only depends on forming a word
  return false;
}

bool clsWordGameBoard::gameIsOver(clsPlayer<char> *player) {
  return isWin(player) || isDraw(player);
}
