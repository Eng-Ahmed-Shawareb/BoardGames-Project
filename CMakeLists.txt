cmake_minimum_required(VERSION 3.28.3)
project(BoardGames)
file(GLOB SRC_FILES src/*.cpp)
file(GLOB SRC_GAMES_FILES src/Games/*cpp)
file(GLOB SRC_CONTROL_FILES src/Controllers/*cpp)
file(GLOB SRC_PLAYERS_FILES src/Players/*cpp)
file(GLOB SRC_CORE_FILES src/Core/*cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES} ${SRC_GAMES_FILES} ${SRC_CONTROL_FILES} ${SRC_PLAYERS_FILES} ${SRC_CORE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC 
    include/
    include/Core/
    include/Games/
    include/Controllers
    include/Players
    )