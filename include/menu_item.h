#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class MenuItem
{

public:
	MenuItem(sf::RenderWindow* window, const sf::Font& font, const std::string& text, const sf::Vector2f& position);

	void setSelected(bool isSelected);
	void draw();

private:
	sf::RenderWindow* window;

	std::string text;
	sf::Font font;
	sf::Text label;
};

