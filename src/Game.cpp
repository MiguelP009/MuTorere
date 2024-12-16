#include "../include/Game.hpp"
#include "../include/ReinforcementLearningAgent.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <ostream>

Game::Game(Agent* player1, Agent* player2) : player1(player1), player2(player2) {}

void Game::playDebug() {
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



void Game::play(std::vector<double>& totalRewardsPlayer1, std::vector<double>& totalRewardsPlayer2, std::vector<int>& results) {
    MuTorereBoard oldBoard = board; // État précédent pour les agents
    double totalRewardPlayer1 = 0.0; // Récompenses cumulées pour le joueur 1
    double totalRewardPlayer2 = 0.0; // Récompenses cumulées pour le joueur 2

    while (!board.isGameOver()) {
        // Tour du joueur 1
        int move1 = player1->chooseMove(board);

        if (move1 != -1) {
            board.makeMove(1, move1);

            // Mise à jour des Q-valeurs pour le joueur 1 (si RL)
            auto* rlAgent1 = dynamic_cast<ReinforcementLearningAgent*>(player1);
            if (rlAgent1) {
                int reward = board.isGameOver() ? (board.getWinner() == 1 ? +10 : -5) : -1;
                rlAgent1->updateQValues(reward, oldBoard, move1, board);
                totalRewardPlayer1 += reward;
            }

            // Mettre à jour l'ancien état
            oldBoard = board;
        }

        if (board.isGameOver()) break;

        // Tour du joueur 2
        int move2 = player2->chooseMove(board);

        if (move2 != -1) {
            board.makeMove(2, move2);

            // Mise à jour des Q-valeurs pour le joueur 2 (si RL)
            auto* rlAgent2 = dynamic_cast<ReinforcementLearningAgent*>(player2);
            if (rlAgent2) {
                int reward = board.isGameOver() ? (board.getWinner() == 2 ? +10 : -1) : -1;
                rlAgent2->updateQValues(reward, oldBoard, move2, board);
                totalRewardPlayer2 += reward;
            }

            // Mettre à jour l'ancien état
            oldBoard = board;
        }
    }

    // Sauvegarde des récompenses cumulées pour les deux joueurs
    totalRewardsPlayer1.push_back(totalRewardPlayer1);
    totalRewardsPlayer2.push_back(totalRewardPlayer2);

    // Sauvegarde du résultat de la partie (1: victoire joueur 1, 2: victoire joueur 2, 0: nul)
    results.push_back(board.getWinner());
}


int Game::getWinner() {
    return board.getWinner();
}

