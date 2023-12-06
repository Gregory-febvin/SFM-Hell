#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "constantes.h"

class MenuItem
{

public:
	MenuItem(sf::RenderWindow* window, const sf::Font& font, const std::string& text, const sf::Vector2f& position);

	void setMenuItemStart();
	void setSelectedItemStart(bool isSelected);
	void setMenuItemChapter();
	void setSelectedItemChapter(bool isSelected);
	void setSelected(bool isSelected, int id_menu);
	void draw();

private:
	sf::RenderWindow* window;

	std::string text;
	sf::Font font;
	sf::Text label;
	sf::RectangleShape rectangle;
	sf::Vector2f position;
};

