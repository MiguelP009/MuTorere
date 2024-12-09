#include "../include/Game.hpp"
#include <thread>        // Pour std::this_thread::sleep_for
#include <chrono>        // Pour std::chrono::milliseconds
#include <iostream>
#include <ostream>

Game::Game(Agent* player1, Agent* player2) : player1(player1), player2(player2) {}

void Game::play() {
    //board.displayBoard();
    board.displayBoard();
    while (!board.isGameOver()) {        
        int move = player1->chooseMove(board);
        std::cout << "Joueur 1 (Bleu) joue : " << move << std::endl;
        board.makeMove(1, move);
        board.displayBoard();
        if (board.isGameOver()) break;

        move = player2->chooseMove(board);
        std::cout << "Joueur 2 (Rouge) joue : " << move << std::endl;
        board.makeMove(2, move);
        board.displayBoard();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }

    int winner = board.getWinner();
    // Annonce du gagnant
    if (winner == 1) {
        std::cout << "Joueur 1 (Bleu) gagne !" << std::endl;
    } else if (winner == 2) {
        std::cout << "Joueur 2 (Rouge) gagne !" << std::endl;
    } else {
        std::cout << "Match nul !" << std::endl;
    }
}