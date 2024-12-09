#include "../include/Agent.hpp"
#include <cstdlib>
#include <iostream>



Agent::Agent(int playerId) : playerId(playerId) {}

int Agent::chooseMove(const MuTorereBoard& board) {
    int move = rand() % 9;
    while(!board.isValidMove(playerId, move)) {
        std::cout << "PlayerID: " << playerId << " Move : " << move << std::endl;
        move = rand() % 9;
    }
    return move;
}