//
// Created by kevin on 17/03/19.
//

#ifndef SCRABBLE_SERVER_TAIL_H
#define SCRABBLE_SERVER_TAIL_H


#include "TailNode.h"

class Tail {

public:

    static Tail* getInstance();

    TailNode* head = nullptr;

    int getLenght();
    void setLenght(int lenght);
    void addToTail(char ip);
    void printTail();
    void deleteFirst4();

private:

    Tail() = default;
    Tail(Tail const&) = default;
    Tail& operator = (Tail const&) = default;

    int lenght = 0;
    static Tail* tail;

};


#endif //SCRABBLE_SERVER_TAIL_H
