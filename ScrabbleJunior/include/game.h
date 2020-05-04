#ifndef GAME_H
#define GAME_H

class Game;

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include "player.h"
#include "board.h"
#include "pool.h"
#include "position.h"
#include "displayer.h"

// TODO a state machine would probably be better than an enum
enum State {
    Unstarted,
    Ongoing,
    Finished
};

class Game {
    Board board;
    std::vector<Player> players;
    Pool pool;
    int turn;
    int moves_left;
    State state;

    public:
    Game(int num_players);
    bool loadBoardFile(std::istream &board_file);
    void startGame(std::default_random_engine &rng);

    const std::vector<Player>& getPlayers() const;
    const Board& getBoard() const;
    const Pool& getPool() const;

    Player& getCurrentPlayer();
    int getCurrentPlayerNumber();
    int getMovesLeftThisTurn();
    int getMovesThisTurn();
    bool canCurrentPlayerMove();

    bool move(Position position, GameDisplayer &displayer);
    void exchangePair(char letter1, char letter2, GameDisplayer &displayer, default_random_engine &rng);
    void nextTurn();

    void printGame(std::ostream &out);
};

#endif