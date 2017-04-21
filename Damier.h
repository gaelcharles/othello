#ifndef DAMIER_H
#define DAMIER_H
#include "Console.h"

#include <vector>

class Damier
{
    public:

        Damier(int _taille, int _ligneAffichage, int _colonneAffichage); //constructeur surcharge
        Damier(Damier* copie); //constructeur par copie
        ~Damier(); //destructeur

        //getters
        int getTaille() const { return m_taille; }
        int getLigneAffichage() const { return m_ligneAffichage; }
        int getColonneAffichage() const { return m_colonneAffichage; }

        std::vector< std::vector<char> > getDamier() { return m_damier; }

        void Afficher(Console* _pConsole); //affiche le damier a partir du coin superieur gauche (point d'affichage)
        void CoupsPossibles(int ligne, int colonne, char couleur_tour); //cherche les coups possibles d'un joueur
        void ReinitialiserPossibilites(); //reinitialise le type des cases de type 'COUP_JOUABLE'
        void ChangerCouleurPions(int ligne, int colonne, char couleur_tour);
        int CompterPions(char _color); //retourne le nombre de pions de la couleur du joueur en parametre

    private:
        int m_taille; //nombre de lignes et de colonnes du damier
        //coordonnees auxquelles il faut afficher le damier
        int m_ligneAffichage;
        int m_colonneAffichage;

        std::vector< std::vector<char> > m_damier; //vecteur de caracteres contenant les cases du damier
};


#endif // DAMIER_H

