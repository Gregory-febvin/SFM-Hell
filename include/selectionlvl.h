#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/constantes.h"
#include "../include/jeu.h"
#include "../include/editeur.h"

#include "../include/audio.h"
#include "../include/Menu.h"

using namespace std;

class SelectionLvl
{

public:
	SelectionLvl(sf::RenderWindow* window);

	void selectGame();
	void selectChapter();
	void selectChapterEditor();
	void loadAssets();

private:
	sf::RenderWindow* window;
	sf::Clock clock;
	sf::Time frameTime;

	sf::Sprite background_sprite, character_sprite;
	sf::Texture background_texture, character_texture;
	sf::Text text_title, text_command_quit, text_command_select;
	sf::Font font;
};