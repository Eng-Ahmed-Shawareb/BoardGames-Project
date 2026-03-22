#include "clsMainMenu.h"
#include "clsAppController.h"
#include "clsTUIUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void clsMainMenu::showLoadingAnimation() {
    clsTUIUtils::clearScreen();
    clsTUIUtils::hideCursor();

    const string spinner = "-\\|/";

    for (int i = 0; i < 20; i++) {
        clsTUIUtils::clearScreen();

        int boxWidth = 30;

        clsTUIUtils::color(enTUIColor::CYAN);
        clsTUIUtils::gotoxy(25, 10);
        cout << "\u256D";
        for (int j = 0; j < boxWidth; j++) cout << "\u2500";
        cout << "\u256E";

        clsTUIUtils::gotoxy(25, 11);
        cout << "\u2502";
        clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
        cout << "      BOARD GAMES ARCADE      ";
        clsTUIUtils::color(enTUIColor::CYAN);
        cout << "\u2502";

        clsTUIUtils::gotoxy(25, 12);
        cout << "\u2502";
        clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
        cout << "        Initializing " << spinner[i % 4] << "        ";
        clsTUIUtils::color(enTUIColor::CYAN);
        cout << "\u2502";

        clsTUIUtils::gotoxy(25, 13);
        cout << "\u2570";
        for (int j = 0; j < boxWidth; j++) cout << "\u2500";
        cout << "\u256F";

        sleepMs(60);
    }

    for (int i = 0; i < 3; i++) {
        clsTUIUtils::gotoxy(26, 12);
        clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
        cout << "            READY!            ";
        cout.flush();
        sleepMs(100);
        clsTUIUtils::gotoxy(26, 12);
        clsTUIUtils::color(enTUIColor::GREEN);
        cout << "            READY!            ";
        cout.flush();
        sleepMs(100);
    }
    sleepMs(200);
}

clsMainMenu::_enUserChoice clsMainMenu::readChoiceArrow() {
    vector<string> menu = {
        "  [1] XO Game.               ",
        "  [2] Numerical Game.        ",
        "  [3] SUS Game.              ",
        "  [4] Four In Row Game.      ",
        "  [5] XO Memory Game.        ",
        "  [6] XO Misere Game.        ",
        "  [7] XO Four by Four Game.  ",
        "  [8] Infinity XO Game.      ",
        "  [9] Pyramid Tic-Tac-Toe.   ",
        "  [10] 5x5 Tic-Tac-Toe.      ",
        "  [11] Word Tic-Tac-Toe.     ",
        "  [12] EXIT GAME             "
    };

    showLoadingAnimation();

    int selected = 0;
    int width = 44;
    int startX = 18, startY = 2;
    int menuHeight = (int)menu.size() + 6;

    while (true) {
        clsTUIUtils::clearScreen();
        clsTUIUtils::hideCursor();

        clsTUIUtils::color(enTUIColor::CYAN);

        clsTUIUtils::gotoxy(startX - 2, startY - 1);
        cout << "\u256D";
        for (int i = 0; i < width + 4; i++) cout << "\u2500";
        cout << "\u256E";

        for (int i = 0; i < menuHeight + 2; i++) {
            clsTUIUtils::gotoxy(startX - 2, startY + i);
            cout << "\u2502";
            clsTUIUtils::gotoxy(startX + width + 3, startY + i);
            cout << "\u2502";
        }

        clsTUIUtils::gotoxy(startX - 2, startY + menuHeight + 2);
        cout << "\u2570";
        for (int i = 0; i < width + 4; i++) cout << "\u2500";
        cout << "\u256F";

        clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
        clsTUIUtils::gotoxy(startX + 6, startY + 1);
        cout << " *** GAMES ARCADE *** ";

        clsTUIUtils::color(enTUIColor::CYAN);
        clsTUIUtils::gotoxy(startX - 1, startY + 2);
        for (int i = 0; i < width + 2; i++) cout << "\u2500";

        int menuStartY = startY + 4;

        for (int i = 0; i < (int)menu.size(); i++) {
            clsTUIUtils::gotoxy(startX + 3, menuStartY + i);

            if (i == selected) {

                clsTUIUtils::color(enTUIColor::BRIGHT_CYAN);
                cout << "\u25B6 ";
                clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
                cout << menu[i];
                clsTUIUtils::color(enTUIColor::BRIGHT_CYAN);
                cout << " \u25C0";
            } else if (i == (int)menu.size() - 1) {
                clsTUIUtils::color(enTUIColor::MAGENTA);
                cout << "  " << menu[i] << "   ";
            } else {
                clsTUIUtils::color(enTUIColor::BRIGHT_BLACK);
                cout << "  " << menu[i] << "   ";
            }
        }

        clsTUIUtils::color(enTUIColor::CYAN);
        clsTUIUtils::gotoxy(startX - 1, startY + menuHeight);
        for (int i = 0; i < width + 2; i++) cout << "\u2500";

        clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
        clsTUIUtils::gotoxy(startX + 1, startY + menuHeight + 1);
        cout << "  [";
        clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
        cout << "\u2191/\u2193";
        clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
        cout << "] Move Cursor   [";
        clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
        cout << "ENTER";
        clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
        cout << "] Choose Game  ";

        cout.flush();

        int key = clsTUIUtils::getch();

        if (key == 72) {
            selected = (selected - 1 + (int)menu.size()) % (int)menu.size();
        } else if (key == 80) {
            selected = (selected + 1) % (int)menu.size();
        } else if (key == '\n' || key == '\r') {

            for (int flash = 0; flash < 3; flash++) {
                clsTUIUtils::color(enTUIColor::BLACK);
                clsTUIUtils::gotoxy(startX + 3, menuStartY + selected);
                cout << "\u25B6 " << menu[selected] << " \u25C0";
                cout.flush();
                sleepMs(80);

                clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
                clsTUIUtils::gotoxy(startX + 3, menuStartY + selected);
                cout << "\u25B6 " << menu[selected] << " \u25C0";
                cout.flush();
                sleepMs(80);
            }
            clsTUIUtils::showCursor();
            clsTUIUtils::resetColor();
            clsTUIUtils::clearScreen();
            return static_cast<_enUserChoice>(selected + 1);
        }
    }
}

