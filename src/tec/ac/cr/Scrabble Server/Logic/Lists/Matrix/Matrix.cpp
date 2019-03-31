//
// Created by Alejandro Ibarra on 2019-03-23.
//

#include "Matrix.h"
#include "LastPlayList.h"
#include "../Dictionary/WordList.h"
#include "../Letters/LetterList.h"
#include <unordered_set>

Matrix* Matrix::matrix = nullptr;

/**
* Gets Singleton instance of Matrix. Default is 15x15 board.
* @return Matrix instance
*/
Matrix* Matrix::getInstance() {
    if (!matrix) {
        matrix = new Matrix;
        matrix->initialize();
        matrix->assignMultipliers();
    }
    return matrix;
}

int Matrix::getLenght() {
    return this->length;
}

void Matrix::setLenght(int lenght) {
    this->length = lenght;
}

int Matrix::getRows() {
    return this->rows;
}

void Matrix::setRows(int rows) {
    this->rows = rows;
}

int Matrix::getColumns() {
    return this->columns;
}

void Matrix::setColumns(int columns) {
    this->columns = columns;
}

int Matrix::getLastPlayRow() {
    return this->lastPlayRow;
}

void Matrix::setLastPlayRow(int row) {
    this->lastPlayRow = row;
}

int Matrix::getLastPlayColumn() {
    return this->lastPlayColumn;
}

void Matrix::setLastPlayColumn(int column) {
    this->lastPlayColumn = column;
}

int Matrix::getPreLastPlayRow() {
    return this->preLastPlayRow;
}

void Matrix::setPreLastPlayRow(int row) {
    this->preLastPlayRow = row;
}

int Matrix::getPreLastPlayColumn() {
    return this->preLastPlayColumn;
}

void Matrix::setPreLastPlayColumn(int column) {
    this->preLastPlayColumn = column;
}

