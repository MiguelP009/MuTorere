#include "../include/RandomAgent.hpp"
#include <cstdlib>

RandomAgent::RandomAgent(int playerId) : Agent(playerId) {}

int RandomAgent::chooseMove(const MuTorereBoard& board) {
    std::vector<int> availableMoves = board.getAvailableMoves(playerId);
    
    if (availableMoves.empty()) {
        // Gestion du cas où aucun mouvement n'est possible (ne devrait pas arriver)
        return -1;
    }
    
    // Choisir un mouvement aléatoirement parmi les mouvements disponibles
    return availableMoves[rand() % availableMoves.size()];
}