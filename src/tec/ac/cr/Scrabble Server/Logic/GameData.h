//
// Created by kevin on 24/03/19.
//

#ifndef SCRABBLE_SERVER_GAMEDATA_H
#define SCRABBLE_SERVER_GAMEDATA_H


class GameData {

public:

    static GameData* getInstance();

    //matriz
    //lista de letras


private:

    GameData() = default;
    GameData(GameData const&) = default;
    GameData& operator = (GameData const&) = default;

    static GameData* gameData;

};


#endif //SCRABBLE_SERVER_GAMEDATA_H
