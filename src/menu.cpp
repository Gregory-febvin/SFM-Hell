#include "../include/menu.h"

Menu::Menu(sf::RenderWindow* window) 
	: window(window)
{
	
}

void Menu::draw() {
	for (const auto& item : menu_items) {
		item->draw();
	}
}

void Menu::moveUp(int id_menu) {
	if (selectedItemIndex > 0) {
		menu_items[selectedItemIndex]->setSelected(false, id_menu);
		selectedItemIndex--;
		menu_items[selectedItemIndex]->setSelected(true, id_menu);
	}
}

void Menu::moveDown(int id_menu) {
	if (selectedItemIndex < menu_items.size() - 1) {
		menu_items[selectedItemIndex]->setSelected(false, id_menu);
		selectedItemIndex++;
		menu_items[selectedItemIndex]->setSelected(true, id_menu);
	}
}

int Menu::getSelectedItemIndex() const {
	return selectedItemIndex;
}

void Menu::create_start_menu()
{

	musicMenu();

	if (!font.loadFromFile("./assets/font/CrimsonPro-SemiBold.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
	}

	menu_items.push_back(std::make_shared<MenuItem>(window, font, "NEW GAME", sf::Vector2f(LARGEUR_FENETRE, SIZE_SPEECH + 50 * (menu_items.size() + 1))));
	menu_items.push_back(std::make_shared<MenuItem>(window, font, "SELECT CHAPTER", sf::Vector2f(LARGEUR_FENETRE, SIZE_SPEECH + 50 * (menu_items.size() + 1))));
	menu_items.push_back(std::make_shared<MenuItem>(window, font, "EDITOR", sf::Vector2f(LARGEUR_FENETRE, SIZE_SPEECH + 50 * (menu_items.size() + 1))));
	menu_items.push_back(std::make_shared<MenuItem>(window, font, "EXIT", sf::Vector2f(LARGEUR_FENETRE, SIZE_SPEECH + 50 * (menu_items.size() + 1))));

	for (std::shared_ptr<MenuItem>& menu_item : menu_items) {
		menu_item->setMenuItemStart();
	}

	selectedItemIndex = 0;
	if (selectedItemIndex >= 0 && selectedItemIndex < menu_items.size()) {
		menu_items[selectedItemIndex]->setSelectedItemStart(true);
	}

}

void Menu::select_start_menu(sf::Event event) 
{

	SelectionLvl selectionLvl(window);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			moveUp(ID_MENU_START);
		}
		if (event.key.code == sf::Keyboard::Down) {
			moveDown(ID_MENU_START);
		}
		if (event.key.code == sf::Keyboard::Enter) {
			switch (getSelectedItemIndex())
			{
			case 0:
				audio.stopMusic();
				selectionLvl.selectGame();
				break;
			case 1:
				selectionLvl.selectChapter();
				break;
			case 2:
				selectionLvl.selectChapterEditor();
				break;
			case 3:
				window->close();
				break;
			default:
				break;
			}
		}
	}

}

void Menu::create_chapter_menu()
{

	if (!font.loadFromFile("./assets/font/CrimsonPro-SemiBold.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
	}

	Fichier fichier;
	int entry_count = fichier.nbLvlFile();

	for (int i = 0; i < entry_count; i++) {
		menu_items.push_back(std::make_shared<MenuItem>(window, font, fichier.convertIntToRoman(i + 1),
			sf::Vector2f(((LARGEUR_FENETRE - ((LARGEUR_LABEL_LVL + 10) * entry_count)) / 2) + ((LARGEUR_LABEL_LVL + 10) * i), SIZE_SPEECH + LARGEUR_LABEL_LVL * 2)
			));
	}

	for (std::shared_ptr<MenuItem>& menu_item : menu_items) {
		menu_item->setMenuItemChapter();
	}


	selectedItemIndex = 0;
	if (selectedItemIndex >= 0 && selectedItemIndex < menu_items.size()) {
		menu_items[selectedItemIndex]->setSelectedItemChapter(true);
	}

}

void Menu::select_chapter_menu(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			moveUp(ID_MENU_CHAPTER);
		}
		if (event.key.code == sf::Keyboard::Right) {
			moveDown(ID_MENU_CHAPTER);
		}
		if (event.key.code == sf::Keyboard::Enter) {
			Jeu jeu(window, getSelectedItemIndex() + 1);

			int cinematic = jeu.cinematic();
			if (cinematic == ERROR_EXIT) {
				return;
			}

			int jouer = jeu.jouer();
			if (jouer == ERROR_EXIT) {
				return;
			}
		}
	}
}

void Menu::select_editor_menu(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			moveUp(ID_MENU_CHAPTER);
		}
		if (event.key.code == sf::Keyboard::Right) {
			moveDown(ID_MENU_CHAPTER);
		}
		if (event.key.code == sf::Keyboard::Enter) {
			editeur(window, getSelectedItemIndex() + 1);
		}
	}
}

void Menu::musicMenu() {

	if (!audio.loadMusic("./assets/audio/musics/Title_Theme.ogg")) {
		cout << "La musique n'a pas chargée";
	} else {
		audio.playMusic();
	}

}

void Menu::clearMenu() {
	window->clear();
	menu_items.clear();
	selectedItemIndex = 0;
}
