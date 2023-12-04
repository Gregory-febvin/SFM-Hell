#include "../include/jeu.h"

Jeu::Jeu(sf::RenderWindow* window, int lvl) 
	: window(window), lvl(lvl) 
{
	loadAssets();
}

void Jeu::loadAssets() {
	// Chargement de la police d'écriture
	font.loadFromFile("./assets/font/Ketchum.otf");

	// Chargement des textures des objets
	textureVide.loadFromFile("./assets/textures/vide.png");
	vide.setTexture(textureVide);

	textureMur.loadFromFile("./assets/textures/mur.png");
	mur.setTexture(textureMur);

	textureCaisse.loadFromFile("./assets/textures/caisse.png");
	caisse.setTexture(textureCaisse);

	textureCaisseOk.loadFromFile("./assets/textures/caisse_ok.png");
	caisseOk.setTexture(textureCaisseOk);

	textureObjectif.loadFromFile("./assets/textures/objectif.png");
	objectif.setTexture(textureObjectif);

	textureMario[HAUT].loadFromFile("./assets/textures/mario_haut.png");

	textureMario[BAS].loadFromFile("./assets/textures/mario_bas.png");

	textureMario[GAUCHE].loadFromFile("./assets/textures/mario_gauche.png");

	textureMario[DROITE].loadFromFile("./assets/textures/mario_droite.png");
}

int Jeu::cinematic() {
	bool continuer = true;
	sf::Event event;
	sf::Sprite background_sprite, character_sprite;
	sf::Texture background_texture, character_texture;

	if (!font.loadFromFile("./assets/font/Ketchum.otf")) {
		std::cout << "Failed to load font!" << std::endl;
	}

	size_t currentDialogueIndex = 0;
	std::vector<Fichier::DialogueData> dialogues = fichier.readDialogues(lvl);

	sf::Text name;
	name.setFont(font);
	name.setFillColor(sf::Color::Red);
	name.setCharacterSize(22);
	name.setString(dialogues[currentDialogueIndex].name);
	name.setPosition(
		(LARGEUR_FENETRE - name.getLocalBounds().width) / 2,
		(SIZE_SPEECH + name.getLocalBounds().height)
	);

	sf::Text speech;
	speech.setFont(font);
	speech.setFillColor(sf::Color::White);
	speech.setCharacterSize(18);
	speech.setString(dialogues[currentDialogueIndex].speech);
	speech.setPosition(
		(LARGEUR_FENETRE - speech.getLocalBounds().width) / 2,
		(SIZE_SPEECH + name.getLocalBounds().height * 3)
	);

	if (character_texture.loadFromFile(dialogues[currentDialogueIndex].path)) {
		character_sprite.setTexture(character_texture);
		float scale = (SIZE_SPEECH) / character_sprite.getGlobalBounds().height;
		character_sprite.setScale(scale, scale);
		character_sprite.setPosition((LARGEUR_FENETRE - character_sprite.getGlobalBounds().width) / 2, 0);
	}

	if (background_texture.loadFromFile("./assets/textures/background.png")) {
		background_sprite.setTexture(background_texture);
		float scale = (HAUTEUR_FENETRE) / background_sprite.getGlobalBounds().height;
		background_sprite.setScale(scale, scale);
		background_sprite.setPosition(0, 0);
	}

	// Affichage des dialogues
	while (continuer) {
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				continuer = false;
				return ERROR_EXIT;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
					continuer = false;
					return ERROR_NEXT;
				}
				if (event.key.code == sf::Keyboard::Enter) {
					// Affiche le prochain dialogue lorsque l'utilisateur appuie sur "Enter"
					if (currentDialogueIndex < dialogues.size() - 1) {
						++currentDialogueIndex;

						name.setString(dialogues[currentDialogueIndex].name);
						name.setPosition(
							(LARGEUR_FENETRE - name.getLocalBounds().width) / 2,
							(SIZE_SPEECH + name.getLocalBounds().height)
						);

						speech.setString(dialogues[currentDialogueIndex].speech);
						speech.setPosition(
							(LARGEUR_FENETRE - speech.getLocalBounds().width) / 2,
							(SIZE_SPEECH + name.getLocalBounds().height * 3)
						);

						if (character_texture.loadFromFile(dialogues[currentDialogueIndex].path)) {
							character_sprite.setTexture(character_texture);
						}
					}
					else {
						// Si tous les dialogues ont été affichés, réinitialisez l'index pour les itérations suivantes
						name.setString("");
						speech.setString("");
						character_sprite.setTexture(sf::Texture());
						background_sprite.setTexture(sf::Texture());
						dialogues.clear();
						currentDialogueIndex = -1;
						continuer = false;
					}
				}
			}
		}

		window->clear();
		window->draw(background_sprite);
		window->draw(character_sprite);
		window->draw(name);
		window->draw(speech);
		window->display();
	}
}


