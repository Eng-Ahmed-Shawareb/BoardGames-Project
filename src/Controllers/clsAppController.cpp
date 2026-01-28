#include "clsAppController.h"
#include "BoardGame_Classes.h"
#include "clsFourInRowBoard.h"
#include "clsFourInRowUI.h"
#include "clsMemoryGameUI.h"
#include "clsNumericalBoard.h"
#include "clsNumericalUI.h"
#include "clsSUSBoard.h"
#include "clsSUSUI.h"
#include "clsXOBoard.h"
#include "clsXOUI.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

void clsAppController::playXOGame() {
  UI<char> *gameUI = new clsXOUI();

  Board<char> *XOBoard = new clsXOBoard();

  Player<char> **players = gameUI->setup_players();

  GameManager<char> XOGame(XOBoard, players, gameUI);

  XOGame.run();

  delete XOBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playNumericalGame() {

  UI<int> *gameUI = new clsNumericalUI();

  Board<int> *NumericalBoard = new clsNumericalBoard();

  Player<int> **players = gameUI->setup_players();

  GameManager<int> NumericalGame(NumericalBoard, players, gameUI);

  NumericalGame.run();

  delete NumericalBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playSUSGame() {

  UI<char> *gameUI = new clsSUSUI();

  Board<char> *SUSBoard = new clsSUSBoard();

  Player<char> **players = gameUI->setup_players();

  GameManager<char> SUSGame(SUSBoard, players, gameUI);

  SUSGame.run();

  delete SUSBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playFourInRowGame() {
  UI<char> *gameUI = new clsFourInRowUI();

  Board<char> *FourInRowBoard = new clsFourInRowBoard();

  Player<char> **players = gameUI->setup_players();

  GameManager<char> FourInRowGame(FourInRowBoard, players, gameUI);

  FourInRowGame.run();

  delete FourInRowBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playMemoryGame() {
  UI<char> *gameUI = new clsMemoryGameUI();

  Board<char> *MemoryGameBoard = new clsXOBoard();

  Player<char> **players = gameUI->setup_players();

  GameManager<char> MemoryGame(MemoryGameBoard, players, gameUI);

  MemoryGame.run();

  delete MemoryGameBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}
