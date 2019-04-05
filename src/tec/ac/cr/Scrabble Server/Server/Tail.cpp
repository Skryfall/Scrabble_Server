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

void Tail::addToTail(char ip) {
    if (this->head == nullptr){
        this->head = new TailNode(ip);
        this->lenght++;
    }else{
        TailNode* tmp = this->head;
        while (tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = new TailNode(ip);
        this->lenght++;
    }
}

void Tail::printTail() {
    TailNode* tmp = this->head;
    while (tmp != nullptr){
        cout << tmp->getIp() << ",";
        tmp = tmp->next;
    }
}

void Tail::deleteFirst4() {
    if (this->head == nullptr){
        printf("Nada que eliminar");
    }else{
        this->head = this->head->next->next->next->next;
    }
}

bool Tail::searchIP(char ip) {
    if (this->head == nullptr){
        return false;
    }else{
        TailNode* tmp = this->head;
        while (tmp != nullptr){
            if (tmp->getIp() == ip){
                return true;
            }else{
                tmp = tmp->next;
            }
        }
        return false;
    }
}

bool Tail::searchCurrentPlayers(char ip) {
    if (this->head == nullptr){
        return false;
    }else{
        int i = 1;
        TailNode* tmp = this->head;
        while (tmp != nullptr && i != 5){
            if (tmp->getIp() == ip){
                return true;
            }else{
                tmp = tmp->next;
                i++;
            }
        }
        return false;
    }
}

TailNode* Tail::searchPlayer(char ip) {
    if (this->head == nullptr){
        return nullptr;
    }else{
        int i = 1;
        TailNode* tmp = this->head;
        while (tmp != nullptr && i != 5){
            if (tmp->getIp() == ip){
                return tmp;
            }else{
                tmp = tmp->next;
                i++;
            }
        }
        return nullptr;
    }
}

int Tail::numberOfPlayer(char ip) {
    if (this->head == nullptr){
        return -1;
    }else{
        int i = 1;
        TailNode* tmp = this->head;
        while (tmp != nullptr && i != 5){
            if (tmp->getIp() == ip){
                return i;
            }else{
                tmp = tmp->next;
                i++;
            }
        }
        return -1;
    }
}

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