#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/// MACROS ///

#define DEFAULT_COLOR Color(BLANC_CONSOLE, VERT)
#define BLANC true
#define NOIR false

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

/// CONSTANTES ///

#define NONE -1

/// STRUCTURES & ENUMERATIONS ///

typedef struct StructCoords
{
    int x, y;
}Coords;


typedef enum EnumColors
{
    NOIR_CONSOLE,
    BLEU_FONCE,
    VERT,
    BLEU_VERT,
    MARRON,
    VIOLET,
    OR,
    GRIS_CLAIR,
    GRIS,
    BLEU,
    VERT_CLAIR,
    CYAN,
    ROUGE,
    ROSE,
    JAUNE,
    BLANC_CONSOLE
}e_color;

#endif // CONSTANTES_H_INCLUDED
