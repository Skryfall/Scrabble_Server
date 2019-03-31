//
// Created by kevin on 24/03/19.
//

#ifndef SCRABBLE_SERVER_GAMEDATA_H
#define SCRABBLE_SERVER_GAMEDATA_H


#include "../Lists/Letters/LetterList.h"

class GameData {

public:

    static GameData* getInstance();

    int getNumberOfPlayers();
    void setNumberOfPlayers(int number);
    int getRoomCode();
    void setRoomCode(int code);
    void addPlayer();
    void generateRoom();
    Holder* beginGame(Holder* holder);
    Holder* processPlay(Holder* holder);


private:

    GameData() = default;
    GameData(GameData const&) = default;
    GameData& operator = (GameData const&) = default;

    static GameData* gameData;
    LetterList letterList = new LetterList;
    int numberOfPlayers = 0;
    int roomCode = 0;

};


#endif //SCRABBLE_SERVER_GAMEDATA_H
