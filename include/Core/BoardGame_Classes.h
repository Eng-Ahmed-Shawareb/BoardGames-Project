// BoardGame_classes.h
// Version 2.3
// Date: 25 Nov 2023
// Author: Mohammad El-Ramly
// Putpose: Core classes to build board XO-style games (x-o, connect4, etc)

#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////////////

template <typename T> class clsPlayer;
template <typename T> class clsMove;

/////////////////////////////////////////////////////////////
// Class declarations
/////////////////////////////////////////////////////////////

/**
 * @brief Represents the type of player in the game.
 */
enum class enPlayerType {
  HUMAN,    ///< A human player.
  COMPUTER, ///< A computer-controlled player.
  AI,       ///< An AI player.
  RANDOM    ///< A Random player.
};

/**
 * @brief Base template for any board used in board games.
 *
 * @tparam T Type of the elements stored on the board (e.g., char, int, string).
 *
 * Provides core data (rows, columns, matrix) and virtual methods to be
 * implemented by specific games like Tic-Tac-Toe, Connect4, etc.
 */
template <typename T> 

class clsBoard {
protected:
  int rows;                 ///< Number of rows
  int columns;              ///< Number of columns
  vector<vector<T>> vBoard; ///< 2D vector for the board
  int nMoves = 0;           ///< Number of moves made

public:
  /**
   * @brief Construct a board with given dimensions.
   */
  clsBoard(int rows, int columns)
      : rows(rows), columns(columns), vBoard(rows, vector<T>(columns)) {}

  /**
   * @brief Virtual destructor. Frees allocated board memory.
   */
  virtual ~clsBoard() {}

  /**
   * @brief Update the board with a new move.
   * @param move The move object containing position and symbol.
   * @return true if the move is valid and applied, false otherwise.
   */
  virtual bool updateBoard(clsMove<T> *move) = 0;

  /** @brief Check if a player has won. */
  virtual bool isWin(clsPlayer<T> *) = 0;

  /** @brief Check if a player has lost. */
  virtual bool isLose(clsPlayer<T> *) = 0;

  /** @brief Check if the game ended in a draw. */
  virtual bool isDraw(clsPlayer<T> *) = 0;

  /** @brief Check if the game is over. */
  virtual bool gameIsOver(clsPlayer<T> *) = 0;

  /**
   * @brief Return a copy of the current board as a 2D vector.
   */
  vector<vector<T>> getBoardMatrix() const { return vBoard; }

  /** @brief Get number of rows. */
  int getRows() const { return rows; }

  /** @brief Get number of columns. */
  int getColumns() const { return columns; }

  /** @brief Get number of moves. */
  int getNMoves() const { return nMoves; }

  /** @brief Return content of cell x, y in current board. */
  T getCell(int x, int y) { return vBoard[x][y]; }
};

//-----------------------------------------------------
/**
 * @brief Represents a single move in a board game.
 *
 * @tparam T Type of symbol placed on the board (e.g., char, int).
 */
template <typename T> 

class clsMove {
  int _x;    ///< Row index
  int _y;    ///< Column index
  T _symbol; ///< Symbol used in the move

public:
  /** @brief Construct a move at (x, y) using a symbol. */
  clsMove(int x, int y, T symbol) : _x(x), _y(y), _symbol(symbol) {}

  /** @brief Get row index. */
  int getX() const { return _x; }

  /** @brief Get column index. */
  int getY() const { return _y; }

  /** @brief Get the move symbol. */
  T getSymbol() const { return _symbol; }
};

//-----------------------------------------------------
/**
 * @brief Base template for all players (human or AI).
 *
 * @tparam T Type of symbol used by the player.
 */
template <typename T> 

class clsPlayer {
protected:
  string name;           ///< Player name
  enPlayerType type;     ///< Player type (e.g., HUMAN or COMPUTER)
  T symbol;              ///< Player's symbol on board
  clsBoard<T> *boardPtr; ///< Pointer to the game board

public:
  /**
   * @brief Construct a player with name, symbol, and type.
   */
  clsPlayer(string n, T s, enPlayerType t)
      : name(n), symbol(s), type(t), boardPtr(nullptr) {}

  virtual ~clsPlayer() {}

  /** @brief Get the player's name. */
  string getName() const { return name; }

  /** @brief Get player type (e.g., 'H' or 'C'). */
  enPlayerType getType() const { return type; }

  /** @brief Get the player's symbol. */
  T getSymbol() const { return symbol; }

  /** @brief Get a pointer to the game board. */
  clsBoard<T> *getBoardPtr() const { return boardPtr; }

  /** @brief Assign the board pointer for the player. */
  void setBoardPtr(clsBoard<T> *b) { boardPtr = b; }
};

//-----------------------------------------------------
/**
 * @brief Base class for handling user interface and input/output.
 *
 * @tparam T The type of symbol used on the board.
 */
template <typename T>

class clsUI {
protected:
  int cellWidth; ///< Width of each displayed board cell

  /**
   * @brief Ask the user for the player's name.
   */
  virtual string getPlayerName(string playerLabel) {
    string name;
    cout << "Enter " << playerLabel << " name: ";
    getline(cin >> ws, name);
    return name;
  }

