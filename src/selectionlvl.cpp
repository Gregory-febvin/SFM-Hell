#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/constantes.h"
#include "../include/fichier.h"
#include "../include/jeu.h"
#include "../include/editeur.h"
#include "../include/audio.h"
#include "../include/Menu.h"

void selectionJeu(sf::RenderWindow& window) 
{

	int continuer = 1;
	Menu* menu = new Menu(window);
	menu->create_chapter_menu();

	// Chargement des textures du Menu de selection de niveau
	sf::Texture textureSeclectionLvl;
	sf::Sprite selectionLvl;

	textureSeclectionLvl.loadFromFile("./assets/textures/selectionlvljeu.png");
	//selectionLvl.setTexture(textureSeclectionLvl);

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer == 1) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return;
			}
			menu->select_chapter_menu(event);
		}

		// Effacement et dessin
		window.clear(sf::Color::Black);
		menu->draw();
		window.display();
	}

	delete menu;

}

void selectionEdition(sf::RenderWindow* window) {

    int continuer = 1;

    // Chargement des textures du Menu de selection de niveau pour edition
    sf::Texture textureSeclectionLvl;
    sf::Sprite selectionLvl;

    textureSeclectionLvl.loadFromFile("./assets/textures/selectionlvledition.png");
    selectionLvl.setTexture(textureSeclectionLvl);

    // On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (continuer == 1) {
        // On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    continuer = 0;
                }
                // Selection du niveau
                if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                    editeur(window, 1);
                }
                if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    editeur(window, 2);
                }
                if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    editeur(window, 3);
                }
                if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                    editeur(window, 4);
                }
                if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                    editeur(window, 5);
                }
            }
            window->draw(selectionLvl);
            window->display();
        }
        window->clear(sf::Color::Black);
    }
}

void regle(sf::RenderWindow* window) {

    int continuer = 1;

    // Chargement des textures du Menu de selection de niveau
    sf::Texture textureRegle;
    sf::Sprite regle;

    textureRegle.loadFromFile("./assets/textures/regle.png");
    regle.setTexture(textureRegle);

    // On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (continuer == 1) {
        // On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    continuer = 0;
                }
            }
            window->draw(regle);
            window->display();
        }
        window->clear(sf::Color::Black);
    }
}