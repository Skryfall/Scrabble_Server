//
// Created by kevin on 24/03/19.
//

#include "GameData.h"
#include "../Lists/Letters/LetterList.h"
#include "Holder.h"
#include "../Lists/Matrix/Matrix.h"
#include "../../Server/Tail.h"

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

int GameData::getMaxNumberOfPlayers() {
    return this->maxNumberOfPlayers;
}

void GameData::setMaxNumberOfPlayers(int players) {
    this->maxNumberOfPlayers = players;
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

 //! Method that prepares the beginning of the game
 //! \param holder holder that has the player data
 //! \return holder with the updated player data
Holder* GameData::beginGame(Holder* holder) {
    Tail* tail = Tail::getInstance();
    if (this->numberOfPlayers == 0){
        tail->setAllUpdated();
        this->generateRoom();
        holder->setTurn(true);
        this->initialize();
        if (holder->getPoints() == 4){
            this->maxNumberOfPlayers = 4;
        }if (holder->getPoints() == 3){
            this->maxNumberOfPlayers = 3;
        }if (holder->getPoints() == 2){
            this->maxNumberOfPlayers = 2;
        }
        holder->setPoints(0);
    }
    this->addPlayer();
    holder->setCodetoEnter(this->roomCode);
    LetterList* letterList = LetterList::getInstance();
    holder->letterList = letterList->giveLetters(8);
    tail->newPlayer();
    return holder;
}

 //! Method that processes the current play
 //! \param holder holder that has the player data
 //! \return holder with the updated data
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
        tmp = holder->lastPlayList->head;
        while (tmp != nullptr){
            holder->letterList->deleteNode(tmp->getLetter());
            tmp = tmp->next;
        }
        int currentLetters = holder->letterList->getLenght();
        if (currentLetters != 8){
            LetterList* letterList = LetterList::getInstance();
            holder->letterList = letterList->giveLetters(8 - currentLetters);
        }
        holder->setTurn(false);
        holder->setPoints(matrix->calculatePoints(holder->lastPlayList, letterList));
        LastPlayList::setInstance(holder->lastPlayList);
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