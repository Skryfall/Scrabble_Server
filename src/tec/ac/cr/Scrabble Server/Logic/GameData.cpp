//
// Created by kevin on 24/03/19.
//

#include "GameData.h"

GameData* GameData::gameData = nullptr;

GameData* GameData::getInstance() {
    if (!gameData){
        gameData = new GameData();
    }
    return gameData;
}

