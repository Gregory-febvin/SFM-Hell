#include "../include/editeur.h"

Editeur::Editeur(sf::RenderWindow * window, int lvl)
	: window(window), lvl(lvl)
{
	loadAssets();
	loadTexts();
	editer();
}

void Editeur::loadAssets()
{
	// Chargement de la police d'écriture
	font.loadFromFile("./assets/font/CrimsonPro-SemiBold.ttf");

	// Chargement de l'overlay
	texture_overlay.loadFromFile("./assets/textures/game_overlay.jpg");
	sprite_overlay.setTexture(texture_overlay);
	float scale = (LARGEUR_FENETRE) / sprite_overlay.getGlobalBounds().width;
	sprite_overlay.setScale(scale, scale);
	sprite_overlay.setPosition(0, 0);

	// Chargement des sprites
	textureVide.loadFromFile("./assets/textures/vide.png");
	vide.setTexture(textureVide);

	textureChoixVide.loadFromFile("./assets/textures/choix_vide.png");
	choixVide.setTexture(textureChoixVide);

	textureMur.loadFromFile("./assets/textures/mur.png");
	mur.setTexture(textureMur);

	textureChoixMur.loadFromFile("./assets/textures/choix_mur.png");
	choixMur.setTexture(textureChoixMur);

	textureCaisse.loadFromFile("./assets/textures/caisse.png");
	caisse.setTexture(textureCaisse);

	textureChoixCaisse.loadFromFile("./assets/textures/choix_caisse.png");
	choixCaisse.setTexture(textureChoixCaisse);

	textureObjectif.loadFromFile("./assets/textures/objectif.png");
	objectif.setTexture(textureObjectif);

	textureChoixObjectif.loadFromFile("./assets/textures/choix_objectif.png");
	choixObjectif.setTexture(textureChoixObjectif);

	textureCaisseOk.loadFromFile("./assets/textures/caisse_ok.png");
	caisseOk.setTexture(textureCaisseOk);

	textureChoixCaisseOK.loadFromFile("./assets/textures/choix_caisse_ok.png");
	choixCaisseOk.setTexture(textureChoixCaisseOK);

	textureMario.loadFromFile("./assets/textures/mario_bas.png");
	mario.setTexture(textureMario);

	textureChoixMario.loadFromFile("./assets/textures/mario.png");
	choixMario.setTexture(textureChoixMario);
}

void Editeur::loadTexts()
{
	// Affichage commandes
	text_command_quit.setFont(font);
	text_command_quit.setCharacterSize(FONT_SIZE_COMMAND);
	text_command_quit.setString("- QUIT [ ECHAP ] -");
	text_command_quit.setPosition(
		(LARGEUR_FENETRE - text_command_quit.getLocalBounds().width) * 1 / 3,
		(HAUTEUR_FENETRE - text_command_quit.getLocalBounds().height * 2)
	);

	text_command_save.setFont(font);
	text_command_save.setCharacterSize(FONT_SIZE_COMMAND);
	text_command_save.setString("- SAVE [ ENTER ] -");
	text_command_save.setPosition(
		(LARGEUR_FENETRE - text_command_save.getLocalBounds().width) * 2 / 3,
		(HAUTEUR_FENETRE - text_command_save.getLocalBounds().height * 2)
	);

	// Affichage du numéro du niveau
	text_lvl.setFont(font);
	text_lvl.setCharacterSize(FONT_SIZE_NUMBER);
	text_lvl.setString(fichier.convertIntToRoman(lvl));
	text_lvl.setPosition(
		(LARGEUR_FENETRE - text_lvl.getLocalBounds().width) * 8 / 9,
		(HAUTEUR_FENETRE - text_lvl.getLocalBounds().height) * 6 / 8
	);

	// Affichage du nombre d'ennemis
	text_ennemy.setFont(font);
	text_ennemy.setCharacterSize(FONT_SIZE_NUMBER);
}

