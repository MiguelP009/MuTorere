#ifndef MUtOREREBOARD_HPP
#define MUtOREREBOARD_HPP


#include <vector>

class MuTorereBoard {
public:
    MuTorereBoard();
    void displayBoard() const;
    std::vector<int> getBoardState() const; 
    bool makeMove(int player, int move);
    bool isValidMove(int player, int move) const;
    bool isGameOver() const;
    int getWinner() const;
    std::vector<int> getAvailableMoves(int player) const;
private:
    std::vector<int> board; //9 positions (0: vide, 1: joueur 1, 2: joueur 2)
    std::vector<std::vector<int>> connections;
    int winner;
    bool isFirstTurn;
};



#endif // MUtOREREBOARD_HPP