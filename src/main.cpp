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
#include "../include/Menu.h"

int main(int argc, char **argv) {
	using namespace std;
	Audio audio;

	sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32), "Hero Quest");
	Menu* menu = new Menu(window);

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

	sf::Texture textureMenu;
	if (!textureMenu.loadFromFile("./assets/textures/Menu.png"))
	{
		cout << "La texture n'a pas chargée";
	}

	// Chargement de la texturesdu Menu
	sf::Sprite sprite;
	sprite.setTexture(textureMenu);
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
				menu->start_menu(event);
				audio.stopMusic();
			}
		}

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}
		return 0;
}