#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/audio.h"
#include "../include/constantes.h"
#include "../include/fichier.h"
#include "../include/jeu.h"
#include "../include/editeur.h"

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

void Audio::musicMenu() {

	if (!loadMusic("./assets/audio/musics/Title_Theme.ogg")) {
		cout << "La musique n'a pas chargée";
	}
	else {
		playMusic();
	}

}