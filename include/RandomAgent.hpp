#ifndef RANDOMAGENT_HPP
#define RANDOMAGENT_HPP

#include "Agent.hpp"


class RandomAgent : public Agent {

public:
    RandomAgent(int playerId);
    int chooseMove(const MuTorereBoard& board) override;

};




#endif // RANDOMAGENT_HPP