# 🎮 Shawareb’s BoardGames Hub

![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey)
![Architecture](https://img.shields.io/badge/Architecture-OOP-success)
![AI](https://img.shields.io/badge/AI-Minimax%20%2B%20AlphaBeta-orange)

**Shawareb’s BoardGames Hub** is a highly scalable, cross-platform terminal game engine written in C++. Expanding far beyond a standard console application, this framework supports **11 distinct games**, features a dynamic custom Text User Interface (TUI), and integrates a universal Artificial Intelligence engine capable of playing optimally against human opponents.

> **🎥 [Watch the Full Video Demonstration Here](#)** *(https://youtu.be/6iBGyr11xTA)*

---

## 🌟 Key Features

### 🎲 11 Playable Games
1. **Classic Tic-Tac-Toe (3x3)**
2. **Numerical Tic-Tac-Toe**
3. **Pyramic Tic-Tac-Toe**
4. **Four-in-a-Row (Connect 4)**
5. **5x5 Tic-Tac-Toe**
6. **Word Tic-Tac-Toe** *(Validated against a real English dictionary)*
7. **Misere Tic-Tac-Toe**
8. **Memory Game**
9. **Infinity Tic-Tac-Toe**
10. **4x4 Tic-Tac-Toe**
11. **SUS Game**

### 🧠 "Smart AI" Engine
Every game includes a dedicated AI opponent powered by the **Minimax algorithm**.
* **Alpha-Beta Pruning:** Implemented to instantly cut off mathematically weak decision branches, saving millions of calculations in massive game trees like Four-in-a-Row.
* **Depth Limiting:** Applied to complex variants to ensure the game remains responsive in real-time.

### 🖥️ Custom Text User Interface (TUI)
Standard C++ `std::cout` forces a scrolling terminal. To solve this, a custom cross-platform TUI was engineered (`clsTUIUtils`). By bypassing standard streams and utilizing ANSI Escape Sequences (Linux) and `<windows.h>` APIs (Windows), the engine achieves:
* Dynamic, stationary grid rendering (no scrolling!)
* Colored text formatting
* Real-time arrow-key navigation without input-buffer ghosting

---

## 🏗️ Software Architecture (OOP)

The core strength of this framework is its strict adherence to Object-Oriented Design principles, allowing infinite games to be added without altering the core engine.
* **Abstraction & Inheritance:** Built upon base abstract classes (`clsBoard`, `clsPlayer`), every game variant inherits core mechanics to drastically reduce code duplication.
* **Runtime Polymorphism:** The main application controller operates using generic pointers. It executes the game loop dynamically without needing to hardcode the rules for the specific game being played.
* **Data Structures for Performance:** The Word Game utilizes an $O(1)$ Hash Table (`std::unordered_set`) to instantly validate user inputs against an English dictionary without freezing the terminal.

---

## 🚀 Getting Started

### Prerequisites
* A C++ compiler supporting **C++17** or higher (GCC, Clang, or MSVC).
* **CMake** (version 3.10 or higher).

### Build Instructions (Linux / Mac / Windows)
1. **Clone the repository:**
   `git clone https://github.com/your-username/boardgames-project.git`
   `cd boardgames-project`

2. **Create a build directory:**
   `mkdir build && cd build`

3. **Generate build files using CMake:**
   `cmake ..`

4. **Compile the engine:**
   `make`

5. **Run the Hub:**
   `./BoardGamesHub`

*(Note: Ensure your terminal window is appropriately sized to fully enjoy the TUI layout).*

---

## 📂 Project Structure

    ├── CMakeLists.txt              # CMake build configuration
    ├── .gitignore                  # Git ignore rules for clean commits
    ├── Project_Report_Shawarebs_BoardGames_Hub.pdf # Detailed technical project report
    ├── include/                    # Header files (.h)
    │   ├── Core/                   # Base classes, TUI Utils, Input Validation, and Dictionary (dic.txt)
    │   ├── Controllers/            # AppController and MainMenu routing
    │   ├── Games/                  # Board and UI definitions for all 11 games
    │   └── Players/                # AI Player logic (Minimax algorithms)
    └── src/                        # Implementation files (.cpp)
        ├── main.cpp                # Application entry point
        ├── Controllers/            
        ├── Games/                  
        ├── Players/                
        └── Core/                   

---

## 📜 Credits & Acknowledgments
* **Developer:** Ahmed Amr Abdelbadea Ali Shawareb (Cairo University)
* **Base Framework:** The foundational abstract classes (`BoardGame_Classes.h`) were generously provided by Dr. Mohammad El-Ramly as part of the course materials. All extended game logic, TUI utilities, and Minimax AI implementations were built on top of this initial architecture.

## 📬 Contact
* **Email:** eng.ahmedshawareb@gmail.com
* **LinkedIn:** [Ahmed Shawareb](#) *(https://www.linkedin.com/in/ahmed-shawareb-82183133b/)*
