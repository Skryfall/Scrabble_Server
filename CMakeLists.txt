cmake_minimum_required(VERSION 3.13)
project(Scrabble_Server)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(Scrabble_Server "src/tec/ac/cr/Scrabble Server/main.cpp" "src/tec/ac/cr/Scrabble Server/Server/Server.cpp" "src/tec/ac/cr/Scrabble Server/Server/Server.h" "src/tec/ac/cr/Scrabble Server/Server/Tail.cpp" "src/tec/ac/cr/Scrabble Server/Server/Tail.h" "src/tec/ac/cr/Scrabble Server/Server/TailNode.cpp" "src/tec/ac/cr/Scrabble Server/Server/TailNode.h" "src/tec/ac/cr/Scrabble Server/Logic/Data/GameData.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Data/GameData.h" "src/tec/ac/cr/Scrabble Server/Logic/Data/Holder.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Dictionary/WordList.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Dictionary/WordList.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Dictionary/WordNode.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Dictionary/WordNode.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Letters/LetterList.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Letters/LetterList.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Letters/LetterNode.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Letters/LetterNode.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/LastPlayList.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/LastPlayList.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/LastPlayNode.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/LastPlayNode.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/List.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/List.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/Node.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/Node.cpp" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/Matrix.h" "src/tec/ac/cr/Scrabble Server/Logic/Lists/Matrix/Matrix.cpp")

target_link_libraries(Scrabble_Server Qt5::Core Qt5::Gui Qt5::Widgets)