#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include "Constantes.h"

class Pion
{
    private :
        bool m_couleur; // Couleur : true (blanc) / false (noir)
        Coords m_pos; // Coordonn�es x&y du pion dans le damier
    public :
        // C & D
        Pion();
        Pion(bool _couleur, int _x, int _y);
        ~Pion();
};


#endif // PION_H_INCLUDED
