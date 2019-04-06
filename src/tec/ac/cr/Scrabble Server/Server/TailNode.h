//
// Created by kevin on 17/03/19.
//

#ifndef SCRABBLE_SERVER_TAILNODE_H
#define SCRABBLE_SERVER_TAILNODE_H

#include <string>

using namespace std;

class TailNode {

public:

    TailNode(string user){
        this->name = user;
    }

    TailNode* next = nullptr;

    void setName(string name);
    string getName();
    void setUpdated(bool updated);
    bool getUpdated();

private:

    string name;
    bool updated = false;

};


#endif //SCRABBLE_SERVER_TAILNODE_H
