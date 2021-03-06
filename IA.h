/// \file IA.h
/// \brief Contient la classe IA ainsi que les prototypes de ses méthodes
/// \author Gaël, Camille, Tom
/// \version Version finale

#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "Console.h"
#include "Damier.h"
#include "FenetreAllegro.h"
#include <vector>

class IA
{
    private :
        int m_difficulte; // 1: facile (aléatoire), 2: moyen(minmax)
    public :
        // C & D
        IA();
        ~IA();

        //Methodes
        std::vector< std::vector<int> > CasesJouables(Damier* _pDamier);
        int Min(Damier* _pEtat, int _profondeur);
        int Max(Damier* _pEtat, int _profondeur);
        bool TourOrdinateur(Console* _pConsole, Damier* _pDamier, FenetreAllegro* _pAllegro, char _couleur_tour); //deroulement du tour de l'ordinateur

        //G & S
        int getDifficulte() const { return m_difficulte; }
        void setDifficulte(int _difficulte);
};

#endif // IA_H_INCLUDED
