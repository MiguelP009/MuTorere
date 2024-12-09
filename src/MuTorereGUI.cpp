#include "../include/MuTorereGUI.hpp"
#include <cmath>
#include <iostream>

MuTorereGUI::MuTorereGUI() : window(sf::VideoMode(800, 600), "Mu Torere Game") {
    // Initialisation des positions des cases autour du putahi
    kewaiPositions.resize(8);
    float radius = 200.0f;
    for (int i = 0; i < 8; ++i) {
        float angle = i * M_PI / 4.0f; // 45 degrés en radians
        kewaiPositions[i].setRadius(20.0f);
        kewaiPositions[i].setFillColor(sf::Color::White);
        kewaiPositions[i].setPosition(400 + radius * cos(angle), 300 + radius * sin(angle));
        kewaiPositions[i].setOrigin(20.0f, 20.0f); // Centrer le cercle
    }

    // Initialisation de la case centrale (putahi)
    putahi.setRadius(25.0f);
    putahi.setFillColor(sf::Color::Cyan);
    putahi.setPosition(400, 300);
    putahi.setOrigin(25.0f, 25.0f); // Centrer le cercle
}

void MuTorereGUI::displayBoard(const MuTorereBoard& board) {
    // Gérer la fermeture de la fenêtre
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);  // Ferme le programme si la fenêtre est fermée
        }
    }

    // Rafraîchir l'affichage du plateau et des pions
    window.clear(sf::Color::Black);
    drawBoard();
    drawPawns(board);
    window.display();
}

void MuTorereGUI::drawBoard() {
    // Dessine le putahi
    window.draw(putahi);

    // Dessine les kewai
    for (const auto& kewai : kewaiPositions) {
        window.draw(kewai);
    }
}

void MuTorereGUI::drawPawns(const MuTorereBoard& board) {
    // Récupère l'état du plateau pour positionner les pions
    std::vector<int> state = board.getBoardState();
    for (int i = 0; i < 8; ++i) {
        if (state[i] != 0) {
            sf::CircleShape pawn(15.0f);
            pawn.setOrigin(15.0f, 15.0f);
            pawn.setFillColor(state[i] == 1 ? sf::Color::Blue : sf::Color::Red);
            pawn.setPosition(kewaiPositions[i].getPosition());
            window.draw(pawn);
        }
    }

    // Dessine le pion au centre s'il y en a un
    if (state[4] != 0) {
        sf::CircleShape pawn(15.0f);
        pawn.setOrigin(15.0f, 15.0f);
        pawn.setFillColor(state[4] == 1 ? sf::Color::Blue : sf::Color::Red);
        pawn.setPosition(putahi.getPosition());
        window.draw(pawn);
    }
}
