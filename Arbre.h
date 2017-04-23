#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include "Damier.h"
#include <allegro.h>
#include <winalleg.h>
#include <vector>

class Transition
/**********************************************************************************************
 * \class Transition                                                                          *
 * \brief Une transition est une ar�te de l'arbre de recherche. Elle relie deux �tats (deux   *
 *        noeuds) entre eux.                                                                  *
 * \author Ga�l                                                                               *
 *                                                                                            *
 **********************************************************************************************/
{
    private :
        COORD m_pos; // Coordonn�es de la case qui m�ne � cette transition
        bool m_selectionne; // Bool�en indiquant si le curseur s�lectionne cette transition ou pas
    public :
        // C & D
        Transition(int _posx, int _posy);
        ~Transition();

        // Getters & Setters
        COORD getPos() const { return m_pos; }
        bool estSelectionne() const { return m_selectionne; }
        void selectionner(bool _selection) { m_selectionne = _selection; }
};

class Etat
/**********************************************************************************************
 * \class Etat                                                                                *
 * \brief Un �tat est un noeud de l'arbre de recherche. C'est la situation du plateau de jeu  *
 *        � un moment donn�.                                                                  *
 * \author Ga�l                                                                               *
 *                                                                                            *
 **********************************************************************************************/
{
    private :
        Damier* m_situation_damier; // Situation du damier dans cet �tat
        std::vector<Transition*> m_aretes; // Vecteur d'ar�tes reli�es � ce noeud : correspond � la liste des transitions possibles � partir de cet �tat
        unsigned int m_degre; // Degr� du noeud : nombre de transitions possibles (nombre de coups jouables) � partir de cet �tat
        char m_couleur_tour; // La couleur du joueur qui prend son tour lors de cet �tat
    public :
        // C & D
        Etat(Damier* _pDamierPrecedent, int _ligne, int _colonne, char _couleur_precedente);
        ~Etat();

        // Getters
        Damier* getSituationDamier() const { return m_situation_damier; }
        std::vector<Transition*> getAretes() const { return m_aretes; }
        unsigned int getDegre() const { return m_degre; }
        char getTour() const { return m_couleur_tour; }

        int getScore(char _couleur) const { return m_situation_damier->CompterPions(_couleur); }
        int getIndiceTransitionSelectionnee() const;

        // M�thodes
        void AfficherEtat(Console* _pConsole, int _decalage_colonne);
        void DesafficherEtat(Console* _pConsole, int _decalage_colonne);
};

#endif // ARBRE_H_INCLUDED
