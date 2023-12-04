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

void Menu::moveUp() {
	if (selectedItemIndex > 0) {
		menu_items[selectedItemIndex]->setSelected(false);
		selectedItemIndex--;
		menu_items[selectedItemIndex]->setSelected(true);
	}
}

void Menu::moveDown() {
	if (selectedItemIndex < menu_items.size() - 1) {
		menu_items[selectedItemIndex]->setSelected(false);
		selectedItemIndex++;
		menu_items[selectedItemIndex]->setSelected(true);
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

	menu_items.push_back(std::make_shared<MenuItem>(window, font, "NEW GAME", sf::Vector2f(100, 100)));
	menu_items.push_back(std::make_shared<MenuItem>(window, font, "SELECT CHAPTER", sf::Vector2f(100, 150)));
	menu_items.push_back(std::make_shared<MenuItem>(window, font, "EDITOR", sf::Vector2f(100, 200)));
	menu_items.push_back(std::make_shared<MenuItem>(window, font, "EXIT", sf::Vector2f(100, 250)));

	selectedItemIndex = 0;
	if (selectedItemIndex >= 0 && selectedItemIndex < menu_items.size()) {
		menu_items[selectedItemIndex]->setSelected(true);
	}

}

void Menu::select_start_menu(sf::Event event) 
{

	SelectionLvl selectionLvl(window);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			moveUp();
		}
		if (event.key.code == sf::Keyboard::Down) {
			moveDown();
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
		menu_items.push_back(std::make_shared<MenuItem>(
			window,
			font,
			intToRoman(i + 1),
			sf::Vector2f(((LARGEUR_FENETRE - (LARGEUR_LABEL_LVL * entry_count)) / 2) + (LARGEUR_LABEL_LVL * i), 100)
			));
	}


	selectedItemIndex = 0;
	if (selectedItemIndex >= 0 && selectedItemIndex < menu_items.size()) {
		menu_items[selectedItemIndex]->setSelected(true);
	}

}

void Menu::select_chapter_menu(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			moveUp();
		}
		if (event.key.code == sf::Keyboard::Right) {
			moveDown();
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
			moveUp();
		}
		if (event.key.code == sf::Keyboard::Right) {
			moveDown();
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

string Menu::intToRoman(int num) {
	std::vector<int> values = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	std::vector<std::string> numerals = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

	std::string result = "";
	for (size_t i = 0; i < values.size(); ++i) {
		while (num >= values[i]) {
			num -= values[i];
			result += numerals[i];
		}
	}

	return result;
}
