#include "../include/RealPlayerAgent.hpp"

#include <iostream>
#include <algorithm>

RealPlayerAgent::RealPlayerAgent(int playerId) : Agent(playerId) {}

int RealPlayerAgent::chooseMove(const MuTorereBoard& board) {
    // Obtenir les coups possibles
    std::vector<int> availableMoves = board.getAvailableMoves(playerId);

    // Afficher l'état actuel du plateau
    std::cout << "\nCurrent Board State:\n";
    board.displayBoard();

    // Afficher les coups possibles
    std::cout << "\nAvailable Moves for Player " << playerId << ": ";
    for (int move : availableMoves) {
        std::cout << move << " ";
    }
    std::cout << "\n";

    // Demander à l'utilisateur de choisir un coup
    int chosenMove;
    while (true) {
        std::cout << "Enter your move: ";
        std::cin >> chosenMove;

        // Vérifier si le coup est valide
        if (std::find(availableMoves.begin(), availableMoves.end(), chosenMove) != availableMoves.end()) {
            break;
        }

        std::cout << "Invalid move. Please choose a valid move.\n";
    }

    return chosenMove;
}