void clsMainMenu::implementUserChoice(_enUserChoice choice) {
  switch (choice) {
  case _enUserChoice::XO_GAME:
    clsAppController::playXOGame();
    break;
  case _enUserChoice::NUMERICAL_GAME:
    clsAppController::playNumericalGame();
    break;
  case _enUserChoice::SUS_GAME:
    clsAppController::playSUSGame();
    break;
  case _enUserChoice::FOURINROW_GAME:
    clsAppController::playFourInRowGame();
    break;
  case _enUserChoice::MEMORY_GAME:
    clsAppController::playMemoryGame();
    break;
  case _enUserChoice::MISERE_GAME:
    clsAppController::playMisereGame();
    break;
  case _enUserChoice::FOUR_BY_FOUR_GAME:
    clsAppController::playFourByFourGame();
    break;
  case _enUserChoice::INFINITY_GAME:
    clsAppController::playInfinityGame();
    break;
  case _enUserChoice::PYRAMID_GAME:
    clsAppController::playPyramidGame();
    break;
  case _enUserChoice::FIVE_BY_FIVE_GAME:
    clsAppController::playFiveByFiveGame();
    break;
  case _enUserChoice::WORD_GAME:
    clsAppController::playWordGame();
    break;
  case _enUserChoice::EXIT:
    break;
  }
}

