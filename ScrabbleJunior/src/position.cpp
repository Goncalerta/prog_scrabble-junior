#include "position.h"

using namespace std;

Position::Position(): Position(0, 0) {}

Position::Position(int x, int y): x(x), y(y) {}

Position::Position(char x, char y) {
    this->x = x - 'a';
    this->y = y - 'A';
}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

Position& Position::stepForward(Orientation orientation) {
    if(orientation == Horizontal) x += 1;
    else y += 1;
    
    return *this;
}

Position& Position::stepBackwards(Orientation orientation) {
    if(orientation == Horizontal) x -= 1;
    else y -= 1;

    return *this;
}

pair<Position, Position> Position::laterals(Orientation orientation) const {
    if(orientation == Horizontal) {
        return pair<Position, Position>(Position(x, y+1), Position(x, y-1));
    } else {
        return pair<Position, Position>(Position(x+1, y), Position(x-1, y));
    }
}

bool Position::inLimits(int width, int height) const {
    return x >= 0 && y >= 0 && x < width && y < height;
}

bool Position::operator==(const Position &other) const {
    return x == other.x && y == other.y;
}

ostream& operator<<(ostream &out, const Position &pos) {
    out << (char)('A' + pos.y) << (char)('a' + pos.x);
    return out;
}
