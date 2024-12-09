#include "../include/MuTorereBoard.hpp"
#include <iostream>
#include <algorithm>



MuTorereBoard::MuTorereBoard() : board(9, 0), winner(0), isFirstTurn(true) {
    for(int i=0; i<4; i++) {
        board[i] = 1;
        board[i+5] = 2;
    }
    board[4] = 0;

    connections = {
        {1, 3, 4},   // Connexions pour board[0]
        {0, 2, 4},   // Connexions pour board[1]
        {1, 5, 4},   // Connexions pour board[2]
        {0, 6, 4},   // Connexions pour board[3]
        {0, 1, 2, 3, 5, 6, 7, 8},          // Connexions pour board[4]
        {2, 8, 4},   // Connexions pour board[5]
        {3, 7, 4},   // Connexions pour board[6]
        {6, 8, 4},   // Connexions pour board[7]
        {5, 7, 4}    // Connexions pour board[8]
    };
    
    
}

void MuTorereBoard::displayBoard() const {
    std::cout << "  " << board[0] << " - " << board[1] << " - " << board[2] << std::endl;
    std::cout << "  | \\ | / |" << std::endl;
    std::cout << "  "<<board[3] << " - " << board[4] << " - " << board[5] << std::endl;
    std::cout << "  | / | \\ |" << std::endl;
    std::cout << "  " << board[6] << " - " << board[7] << " - " << board[8] << std::endl;
}
/*
bool MuTorereBoard::isValidMove(int player, int move) const {
    // Vérifie si un mouvement est valide pour le joueur
    if (move < 0 || move >= 9 || board[move] != 0) return false;

    // Vérification de la règle des pions adjacents
    int left = (move == 0) ? 3 : move - 1;
    int right = (move == 3) ? 0 : move + 1;
    if (board[left] != 3 - player && board[right] != 3 - player && move != 4) {
        return false; // Le pion doit être adjacent à un pion adverse, sauf pour le putahi
    }

    if (move == 4) { // Si la case centrale (putahi) est la source
        for (int adj : {0, 1, 2, 3, 5, 6, 7, 8}) {
            if (board[adj] == 0) return true; // Mouvement vers une case vide adjacente
        }
    } else {
        // Mouvement d'un kewai vers putahi ou un kewai adjacent
        if (board[4] == 0) return true; // Vers le putahi vide
        left = (move == 0) ? 3 : move - 1;
        right = (move == 3) ? 0 : move + 1;
        if (board[left] == 0 || board[right] == 0) return true;
    }

    return false;
}
*/

bool MuTorereBoard::isValidMove(int player, int move) const {
    // Vérifie que la case source appartient au joueur
    if (move < 0 || move >= 9 || board[move] != player) return false;

    // Cas particulier : déplacement vers le putahi (case centrale)
    if (std::find(connections[move].begin(), connections[move].end(), 4) != connections[move].end() && board[4] == 0) {
        // Vérifie si au moins une case adjacente au pion est occupée par l’adversaire
        for (int adj : connections[move]) {
            if (adj != 4 && board[adj] == 3 - player) {
                return true;
            }
        }
    }

    // Déplacement vers une case périphérique adjacente vide
    for (int adj : connections[move]) {
        if (adj != 4 && board[adj] == 0) {
            return true;
        }
    }

    return false; // Aucun mouvement valide trouvé
}
/*
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
*/
bool MuTorereBoard::makeMove(int player, int move) {
    if (!isValidMove(player, move)) return false;

    // Déplacement vers le putahi
    if (board[4] == 0 && std::find(connections[move].begin(), connections[move].end(), 4) != connections[move].end()) {
        board[4] = player;
        board[move] = 0;
        return true;
    }

    // Déplacement vers une case périphérique vide
    for (int adj : connections[move]) {
        if (board[adj] == 0) {
            board[adj] = player;
            board[move] = 0;
            return true;
        }
    }

    return false; // Aucune action n’a pu être effectuée
}


/*
bool MuTorereBoard::isGameOver() const {
    // Vérifie si l'un des joueurs est bloqué
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 0 && isValidMove(board[i], i)) {
            return false; // Un mouvement est encore possible
        }
    }
    return true;
}
*/
/*
bool MuTorereBoard::isGameOver() const {
    // Vérifie si un joueur peut encore bouger
    bool player1CanMove = false;
    bool player2CanMove = false;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == 1 && isValidMove(1, i)) {
            player1CanMove = true;
        }
        if (board[i] == 2 && isValidMove(2, i)) {
            player2CanMove = true;
        }
        // Si les deux joueurs peuvent bouger, le jeu continue
        if (player1CanMove && player2CanMove) {
            return false;
        }
    }

    // Si aucun joueur ne peut bouger, la partie est terminée
    return !player1CanMove || !player2CanMove;
}


int MuTorereBoard::getWinner() const {
    if (!isGameOver()) return 0; // La partie n'est pas terminée

    bool player1CanMove = false;
    bool player2CanMove = false;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == 1 && isValidMove(1, i)) {
            player1CanMove = true;
        }
        if (board[i] == 2 && isValidMove(2, i)) {
            player2CanMove = true;
        }
    }

    // Détermine le gagnant
    if (!player1CanMove) return 2; // Joueur 1 est bloqué, Joueur 2 gagne
    if (!player2CanMove) return 1; // Joueur 2 est bloqué, Joueur 1 gagne
    return 0; // Aucun gagnant (ne devrait pas arriver si isGameOver est correct)
}*/

bool MuTorereBoard::isGameOver() const {
    // Vérifie si un joueur a des mouvements possibles
    bool player1CanMove = false;
    bool player2CanMove = false;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == 1 && isValidMove(1, i)) {
            player1CanMove = true;
        }
        if (board[i] == 2 && isValidMove(2, i)) {
            player2CanMove = true;
        }
    }

    // Le jeu est terminé si un des joueurs ne peut plus bouger
    return !(player1CanMove && player2CanMove);
}

// bool MuTorereBoard::isGameOver() const {
//     bool out = getAvailableMoves(1).empty() && getAvailableMoves(2).empty();
//     std::cout << "isGameOver: " << out << std::endl;
//     return out;
// }

int MuTorereBoard::getWinner() const {
    if (!isGameOver()) return 0; // Pas de gagnant si le jeu n'est pas terminé

    bool player1CanMove = false;
    bool player2CanMove = false;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == 1 && isValidMove(1, i)) {
            player1CanMove = true;
        }
        if (board[i] == 2 && isValidMove(2, i)) {
            player2CanMove = true;
        }
    }

    // Le gagnant est celui qui peut encore bouger
    if (!player1CanMove) return 2; // Joueur 1 bloqué, joueur 2 gagne
    if (!player2CanMove) return 1; // Joueur 2 bloqué, joueur 1 gagne
    
    return 0; // Normalement ne devrait jamais arriver
}

std::vector<int> MuTorereBoard::getAvailableMoves(int player) const {
    std::vector<int> moves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == player && isValidMove(player, i)) {
            moves.push_back(i);
        }
    }
    return moves;
}

std::vector<int> MuTorereBoard::getBoardState() const {
    // Retourne l'état actuel du plateau
    return board;
}