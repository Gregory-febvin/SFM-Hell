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

	menu.create_start_menu();

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen()) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			menu.select_start_menu(event);
		}

		window.clear();
		menu.draw();
		window.display();
	}

	return 0;
}