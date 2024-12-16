#include "include/ReinforcementLearningAgent.hpp"
#include "include/RandomAgent.hpp"
#include "include/RealPlayerAgent.hpp"
#include "include/MuTorereBoard.hpp"
#include "include/Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>


#define MAIN_GAME

#ifdef MAIN_GAME

// Fonction pour afficher l'utilisation du programme
void printUsage() {
    std::cout << "Usage: ./mu_torere_simulation [OPTIONS]\n"
              << "Options:\n"
              << "  --agent1 [random|rl|real]   Type of agent 1\n"
              << "  --agent2 [random|rl|real]   Type of agent 2\n"
              << "  --games <n>                 Number of games to play\n"
              << "  --train                     Train RL agent(s)\n"
              << "  --export-qvalues <file>     Export Q-values to the specified file\n"
              << "  --load-qvalues <file>       Load Q-values from the specified file\n"
              << "  --output-results <file>     Save game results to the specified file\n"
              << "  --window-size <n>           Window size for calculating win rate (default: 100)\n"
              << "  --help                      Display this help message\n";
}

int main(int argc, char* argv[]) {
    // Variables de configuration
    std::string agent1Type = "random";
    std::string agent2Type = "random";
    int numGames = 1000;
    bool train = false;
    std::string qvaluesExportFile = "";
    std::string qvaluesLoadFile = "";
    std::string resultsFile = "results.csv";

    // Parse les arguments en ligne de commande
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--agent1" && i + 1 < argc) {
            agent1Type = argv[++i];
        } else if (arg == "--agent2" && i + 1 < argc) {
            agent2Type = argv[++i];
        } else if (arg == "--games" && i + 1 < argc) {
            numGames = std::stoi(argv[++i]);
        } else if (arg == "--train") {
            train = true;
        } else if (arg == "--export-qvalues" && i + 1 < argc) {
            qvaluesExportFile = argv[++i];
        } else if (arg == "--load-qvalues" && i + 1 < argc) {
            qvaluesLoadFile = argv[++i];
        } else if (arg == "--output-results" && i + 1 < argc) {
            resultsFile = argv[++i];
        } else if (arg == "--help") {
            printUsage();
            return 0;
        } else {
            std::cerr << "Unknown option: " << arg << "\n";
            printUsage();
            return 1;
        }
    }

    // Créer les agents
    Agent* player1 = nullptr;
    Agent* player2 = nullptr;

    bool player1IsRL = false;
    bool player2IsRL = false;
    bool player1IsReal = false;
    bool player2IsReal = false;

    if (agent1Type == "random") {
        player1 = new RandomAgent(1);
    } else if (agent1Type == "rl") {
        auto* rlAgent1 = new ReinforcementLearningAgent(1, 0.3, 0.8, 1.0, 0.99, 0.1);
        if (!qvaluesLoadFile.empty()) {
            rlAgent1->loadQValues(qvaluesLoadFile);
        }
        player1 = rlAgent1;
        player1IsRL = true;
    } else if (agent1Type == "real") {
        player1 = new RealPlayerAgent(1);
        player1IsReal = true;
    }else {
        std::cerr << "Invalid agent1 type: " << agent1Type << "\n";
        printUsage();
        return 1;
    }

    if (agent2Type == "random") {
        player2 = new RandomAgent(2);
    } else if (agent2Type == "rl") {
        auto* rlAgent2 = new ReinforcementLearningAgent(1, 0.3, 0.8, 1.0, 0.99, 0.1);
        if (!qvaluesLoadFile.empty()) {
            rlAgent2->loadQValues(qvaluesLoadFile);
        }
        player2 = rlAgent2;
        player2IsRL = true;
    }else if (agent2Type == "real") {
        player2 = new RealPlayerAgent(2);
        player2IsReal = true;
    }else {
        std::cerr << "Invalid agent2 type: " << agent2Type << "\n";
        printUsage();
        return 1;
    }

    // Enregistrement des résultats
    std::vector<double> totalRewardsPlayer1;
    std::vector<double> totalRewardsPlayer2;
    std::vector<int> results;
    int wins = 0, losses = 0, draws = 0;
    std::vector<double> winRates;
    int windowSize = 100;

    // Lancer les jeux
    for (int i = 0; i < numGames; ++i) {
        Game game(player1, player2);
        game.play(totalRewardsPlayer1, totalRewardsPlayer2, results);
        if (player1IsReal || player2IsReal) {
            if (player1IsReal && game.getWinner() == 1) {
                std::cout << "You win!\n";
            }
            else if (player2IsReal && game.getWinner() == 2) {
                std::cout << "You win!\n";
            }
            else{
                std::cout << "You lose!\n";
            }

        }

        // Mise à jour des résultats
        if (results.back() == 1) {
            ++wins;
        } else if (results.back() == 2) {
            ++losses;
        } else {
            ++draws;
        }

        // Calcul du winrate tous les `windowSize` épisodes
        if ((i + 1) % windowSize == 0) {
            double winRate = static_cast<double>(wins) / windowSize;
            winRates.push_back(winRate);

            std::cout << "Win rate (last " << windowSize << " games): " << winRate << std::endl;

            // Réinitialisation pour la prochaine fenêtre
            wins = 0;
            losses = 0;
            draws = 0;
        }

        // Décroissance de l'epsilon pour les agents RL
        if (auto* rlAgent1 = dynamic_cast<ReinforcementLearningAgent*>(player1)) {
            rlAgent1->decayEpsilon();
        }
        if (auto* rlAgent2 = dynamic_cast<ReinforcementLearningAgent*>(player2)) {
            rlAgent2->decayEpsilon();
        }
        
    }

    // Sauvegarder les Q-values si demandé
    if (train && !qvaluesExportFile.empty()) {
        if (player1IsRL) {
            dynamic_cast<ReinforcementLearningAgent*>(player1)->saveQValues(qvaluesExportFile + "_agent1.csv");
        }
        if (player2IsRL) {
            dynamic_cast<ReinforcementLearningAgent*>(player2)->saveQValues(qvaluesExportFile + "_agent2.csv");
        }
    }

    // Sauvegarder les résultats
    std::ofstream outFile(resultsFile);

    // Ajouter les en-têtes dynamiquement
    outFile << "Game";
    if (player1IsRL) outFile << ",TotalReward";
    if (player2IsRL) outFile << ",TotalRewardPlayer2";
    outFile << ",WinRate\n";

    for (size_t i = 0; i < totalRewardsPlayer1.size(); ++i) {
        double winRate = (i / windowSize < winRates.size()) ? winRates[i / windowSize] : winRates.back();
        outFile << i + 1;
        if (player1IsRL) outFile << "," << totalRewardsPlayer1[i];
        if (player2IsRL) outFile << "," << totalRewardsPlayer2[i];
        outFile << "," << winRate << "\n";
    }
    outFile.close();

    std::cout << "Results saved to " << resultsFile << "\n";

    // Libérer la mémoire
    delete player1;
    delete player2;

    return 0;
}


#endif