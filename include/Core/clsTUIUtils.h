
#pragma once

#include <string>
#include <iostream>

using namespace std;

enum class enTUIColor {
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    DEFAULT = 39,
    BRIGHT_BLACK = 90,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN = 96,
    BRIGHT_WHITE = 97
};

class clsTUIUtils {
public:

    static void gotoxy(int x, int y);

    static void color(enTUIColor colorCode);

    static void resetColor();

    static void hideCursor();

    static void showCursor();

    static void clearScreen();

    static int getch();

    static void printCentered(int y, const string& text, int totalWidth, int offsetX = 0);

    static void drawHLine(int x, int y, int length, string ch);

    static void flushInput();
};
