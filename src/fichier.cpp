#include "../include/fichier.h"

Fichier::Fichier()
{
}

int Fichier::chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl){

	FILE* fichier = NULL;
	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = { 0 };
	int i = 0, j = 0;

    // Chemin de fichier de niveau
    std::string path = "./assets/stage/niveau";
    path += std::to_string(lvl);
    path += ".lvl";

    fichier = fopen(path.c_str(), "r");
	if (fichier == NULL) {
		return 0;
	}else{
		fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
        for (i = 0; i < NB_BLOCS_LARGEUR; i++){
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++){
                switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j]){
                    case '0':
                        niveau[j][i] = 0;
                        break;
                    case '1':
                        niveau[j][i] = 1;
                        break;
                    case '2':
                        niveau[j][i] = 2;
                        break;
                    case '3':
                        niveau[j][i] = 3;
                        break;
                    case '4':
                        niveau[j][i] = 4;
                        break;
                    case '5':
                        niveau[j][i] = 5;
                        break;
                }
            }
        }
	}
    fclose(fichier);
    return 1;
}

int Fichier::sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl){

    FILE* fichier = NULL;
    int i = 0, j = 0;

    // Chemin de fichier de niveau
    std::string path = "./assets/stage/niveau";
    path += std::to_string(lvl);
    path += ".lvl";

    fichier = fopen(path.c_str(), "w");
    if (fichier == NULL)
        return 0;

    for (i = 0; i < NB_BLOCS_LARGEUR; i++)
    {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
        {
            fprintf(fichier, "%d", niveau[j][i]);
        }
    }

    fclose(fichier);
    return 1;
}

std::vector<Fichier::DialogueData> Fichier::readDialogues(int lvl) {

	// Chemin du fichier de niveau
	std::string path = "./assets/speech/niveau";
	path += std::to_string(lvl);
	path += ".sp";

	std::vector<DialogueData> dialogues;

	std::ifstream fichier(path);
	if (!fichier.is_open()) {
		std::cerr << "Erreur lors de l'ouverture du fichier : " << path << std::endl;
		return dialogues;
	}

	std::string line;
	while (std::getline(fichier, line)) {
		std::regex regexPattern(R"(([^$]+)\$([^$]+)\$([^$]+))");
		std::smatch match;

		if (std::regex_match(line, match, regexPattern)) {
			DialogueData dialogueData;
			dialogueData.name = match[1];
			dialogueData.speech = match[2];
			dialogueData.path = match[3];
			dialogues.push_back(dialogueData);
		}
	}

	fichier.close();

	return dialogues;
}

int Fichier::nbLvlFile()
{
	int entry_count = 0;
	for (const auto& entry : fs::directory_iterator("./assets/stage")) {
		if (entry.is_regular_file()) {
			entry_count++;
		}
	}
	return entry_count;
}