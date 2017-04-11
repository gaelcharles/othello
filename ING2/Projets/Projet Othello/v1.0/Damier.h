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
        int getTaille() { return m_taille; }

        int getLigneAffichage() { return m_ligneAffichage; }
        int getColonneAffichage() { return m_colonneAffichage; }

        std::vector< std::vector<char> > getDamier() {return m_damier; }

        //affiche le damier � partir du coin sup�rieur gauche (point d'affichage)
        void afficher(Console* _pConsole);
        void coups(char tour, char adv, int ligne, int colonne);
        void changement(char tour, char adv, int ligne, int colonne);
        void reset();
        int comptageNoir();
        int comptageBlanc();

    protected:
        //nombre de lignes et de colonnes du damier
        int m_taille;
        //coordonn�es auxquelles il faut afficher le damier
        int m_ligneAffichage;
        int m_colonneAffichage;

        std::vector< std::vector<char> > m_damier; //cases du damier

    private:

};


#endif // DAMIER_H
