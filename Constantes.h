#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/// MACROS ///

#define DEFAULT_COLOR Color(BLANC, VERT)

/// CONSTANTES ///

#define NONE -1

/// STRUCTURES & ENUMERATIONS ///

typedef struct StructCoords
{
    int x, y;
}Coords;


typedef enum EnumColors
{
    NOIR,
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
    BLANC
}e_color;

#endif // CONSTANTES_H_INCLUDED
