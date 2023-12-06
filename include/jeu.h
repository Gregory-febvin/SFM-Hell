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
	void loadTexts();
	int cinematic();
	int jouer();
	int nbEnnemy(int carte[][NB_BLOCS_HAUTEUR]);
	void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i* pos, int direction);
	void deplacerCaisse(int* premiereCase, int* secondeCase);

private:
	sf::RenderWindow* window;
	sf::Clock clock;
	sf::Time frameTime;

	sf::Font font;
	sf::Sprite sprite_overlay, vide, mur, caisse, objectif, caisseOk, mario;
	sf::Sprite* allAsset[6] = { &vide, &mur, &caisse, &objectif, &caisseOk, &mario };
	sf::Texture texture_overlay, textureVide, textureMur, textureCaisse, textureCaisseOk, textureObjectif, textureMario[5];
	sf::Vector2i Position, PositionJoueur;
	sf::Text text_command_restart, text_command_quit, text_command_skip, text_lvl, text_ennemy;

	Fichier fichier;

	int lvl, nb_ennemy;
};

