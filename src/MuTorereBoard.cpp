#include "../include/MuTorereBoard.hpp"
#include <iostream>



MuTorereBoard::MuTorereBoard() : board(9, 0), winner(0), isFirstTurn(true) {
    for(int i=0; i<4; i++) {
        board[i] = 1;
        board[i+5] = 2;
    }
    board[4] = 0;
    
    
}

void MuTorereBoard::displayBoard() const {
    std::cout << "  " << board[0] << " - " << board[1] << " - " << board[2] << std::endl;
    std::cout << "  | \\ | / |" << std::endl;
    std::cout << board[3] << " - " << board[4] << " - " << board[5] << std::endl;
    std::cout << "  | / | \\ |" << std::endl;
    std::cout << "  " << board[6] << " - " << board[7] << " - " << board[8] << std::endl;
}

bool MuTorereBoard::isValidMove(int player, int move) const {
    // Vérifie si un mouvement est valide pour le joueur
    if (move < 0 || move >= 9 || board[move] != player) return false;

    // Règles pour les mouvements
    if (isFirstTurn) {
        int left = (move == 0) ? 3 : move - 1;
        int right = (move == 3) ? 0 : move + 1;
        // Vérifie si le pion est adjacent à un pion adverse
        if (board[left] != 3 - player && board[right] != 3 - player) return false;
    }
    if (move == 4) { // Si la case centrale (putahi) est la source
        for (int adj : {0, 1, 2, 3, 5, 6, 7, 8}) {
            if (board[adj] == 0) return true; // Mouvement vers une case vide adjacente
        }
    } else {
        // Mouvement d'un kewai vers putahi ou un kewai adjacent
        if (board[4] == 0) return true; // Vers le putahi vide
        int left = (move == 0) ? 3 : move - 1;
        int right = (move == 3) ? 0 : move + 1;
        if (board[left] == 0 || board[right] == 0) return true;
    }
    return false;
}

bool MuTorereBoard::makeMove(int player, int move) {
    // Vérifie que le mouvement est valide
    if (!isValidMove(player, move)) return false;

    // Déplacement du pion vers une case vide
    if (move == 4) { // Le joueur déplace un pion du centre (putahi) vers un kewai
        for (int i : {0, 1, 2, 3, 5, 6, 7, 8}) {
            if (board[i] == 0) {  // Trouver un kewai vide pour le déplacement
                board[i] = player;
                board[4] = 0; // Libère le centre
                return true;
            }
        }
    } else {
        // Déplacement d'un kewai vers le centre ou un kewai adjacent vide
        if (board[4] == 0) { // Si le centre est vide
            board[4] = player;
            board[move] = 0;
            return true;
        }
        // Sinon, tente de déplacer le pion vers un kewai adjacent vide
        int left = (move == 0) ? 3 : move - 1;
        int right = (move == 3) ? 0 : move + 1;
        if (board[left] == 0) {
            board[left] = player;
            board[move] = 0;
            return true;
        } else if (board[right] == 0) {
            board[right] = player;
            board[move] = 0;
            return true;
        }
    }
    return false;
}


bool MuTorereBoard::isGameOver() const {
    // Vérifie si l'un des joueurs est bloqué
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 0 && isValidMove(board[i], i)) {
            return false; // Un mouvement est encore possible
        }
    }
    return true;
}

int MuTorereBoard::getWinner() const {
    // Vérifie si un joueur est bloqué pour déterminer le gagnant
    if (!isGameOver()) return 0;

    int player1Moves = 0;
    int player2Moves = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 1 && isValidMove(1, i)) player1Moves++;
        if (board[i] == 2 && isValidMove(2, i)) player2Moves++;
    }
    if (player1Moves == 0) return 2; // Joueur 1 bloqué, joueur 2 gagne
    if (player2Moves == 0) return 1; // Joueur 2 bloqué, joueur 1 gagne
    return 0;
}

std::vector<int> MuTorereBoard::getAvailableMoves() const {
    // Retourne une liste de toutes les cases occupées par un joueur pouvant effectuer un mouvement valide
    std::vector<int> moves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 0 && isValidMove(board[i], i)) {
            moves.push_back(i);
        }
    }
    return moves;
}

std::vector<int> MuTorereBoard::getBoardState() const {
    // Retourne l'état actuel du plateau
    return board;
}