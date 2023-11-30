#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"

int jouer(sf::RenderWindow* window, int lvl);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i* pos, int direction);
void deplacerCaisse(int* premiereCase, int* secondeCase);
