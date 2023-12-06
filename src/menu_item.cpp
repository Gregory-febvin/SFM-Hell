#include "../include/menu_item.h"

MenuItem::MenuItem(sf::RenderWindow* window, const sf::Font& font, const std::string& text, const sf::Vector2f& position) 
	: window(window), font(font), text(text)
{		
	this->font = font;
	this->position = position;

	label.setFont(this->font);
	label.setString(text);
	label.setCharacterSize(FONT_SIZE_TEXT);

}

void MenuItem::setMenuItemStart() {
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color(101, 61, 72));
	rectangle.setOutlineThickness(2.0f);
	rectangle.setSize(sf::Vector2f(LARGEUR_FENETRE / 3, label.getLocalBounds().height + 10));
	rectangle.setPosition(LARGEUR_FENETRE / 3, position.y + 5);

	label.setPosition((position.x - label.getLocalBounds().width) / 2, position.y);
}

void MenuItem::setSelectedItemStart(bool isSelected) {
	rectangle.setOutlineColor(isSelected ? sf::Color(230, 77, 81) : sf::Color(101, 61, 72));

	const float scale = 1.1f;
	rectangle.setScale(isSelected ? scale : 1, isSelected ? scale : 1);

	float offsetX = ((LARGEUR_FENETRE / 3) * (scale - 1)) / 2.0f;
	float offsetY = (label.getLocalBounds().height * (scale - 1));
	rectangle.setPosition(
		isSelected ? (LARGEUR_FENETRE / 3) - offsetX : (LARGEUR_FENETRE / 3),
		isSelected ? position.y + 5 - offsetY : position.y + 5);
}

void MenuItem::setMenuItemChapter() {
	rectangle.setFillColor(sf::Color(2, 2, 27));
	rectangle.setOutlineColor(sf::Color(103, 103, 118));
	rectangle.setOutlineThickness(2.0f);
	rectangle.setSize(sf::Vector2f(LARGEUR_LABEL_LVL, HAUTEUR_LABEL_LVL));
	rectangle.setPosition(position);

	label.setColor(sf::Color(103, 103, 118));
	label.setPosition((position.x + LARGEUR_LABEL_LVL / 2) - label.getLocalBounds().width + 10, (position.y + HAUTEUR_LABEL_LVL / 2) - label.getLocalBounds().height);
}

void MenuItem::setSelectedItemChapter(bool isSelected) {
	rectangle.setFillColor(isSelected ? sf::Color(65, 65, 83) : sf::Color(2, 2, 27));
	rectangle.setOutlineColor(isSelected ? sf::Color::White : sf::Color(103, 103, 118));

	label.setColor(isSelected ? sf::Color::White : sf::Color(103, 103, 118));
}

void MenuItem::setSelected(bool isSelected, int id_menu)
{
	switch (id_menu)
	{
	case ID_MENU_START:
		setSelectedItemStart(isSelected);
		break;
	case ID_MENU_CHAPTER:
		setSelectedItemChapter(isSelected);
		break;
	default:
		break;
	}
}

void MenuItem::draw() {
	window->draw(this->rectangle);
	window->draw(this->label);
}
