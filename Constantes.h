#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/// MACROS ///

// Caractères spéciaux
#define BORDURE_ANGLE_HD char(191)
#define BORDURE_ANGLE_BD char(217)
#define BORDURE_ANGLE_HG char(218)
#define BORDURE_ANGLE_BG char(192)
#define BORDURE_BARRE_HORZ char(196)
#define BORDURE_BARRE_VERT char(179)
#define BORDURE_INTER3_HAUT char(193)
#define BORDURE_INTER3_BAS char(194)
#define BORDURE_INTER3_DROITE char(195)
#define BORDURE_INTER3_GAUCHE char(180)
#define BORDURE_INTER4 char(197)

#define E_AIGU char(130)
#define E_GRAVE char(138)
#define A_GRAVE char(133)
#define CARAC_CARRE char(254)

// Macros de lisibilité de code
#define BLANC 'B'
#define NOIR 'N'
#define COUP_JOUABLE '.'

#define MENU_ASCII_ART "          ___  _   _          _ _\n         / _ \\| |_| |__   ___| | | ___\n        | | | | __|  _ \\ / _ \\ | |/ _ \\\n        | |_| | |_| | | |  __/ | | (_) |\n         \\___/ \\__|_| |_|\\___|_|_|\\___/"


/// CONSTANTES ///

// Constantes d'affichage console
#define TAILLE_PLATEAU 8
#define LIGNE_AFFICHAGE 5
#define COLONNE_AFFICHAGE 4

// Constantes d'affichage Allegro
#define ALLEG_TCASE 60
#define ALLEG_COULEUR_VERT makecol(46,119,57)
#define ALLEG_COULEUR_MARRON makecol(110,35,12)
#define ALLEG_COULEUR_PALE makecol(187,250,141)

// Touches directionnelles
#define FLECHE_HAUT 72
#define FLECHE_BAS 80
#define FLECHE_GAUCHE 75
#define FLECHE_DROITE 77

#endif // CONSTANTES_H_INCLUDED
