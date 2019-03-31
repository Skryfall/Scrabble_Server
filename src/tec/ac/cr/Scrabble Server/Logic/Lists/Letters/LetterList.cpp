//
// Created by kevin on 24/03/19.
//

#include <string>
#include <iostream>
#include "LetterList.h"
#include "../../rapidjson/document.h"

using namespace std;

LetterList* LetterList::letterList = nullptr;

LetterList* LetterList::getInstance() {
    if (!letterList){
        letterList = new LetterList;
        letterList->letterSorter();
    }
    return letterList;
}

void LetterList::letterSorter() {
    insertNode("A", 1, 12);
    insertNode("E", 1, 12);
    insertNode("0", 1, 9);
    insertNode("I", 1, 6);
    insertNode("S", 1, 6);
    insertNode("N", 1, 5);
    insertNode("L", 1, 4);
    insertNode("R", 1, 5);
    insertNode("U", 1, 5);
    insertNode("T", 1, 4);
    insertNode("D", 2, 5);
    insertNode("G", 2, 2);
    insertNode("C", 3, 4);
    insertNode("B", 3, 2);
    insertNode("M", 3, 2);
    insertNode("P", 3, 2);
    insertNode("H", 4, 2);
    insertNode("F", 4, 1);
    insertNode("V", 4, 1);
    insertNode("Y", 4, 1);
    insertNode("Ch", 5, 1);
    insertNode("Q", 5, 1);
    insertNode("J", 8, 1);
    insertNode("Ll", 8, 1);
    insertNode("Ñ", 8, 1);
    insertNode("RR", 8, 1);
    insertNode("X", 8, 1);
    insertNode("Z", 10, 1);
    insertNode("", 0, 2);
}

int LetterList::getLenght() {
    return this->length;
}

void LetterList::setLenght(int lenght) {
    this->length = lenght;
}

void LetterList::insertNode(string letter, int points, int counter) {
    if (this->head == nullptr){
        this->head = new LetterNode(letter, points, counter);
        this->length++;
    }else{
        LetterNode* tmp = this->head;
        while (tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = new LetterNode(letter, points, counter);
        this->length++;
    }
}

void LetterList::deleteNode(string letter) {
    if (this->head == nullptr){
        printf("Theres no node to delete");
    }else if(this->head->getLetter() == letter){
        this->head = this->head->next;
        this->length--;
    }else{
        LetterNode* tmp = this->head;
        while (tmp->next != nullptr){
            if (tmp->next->getLetter() == letter){
                tmp->next = tmp->next->next;
                this->length--;
                break;
            }else{
                tmp = tmp->next;
            }
        }
    }
}

void LetterList::printList() {
    if (this->head == nullptr){
        printf("Lista nula");
    }else{
        LetterNode* tmp = this->head;
        while (tmp != nullptr){
            cout << tmp->getLetter() << endl;
            tmp = tmp->next;
        }
    }
}

LetterNode* LetterList::searchNode(int num) {
    LetterNode* tmp = this->head;
    for (int i = 0; i != num; i++){
        tmp = tmp->next;
    }
    return tmp;
}

LetterList* LetterList::giveLetters(int num) {
    LetterList* letterList1 = new LetterList;
    for(int i = 0; i != num; i++){
        LetterNode* tmp = this->searchNode(rand() % this->length);
        letterList1->insertNode(tmp->getLetter(), tmp->getPoints(), 1);
        this->reduceLetter(tmp);
    }
    return letterList1;
}

void LetterList::reduceLetter(LetterNode* tmp) {
    tmp->lowerCounter();
    if (tmp->getCounters() == 0){
        this->deleteNode(tmp->getLetter());
    }
}

int LetterList::findPoint(string letter) {
    LetterNode* letterNode = this->head;
    while (letterNode != nullptr){
        if (letterNode->getLetter() == letter){
            return letterNode->getPoints();
        }
        letterNode = letterNode->next;
    }
}

string LetterList::serialize() {
    StringBuffer sB;
    Writer<StringBuffer> writer(sB);
    this->serializer(writer);
    return sB.GetString();
}

template<typename Writer>
void LetterList::serializer(Writer &writer) const {
    writer.StartObject();
    writer.String("lenght");
    writer.Int(this->length);
    writer.String("head");
    if (this->head == nullptr){
        writer.Null();
        writer.EndObject();
    }else{
        writer.String(this->head->serialize().c_str());
        writer.EndObject();
    }
}

LetterList* LetterList::deserialize(const char *json) {
    LetterList* parsedList = new LetterList();
    Document doc;
    doc.Parse(json);
    parsedList->setLenght(doc["lenght"].GetInt());
    if (doc["head"].IsNull()){
        parsedList->head = nullptr;
        return parsedList;
    }else{
        parsedList->head = this->head->deserialize(doc["head"].GetString());
        return parsedList;
    }
}