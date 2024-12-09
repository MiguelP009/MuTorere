#include "include/ReinforcementLearningAgent.hpp"
#include "include/RandomAgent.hpp"
#include "include/MuTorereBoard.hpp"
#include "include/Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Initialisation du générateur de nombres aléatoires
    std::srand(std::time(nullptr));

    // Configuration des agents
    ReinforcementLearningAgent player1(1, 0.1, 0.9, 0.2);  // Joueur bleu
    //RandomAgent player2(2);  // Joueur rouge (aléatoire)
    ReinforcementLearningAgent player2(2, 0.1, 0.9, 0.2);
    // Création du jeu
    Game game(&player1, &player2);
    
    // Lancement du jeu
    game.play();

    return 0;
}

