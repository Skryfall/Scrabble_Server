//
// Created by kevin on 17/03/19.
//

#include <cstdio>
#include <iostream>
#include "Tail.h"
#include "../Logic/Data/GameData.h"

using namespace std;
Tail* Tail::tail = nullptr;


Tail* Tail::getInstance() {
    if (!tail){
        tail = new Tail;
    }
    return tail;
}

int Tail::getLenght() {
    return this->lenght;
}

void Tail::setLenght(int lenght) {
    this->lenght = lenght;
}

int Tail::getP1() {
    return this->p1;
}

void Tail::setP1(int p1) {
    this->p1 = p1;
}

int Tail::getP2() {
    return this->p2;
}

void Tail::setP2(int p2) {
    this->p2 = p2;
}

int Tail::getP3() {
    return this->p3;
}

void Tail::setP3(int p3) {
    this->p3 = p3;
}

int Tail::getP4() {
    return this->p4;
}

void Tail::setP4(int p4) {
    this->p4 = p4;
}

bool Tail::getAllUpdated() {
    return this->allUpdated;
}

//! Method that puts all the players in an updated state
void Tail::setAllUpdated() {
    if (this->head == nullptr){
        cout << "No hay nada" << endl;
    }else{
        TailNode* tmp = this->head;
        int i = 0;
        while (tmp != nullptr && i != 5){
            tmp->setUpdated(true);
            tmp = tmp->next;
            i++;
        }
    }
}

 //! Method that adds a player to the tail
 //! \param ip of the player that will be added
void Tail::addToTail(string name) {
    if (this->head == nullptr){
        this->head = new TailNode(name);
        this->lenght++;
    }else{
        TailNode* tmp = this->head;
        while (tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = new TailNode(name);
        this->lenght++;
    }
}

//! Method that prints the tail
void Tail::printTail() {
    TailNode* tmp = this->head;
    while (tmp != nullptr){
        cout << tmp->getName() << ",";
        tmp = tmp->next;
    }
}

//! Method that deletes the first four nodes from the list
void Tail::deleteFirst4() {
    if (this->head == nullptr){
        printf("Nada que eliminar");
    }else{
        this->head = this->head->next->next->next->next;
    }
}

//! Method that searches a player from its ip
//! \param ip that will be used to search a player
//! \return boolean to know if it exists or not
bool Tail::searchName(string name) {
    if (this->head == nullptr){
        return false;
    }else{
        TailNode* tmp = this->head;
        while (tmp != nullptr){
            if (tmp->getName() == name){
                return true;
            }else{
                tmp = tmp->next;
            }
        }
        return false;
    }
}

//! Method that searches a player that is currently playing
//! \param ip that will be used to search a player
//! \return boolean to know if it exists or not
bool Tail::searchCurrentPlayers(string name) {
    if (this->head == nullptr){
        return false;
    }else{
        int i = 1;
        TailNode* tmp = this->head;
        while (tmp != nullptr && i != 5){
            if (tmp->getName() == name){
                return true;
            }else{
                tmp = tmp->next;
                i++;
            }
        }
        return false;
    }
}

bool Tail::searchLastJoined(string name) {
    if (this->head == nullptr){
        return false;
    }else{
        int i = 1;
        TailNode* tmp = this->head;
        while (tmp->next != nullptr && i != 5){
            if (tmp->getName() == name){
                return true;
            }else{
                tmp = tmp->next;
                i++;
            }
        }
        return false;
    }
}

 //! Method that searches a player that is currently playing
 //! \param ip that will be used to search a player
 //! \return the node of the player
TailNode* Tail::searchPlayer(string name) {
    if (this->head == nullptr){
        return nullptr;
    }else{
        int i = 1;
        TailNode* tmp = this->head;
        while (tmp != nullptr && i != 5){
            if (tmp->getName() == name){
                return tmp;
            }else{
                tmp = tmp->next;
                i++;
            }
        }
        return nullptr;
    }
}

//! Method that searches the number of a player
//! \param ip that will be used to search a player
//! \return an integer with the number of the player
int Tail::numberOfPlayer(string name) {
    if (this->head == nullptr){
        return -1;
    }else{
        int i = 1;
        TailNode* tmp = this->head;
        while (tmp != nullptr && i != 5){
            if (tmp->getName() == name){
                return i;
            }else{
                tmp = tmp->next;
                i++;
            }
        }
        return -1;
    }
}

//! Method that adds a player to the game
void Tail::newPlayer() {
    if (this->p1 == 0){
        this->p1 = 1;
    }else if (this->p2 == 0){
        this->p2 = 2;
    }else if (this->p3 == 0){
        this->p3 = 3;
    }else{
        this->p4 = 4;
    }
}

//! Method that changes players turns
void Tail::changeTurns() {
    GameData* gameData = GameData::getInstance();
    if (this->p1 == 1){
        this->p1 = gameData->getMaxNumberOfPlayers();
        this->p2--;
        this->p3--;
        this->p4--;
    }if (this->p2 == 1){
        this->p1--;
        this->p2 = gameData->getMaxNumberOfPlayers();
        this->p3--;
        this->p4--;
    }if (this->p3 == 1){
        this->p1--;
        this->p2--;
        this->p3 = gameData->getMaxNumberOfPlayers();
        this->p4--;
    }else{
        this->p1--;
        this->p2--;
        this->p3--;
        this->p4 = gameData->getMaxNumberOfPlayers();
    }
}

//! Method that searches the current player turn
//! \return an integer with the current number of player that has an active turn
int Tail::searchCurrentPlayerTurn() {
    if (this->p1 == 1){
        return 1;
    }if (this->p2 == 1){
        return 2;
    }if (this->p3 == 1){
        return 3;
    }else{
        return 4;
    }
}

//! Method that checks if all the players are updated
//! \return boolean to know if all of them are updated or not
bool Tail::checkAllUpdated() {
    if (this->head == nullptr){
        return false;
    }else{
        TailNode* tmp = this->head;
        int i = 0;
        while (tmp != nullptr && i != 5){
            if (!tmp->getUpdated()){
                return false;
            }
            tmp = tmp->next;
            i++;
        }
        return true;
    }
}

//! Method that sets all the players to outdated
void Tail::setAllOutdated() {
    if (this->head == nullptr){
        cout << "No hay nada" << endl;
    }else{
        TailNode* tmp = this->head;
        int i = 0;
        while (tmp != nullptr && i != 5){
            tmp->setUpdated(false);
            tmp = tmp->next;
            i++;
        }
    }
}