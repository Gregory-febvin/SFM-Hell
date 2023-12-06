#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/constantes.h"
#include "../include/selectionlvl.h"
#include "../include/fichier.h"
#include "../include/Menu.h"

int main(int argc, char **argv) {
	

	sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32), "SFM HELL");
	Menu menu(&window);

	sf::Clock clock;
	sf::Time frameTime = sf::seconds(FRAMERATE);

	sf::Sprite title_screen_sprite;
	sf::Texture title_screen_texture;

	if (title_screen_texture.loadFromFile("./assets/textures/title_screen.jpg")) {
		title_screen_sprite.setTexture(title_screen_texture);
		float scale = (HAUTEUR_FENETRE) / title_screen_sprite.getGlobalBounds().height;
		title_screen_sprite.setScale(scale, scale);
		title_screen_sprite.setPosition(0, 0);
	}

	sf::RectangleShape transparentRect;
	transparentRect.setSize(sf::Vector2f(LARGEUR_FENETRE, HAUTEUR_FENETRE - SIZE_SPEECH));
	transparentRect.setPosition(0, SIZE_SPEECH);
	transparentRect.setFillColor(sf::Color(5, 5, 29, 192));

	menu.create_start_menu();

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			menu.select_start_menu(event);
		}

		if (elapsed >= frameTime) {
			window.clear();
			window.draw(title_screen_sprite);
			window.draw(transparentRect);
			menu.draw();

			window.display();
		}
	}

	return 0;
}