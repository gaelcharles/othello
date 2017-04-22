#ifndef DAMIER_H
#define DAMIER_H
#include "Console.h"

#include <vector>
#include <string>

class Damier
{
    public:

        Damier(int _taille, int _ligneAffichage, int _colonneAffichage);
        Damier(Damier* _pCopie);
        ~Damier();

        //Getters
        int getTaille() const { return m_taille; }
        int getLigneAffichage() const { return m_ligneAffichage; }
        int getColonneAffichage() const { return m_colonneAffichage; }
        std::vector< std::vector<char> > getDamier() { return m_damier; }
        std::string getNomCase(int _ligne, int _colonne);

        //Methodes de la classe
        void Afficher(Console* _pConsole); //affiche le damier à partir du coin superieur gauche (point d'affichage)
        void CoupsPossibles(int _ligne, int _colonne, char _couleur_tour); //cherche tous les coups possibles pour un joueur
        std::vector< std::vector<int> > CasesJouables(); //retourne une liste de tous les coups jouables
        void ChangerCouleurPions(int _ligne, int _colonne, char _couleur_tour); //retourne les pions selon le pion joue aux coordonnees en parametres
        void ReinitialiserPossibilites(); //retourne le nombre de pions de la couleur du joueur en parametre
        int CompterPions(char _couleur); //retourne le nombre de pions de la couleur en parametre
        int Chargement(char& _couleur_tour); //charge une partie sauvegardée
        Damier* SimulerCoup(int _ligne, int _colonne, char _couleur);
        void AfficherArbreRecherche(Console* _pConsole, int _ligne, int _colonne);

    private:
        int m_taille; //nombre de lignes et de colonnes du damier

        //Coordonnees auxquelles il faut afficher le damier
        int m_ligneAffichage;
        int m_colonneAffichage;

        std::vector< std::vector<char> > m_damier; //cases du damier
};


#endif // DAMIER_H

