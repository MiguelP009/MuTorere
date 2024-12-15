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

// void Game::play() {
//     moveCount = 0;
//     while (!board.isGameOver()) {
//         int move = player1->chooseMove(board);
//         board.makeMove(1, move);
//         player1->updateQValues(0, board, move, board);
//         moveCount++;
//         if (board.isGameOver()) break;

//         move = player2->chooseMove(board);
//         board.makeMove(2, move);

//     }
// }

void Game::play() {
    MuTorereBoard oldBoard = board; // État précédent pour le joueur 1
    // board.displayBoard();
    while (!board.isGameOver()) {
        

        // Tour du joueur 1 (Reinforcement Learning Agent)
        int move = player1->chooseMove(board);
        // std::cout << "Player 1 (RL Agent) chooses move: " << move << std::endl;

        if (move != -1) {
            board.makeMove(1, move);
            // board.displayBoard();
            // Mise à jour des Q-valeurs pour le joueur 1
            auto* rlAgent = dynamic_cast<ReinforcementLearningAgent*>(player1);
            if (rlAgent) {
                int reward = board.isGameOver() ? (board.getWinner() == 1 ? +1 : -1) : 0;
                rlAgent->updateQValues(reward, oldBoard, move, board);
            }

            // Mettre à jour l'ancien état
            oldBoard = board;
        }

        if (board.isGameOver()) break;

        // Tour du joueur 2
        int move2 = player2->chooseMove(board);
        // std::cout << "Player 2 chooses move: " << move2 << std::endl;

        if (move2 != -1) {
            board.makeMove(2, move2);
            // board.displayBoard();
        }
    }
}

void Game::playGetRewards(std::vector<double>& totalRewards) {
    MuTorereBoard oldBoard = board; // État précédent pour le joueur 1
    double totalReward = 0.0;       // Récompenses cumulées pour le joueur 1

    while (!board.isGameOver()) {
        // board.displayBoard();

        // Tour du joueur 1 (Reinforcement Learning Agent)
        int move = player1->chooseMove(board);
        // std::cout << "Player 1 (RL Agent) chooses move: " << move << std::endl;

        if (move != -1) {
            board.makeMove(1, move);

            // Mise à jour des Q-valeurs pour le joueur 1
            auto* rlAgent = dynamic_cast<ReinforcementLearningAgent*>(player1);
            if (rlAgent) {
                int reward = board.isGameOver() ? (board.getWinner() == 1 ? +10 : -1) : -1;
                rlAgent->updateQValues(reward, oldBoard, move, board);
                totalReward += reward; // Ajouter la récompense au total
            }

            // Mettre à jour l'ancien état
            oldBoard = board;
        }

        if (board.isGameOver()) break;

        // Tour du joueur 2
        int move2 = player2->chooseMove(board);
        // std::cout << "Player 2 chooses move: " << move2 << std::endl;

        if (move2 != -1) {
            board.makeMove(2, move2);
        }
    }

    // Sauvegarde du total de récompenses pour la partie
    totalRewards.push_back(totalReward);
}

void Game::playGetResults(std::vector<double>& totalRewards, std::vector<int>& results) {
    MuTorereBoard oldBoard = board; // État précédent pour le joueur 1
    double totalReward = 0.0;       // Récompenses cumulées pour le joueur 1

    while (!board.isGameOver()) {
        // board.displayBoard();

        // Tour du joueur 1 (Reinforcement Learning Agent)
        int move = player1->chooseMove(board);
        // std::cout << "Player 1 (RL Agent) chooses move: " << move << std::endl;

        if (move != -1) {
            board.makeMove(1, move);

            // Mise à jour des Q-valeurs pour le joueur 1
            auto* rlAgent = dynamic_cast<ReinforcementLearningAgent*>(player1);
            if (rlAgent) {
                int reward = board.isGameOver() ? (board.getWinner() == 1 ? +10 : -1) : -1;
                rlAgent->updateQValues(reward, oldBoard, move, board);
                totalReward += reward; // Ajouter la récompense au total
            }

            // Mettre à jour l'ancien état
            oldBoard = board;
        }

        if (board.isGameOver()) break;

        // Tour du joueur 2
        int move2 = player2->chooseMove(board);
        // std::cout << "Player 2 chooses move: " << move2 << std::endl;

        if (move2 != -1) {
            board.makeMove(2, move2);
        }
    }

    // Sauvegarde du total de récompenses pour la partie
    totalRewards.push_back(totalReward);

    // Sauvegarde du résultat de la partie (1: victoire RL, 2: défaite RL, 0: nul)
    results.push_back(board.getWinner());
}


void Game::playDualRLAgent(std::vector<double>& totalRewardsPlayer1, std::vector<double>& totalRewardsPlayer2) {
    MuTorereBoard oldBoard = board; // État précédent
    double totalRewardPlayer1 = 0.0; // Récompenses cumulées pour le joueur 1
    double totalRewardPlayer2 = 0.0; // Récompenses cumulées pour le joueur 2

    while (!board.isGameOver()) {
        // board.displayBoard();

        // Tour du joueur 1
        int move1 = player1->chooseMove(board);
        // std::cout << "Player 1 (RL Agent) chooses move: " << move1 << std::endl;

        if (move1 != -1) {
            board.makeMove(1, move1);

            // Mise à jour des Q-valeurs pour le joueur 1
            auto* rlAgent1 = dynamic_cast<ReinforcementLearningAgent*>(player1);
            if (rlAgent1) {
                int reward = board.isGameOver() ? (board.getWinner() == 1 ? +10 : -1) : -1;
                rlAgent1->updateQValues(reward, oldBoard, move1, board);
                totalRewardPlayer1 += reward; // Ajouter la récompense au total
            }

            oldBoard = board; // Mettre à jour l'état précédent
        }

        if (board.isGameOver()) break;

        // Tour du joueur 2
        int move2 = player2->chooseMove(board);
        // std::cout << "Player 2 (RL Agent) chooses move: " << move2 << std::endl;

        if (move2 != -1) {
            board.makeMove(2, move2);

            // Mise à jour des Q-valeurs pour le joueur 2
            auto* rlAgent2 = dynamic_cast<ReinforcementLearningAgent*>(player2);
            if (rlAgent2) {
                int reward = board.isGameOver() ? (board.getWinner() == 2 ? +10 : -1) : -1;
                rlAgent2->updateQValues(reward, oldBoard, move2, board);
                totalRewardPlayer2 += reward; // Ajouter la récompense au total
            }

            oldBoard = board; // Mettre à jour l'état précédent
        }
    }

    // Sauvegarder les récompenses totales pour chaque joueur
    totalRewardsPlayer1.push_back(totalRewardPlayer1);
    totalRewardsPlayer2.push_back(totalRewardPlayer2);
}






int Game::getWinner() {
    return board.getWinner();
}

