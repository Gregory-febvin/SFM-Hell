#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <iostream>

#include "audio.h"
#include "menu_item.h"
#include "selectionlvl.h"
#include "jeu.h"
#include "constantes.h"
#include "fichier.h"

namespace fs = std::filesystem;

class Menu
{

public:
	Menu(sf::RenderWindow* window);

	void create_start_menu();
	void select_start_menu(sf::Event event);
	void create_chapter_menu();
	void select_chapter_menu(sf::Event event);
	void select_editor_menu(sf::Event event);

	void draw();
	void moveUp();
	void moveDown();
	int getSelectedItemIndex() const;

	void musicMenu();
	void clearMenu();
	std::string intToRoman(int num);

private:
	sf::RenderWindow* window;
	sf::Font font;

	Audio audio;

	std::vector<std::shared_ptr<MenuItem>> menu_items;
	int selectedItemIndex;

};
