#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define LARGEUR_FENETRE		1366
#define HAUTEUR_FENETRE		768

#define FRAMERATE			1.0f / 60.0f

#define TAILLE_BLOC         34
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_LABEL_LVL	60
#define HAUTEUR_LABEL_LVL	40
#define LARGEUR_LABEL_MENU	200
#define SIZE_SPEECH			HAUTEUR_FENETRE * 4 / 6

#define FONT_SIZE_TEXT		24
#define FONT_SIZE_NAME		28
#define FONT_SIZE_NUMBER	60
#define FONT_SIZE_COMMAND	18
#define FONT_SIZE_TITLE		72

#define LARGEUR_FENETRE_JEU     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE_JEU     TAILLE_BLOC * NB_BLOCS_HAUTEUR

#define ID_MENU_START		1
#define ID_MENU_CHAPTER		2

#define ERROR_EXIT	0
#define ERROR_NEXT	1

enum {STATIC, HAUT, BAS, GAUCHE, DROITE};
enum {VIDE, MUR, CAISSE, OBJECTIF, CAISSE_OK, MARIO};

#endif