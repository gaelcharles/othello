#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "Console.h"
#include "Damier.h"
#include <vector>

class IA
{
    private :
        int m_difficulte; // 1: facile (al�atoire)
    public :
        // Constructeur & Destructeur
        IA();
        ~IA();

        // M�thodes de la classe
        std::vector<std::vector<int>> CasesJouables(Damier* _pDamier);
        int Min(Damier* _etat_actuel, int _profondeur, char _couleur_tour);
        int Max(Damier* _etat_actuel, int _profondeur, char _couleur_tour);
        bool TourOrdinateur(Console* _pConsole, Damier* _pDamier, char couleur_tour);

        // Getters & Setters
        int getDifficulte() const { return m_difficulte; }
        void setDifficulte(int _difficulte);
};

#endif // IA_H_INCLUDED
