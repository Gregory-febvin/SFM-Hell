#include "../include/selectionlvl.h"

SelectionLvl::SelectionLvl(sf::RenderWindow* window) : window(window)
{
	loadAssets();
}

void SelectionLvl::loadAssets() 
{
	if (!font.loadFromFile("./assets/font/CrimsonPro-SemiBold.ttf")) {

	}


	if (background_texture.loadFromFile("./assets/textures/background.png")) {
		background_sprite.setTexture(background_texture);
		float scale = (HAUTEUR_FENETRE) / background_sprite.getGlobalBounds().height;
		background_sprite.setScale(scale, scale);
		background_sprite.setPosition(0, 0);
	}

	text_title.setFont(font);
	text_title.setCharacterSize(FONT_SIZE_TITLE);

	text_command_quit.setFont(font);
	text_command_quit.setCharacterSize(FONT_SIZE_COMMAND);
	text_command_quit.setString("- QUIT [ ECHAP ] -");
	text_command_quit.setPosition(
		(LARGEUR_FENETRE - text_command_quit.getLocalBounds().width) * 1 / 3,
		(HAUTEUR_FENETRE - text_command_quit.getLocalBounds().height * 2)
	);

	text_command_select.setFont(font);
	text_command_select.setCharacterSize(FONT_SIZE_COMMAND);
	text_command_select.setString("- SELECT [ ENTER ] -");
	text_command_select.setPosition(
		(LARGEUR_FENETRE - text_command_select.getLocalBounds().width) * 2 / 3,
		(HAUTEUR_FENETRE - text_command_select.getLocalBounds().height * 2)
	);
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

	text_title.setString("SELECT CHAPTER");
	text_title.setPosition(
		(LARGEUR_FENETRE - text_title.getLocalBounds().width) / 2,
		(text_title.getLocalBounds().height / 2)
	);

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
		window->draw(text_title);
		window->draw(text_command_quit);
		window->draw(text_command_select);
		menu.draw();
		window->display();
	}

}

void SelectionLvl::selectChapterEditor() {

    int continuer = true;

	text_title.setString("EDITOR");
	text_title.setPosition(
		(LARGEUR_FENETRE - text_title.getLocalBounds().width) / 2,
		(text_title.getLocalBounds().height / 2)
	);

	Menu menu(window);
	menu.create_chapter_menu();

    // On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer) {
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
		window->draw(background_sprite);
		window->draw(text_title);
		window->draw(text_command_quit);
		window->draw(text_command_select);
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