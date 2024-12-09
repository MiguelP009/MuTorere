#ifndef RANDOMAGENT_HPP
#define RANDOMAGENT_HPP

#include "Agent.hpp"
#include "MuTorereBoard.hpp"
#include <random>

class RandomAgent : public Agent {
public:
    RandomAgent(int playerId);
    int chooseMove(const MuTorereBoard& board) override;

private:
    std::mt19937 rng; // Générateur de nombres aléatoires
};

#endif // RANDOMAGENT_HPP