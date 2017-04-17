#ifndef DAMIER_H
#define DAMIER_H
#include "Console.h"

#include <vector>

class Damier
{
    public:

        Damier(int _taille, int _ligneAffichage, int _colonneAffichage);
        ~Damier();

        //getters
        int getTaille() const { return m_taille; }
        int getLigneAffichage() const { return m_ligneAffichage; }
        int getColonneAffichage() const { return m_colonneAffichage; }

        std::vector< std::vector<char> > getDamier() { return m_damier; }

        //affiche le damier à partir du coin supérieur gauche (point d'affichage)
        void afficher(Console* _pConsole);
        void coups(char tour, char adv, int ligne, int colonne);
        void changement(char tour, char adv, int ligne, int colonne);
        void reset();
        int comptagePions(char _color);

    private:
        //nombre de lignes et de colonnes du damier
        int m_taille;
        //coordonnées auxquelles il faut afficher le damier
        int m_ligneAffichage;
        int m_colonneAffichage;

        std::vector< std::vector<char> > m_damier; //cases du damier
};


#endif // DAMIER_H

