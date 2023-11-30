#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/constantes.h"
#include "../include/selectionlvl.h"
#include "../include/fichier.h"
#include "../include/audio.h"

int main(int argc, char **argv) {
	using namespace std;
	Audio audio;

	sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32), "Hero Quest");

	if (!audio.loadMusic("./assets/audio/musics/Title_Theme.ogg")) {
		cout << "La musique n'a pas chargée";
	}
	else {
		audio.playMusic();
	}

	sf::Texture texture;
	if (!texture.loadFromFile("./assets/textures/caisse.png")) // permet de charger la texture
	{
		cout << "La texture n'a pas chargée";
	}

	sf::Texture texturemenu;
	if (!texturemenu.loadFromFile("./assets/textures/menu.png"))
	{
		cout << "La texture n'a pas chargée";
	}

	// Chargement de la texturesdu menu
	sf::Sprite sprite;
	sprite.setTexture(texturemenu);
	// Modification la position absolue
	sprite.setPosition(sf::Vector2f(0.f, 0.f)); 

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen()) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
				if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
					audio.stopMusic();
					selectionJeu(&window);
				}
				if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
					audio.stopMusic();
					selectionEdition(&window);
				}
				if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
					audio.stopMusic();
					regle(&window);
				}
			}
		}

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}
		return 0;
}