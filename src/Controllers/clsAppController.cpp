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
#include "clsInfinityBoard.h"
#include "clsInfinityUI.h"
#include "clsPyramidBoard.h"
#include "clsPyramidUI.h"
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

  clsBoard<int> *numericalBoard = new clsNumericalBoard();

  clsPlayer<int> **players = gameUI->setupPlayers();

  clsGameManager<int> numericalGame(numericalBoard, players, gameUI);

  numericalGame.run();

  delete numericalBoard;

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

  clsBoard<char> *fourInRowBoard = new clsFourInRowBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> fourInRowGame(fourInRowBoard, players, gameUI);

  fourInRowGame.run();

  delete fourInRowBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playMemoryGame() {
  clsUI<char> *gameUI = new clsMemoryGameUI();

  clsBoard<char> *memoryGameBoard = new clsXOBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> memoryGame(memoryGameBoard, players, gameUI);

  memoryGame.run();

  delete memoryGameBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playMisereGame() {
  clsUI<char> *gameUI = new clsMisereUI();

  clsBoard<char> *misereGameBoard = new clsMisereBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> misereGame(misereGameBoard, players, gameUI);

  misereGame.run();

  delete misereGameBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playFourByFourGame(){
  clsUI<char> *gameUI = new clsFourByFourUI();

  clsBoard<char> *fourByFourBoard = new clsFourByFourBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> fourByFourGame(fourByFourBoard, players, gameUI);

  fourByFourGame.run();

  delete fourByFourBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playInfinityGame(){
  clsUI<char> *gameUI = new clsInfinityUI();

  clsBoard<char> *infinityBoard = new clsInfinityBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> infinityGame(infinityBoard, players, gameUI);

  infinityGame.run();

  delete infinityBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}

void clsAppController::playPyramidGame(){
  clsUI<char> *gameUI = new clsPyramidUI();

  clsBoard<char> *pyramidBoard = new clsPyramidBoard();

  clsPlayer<char> **players = gameUI->setupPlayers();

  clsGameManager<char> pyramidGame(pyramidBoard, players, gameUI);

  pyramidGame.run();

  delete pyramidBoard;

  for (int i = 0; i < 2; ++i) {
    delete players[i];
  }

  delete gameUI;

  delete[] players;
}