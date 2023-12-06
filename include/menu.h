#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <iostream>

#include "audio.h"
#include "menu_item.h"
#include "selectionlvl.h"
#include "jeu.h"
#include "editeur.h"
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
	int select_chapter_menu(sf::Event event);
	int select_editor_menu(sf::Event event);

	void draw();
	void moveUp(int id_menu);
	void moveDown(int id_menu);
	int getSelectedItemIndex() const;

	void musicMenu();
	void clearMenu();

private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::RectangleShape rectangle;

	Fichier fichier;
	Audio audio;

	std::vector<std::shared_ptr<MenuItem>> menu_items;
	int selectedItemIndex;

};
