#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "audio.h"
#include "constantes.h"
#include "fichier.h"
#include "jeu.h"
#include "editeur.h"

Audio::Audio() {
    
}

bool Audio::loadMusic(const std::string& filePath) {
    if (!buffer.openFromFile(filePath)) {
        // Le chargement de musique a échoué
        return false;
    }
    return true;
}

void Audio::playMusic() {
    buffer.play();
}

void Audio::stopMusic() {
    buffer.stop();
}