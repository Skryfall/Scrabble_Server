cmake_minimum_required(VERSION 3.13)
project(Scrabble_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Scrabble_Server "src/tec/ac/cr/Scrabble Server/main.cpp" "src/tec/ac/cr/Scrabble Server/Server/Server.cpp" "src/tec/ac/cr/Scrabble Server/Server/Server.h" "src/tec/ac/cr/Scrabble Server/Server/Tail.cpp" "src/tec/ac/cr/Scrabble Server/Server/Tail.h" "src/tec/ac/cr/Scrabble Server/Server/TailNode.cpp" "src/tec/ac/cr/Scrabble Server/Server/TailNode.h" "src/tec/ac/cr/Scrabble Server/Logic/GameData.cpp" "src/tec/ac/cr/Scrabble Server/Logic/GameData.h" "src/tec/ac/cr/Scrabble Server/Logic/Player.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Player.h")