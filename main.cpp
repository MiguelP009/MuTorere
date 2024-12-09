#include "include/ReinforcementLearningAgent.hpp"
#include "include/MuTorereBoard.hpp"
#include "include/MuTorereGUI.hpp"
#include "include/Game.hpp"
#include <thread>        // Pour std::this_thread::sleep_for
#include <chrono>        // Pour std::chrono::milliseconds
#include <iostream>

int main() {
    MuTorereBoard board;
    MuTorereGUI gui;
    ReinforcementLearningAgent player1(1);  // Joueur bleu
    ReinforcementLearningAgent player2(2);  // Joueur rouge

    Game game(&player1, &player2);
    
    // Boucle de jeu principale
    //gui.displayBoard(board);

    game.play();
    while(1);
    /*
    while (!board.isGameOver()) {
        // Tour de joueur 1 (Bleu)
        int move1 = player1.chooseMove(board);
        board.makeMove(1, move1);

        // Rafraîchissement de l'interface graphique
        gui.displayBoard(board);

        // Pause de 500 ms pour observer le coup
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (board.isGameOver()) break;

        // Tour de joueur 2 (Rouge)
        int move2 = player2.chooseMove(board);
        board.makeMove(2, move2);

        // Rafraîchissement de l'interface graphique
        gui.displayBoard(board);

        // Pause de 500 ms pour observer le coup
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Afficher le résultat
    int winner = board.getWinner();
    if (winner == 1) {
        std::cout << "Joueur 1 (Bleu) gagne !" << std::endl;
    } else if (winner == 2) {
        std::cout << "Joueur 2 (Rouge) gagne !" << std::endl;
    } else {
        std::cout << "Match nul !" << std::endl;
    }*/

    return 0;
}

