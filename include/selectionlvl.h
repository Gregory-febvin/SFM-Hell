#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/constantes.h"
#include "../include/jeu.h"
#include "../include/editeur.h"
using namespace std;

#include "../include/audio.h"
#include "../include/Menu.h"

class SelectionLvl
{

public:
	SelectionLvl(sf::RenderWindow* window);

	void selectionJeu();
	void selectionEdition();
	//void regle();

private:
	sf::RenderWindow* window;
};