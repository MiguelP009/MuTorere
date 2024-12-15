#ifndef REINFORCEMENTLEARNINGAGENT_HPP
#define REINFORCEMENTLEARNINGAGENT_HPP

#include "Agent.hpp"
#include "MuTorereBoard.hpp"
#include <map>
#include <vector>
#include <utility>
#include <random>

class ReinforcementLearningAgent : public Agent {
public:
    ReinforcementLearningAgent(int playerId, double alpha = 0.1, double gamma = 0.9, double epsilon = 0.1);
    int chooseMove(const MuTorereBoard& board) override;
    void updateQValues(int reward, const MuTorereBoard& oldBoard, int move, const MuTorereBoard& newBoard);
    void saveQValues(const std::string& filename) const;
    void loadQValues(const std::string& filename);



private:
    std::map<std::pair<int, int>, double> qValues; // Table des Q-valeurs pour (état, action)
    double alpha;  // Taux d’apprentissage
    double gamma;  // Facteur de discount
    double epsilon; // Paramètre pour l'exploration
    int getBestMove(const MuTorereBoard& board);
    int getStateHash(const MuTorereBoard& board) const; // Fonction de hachage pour l’état
};

#endif // REINFORCEMENTLEARNINGAGENT_HPP
