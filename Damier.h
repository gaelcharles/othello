/// \file Damier.h
/// \brief Contient la classe Damier ainsi que les prototypes de ses méthodes
/// \author Gaël, Camille, Tom
/// \version Version finale

#ifndef DAMIER_H
#define DAMIER_H
#include "Console.h"

#include <vector>
#include <string>

class Damier
{
    public:
        Damier(int _taille, int _ligneAffichage, int _colonneAffichage); //constructeur surcharge
        Damier(Damier* _pDamier); //constructeur par copie
        ~Damier(); //destructeur

        //Getters
        int getTaille() const { return m_taille; }
        int getLigneAffichage() const { return m_ligneAffichage; }
        int getColonneAffichage() const { return m_colonneAffichage; }
        std::vector< std::vector<char> > getDamier() { return m_damier; }
        std::string getNomCase(int _ligne, int _colonne);

        //setter
        void setCaseDamier(int _ligne, int _colonne, char _valeur);

        //Methodes de la classe
        void Afficher(Console* _pConsole); //affiche le damier à partir du coin superieur gauche (point d'affichage)
        void CoupsPossibles(int _ligne, int _colonne, char _couleur_tour); //cherche tous les coups possibles pour un joueur
        std::vector< std::vector<int> > CasesJouables(); //retourne une liste de tous les coups jouables
        void ChangerCouleurPions(int _ligne, int _colonne, char _couleur_tour); //retourne les pions selon le pion joue aux coordonnees en parametres
        void ReinitialiserPossibilites(); //reinitialise le type des cases de type COUP_JOUABLE
        int CompterPions(char _couleur); //retourne le nombre de pions de la couleur en parametre
        int Chargement(char& _couleur_tour); //charge une partie sauvegardée
        void AfficherPetitDamier(Console* _pConsole, const int _ligne_orig, const int _colonne_orig); // Affiche le petit damier simulé

    private:
        int m_taille; //nombre de lignes et de colonnes du damier

        //Coordonnees auxquelles il faut afficher le damier
        int m_ligneAffichage;
        int m_colonneAffichage;

        std::vector< std::vector<char> > m_damier; //cases du damier
};


#endif // DAMIER_H

