//
// Created by kevin on 24/03/19.
//

#include "LetterNode.h"
#include "../../rapidjson/document.h"

void LetterNode::setLetter(string letter) {
    this->letter = letter;
}

string LetterNode::getLetter() {
    return this->letter;
}

void LetterNode::setPoints(int point) {
    this->point = point;
}

int LetterNode::getPoints() {
    return this->point;
}

void LetterNode::setCounters(int counter) {
    this->counter = counter;
}

int LetterNode::getCounters() {
    return this->counter;
}

void LetterNode::lowerCounter() {
    this->counter--;
}

 //! Method that deserializes a LastPlayNode from json
 //! \param json where the data is
void LetterNode::read(const QJsonObject &json) {
    if (json.contains("letter") && json["letter"].isString()){
        letter = (json["letter"].toString().toUtf8().constData());
    }if (json.contains("point") && json["point"].isDouble()){
        point = (json["point"].toInt());
    }if (json.contains("counter") && json["counter"].isDouble()){
        counter = (json["counter"].toInt());
    }
}

 //! Method that serializes a LastPlayNode to json
 //! \param json where the data will be
void LetterNode::write(QJsonObject &json) const {
    json["letter"] = QString::fromStdString(letter);
    json["point"] = point;
    json["counter"] = counter;
}