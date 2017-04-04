#ifndef DAMIER_H_INCLUDED
#define DAMIER_H_INCLUDED

#include <vector>
#include "Pion.h"

class Damier
{
    private :
        std::vector<std::vector<Pion*> > m_plateau; // Vecteur de vecteur de pointeurs sur pions qui repr�sente le plateau de jeu
        int m_taille; // Taille du plateau carr�, en cases (8)
    public :
        // C & D
        Damier();
        ~Damier();
};


#endif // DAMIER_H_INCLUDED
