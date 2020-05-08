#include <algorithm>
#include "player.h"

using namespace std;

Player::Player(unsigned int id): 
    id(id), 
    score(0)
{}

const Hand& Player::getHand() const {
    return hand;
}

Hand& Player::getHand() {
    return hand;
}

unsigned int Player::getId() const {
    return id;
}

unsigned int Player::getScore() const {
    return score;
}

void Player::addScore(unsigned int score) {
    this->score += score;
}
