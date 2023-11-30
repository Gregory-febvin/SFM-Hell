#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "constantes.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl);
int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl);
std::vector<std::string> readDialogues(int lvl);