  /**
   * @brief Ask the user to choose the player type from a list.
   */
  virtual enPlayerType getPlayerTypeChoice(string playerLabel,
                                           const vector<string> &options) {
    cout << "Choose " << playerLabel << " type:\n";
    for (size_t i = 0; i < options.size(); ++i)
      cout << i + 1 << ". " << options[i] << "\n";
    int choice;
    while (!clsInputValidate::validIntegerInRange(
        choice, 1, static_cast<int>(options.size()))) {
      cout << "Invalid input , Please enter the type number : " << endl;
    }
    return (choice == 2) ? enPlayerType::COMPUTER : enPlayerType::HUMAN;
  }

public:
  /**
   * @brief Construct the UI and display a welcome message.
   */
  clsUI(int cellDisplayWidth = 3) : cellWidth(cellDisplayWidth) {}

  /**
   * @brief Construct the UI and display a welcome message.
   */
  clsUI(string message, int cellDisplayWidth) : cellWidth(cellDisplayWidth) {
    cout << message << endl;
  }

  virtual ~clsUI() {}

  /** @brief Display any message to the user. */
  virtual void displayMessage(string message) { cout << message << "\n"; }

  /**
   * @brief Ask the user (or AI) to make a move.
   */
  virtual clsMove<T> *getMove(clsPlayer<T> *) = 0;

  /**
   * @brief Set up players for the game.
   */
  virtual clsPlayer<T> **setupPlayers();

  /**
   * @brief Create a player object based on input name, symbol, and type.
   */
  virtual clsPlayer<T> *createPlayer(string &name, T symbol, enPlayerType type);

  /**
   * @brief Display the current board matrix in formatted form.
   */

  virtual void displayBoardMatrix(const vector<vector<T>> &matrix) const {
    if (matrix.empty() || matrix[0].empty())
      return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "\n    ";
    for (int j = 0; j < cols; ++j)
      cout << setw(cellWidth + 1) << j;
    cout << "\n   " << string((cellWidth + 2) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
      cout << setw(2) << i << " |";
      for (int j = 0; j < cols; ++j)
        cout << setw(cellWidth) << matrix[i][j] << " |";
      cout << "\n   " << string((cellWidth + 2) * cols, '-') << "\n";
    }
    cout << endl;
  }
};

//-----------------------------------------------------
/**
 * @brief Controls the flow of a board game between two players.
 *
 * @tparam T Type of symbol used on the board.
 */
template <typename T> class clsGameManager {
  clsBoard<T> *_boardPtr;    ///< Game board
  clsPlayer<T> *_players[2]; ///< Two players
  clsUI<T> *_UI;             ///< User interface

public:
  /**
   * @brief Construct a game manager with board, players, and UI.
   */
  clsGameManager(clsBoard<T> *b, clsPlayer<T> *p[2], clsUI<T> *u)
      : _boardPtr(b), _UI(u) {
    _players[0] = p[0];
    _players[1] = p[1];
    _players[0]->setBoardPtr(b);
    _players[1]->setBoardPtr(b);
  }

  /**
   * @brief Run the main game loop until someone wins or the game ends.
   */
  void run() {
    _UI->displayBoardMatrix(_boardPtr->getBoardMatrix());
    clsPlayer<T> *currentPlayer = _players[0];

    while (true) {
      for (int i : {0, 1}) {
        currentPlayer = _players[i];
        clsMove<T> *move = _UI->getMove(currentPlayer);

        while (!_boardPtr->updateBoard(move))
          move = _UI->getMove(currentPlayer);

        _UI->displayBoardMatrix(_boardPtr->getBoardMatrix());

        if (_boardPtr->isWin(currentPlayer)) {
          _UI->displayMessage(currentPlayer->getName() + " wins!");
          return;
        }
        if (_boardPtr->isLose(currentPlayer)) {
          _UI->displayMessage(_players[1 - i]->getName() + " wins!");
          return;
        }
        if (_boardPtr->isDraw(currentPlayer)) {
          _UI->displayMessage("Draw!");
          return;
        }
      }
    }
  }
};

//-----------------------------------------------------
/**
 * @brief Default implementation of setting up two players.
 */
template <typename T> clsPlayer<T> **clsUI<T>::setupPlayers() {
  clsPlayer<T> **players = new clsPlayer<T> *[2];
  vector<string> typeOptions = {"Human", "Computer"};

  string nameX = getPlayerName("Player X");
  enPlayerType typeX = getPlayerTypeChoice("Player X", typeOptions);
  players[0] = createPlayer(nameX, static_cast<T>('X'), typeX);

  string nameO = getPlayerName("Player O");
  enPlayerType typeO = getPlayerTypeChoice("Player O", typeOptions);
  players[1] = createPlayer(nameO, static_cast<T>('O'), typeO);

  return players;
}

/**
 * @brief Default implementation of creating two players.
 */
template <typename T>
clsPlayer<T> *clsUI<T>::createPlayer(string &name, T symbol,
                                     enPlayerType type) {
  // Create player based on type
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << " player: " << name << " (" << symbol << ")\n";

  return new clsPlayer<T>(name, symbol, type);
}

#endif // BOARDGAME_CLASSES_H
