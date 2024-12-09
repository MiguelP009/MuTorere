#include "../include/Agent.hpp"
#include <cstdlib>



Agent::Agent(int playerId) : playerId(playerId) {}

int Agent::chooseMove(const MuTorereBoard& board) {
    int move = rand() % 9;
    while(!board.isValidMove(playerId, move)) {
        move = rand() % 9;
    }
    return move;
}