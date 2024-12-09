#ifndef GAME_HPP
#define GAME_HPP


#include "MuTorereBoard.hpp"
#include "Agent.hpp"


class Game {
public:
    Game(Agent* player1, Agent* player2);
    void play();

private:
    MuTorereBoard board;
    Agent* player1;
    Agent* player2;
};


#endif // GAME_HPP