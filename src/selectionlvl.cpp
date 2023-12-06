#include "../include/selectionlvl.h"

SelectionLvl::SelectionLvl(sf::RenderWindow* window) : window(window)
{

}

void SelectionLvl::selectGame()
{
	bool continuer = true;

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window->close();
			}

			Fichier fichier;
			for (int i = 1; i < fichier.nbLvlFile() + 1; i++) {
				Jeu jeu(window, i);

				int cinematic = jeu.cinematic();
				if (cinematic == ERROR_EXIT) {
					return;
				}

				int jouer = jeu.jouer();
				if (jouer == ERROR_EXIT) {
					return;
				}
			}
			return;

		}

		// Effacement et dessin
		window->clear();
		window->display();
	}
}

void SelectionLvl::selectChapter()
{

	bool continuer = true;

	sf::Sprite background_sprite, character_sprite;
	sf::Texture background_texture, character_texture;

	if (background_texture.loadFromFile("./assets/textures/background.png")) {
		background_sprite.setTexture(background_texture);
		float scale = (HAUTEUR_FENETRE) / background_sprite.getGlobalBounds().height;
		background_sprite.setScale(scale, scale);
		background_sprite.setPosition(0, 0);
	}

	Menu menu(window);
	menu.create_chapter_menu();

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					menu.clearMenu();
					return;
				}
			}
			menu.select_chapter_menu(event);
		}

		// Effacement et dessin
		window->clear();
		window->draw(background_sprite);
		menu.draw();
		window->display();
	}

}

void SelectionLvl::selectChapterEditor() {

    int continuer = 1;
	Menu menu(window);
	menu.create_chapter_menu();

    // On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer == 1) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					menu.clearMenu();
					return;
				}
			}
			menu.select_editor_menu(event);
		}

		// Effacement et dessin
		window->clear();
		menu.draw();
		window->display();
	}
}

/*void SelectionLvl::regle() {

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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    continuer = 0;
                }
            }
            window.draw(regle);
            window.display();
        }
        window.clear(sf::Color::Black);
    }
}*/