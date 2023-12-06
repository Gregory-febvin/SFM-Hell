#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/constantes.h"
#include "../include/fichier.h"

using namespace std;

class Editeur
{

public:
	Editeur(sf::RenderWindow* window, int lvl);

	void loadAssets();
	int editer();

private:
	sf::RenderWindow* window;
	sf::Clock clock;
	sf::Time frameTime;

	sf::Sprite vide, mur, caisse, objectif, caisseOk, mario;
	sf::Sprite choixVide, choixMur, choixCaisse, choixObjectif, choixCaisseOk, choixMario;
	sf::Sprite *allAsset[6] = { &vide, &mur, &caisse, &objectif, &caisseOk, &mario };
	sf::Texture textureVide, textureChoixVide, textureMur, textureChoixMur, textureCaisse, textureChoixCaisse, textureObjectif, textureChoixObjectif, textureCaisseOk, textureChoixCaisseOK, textureMario, textureChoixMario;
	sf::Font font;

	int lvl;
};
