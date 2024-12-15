#include "../include/ReinforcementLearningAgent.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

ReinforcementLearningAgent::ReinforcementLearningAgent(int playerId, double alpha, double gamma, double epsilon)
    : Agent(playerId), alpha(alpha), gamma(gamma), epsilon(epsilon) {}

int ReinforcementLearningAgent::chooseMove(const MuTorereBoard& board) {
    int state = getStateHash(board);
    std::vector<int> availableMoves = board.getAvailableMoves(playerId);

    // Print available moves
    // for (int i=0; i<availableMoves.size(); i++) {
    //     std::cout << availableMoves[i] << " " << std::endl;
    // }

    // Politique epsilon-greedy
    if ((double) rand() / RAND_MAX < epsilon) {
        // Exploration: choisir un mouvement aléatoire parmi ceux disponibles
        return availableMoves[rand() % availableMoves.size()];
    } else {
        // Exploitation: choisir le meilleur mouvement connu
        return getBestMove(board);
    }
}

void ReinforcementLearningAgent::updateQValues(int reward, const MuTorereBoard& oldBoard, int move, const MuTorereBoard& newBoard) {
    int oldState = getStateHash(oldBoard);
    int newState = getStateHash(newBoard);

    double oldQValue = qValues[{oldState, move}];
    double maxFutureQ = 0.0;

    // Obtenir la Q-valeur maximum pour le nouvel état
    std::vector<int> newMoves = newBoard.getAvailableMoves(playerId);
    for (int newMove : newMoves) {
        maxFutureQ = std::max(maxFutureQ, qValues[{newState, newMove}]);
    }

    // Mettre à jour la Q-valeur avec l'équation de Q-learning
    qValues[{oldState, move}] = oldQValue + alpha * (reward + gamma * maxFutureQ - oldQValue);
}

int ReinforcementLearningAgent::getBestMove(const MuTorereBoard& board) {
    int state = getStateHash(board);
    std::vector<int> availableMoves = board.getAvailableMoves(playerId);

    int bestMove = availableMoves[0];
    double bestQValue = qValues[{state, bestMove}];

    for (int move : availableMoves) {
        double qValue = qValues[{state, move}];
        if (qValue > bestQValue) {
            bestQValue = qValue;
            bestMove = move;
        }
    }

    return bestMove;
}

int ReinforcementLearningAgent::getStateHash(const MuTorereBoard& board) const {
    std::vector<int> boardState = board.getBoardState();
    int hash = 0;
    for (int pos : boardState) {
        hash = hash * 3 + pos; // Utilise chaque position pour créer un identifiant unique
    }
    return hash;
}


void ReinforcementLearningAgent::saveQValues(const std::string& filename) const {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving Q-values." << std::endl;
        return;
    }

    // En-tête
    outFile << "State,Action,QValue" << std::endl;

    // Sauvegarder chaque Q-valeur
    for (const auto& entry : qValues) {
        int state = entry.first.first;
        int action = entry.first.second;
        double qValue = entry.second;
        outFile << state << "," << action << "," << qValue << std::endl;
    }

    outFile.close();
    std::cout << "Q-values saved to " << filename << "." << std::endl;
}

void ReinforcementLearningAgent::loadQValues(const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for loading Q-values." << std::endl;
        return;
    }

    std::string line;
    std::getline(inFile, line); // Ignorer l'en-tête

    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        int state, action;
        double qValue;

        char delimiter;
        ss >> state >> delimiter >> action >> delimiter >> qValue;

        qValues[{state, action}] = qValue;
    }

    inFile.close();
    std::cout << "Q-values loaded from " << filename << "." << std::endl;
}