#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector> 
#include <regex>

#include "constantes.h"

namespace fs = std::filesystem;

class Fichier {
public:

	Fichier();

	struct DialogueData {
		std::string name;
		std::string speech;
		std::string path;
	};

	int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl);
	int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl);
	std::vector<DialogueData> readDialogues(int lvl);
	int nbLvlFile();
	std::string convertIntToRoman(int num);
};