int Jeu::jouer()
{
	Audio audio;

	bool continuer = true;
	int objectifsRestants = NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR, direction = BAS, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des musiques
	sf::SoundBuffer sonBufferVictoire;
	sf::Sound sonVictoire;

	sonBufferVictoire.loadFromFile("./assets/audio/musics/victoire.ogg");
	sonVictoire.setBuffer(sonBufferVictoire);

	// Chargement du niveau
	fichier.chargerNiveau(carte, lvl);

	std::string filename = "./assets/audio/musics/Level" + std::to_string(lvl) + ".ogg";

	if (audio.loadMusic(filename)) {
		audio.playMusic();
	}
	else {
		std::cout << "Failed to load music." << std::endl;
	}

	// Recherche de la Position de Mario au départ
	for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
			if (carte[i][j] == MARIO) { // Si Mario se trouve à cette Position
				PositionJoueur.x = i;
				PositionJoueur.y = j;
			}
		}
	}


	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				continuer = false;
				return ERROR_EXIT;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					audio.stopMusic();
					continuer = false;
					return ERROR_EXIT;
				}

				if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
					audio.stopMusic();
					continuer = false;
					return ERROR_NEXT;
				}

				if (event.key.code == sf::Keyboard::Backspace) {
					audio.stopMusic();

					return jouer();
				}

				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z) {
					deplacerJoueur(carte, &PositionJoueur, HAUT);
					direction = HAUT;
				}

				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					deplacerJoueur(carte, &PositionJoueur, BAS);
					direction = BAS;
				}

				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q) {
					deplacerJoueur(carte, &PositionJoueur, GAUCHE);
					direction = GAUCHE;
				}

				if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
					deplacerJoueur(carte, &PositionJoueur, DROITE);
					direction = DROITE;
				}

				carte[PositionJoueur.x][PositionJoueur.y] = MARIO;
			}

			/* Affichage du niveau */
			sf::FloatRect Position;
			for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
				for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) {
					Position.top = colonne * TAILLE_BLOC;
					Position.left = ((LARGEUR_FENETRE) - (LARGEUR_FENETRE_JEU)) / 2 + ligne * TAILLE_BLOC;
					sf::Sprite* asset = allAsset[carte[ligne][colonne]];
					asset->setPosition(Position.left, Position.top);
					window->draw(*asset);
				}
			}
			mario.setTexture(textureMario[direction]);
			window->draw(mario);

			// Affichage du numéro du niveau
			sf::Text niveau;
			niveau.setFont(font);
			niveau.setCharacterSize(36);
			niveau.setString("Niveau " + std::to_string(lvl));
			niveau.setPosition(
				(LARGEUR_FENETRE_JEU - niveau.getLocalBounds().width) / 2,
				(HAUTEUR_FENETRE - niveau.getLocalBounds().height * 2)
			);
			window->draw(niveau);

			// S'il ne reste plus d'objectif on gagne la partie
			if (objectifsRestants == 0) {
				sonVictoire.play();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
					sonVictoire.stop();
					audio.stopMusic();
					continuer = false;
					return ERROR_NEXT;
				}
			}
			else {
				objectifsRestants = NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR;
				for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
					for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
						if (carte[i][j] != OBJECTIF) {
							objectifsRestants--;
						}
					}
				}
			}
			window->display();
		}
		window->clear(sf::Color(2, 2, 26));
	}
}

