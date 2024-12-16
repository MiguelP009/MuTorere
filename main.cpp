#include "include/ReinforcementLearningAgent.hpp"
#include "include/RandomAgent.hpp"
#include "include/RealPlayerAgent.hpp"
#include "include/MuTorereBoard.hpp"
#include "include/Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>



//#define RL_AGENT_REWARD_AND_WINRATE
//#define DUAL_RL_AGENT
//#define RL_AGENT_TEST
#define MAIN_GAME
#ifdef MAIN_TEST

int main() {
    // Initialisation du générateur de nombres aléatoires
    std::srand(std::time(nullptr));

    // Configuration des agents
    ReinforcementLearningAgent player1(1, 0.1, 0.9, 0.2);  // Joueur bleu
    RandomAgent player2(2);  // Joueur rouge (aléatoire)
    //ReinforcementLearningAgent player2(2, 0.1, 0.9, 0.2);
    // Création du jeu
    Game game(&player1, &player2);
    
    // Lancement du jeu
    game.play();

    return 0;
}

#endif

#ifdef RL_AGENT_DATA

#include <vector>
#include <fstream>

int main() {
    const int totalGames = 10000;
    std::vector<int> results; // 1: victoire Joueur 1, 2: victoire Joueur 2, 0: nul
    std::vector<double> rewards; // Récompenses cumulées
    int winsPlayer1 = 0, winsPlayer2 = 0, draws = 0;

    for (int i = 0; i < totalGames; i++) {
        Game game(&player1, &player2);
        game.play();
        int winner = game.getWinner();

        if (winner == 1) winsPlayer1++;
        else if (winner == 2) winsPlayer2++;
        else draws++;

        // Collecte de récompenses
        double reward = calculateReward(player1, player2);
        rewards.push_back(reward);

        results.push_back(winner);

        if ((i + 1) % 100 == 0) {
            std::cout << "Games: " << i + 1 << " | Wins P1: " << winsPlayer1
                      << " | Wins P2: " << winsPlayer2 << " | Draws: " << draws << std::endl;
        }
    }

    // Sauvegarder les données
    std::ofstream outFile("learning_data.csv");
    outFile << "Game,Winner,Reward" << std::endl;
    for (size_t i = 0; i < results.size(); i++) {
        outFile << i + 1 << "," << results[i] << "," << rewards[i] << std::endl;
    }
    outFile.close();

    return 0;
}

#endif


#ifdef RL_AGENT_WINRATE
#include <fstream>

int main() {
    int totalEpisodes = 300000;
    int windowSize = 100;
    int wins = 0, losses = 0, draws = 0;
    std::vector<double> winRates;

    ReinforcementLearningAgent player1(1, 0.5, 0.5, 0.3);  // Joueur bleu
    RandomAgent player2(2);  // Joueur rouge (aléatoire)

    for (int episode = 0; episode < totalEpisodes; ++episode) {
        Game game(&player1, &player2);
        game.play();
        int winner = game.getWinner();

        if (winner == 1) wins++;
        else if (winner == 2) losses++;
        else draws++;

        // Calculez le taux de victoire tous les "windowSize" épisodes
        if ((episode + 1) % windowSize == 0) {
            double winRate = static_cast<double>(wins) / windowSize;
            winRates.push_back(winRate);
            std::cout << "Episodes " << (episode + 1) - windowSize + 1 << "-" << (episode + 1)
                   << ": Win Rate = " << winRate << std::endl;

            wins = 0; losses = 0; draws = 0; // Réinitialiser pour la prochaine fenêtre
        }
    }

    // Sauvegardez les résultats pour analyse ultérieure
    std::ofstream outFile("win_rates.csv");
    outFile << "Window,WinRate" << std::endl;
    for (size_t i = 0; i < winRates.size(); ++i) {
        outFile << i + 1 << "," << winRates[i] << std::endl;
    }
    outFile.close();
    return 0;

}

#endif

#ifdef RL_AGENT_REWARD

int main() {
    // Initialisation des agents
    ReinforcementLearningAgent player1(1, 0.3, 0.7, 0.3);
    RandomAgent player2(2);

    // Enregistrement des récompenses totales par partie
    std::vector<double> totalRewards;

    const int numGames = 50000;
    for (int i = 0; i < numGames; ++i) {
        std::cout << "Game " << i + 1 << " starts." << std::endl;
        Game game(&player1, &player2);
        game.playGetRewards(totalRewards);
    }

    // Sauvegarder les récompenses dans un fichier CSV
    std::ofstream outFile("total_rewards.csv");
    outFile << "Game,TotalReward" << std::endl;
    for (size_t i = 0; i < totalRewards.size(); ++i) {
        outFile << i + 1 << "," << totalRewards[i] << std::endl;
    }
    outFile.close();

    std::cout << "Rewards saved to total_rewards.csv." << std::endl;

    return 0;
}


#endif

