//
// Created by kevin on 26/03/19.
//

#include "WordList.h"
#include "algorithm"

#include <string>
#include<fstream>
#include<iostream>
#include<cstdlib>

WordList* WordList::wordList = nullptr;

WordList* WordList::getInstance() {
    if (!wordList){
        wordList = new WordList;
    }
    return wordList;
}

int WordList::getLenght() {
    return this->lenght;
}

void WordList::setLenght(int lenght) {
    this->lenght = lenght;
}

void WordList::addWord(string word) {
    if (this->head == nullptr) {
        this->head = new WordNode(word);
        this->lenght++;
    }else{
        WordNode* tmp = this->head;
        while (tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = new WordNode(word);
        this->lenght++;
    }
}

bool WordList::searchWord(string word) {
    ifstream fin;
    fin.open("/home/kevin/CLionProjects/Scrabble/src/tec/ac/cr/Scrabble/Logic/Lists/Dictionary/words.text");
    if (fin.fail()) {
        cout << "No hay ni pinga.\n";
        return false;
    }
    string search = word;
    bool isFound = false;
    while (!fin.eof()) {
        string temp;
        getline(fin, temp);
        for (int i = 0; i < search.size(); i++) {
            if (temp[i] == search[i])
                isFound = true;
            else {
                isFound = false;
                break;
            }
        }

        if (isFound) {
            cout << "Su palabra si esta y es ";
            cout << temp;
            fin.close();
            return true;
        }
    }

    if (fin.eof()) {
        cout << "Su palabra no existe F\n";
        fin.close();
        return false;
    }
}

bool WordList::searchDuplicates(string word) {
    if (this->head == nullptr){
        return false;
    }else{
        WordNode* tmp = this->head;
        while (tmp != nullptr){
            if (tmp->getWord() == word){
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
}

bool WordList::checkWordsInList() {
    if (this->head == nullptr){
        return false;
    }else{
        WordNode* tmp = this->head;
        while (tmp != nullptr){
            if (!this->searchWord(tmp->getWord())){
                return false;
            }else{
                tmp = tmp->next;
            }
        }
        return true;
    }
}