void clsMainMenu::startBoardGameProgram() {
  while (true) {
    _enUserChoice choice = readChoiceArrow();

    if (choice == _enUserChoice::EXIT) {
        break;
    }

    bool playAgain = true;
    while (playAgain) {
        clsTUIUtils::clearScreen();
        implementUserChoice(choice);
        clsTUIUtils::flushInput();

        bool validSelection = false;
        int playAgainSelected = 0;
        vector<string> vPaMenu = {"Play Again", "Return to Main Menu"};

        while (!validSelection) {
            clsTUIUtils::clearScreen();
            clsTUIUtils::hideCursor();

            int boxWidth = 36;
            int boxHeight = 6;
            int boxX = 22;
            int boxY = 8;

            clsTUIUtils::color(enTUIColor::CYAN);
            clsTUIUtils::gotoxy(boxX, boxY);
            cout << "\u256D"; for(int i=0; i<boxWidth; i++) cout << "\u2500"; cout << "\u256E";

            for(int i=1; i<=boxHeight; i++) {
                clsTUIUtils::gotoxy(boxX, boxY+i); cout << "\u2502";
                clsTUIUtils::gotoxy(boxX+boxWidth+1, boxY+i); cout << "\u2502";
            }

            clsTUIUtils::gotoxy(boxX, boxY+boxHeight+1);
            cout << "\u2570"; for(int i=0; i<boxWidth; i++) cout << "\u2500"; cout << "\u256F";

            clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
            clsTUIUtils::printCentered(boxY + 1, "*** GAME OVER ***", boxWidth, boxX);

            clsTUIUtils::color(enTUIColor::CYAN);
            clsTUIUtils::gotoxy(boxX + 1, boxY + 2);
            for(int i=0; i<boxWidth; i++) cout << "\u2500";

            for (int i = 0; i < (int)vPaMenu.size(); i++) {
                clsTUIUtils::gotoxy(boxX + 8, boxY + 4 + i);
                if (i == playAgainSelected) {
                    clsTUIUtils::color(enTUIColor::BRIGHT_CYAN);
                    cout << "\u25B6 ";
                    clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
                    cout << vPaMenu[i];
                    clsTUIUtils::color(enTUIColor::BRIGHT_CYAN);
                    cout << " \u25C0";
                } else {
                    clsTUIUtils::color(enTUIColor::BRIGHT_BLACK);
                    cout << "  " << vPaMenu[i] << "   ";
                }
            }

            cout.flush();

            int key = clsTUIUtils::getch();

            if (key == 72) {
                playAgainSelected = (playAgainSelected - 1 + vPaMenu.size()) % vPaMenu.size();
            }

            else if (key == 80) {
                playAgainSelected = (playAgainSelected + 1) % vPaMenu.size();
            }

            else if (key == '\n' || key == '\r' || key == 13 || key == 10) {

                for (int flash = 0; flash < 3; flash++) {
                    clsTUIUtils::color(enTUIColor::BLACK);
                    clsTUIUtils::gotoxy(boxX + 8, boxY + 4 + playAgainSelected);
                    cout << "\u25B6 " << vPaMenu[playAgainSelected] << " \u25C0";
                    cout.flush();
                    sleepMs(80);

                    clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
                    clsTUIUtils::gotoxy(boxX + 8, boxY + 4 + playAgainSelected);
                    cout << "\u25B6 " << vPaMenu[playAgainSelected] << " \u25C0";
                    cout.flush();
                    sleepMs(80);
                }
                validSelection = true;
            }
        }

        if (playAgainSelected == 1) {
            playAgain = false;
        }
    }
  }

  clsTUIUtils::clearScreen();
  clsTUIUtils::hideCursor();

  int exitWidth = 76;
  int exitHeight = 8;
  int exitX = 2;
  int exitY = 8;

  clsTUIUtils::color(enTUIColor::CYAN);
  clsTUIUtils::gotoxy(exitX, exitY);
  cout << "\u256D"; for(int i=0; i<exitWidth; i++) cout << "\u2500"; cout << "\u256E";
  for(int i=1; i<=exitHeight; i++) {
      clsTUIUtils::gotoxy(exitX, exitY+i); cout << "\u2502";
      clsTUIUtils::gotoxy(exitX+exitWidth+1, exitY+i); cout << "\u2502";
  }
  clsTUIUtils::gotoxy(exitX, exitY+exitHeight+1);
  cout << "\u2570"; for(int i=0; i<exitWidth; i++) cout << "\u2500"; cout << "\u256F";

  clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
  clsTUIUtils::printCentered(exitY + 2, "Thank you for using Shawareb's BoardGames Hub", exitWidth, exitX);
  clsTUIUtils::color(enTUIColor::BRIGHT_WHITE);
  clsTUIUtils::printCentered(exitY + 3, "I hope you enjoyed the experience.", exitWidth, exitX);
  clsTUIUtils::color(enTUIColor::BRIGHT_BLACK);
  clsTUIUtils::printCentered(exitY + 5, "For any feedback, suggestions, or inquiries, please feel free to contact me at:", exitWidth, exitX);
  clsTUIUtils::color(enTUIColor::BRIGHT_BLUE);
  clsTUIUtils::printCentered(exitY + 6, "eng.ahmedshawareb@gmail.com", exitWidth, exitX);

  cout << "\n\n\n\n\n\n\n";
  clsTUIUtils::showCursor();
  clsTUIUtils::resetColor();
}