//
// Created by kevin on 17/03/19.
//

#include <cstdio>
#include <iostream>
#include "Tail.h"

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