#ifdef RL_AGENT_REWARD_AND_WINRATE
int main() {
    // Initialisation des agents
    ReinforcementLearningAgent player1(1, 0.3, 0.8, 0.3);
    //RandomAgent player2(1);
    RandomAgent player2(2);

    // Enregistrement des récompenses et des résultats
    std::vector<double> totalRewards;
    std::vector<int> results;

    const int numGames = 100000;
    const int windowSize = 100; // Fenêtre pour calculer le winrate
    int wins = 0, losses = 0, draws = 0;
    std::vector<double> winRates;

    for (int i = 0; i < numGames; ++i) {
        std::cout << "Game " << i + 1 << " starts." << std::endl;
        Game game(&player1, &player2);
        game.playGetResults(totalRewards, results);

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
    }

    // Sauvegarde des données dans un fichier CSV
    std::ofstream outFile("results.csv");
    outFile << "Game,TotalReward,WinRate" << std::endl;
    for (size_t i = 0; i < totalRewards.size(); ++i) {
        double winRate = (i / windowSize < winRates.size()) ? winRates[i / windowSize] : winRates.back();
        outFile << i + 1 << "," << totalRewards[i] << "," << winRate << std::endl;
    }
    outFile.close();

    std::cout << "Results saved to results.csv." << std::endl;

    return 0;
}

#endif

#ifdef DUAL_RL_AGENT
int main() {
    // Initialisation des agents RL
    ReinforcementLearningAgent player1(1, 0.3, 0.8, 0.3);
    ReinforcementLearningAgent player2(1, 0.3, 0.8, 0.3);

    // Enregistrement des récompenses totales
    std::vector<double> totalRewardsPlayer1;
    std::vector<double> totalRewardsPlayer2;

    const int numGames = 100000;
    for (int i = 0; i < numGames; ++i) {
        std::cout << "Game " << i + 1 << " starts." << std::endl;
        Game game(&player1, &player2);
        game.playDualRLAgent(totalRewardsPlayer1, totalRewardsPlayer2);
    }

    // Sauvegarde des résultats dans un fichier CSV
    std::ofstream outFile("dual_rl_rewards.csv");
    outFile << "Game,TotalRewardPlayer1,TotalRewardPlayer2" << std::endl;
    for (size_t i = 0; i < totalRewardsPlayer1.size(); ++i) {
        outFile << i + 1 << "," << totalRewardsPlayer1[i] << "," << totalRewardsPlayer2[i] << std::endl;
    }
    outFile.close();

    std::cout << "Results saved to dual_rl_rewards.csv." << std::endl;
    // Sauvegarde des Q-valeurs mises à jour
    player1.saveQValues("player1_qvalues.csv");
    player2.saveQValues("player2_qvalues.csv");
    return 0;
}

#endif


#ifdef RL_AGENT_TEST



int main() {
    // Initialisation des agents
    ReinforcementLearningAgent player1(1, 0.3, 0.8, 0.3);
    //RandomAgent player2(1);
    RandomAgent player2(2);

    player1.loadQValues("player1_qvalues.csv");


    // Enregistrement des récompenses et des résultats
    std::vector<double> totalRewards;
    std::vector<int> results;

    const int numGames = 100000;
    const int windowSize = 100; // Fenêtre pour calculer le winrate
    int wins = 0, losses = 0, draws = 0;
    std::vector<double> winRates;

    for (int i = 0; i < numGames; ++i) {
        std::cout << "Game " << i + 1 << " starts." << std::endl;
        Game game(&player1, &player2);
        game.playGetResults(totalRewards, results);

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
    }

    // Sauvegarde des données dans un fichier CSV
    std::ofstream outFile("results.csv");
    outFile << "Game,TotalReward,WinRate" << std::endl;
    for (size_t i = 0; i < totalRewards.size(); ++i) {
        double winRate = (i / windowSize < winRates.size()) ? winRates[i / windowSize] : winRates.back();
        outFile << i + 1 << "," << totalRewards[i] << "," << winRate << std::endl;
    }
    outFile.close();

    std::cout << "Results saved to results.csv." << std::endl;

    return 0;
}

#endif

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
        auto* rlAgent1 = new ReinforcementLearningAgent(1, 0.1, 0.9, 0.2);
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
        auto* rlAgent2 = new ReinforcementLearningAgent(2, 0.1, 0.9, 0.2);
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
    if (player1IsRL) outFile << ",TotalRewardPlayer1";
    if (player2IsRL) outFile << ",TotalRewardPlayer2";
    outFile << ",Winner\n";

    for (size_t i = 0; i < totalRewardsPlayer1.size(); ++i) {
        outFile << i + 1;
        if (player1IsRL) outFile << "," << totalRewardsPlayer1[i];
        if (player2IsRL) outFile << "," << totalRewardsPlayer2[i];
        outFile << "," << results[i] << "\n";
    }
    outFile.close();

    std::cout << "Results saved to " << resultsFile << "\n";

    // Libérer la mémoire
    delete player1;
    delete player2;

    return 0;
}


#endif