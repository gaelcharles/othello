#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "Console.h"
#include "Damier.h"
#include <vector>

class IA
{
    private :
        int m_difficulte; // 1: facile (aléatoire)
    public :
        // C & D
        IA();
        ~IA();

        //Methodes
        bool TourOrdinateur(Console* _pConsole, Damier* _pDamier, char _couleur_tour);

        //G & S
        int getDifficulte() const { return m_difficulte; }
        void setDifficulte(int _difficulte);
};

#endif // IA_H_INCLUDED
