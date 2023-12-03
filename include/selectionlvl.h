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
	//void regle();

private:
	sf::RenderWindow* window;
};