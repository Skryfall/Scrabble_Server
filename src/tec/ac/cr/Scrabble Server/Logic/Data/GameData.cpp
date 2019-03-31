//
// Created by kevin on 24/03/19.
//

#include "GameData.h"
#include "../Lists/Letters/LetterList.h"
#include "Holder.h"
#include "../Lists/Matrix/Matrix.h"

GameData* GameData::gameData = nullptr;

GameData* GameData::getInstance() {
    if (!gameData){
        gameData = new GameData();
    }
    return gameData;
}

void GameData::initialize() {
    letterList->letterSorter();
}

int GameData::getNumberOfPlayers() {
    return this->numberOfPlayers;
}

void GameData::setNumberOfPlayers(int number) {
    this->numberOfPlayers = number;
}

int GameData::getRoomCode() {
    return this->roomCode;
}

void GameData::setRoomCode(int code) {
    this->roomCode = code;
}

void GameData::addPlayer() {
    this->numberOfPlayers++;
}

void GameData::generateRoom() {
    this->roomCode = rand() % 100 + 500;
}

Holder* GameData::beginGame(Holder* holder) {
    if (this->numberOfPlayers == 0){
        this->generateRoom();
        holder->setTurn(true);
        this->initialize();
    }
    this->addPlayer();
    holder->setCodetoEnter(this->roomCode);
    LetterList* letterList = LetterList::getInstance();
    holder->letterList = letterList->giveLetters(8);
    return holder;
}

Holder* GameData::processPlay(Holder* holder) {
    Matrix* matrix = Matrix::getInstance();
    LastPlayNode* tmp = holder->lastPlayList->head;
    while (tmp != nullptr){
        matrix->addIndex(tmp->getLetter(), tmp->getRow(), tmp->getColumn());
        tmp = tmp->next;
    }
    bool validated = matrix->checkPlay(holder->lastPlayList);
    holder->setValidatedPlay(validated);
    if (validated){
        int currentLetters = holder->letterList->getLenght();
        if (currentLetters != 8){
            LetterList* letterList = LetterList::getInstance();
            holder->letterList = letterList->giveLetters(8 - currentLetters);
        }
        holder->setTurn(false);
        holder->setPoints(matrix->calculatePoints(holder->lastPlayList, letterList));
        return holder;
    }else{
        tmp = holder->lastPlayList->head;
        while (tmp != nullptr){
            matrix->deleteIndex(tmp->getLetter(), tmp->getRow(), tmp->getColumn());
            tmp = tmp->next;
        }
        return holder;
    }
}