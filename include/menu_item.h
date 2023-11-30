#pragma once
#include <SFML/Graphics.hpp>

class MenuItem
{

public:
	MenuItem(const std::string& text, const sf::Vector2f& position);

	void setSelected(bool isSelected);
	void draw(sf::RenderWindow& window);

private:
	std::string text;
	sf::Font font;
	sf::Text label;

};

