//
// Created by kevin on 17/03/19.
//

#include "TailNode.h"

char TailNode::getIp() {
    return this->ip;
}

void TailNode::setIp(char ip) {
    this->ip = ip;
}

bool TailNode::getUpdated() {
    return this->updated;
}

void TailNode::setUpdated(bool updated) {
    this->updated = updated;
}