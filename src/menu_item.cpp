#include "../include/menu_item.h"

MenuItem::MenuItem(const std::string& text, const sf::Vector2f& position) : text(text)
{
	if (!font.loadFromFile("./assets/font/Ketchum.otf")) {
	}
		
	label.setFont(font);
	label.setString(text);
	label.setPosition(position);
	label.setCharacterSize(24);
}

void MenuItem::setSelected(bool isSelected) {
	label.setFillColor(isSelected ? sf::Color::Red : sf::Color::White);
}

void MenuItem::draw(sf::RenderWindow& window) {
	window.draw(label);
}
