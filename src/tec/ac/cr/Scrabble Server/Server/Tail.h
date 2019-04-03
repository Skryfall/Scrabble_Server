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
    int getP1();
    void setP1(int p1);
    int getP2();
    void setP2(int p2);
    int getP3();
    void setP3(int p3);
    int getP4();
    void setP4(int p4);
    bool getAllUpdated();
    void setAllUpdated(bool updated);
    void printTail();
    void deleteFirst4();
    bool searchIP(char ip);
    bool searchCurrentPlayers(char ip);
    TailNode* searchPlayer(char ip);
    int numberOfPlayer(char ip);
    void newPlayer();
    void changeTurns();
    int searchCurrentPlayerTurn();
    bool checkAllUpdated();
    void setAllOutdated();

private:

    Tail() = default;
    Tail(Tail const&) = default;
    Tail& operator = (Tail const&) = default;

    static Tail* tail;
    int lenght = 0;
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    bool allUpdated = false;

};


#endif //SCRABBLE_SERVER_TAIL_H
