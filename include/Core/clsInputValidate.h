#ifndef INPUT_VALIDATE_H
#define INPUT_VALIDATE_H

#include <iostream>
#include <limits>

using namespace std;

class clsInputValidate {
public:
  static bool validInteger(int &userInput) {
    cin >> userInput;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return false;
    }
    return true;
  }
  static bool validIntegerInRange(int &userInput, int minVal, int maxVal) {
    return (validInteger(userInput) && userInput >= minVal &&
            userInput <= maxVal);
  }
};

#endif