int Editeur::editer()
{
	bool continuer = true;
	int objetSelect = VIDE;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	fichier.chargerNiveau(carte, lvl);

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (continuer) {
		sf::Time elapsed = clock.restart();
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				return ERROR_EXIT;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					continuer = 0;
				}
				//Changement objet
				if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
					objetSelect = MUR;
				}
				if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
					objetSelect = CAISSE;
				}
				if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
					objetSelect = OBJECTIF;
				}
				if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
					objetSelect = CAISSE_OK;
				}
				if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
					objetSelect = MARIO;
				}
				if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
					objetSelect = VIDE;
				}
				//Sauvegarde et chargement du niveau
				if (event.key.code == sf::Keyboard::Enter) {
					fichier.sauvegarderNiveau(carte, lvl);
				}
				if (event.key.code == sf::Keyboard::BackSpace) {
					fichier.chargerNiveau(carte, lvl);
				}
			}

			// Affichage choix des sprites
			sf::RectangleShape select(sf::Vector2f(68.f, 68.f));

			float largeur = choixVide.getLocalBounds().width * 1.3;
			float hauteur = HAUTEUR_FENETRE * 3 / 4;

			select.setFillColor(sf::Color(255, 255, 255, 80));
			choixVide.setPosition((LARGEUR_FENETRE / 3) + largeur * VIDE, hauteur);
			choixMur.setPosition((LARGEUR_FENETRE / 3) + largeur * MUR, hauteur);
			choixCaisse.setPosition((LARGEUR_FENETRE / 3) + largeur * CAISSE, hauteur);
			choixObjectif.setPosition((LARGEUR_FENETRE / 3) + largeur * OBJECTIF, hauteur);
			choixCaisseOk.setPosition((LARGEUR_FENETRE / 3) + largeur * CAISSE_OK, hauteur);
			choixMario.setPosition((LARGEUR_FENETRE / 3) + largeur * MARIO, hauteur);
			if (objetSelect == VIDE) {
				select.setPosition((LARGEUR_FENETRE / 3) + largeur * VIDE, hauteur);
			}
			if (objetSelect == MUR) {
				select.setPosition((LARGEUR_FENETRE / 3) + largeur * MUR, hauteur);
			}
			if (objetSelect == CAISSE) {
				select.setPosition((LARGEUR_FENETRE / 3) + largeur * CAISSE, hauteur);
			}
			if (objetSelect == OBJECTIF) {
				select.setPosition((LARGEUR_FENETRE / 3) + largeur * OBJECTIF, hauteur);
			}
			if (objetSelect == CAISSE_OK) {
				select.setPosition((LARGEUR_FENETRE / 3) + largeur * CAISSE_OK, hauteur);
			}
			if (objetSelect == MARIO) {
				select.setPosition((LARGEUR_FENETRE / 3) + largeur * MARIO, hauteur);
			}

			window->draw(sprite_overlay);
			window->draw(text_command_quit);
			window->draw(text_command_save);
			window->draw(text_lvl);

			//Placement objet
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			int x = (mousePosition.x - ((LARGEUR_FENETRE - LARGEUR_FENETRE_JEU) / 2)) / TAILLE_BLOC;
			int y = mousePosition.y / TAILLE_BLOC;

			// Vérifiez si la position de la souris est à l'intérieur des limites de la carte
			if (x >= 0 && x < NB_BLOCS_LARGEUR && y >= 0 && y < NB_BLOCS_HAUTEUR) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					carte[x][y] = objetSelect;
				}
			}

			// Dessinez les objets en fonction de la carte mise à jour
			for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
				for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) {
					sf::FloatRect Position;
					Position.top = colonne * TAILLE_BLOC;
					Position.left = ((LARGEUR_FENETRE)-(LARGEUR_FENETRE_JEU)) / 2 + ligne * TAILLE_BLOC;

					sf::Sprite* asset = allAsset[carte[ligne][colonne]];
					asset->setPosition(Position.left, Position.top);
					window->draw(*asset);
				}
			}

			nb_ennemy = nbEnnemy(carte);

			text_ennemy.setString(std::to_string(nb_ennemy));
			text_ennemy.setPosition(
				(LARGEUR_FENETRE - text_ennemy.getLocalBounds().width) * 1 / 9,
				(HAUTEUR_FENETRE - text_ennemy.getLocalBounds().height) * 6 / 8
			);
			window->draw(text_ennemy);

			window->draw(choixMur);
			window->draw(choixCaisse);
			window->draw(choixObjectif);
			window->draw(choixCaisseOk);
			window->draw(choixMario);
			window->draw(select);

			window->display();
		}
		window->clear();
	}
}

int Editeur::nbEnnemy(int carte[][NB_BLOCS_HAUTEUR]) {
	int nb_ennemy = 0;
	for (int i = 0; i < NB_BLOCS_LARGEUR; ++i) {
		for (int j = 0; j < NB_BLOCS_HAUTEUR; ++j) {
			if (carte[i][j] == OBJECTIF) {
				nb_ennemy++;
			}
		}
	}
	return nb_ennemy;
}