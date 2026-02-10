#include "clsAppController.h"
#include "BoardGame_Classes.h"
#include "clsFourInRowBoard.h"
#include "clsFourInRowUI.h"
#include "clsMemoryGameUI.h"
#include "clsMisereBoard.h"
#include "clsMisereUI.h"
#include "clsNumericalBoard.h"
#include "clsNumericalUI.h"
#include "clsSUSBoard.h"
#include "clsSUSUI.h"
#include "clsXOBoard.h"
#include "clsXOUI.h"
#include "clsFourByFourXOBoard.h"
#include "clsFourByFourXOUI.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

void clsAppController::playXOGame() {
  clsUI<char> *gameUI = new clsXOUI();

  clsBoard<char> *XOBoard = new clsXOBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> XOGame(XOBoard, players, gameUI);

  XOGame.run();

  delete XOBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playNumericalGame() {

  clsUI<int> *gameUI = new clsNumericalUI();

  clsBoard<int> *NumericalBoard = new clsNumericalBoard();

  clsPlayer<int> **players = gameUI->setupPlayers();

  clsGameManager<int> NumericalGame(NumericalBoard, players, gameUI);

  NumericalGame.run();

  delete NumericalBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playSUSGame() {

  clsUI<char> *gameUI = new clsSUSUI();

  clsBoard<char> *SUSBoard = new clsSUSBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> SUSGame(SUSBoard, players, gameUI);

  SUSGame.run();

  delete SUSBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playFourInRowGame() {
  clsUI<char> *gameUI = new clsFourInRowUI();

  clsBoard<char> *FourInRowBoard = new clsFourInRowBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> FourInRowGame(FourInRowBoard, players, gameUI);

  FourInRowGame.run();

  delete FourInRowBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playMemoryGame() {
  clsUI<char> *gameUI = new clsMemoryGameUI();

  clsBoard<char> *MemoryGameBoard = new clsXOBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> MemoryGame(MemoryGameBoard, players, gameUI);

  MemoryGame.run();

  delete MemoryGameBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playMisereGame() {
  clsUI<char> *gameUI = new clsMisereUI();

  clsBoard<char> *MisereGameBoard = new clsMisereBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> MemoryGame(MisereGameBoard, players, gameUI);

  MemoryGame.run();

  delete MisereGameBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playFourByFourGame(){
  clsUI<char> *gameUI = new clsFourByFourUI();

  clsBoard<char> *fourByFourGameBoard = new clsFourByFourBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> MemoryGame(fourByFourGameBoard, players, gameUI);

  MemoryGame.run();

  delete fourByFourGameBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}
