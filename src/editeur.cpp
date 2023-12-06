#include "../include/editeur.h"

Editeur::Editeur(sf::RenderWindow * window, int lvl)
	: window(window), lvl(lvl)
{
	loadAssets();
	editer();
}

void Editeur::loadAssets()
{
	// Chargement de la police d'écriture
	font.loadFromFile("./assets/font/CrimsonPro-SemiBold.ttf");

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

int Editeur::editer()
{
	bool continuer = true;
	int objetSelect = VIDE;
	int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	Fichier fichier;
	fichier.chargerNiveau(map, lvl);

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
					fichier.sauvegarderNiveau(map, lvl);
				}
				if (event.key.code == sf::Keyboard::BackSpace) {
					fichier.chargerNiveau(map, lvl);
				}
			}

			//Placement objet
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
			sf::FloatRect Position;
			for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
				for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) {
					int x = mousePosition.x / TAILLE_BLOC;
					int y = mousePosition.y / TAILLE_BLOC;
					Position.top = colonne * TAILLE_BLOC;
					Position.left = ligne * TAILLE_BLOC;
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						map[x][y] = objetSelect;
					}
					sf::Sprite* asset = allAsset[map[ligne][colonne]];
					asset->setPosition(Position.left, Position.top);

					window->draw(*asset);
				}
			}

			// Affichage du numéro du niveau
			sf::Text niveau;
			niveau.setFont(font);
			niveau.setString("Edition Niveau " + std::to_string(lvl));
			niveau.setPosition(
				(LARGEUR_FENETRE_JEU - niveau.getLocalBounds().width) / 2,
				(HAUTEUR_FENETRE_JEU + niveau.getLocalBounds().height)
			);

			// Affichage choix des sprites
			sf::RectangleShape select(sf::Vector2f(68.f, 68.f));

			float largeur = LARGEUR_FENETRE - choixVide.getLocalBounds().width * 1.3;
			float hauteur = (TAILLE_BLOC / 2) + (choixVide.getLocalBounds().height);

			select.setFillColor(sf::Color(255, 255, 255, 80));
			choixVide.setPosition(largeur, hauteur * VIDE);
			choixMur.setPosition(largeur, hauteur * MUR);
			choixCaisse.setPosition(largeur, hauteur * CAISSE);
			choixObjectif.setPosition(largeur, hauteur * OBJECTIF);
			choixCaisseOk.setPosition(largeur, hauteur * CAISSE_OK);
			choixMario.setPosition(largeur, hauteur * MARIO);
			if (objetSelect == VIDE) {
				select.setPosition(largeur, hauteur * VIDE);
			}
			if (objetSelect == MUR) {
				select.setPosition(largeur, hauteur * MUR);
			}
			if (objetSelect == CAISSE) {
				select.setPosition(largeur, hauteur * CAISSE);
			}
			if (objetSelect == OBJECTIF) {
				select.setPosition(largeur, hauteur * OBJECTIF);
			}
			if (objetSelect == CAISSE_OK) {
				select.setPosition(largeur, hauteur * CAISSE_OK);
			}
			if (objetSelect == MARIO) {
				select.setPosition(largeur, hauteur * MARIO);
			}

			window->draw(niveau);
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
