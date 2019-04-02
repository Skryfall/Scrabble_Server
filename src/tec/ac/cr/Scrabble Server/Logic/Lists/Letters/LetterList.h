//
// Created by kevin on 24/03/19.
//

#ifndef SCRABBLE_LETTERLIST_H
#define SCRABBLE_LETTERLIST_H

#include <QtCore/QJsonArray>
#include "LetterNode.h"
#include "../../rapidjson/prettywriter.h"

using namespace std;
using namespace rapidjson;

class LetterList {

public:

    LetterList() = default;

    static LetterList* getInstance();

    LetterNode* head = nullptr;

    int getLenght();
    void setLenght(int lenght);
    void insertNode (string letter, int points, int counter);
    void deleteNode (string letter);
    void printList ();
    void letterSorter();
    LetterNode* searchNode(int num);
    LetterList* giveLetters(int num);
    void reduceLetter(LetterNode* tmp);
    int findPoint(string letter);

    static LetterList* read(const QJsonObject& json, const QJsonArray& nodesArray);
    QJsonArray& write(QJsonObject& json, QJsonArray& nodesArray) const;

private:

    LetterList(LetterList const&) = default;
    LetterList& operator = (LetterList const&) = default;

    static LetterList* letterList;

    int length = 0;

};


#endif //SCRABBLE_LETTERLIST_H
