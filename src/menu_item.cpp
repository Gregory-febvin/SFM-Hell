#include "../include/menu_item.h"

MenuItem::MenuItem(sf::RenderWindow* window, const sf::Font& font, const std::string& text, const sf::Vector2f& position) 
	: window(window), font(font), text(text)
{		
	this->font = font;

	label.setFont(this->font);
	label.setString(text);
	label.setPosition(position);
	label.setCharacterSize(18);
}

void MenuItem::setSelected(bool isSelected) {
	label.setFillColor(isSelected ? sf::Color::Red : sf::Color::White);
}

void MenuItem::draw() {
	window->draw(this->label);
}
