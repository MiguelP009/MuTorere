#ifndef REALPLAYERAGENT_HPP
#define REALPLAYERAGENT_HPP

#include "Agent.hpp"
#include "MuTorereBoard.hpp"
#include <iostream>
#include <vector>

class RealPlayerAgent : public Agent {
public:
    RealPlayerAgent(int playerId);

    // Méthode pour choisir un coup
    int chooseMove(const MuTorereBoard& board) override;
};

#endif // REALPLAYERAGENT_HPP
