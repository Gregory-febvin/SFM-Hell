#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

#include "../include/menu_item.h"
#include "../include/selectionlvl.h"
#include "../include/jeu.h"

class Menu
{

public:
	Menu(sf::RenderWindow& window);

	void start_menu(sf::Event event);
	void create_chapter_menu();
	void select_chapter_menu(sf::Event event);

	void draw();
	void moveUp();
	void moveDown();
	int getSelectedItemIndex() const;

private:
	sf::RenderWindow& window;
	sf::Font font;

	std::vector<MenuItem> items;
	int selectedItemIndex;

};
