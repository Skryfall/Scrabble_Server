//
// Created by kevin on 26/03/19.
//

#ifndef SCRABBLE_LASTPLAYLIST_H
#define SCRABBLE_LASTPLAYLIST_H

#include "LastPlayNode.h"
#include <string>
#include <QtCore/QJsonObject>
#include "../../rapidjson/prettywriter.h"

using namespace std;
using namespace rapidjson;

class LastPlayList {

public:

    static LastPlayList* getInstance();

    LastPlayNode* head = nullptr;

    int getLenght();
    void setLenght(int lenght);
    void addPlay(string letter, int row, int column);
    void deletePlay(string letter, int row, int column);

    static LastPlayList* read(const QJsonObject& json, const QJsonArray& nodesArray);
    QJsonArray& write(QJsonObject& json, QJsonArray& nodesArray) const;

private:

    LastPlayList() = default;
    LastPlayList(LastPlayList const&) = default;
    LastPlayList& operator = (LastPlayList const&) = default;

    static LastPlayList* lastPlayList;

    int lenght = 0;

};


#endif //SCRABBLE_LASTPLAYLIST_H