void Jeu::deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i* PositionJoueur, int direction) {

	// Test des collisions dans la direction du haut
	if (direction == HAUT) {
		if (carte[PositionJoueur->x][PositionJoueur->y - 1] != MUR &&
			carte[PositionJoueur->x][PositionJoueur->y - 1] != OBJECTIF &&
			carte[PositionJoueur->x][PositionJoueur->y - 1] != CAISSE_OK &&
			PositionJoueur->x - 1 > 0) {

			if ((carte[PositionJoueur->x][PositionJoueur->y - 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y - 2] != MUR &&
				carte[PositionJoueur->x][PositionJoueur->y - 2] != CAISSE &&
				carte[PositionJoueur->x][PositionJoueur->y - 2] != CAISSE_OK &&
				PositionJoueur->x - 2 > 0)) {

				deplacerCaisse(&carte[PositionJoueur->x][PositionJoueur->y - 1], &carte[PositionJoueur->x][PositionJoueur->y - 2]);
				carte[PositionJoueur->x][PositionJoueur->y - 1] = VIDE;
			}

			// Déplacement du joueur sur le haut
			if ((carte[PositionJoueur->x][PositionJoueur->y - 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y - 2] == MUR ||
				carte[PositionJoueur->x][PositionJoueur->y - 2] == CAISSE ||
				carte[PositionJoueur->x][PositionJoueur->y - 2] == CAISSE_OK)) {

				PositionJoueur->y;
			}
			else {
				PositionJoueur->y--;
				carte[PositionJoueur->x][PositionJoueur->y + 1] = VIDE;
			}
		}
	}

	// Test des collisions dans la direction du bas
	if (direction == BAS) {
		if (carte[PositionJoueur->x][PositionJoueur->y + 1] != MUR &&
			carte[PositionJoueur->x][PositionJoueur->y + 1] != OBJECTIF &&
			carte[PositionJoueur->x][PositionJoueur->y + 1] != CAISSE_OK &&
			PositionJoueur->y + 1 < NB_BLOCS_HAUTEUR) {

			if ((carte[PositionJoueur->x][PositionJoueur->y + 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y + 2] != MUR &&
				carte[PositionJoueur->x][PositionJoueur->y + 2] != CAISSE &&
				carte[PositionJoueur->x][PositionJoueur->y + 2] != CAISSE_OK &&
				PositionJoueur->y + 2 < NB_BLOCS_HAUTEUR)) {

				deplacerCaisse(&carte[PositionJoueur->x][PositionJoueur->y + 1], &carte[PositionJoueur->x][PositionJoueur->y + 2]);
				carte[PositionJoueur->x][PositionJoueur->y + 1] = VIDE;
			}

			// Déplacement du joueur sur le bas
			if ((carte[PositionJoueur->x][PositionJoueur->y + 1] == CAISSE) &&
				(carte[PositionJoueur->x][PositionJoueur->y + 2] == MUR ||
				carte[PositionJoueur->x][PositionJoueur->y + 2] == CAISSE ||
				carte[PositionJoueur->x][PositionJoueur->y + 2] == CAISSE_OK)) {

				PositionJoueur->y;
			}
			else {
				PositionJoueur->y++;
				carte[PositionJoueur->x][PositionJoueur->y - 1] = VIDE;
			}
		}
	}

	// Test des collisions dans la direction de la gauche
	if (direction == GAUCHE) {
		if (carte[PositionJoueur->x - 1][PositionJoueur->y] != MUR &&
			carte[PositionJoueur->x - 1][PositionJoueur->y] != OBJECTIF &&
			carte[PositionJoueur->x - 1][PositionJoueur->y] != CAISSE_OK &&
			PositionJoueur->x - 1 > 0) {

			if ((carte[PositionJoueur->x - 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x - 2][PositionJoueur->y] != MUR &&
				carte[PositionJoueur->x - 2][PositionJoueur->y] != CAISSE &&
				carte[PositionJoueur->x - 2][PositionJoueur->y] != CAISSE_OK &&
				PositionJoueur->x - 2 > 0)) {

				deplacerCaisse(&carte[PositionJoueur->x - 1][PositionJoueur->y], &carte[PositionJoueur->x - 2][PositionJoueur->y]);
				carte[PositionJoueur->x - 1][PositionJoueur->y] = VIDE;

			}

			// Déplacement du joueur sur la gauche
			if ((carte[PositionJoueur->x - 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x - 2][PositionJoueur->y] == MUR ||
				carte[PositionJoueur->x - 2][PositionJoueur->y] == CAISSE ||
				carte[PositionJoueur->x - 2][PositionJoueur->y] == CAISSE_OK)) {

				PositionJoueur->x;
			}
			else {
				PositionJoueur->x--;
				carte[PositionJoueur->x + 1][PositionJoueur->y] = VIDE;
			}
		}
	}

	// Test des collisions dans la direction du droite
	if (direction == DROITE) {
		if (carte[PositionJoueur->x + 1][PositionJoueur->y] != MUR && 
			carte[PositionJoueur->x + 1][PositionJoueur->y] != OBJECTIF && 
			carte[PositionJoueur->x + 1][PositionJoueur->y] != CAISSE_OK &&
			PositionJoueur->x + 1 < NB_BLOCS_LARGEUR) {

			if ((carte[PositionJoueur->x + 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x + 2][PositionJoueur->y] != MUR &&
				carte[PositionJoueur->x + 2][PositionJoueur->y] != CAISSE &&
				carte[PositionJoueur->x + 2][PositionJoueur->y] != CAISSE_OK &&
				PositionJoueur->x + 2 < NB_BLOCS_LARGEUR)) {

					deplacerCaisse(&carte[PositionJoueur->x + 1][PositionJoueur->y], &carte[PositionJoueur->x + 2][PositionJoueur->y]);
					carte[PositionJoueur->x + 1][PositionJoueur->y] = VIDE;
			}

			// Déplacement du joueur sur la droite
			if ((carte[PositionJoueur->x + 1][PositionJoueur->y] == CAISSE) &&
				(carte[PositionJoueur->x + 2][PositionJoueur->y] == MUR ||
				carte[PositionJoueur->x + 2][PositionJoueur->y] == CAISSE ||
				carte[PositionJoueur->x + 2][PositionJoueur->y] == CAISSE_OK)) {

				PositionJoueur->x;
			}
			else {
				PositionJoueur->x++;
				carte[PositionJoueur->x - 1][PositionJoueur->y] = VIDE;
			}
		}
	}
}

void Jeu::deplacerCaisse(int* premiereCase, int* secondeCase) {

	if (*premiereCase == CAISSE) {

		// Si la caisse va sur un objectif, la caisse devient une caisse_ok
		if (*secondeCase == OBJECTIF) {
			(*secondeCase) = CAISSE_OK;
		} else {
			(*secondeCase) = CAISSE;
		}

	}
}