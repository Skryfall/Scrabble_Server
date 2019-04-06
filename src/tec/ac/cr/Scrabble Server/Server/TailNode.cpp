//
// Created by kevin on 17/03/19.
//

#include "TailNode.h"

string TailNode::getName() {
    return this->name;
}

void TailNode::setName(string name) {
    this->name = name;
}

bool TailNode::getUpdated() {
    return this->updated;
}

void TailNode::setUpdated(bool updated) {
    this->updated = updated;
}