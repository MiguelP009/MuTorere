#ifndef AGENT_HPP
#define AGENT_HPP

#include "MuTorereBoard.hpp"

class Agent {
public:
    Agent(int playerId);
    virtual int chooseMove(const MuTorereBoard& board);

protected:
    int playerId;
};


#endif // AGENT_HPP
