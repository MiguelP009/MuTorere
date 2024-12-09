#ifndef MUTOREREGUI_HPP
#define MUTOREREGUI_HPP

#include <SFML/Graphics.hpp>
#include "MuTorereBoard.hpp"

class MuTorereGUI {
public:
    MuTorereGUI();
    void displayBoard(const MuTorereBoard& board); // Mettre à jour l'affichage sans recréer la fenêtre

private:
    sf::RenderWindow window;
    sf::CircleShape putahi; // Case centrale
    std::vector<sf::CircleShape> kewaiPositions; // Emplacements des cases autour du putahi
    void drawBoard();      // Dessine le plateau vide
    void drawPawns(const MuTorereBoard& board); // Dessine les pions
};

#endif // MUTOREREGUI_HPP
