#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <vector>

#include "constantes.h"
#include "fichier.h"
#include "audio.h"
#include "menu.h"

class Jeu {
public:
	Jeu(sf::RenderWindow* window, int lvl);

	void loadAssets();
	int cinematic();
	int jouer();
	void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i* pos, int direction);
	void deplacerCaisse(int* premiereCase, int* secondeCase);

private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Sprite vide, mur, caisse, objectif, caisseOk, mario;
	sf::Sprite* allAsset[6] = { &vide, &mur, &caisse, &objectif, &caisseOk, &mario };
	sf::Texture textureVide, textureMur, textureCaisse, textureCaisseOk, textureObjectif, textureMario[5];
	sf::Vector2i Position, PositionJoueur;

	Fichier fichier;

	int lvl;
};

