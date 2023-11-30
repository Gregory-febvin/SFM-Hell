#include "../include/menu.h"

//namespace fs = std::filesystem;

Menu::Menu(sf::RenderWindow& window) : window(window)
{
	
}

void Menu::draw() {
	for (auto& item : items) {
		item.draw(window);
	}
}

void Menu::moveUp() {
	if (selectedItemIndex > 0) {
		items[selectedItemIndex].setSelected(false);
		selectedItemIndex--;
		items[selectedItemIndex].setSelected(true);
	}
}

void Menu::moveDown() {
	if (selectedItemIndex < items.size() - 1) {
		items[selectedItemIndex].setSelected(false);
		selectedItemIndex++;
		items[selectedItemIndex].setSelected(true);
	}
}

int Menu::getSelectedItemIndex() const {
	return selectedItemIndex;
}

void Menu::start_menu(sf::Event event) 
{

	if (event.key.code == sf::Keyboard::Escape) {
		window.close();
	}
	if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
		selectionJeu(window);
	}
	if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
		selectionEdition(&window);
	}
	if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
		regle(&window);
	}

}

void Menu::create_chapter_menu()
{

	if (!font.loadFromFile("./assets/font/Ketchum.otf")) {
		std::cout << "Failed to load font!" << std::endl;
	}

	items.push_back(MenuItem("Option 1", sf::Vector2f(100, 100)));
	items.push_back(MenuItem("Option 2", sf::Vector2f(100, 150)));
	items.push_back(MenuItem("Option 3", sf::Vector2f(100, 200)));

	/*for (const auto& entry : fs::directory_iterator("./assets/stage")) {
		if (entry.is_regular_file()) {
			std::cout << "File name: " << entry.path().filename() << std::endl;
		}
	}*/


	selectedItemIndex = 0;
	if (selectedItemIndex >= 0 && selectedItemIndex < items.size()) {
		items[selectedItemIndex].setSelected(true);
	}

}

void Menu::select_chapter_menu(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			moveUp();
		}
		if (event.key.code == sf::Keyboard::Down) {
			moveDown();
		}
		if (event.key.code == sf::Keyboard::Enter) {
			std::cout << "Option sélectionnée : " << getSelectedItemIndex() << std::endl;
		}
	}
}
