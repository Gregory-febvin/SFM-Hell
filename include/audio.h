#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "constantes.h"

class Audio {
public:
    Audio();

    bool loadMusic(const std::string& filePath);
    void playMusic();
    void stopMusic();
	void musicMenu();

    sf::Music buffer;
};