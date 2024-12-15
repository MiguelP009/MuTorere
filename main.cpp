#include "include/ReinforcementLearningAgent.hpp"
#include "include/RandomAgent.hpp"
#include "include/MuTorereBoard.hpp"
#include "include/Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>



//#define RL_AGENT_REWARD_AND_WINRATE
//#define DUAL_RL_AGENT
#define RL_AGENT_TEST
#ifdef MAIN_GAME

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