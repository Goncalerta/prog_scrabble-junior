#include "board.h"

using namespace std;

Board::Board(unsigned int width, unsigned int height): 
  width(width), 
  height(height), 
  grid(height, vector<Cell>(width)),
  total_letters(0)
{}

unsigned int Board::countLetters() const {
    return total_letters;
}

unsigned int Board::countWords() const {
    return words.size();
}

unsigned int Board::getHeight() const {
    return height;
}

unsigned int Board::getWidth() const {
    return width;
}

const Cell& Board::getCell(Position position) const {
    return grid[position.getY()][position.getX()];
}

Cell& Board::getCell(Position position) {
    return grid[position.getY()][position.getX()];
}

void Board::addWord(Word &word) {
    Position position = word.getStart();
    Orientation orientation = word.getOrientation();

    for(char letter: word) {
        Cell &cell = getCell(position);
        if(cell.isEmpty()) total_letters += 1;
        cell.setLetter(letter);
        position.stepForward(orientation);
    }

    words.push_back(move(word));
}

bool Board::isWordValid(const Word &word, ostream &error_messages) {
    Position position = word.getStart();
    Orientation orientation = word.getOrientation();

    position.stepBackwards(orientation);
    if(position.inLimits(width, height) && !getCell(position).isEmpty()) {
        position.stepForward(orientation);
        error_messages << "Word would be adjacent to existing word at '" << position << "', creating ambiguity.\n";
        return false;
    }

    // Assume word already exists, if at least on of the cells is empty turns into false.
    bool word_already_exists = true;

    for(char current_letter: word) {
        position.stepForward(orientation);
        if(!position.inLimits(width, height)) {
            position.stepBackwards(orientation);
            error_messages << "Word goes outside the board after position '" << position << "'.\n";
            return false;
        }
        Cell &current_cell = getCell(position);

        if(current_cell.isEmpty()) {
            word_already_exists = false;
            std::pair<Position, Position> laterals = position.laterals(orientation);

            if(laterals.first.inLimits(width, height) && !getCell(laterals.first).isEmpty()) {
                error_messages << "Word would be adjacent to existing word at '" << laterals.first << "', creating ambiguity.\n";
                return false;
            }
            if(laterals.second.inLimits(width, height) && !getCell(laterals.second).isEmpty()) {
                error_messages << "Word would be adjacent to existing word at '" << laterals.second << "', creating ambiguity.\n";
                return false;
            }
        } else if(current_cell.getLetter() != current_letter) {
            error_messages << "Word's letter '" << current_letter << "' intersects with existing letter '" << current_cell.getLetter() << "' at position '" << position << "'.\n";
            return false;
        }
    }
    position.stepForward(orientation);
    if(position.inLimits(width, height) && !getCell(position).isEmpty()) {
        position.stepBackwards(orientation);
        error_messages << "Word would be adjacent to existing word at '" << position << "', creating ambiguity.\n";
        return false;
    }

    if(word_already_exists) {
        error_messages << "This word has already been placed in board at that position.\n";
        return false;
    }

    return true;
}

bool Board::isWordValid(const Word &word) {
    Position position = word.getStart();
    Orientation orientation = word.getOrientation();

    position.stepBackwards(orientation);
    if(position.inLimits(width, height) && !getCell(position).isEmpty()) {
        return false;
    }

    // Assume word already exists, if at least on of the cells is empty turns into false.
    bool word_already_exists = true;

    for(char current_letter: word) {
        position.stepForward(orientation);
        if(!position.inLimits(width, height)) {
            return false;
        }
        Cell &current_cell = getCell(position);

        if(current_cell.isEmpty()) {
            word_already_exists = false;
            std::pair<Position, Position> laterals = position.laterals(orientation);

            if(laterals.first.inLimits(width, height) && !getCell(laterals.first).isEmpty()) {
                return false;
            }
            if(laterals.second.inLimits(width, height) && !getCell(laterals.second).isEmpty()) {
                return false;
            }
        } else if(current_cell.getLetter() != current_letter) {
            return false;
        }
    }
    position.stepForward(orientation);
    if(position.inLimits(width, height) && !getCell(position).isEmpty()) {
        return false;
    }

    if(word_already_exists) {
        return false;
    }

    return true;
}

void Board::writeData(ostream &out) const {
    out << height << " x " << width << endl;

    for(const Word &word: words) {
        out << word << endl;
    }

    out << endl << "  ";
    for(char letter = 'a'; letter < width + 'a'; letter++) {
        out << letter << ' ';
    }
    out << endl;

    for(int j = 0; j < height; j++) {
        char letter = j + 'A';
        out << letter << ' ';

        for(int i = 0; i < width; i++) {
            out << getCell(Position(i, j));
            
            if(i+1 != width) {
                out << ' ';
            }
        }
        out << endl;
    }
}
