#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <ostream>

enum Orientation {
    Vertical,
    Horizontal,
};

Orientation parseOrientation(char c);

std::ostream& operator<<(std::ostream &out, Orientation orientation);

#endif