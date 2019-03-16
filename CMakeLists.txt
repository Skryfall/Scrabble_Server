cmake_minimum_required(VERSION 3.13)
project(Scrabble_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Scrabble_Server "src/tec/ac/cr/Scrabble Server/main.cpp" "src/tec/ac/cr/Scrabble Server/Server/Server.cpp" "src/tec/ac/cr/Scrabble Server/Server/Server.h")