/**
* Add a new value to list.
* @param n int to add
* @param multiplier int specific multiplier of square. Default is 0 (no multiplier)
*/
void Matrix::addRow(List* list) {
    if (this->head == nullptr) {
        this->head = list;
        this->length++;
    }else {
        List* tmp = this->head;
        while (tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = list;
        this->length++;
    }
}

/**
* Adds a specific value in position.
* @param letter string to add to position
* @param i int of row
* @param j int of column
*/
void Matrix::addIndex(string letter, int i, int j) {
    Node* pos = index(i, j);
    pos->setLetter(letter);
    LastPlayList* lastPlayList = LastPlayList::getInstance();
    lastPlayList->addPlay(letter, i, j);
    this->preLastPlayRow = this->lastPlayRow;
    this->preLastPlayColumn = this->lastPlayColumn;
    this->lastPlayRow = i;
    this->lastPlayColumn = j;
}

void Matrix::deleteIndex(string letter, int i, int j) {
    Node* pos = index(i, j);
    pos->setLetter("");
    LastPlayList* lastPlayList = LastPlayList::getInstance();
    lastPlayList->deletePlay(letter, i, j);
}


/**
* Assigns multipliers to nodes based on default Scrabble board.
*/
void Matrix::assignMultipliers() {
    List* currentList = this->head;
    Node* tmp = this->head->getHead();
    unordered_set<int> DL = {4, 12, 37, 39, 46, 53, 60, 93, 97, 99, 103, 109, 117,
                             123, 127, 129, 133, 166, 173, 180, 187, 189, 214, 222};
    unordered_set<int> DW = {17, 29, 33, 43, 49, 57, 65, 71, 155, 161, 169, 177, 183, 193, 197, 209};
    unordered_set<int> TL = {21, 25, 77, 81, 85, 89, 137, 141, 145, 149, 201, 203};
    unordered_set<int> TW = {1, 8, 15, 106, 120, 211, 218, 225};
    while (currentList != nullptr) {
        while (tmp != nullptr) {
            if (DL.count(tmp->getID())) {
                tmp->setMultiplier(1);
            } else if (DW.count(tmp->getID())) {
                tmp->setMultiplier(2);
            } else if (TL.count(tmp->getID())) {
                tmp->setMultiplier(3);
            } else if (TW.count(tmp->getID())) {
                tmp->setMultiplier(4);
            }
            tmp = tmp->next;
        }
        currentList = currentList->next;
        if (currentList != nullptr) {
            tmp = currentList->getHead();
        }
    }
}

/**
 * Displays list as string.
 */
void Matrix::display() {
    List* tmp = this->head;
    while (tmp != nullptr) {
        tmp->display();
        tmp = tmp->next;
    }
}

/**
* Finds the node with a specific index.
* @param i row
* @param j column
* @return *Node
*/
Node* Matrix::index(int i, int j) {
    List* tmp = head;
    int counter = 0;
    while (counter != i) {
        tmp = tmp->next;
        counter++;
    }
    Node* result = tmp->index(j);
    return result;
}

/**
* Initializes empty 15x15 matrix with preset multipliers.
*/
void Matrix::initialize() {
    int rows = 15;
    int columns = 15;
    int columnsBackup = columns;
    int n = 1;

    while (rows != 0) {
        if (this->head == nullptr) {
            this->head = new List();
            while (columns != 0){
                this->head->add(n);
                n++;
                columns--;
            }
        } else {
            List* tmp = this->head;
            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = new List();
            while (columns != 0){
                tmp->next->add(n);
                n++;
                columns--;
            }
        }
        rows--;
        columns = columnsBackup;
        this->length++;
    }
}

bool Matrix::checkPlay(LastPlayList* lastPlayList) {
    LastPlayNode* tmp = lastPlayList->head;
    int firstRow = tmp->getRow();
    int firstColumn = tmp->getColumn();
    tmp = tmp->next;
    while (tmp != nullptr){
        if (tmp->getRow() != firstRow || tmp->getColumn() != firstColumn){
            return false;
        }
        tmp = tmp->next;
    }
    tmp = lastPlayList->head;
    while (tmp != nullptr){
        this->searchWords(tmp->getRow(), tmp->getColumn());
        tmp = tmp->next;
    }
    WordList* wordList = WordList::getInstance();
    return wordList->checkWordsInList();
}

void Matrix::searchWords(int row, int column) {
    string word;
    WordList* wordList = WordList::getInstance();
    int i = row - 1;
    int j = column - 1;
    bool horizontal = false;
    bool vertical = false;
    Node* posva = index(i, column);
    Node* posvp = index(i + 2, column);
    Node* posha = index(row, j);
    Node* poshp = index(row, j + 2);
    if (!posha->getLetter().empty() || !poshp->getLetter().empty()){
        horizontal = true;
    }if (!posva->getLetter().empty() || !posvp->getLetter().empty()){
        vertical = true;
    }if (!horizontal && !vertical){
        cout << "Nel" << endl;
    }else{
        string tmp;
        if (vertical){
            while (i != -1){
                if (!index(i, column)->getLetter().empty()){
                    i--;
                }else{
                    i++;
                    break;
                }
            }
            if (i == -1){
                i = 0;
            }
            while (i != 15){
                tmp = index(i, column)->getLetter();
                if (!tmp.empty()){
                    word.append(tmp);
                    i++;
                }else{
                    break;
                }
            }
            if (!wordList->searchDuplicates(word)){
                wordList->addWord(word);
            }
            word = "";
        }if (horizontal){
            while (j != -1){
                if (!index(row, j)->getLetter().empty()){
                    j--;
                }else{
                    j++;
                    break;
                }
            }
            if (j == -1){
                j = 0;
            }
            while (j != 15){
                tmp = index(row, j)->getLetter();
                if (!tmp.empty()){
                    word.append(tmp);
                    j++;
                }else{
                    break;
                }
            }
            if (!wordList->searchDuplicates(word)){
                wordList->addWord(word);
            }
        }
    }
}

int Matrix::calculatePoints(LastPlayList* lastPlayList, LetterList* letterList) {
    int points = 0;
    LastPlayNode* tmp = lastPlayList->head;
    while (tmp != nullptr){
        points += (index(tmp->getRow(), tmp->getColumn())->getMultiplier() * letterList->findPoint(tmp->getLetter()));
        tmp = tmp->next;
    }
    return points;
}