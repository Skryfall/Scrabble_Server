//
// Created by kevin on 17/03/19.
//

#ifndef SCRABBLE_SERVER_TAILNODE_H
#define SCRABBLE_SERVER_TAILNODE_H


class TailNode {

public:

    TailNode(char user){
        this->ip = user;
    }

    TailNode* next = nullptr;

    void setIp(char ip);
    char getIp();
    void setUpdated(bool updated);
    bool getUpdated();

private:

    char ip;
    bool updated = false;

};


#endif //SCRABBLE_SERVER_TAILNODE_H
