#ifndef GAME_HPP
#define GAME_HPP


#include "MuTorereBoard.hpp"
#include "Agent.hpp"


class Game {
public:
    Game(Agent* player1, Agent* player2);
    void playDebug();
    void play();
    void playGetRewards(std::vector<double>& totalRewards);
    void playGetResults(std::vector<double>& totalRewards, std::vector<int>& results);
    void playDualRLAgent(std::vector<double>& totalRewardsPlayer1, std::vector<double>& totalRewardsPlayer2);
    int getWinner();

private:
    MuTorereBoard board;
    Agent* player1;
    Agent* player2;
    int moveCount = 0;
};


#endif // GAME_HPP