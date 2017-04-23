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
    public :
        // C & D
        Transition(int _posx, int _posy);
        ~Transition();

        // Getters
        COORD getPos() const { return m_pos; }
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
        unsigned int getDegre() const { return m_degre; }
        Damier* getSituationDamier() const { return m_situation_damier; }
        char getTour() const { return m_couleur_tour; }
        int getScore(char _couleur) const { return m_situation_damier->CompterPions(_couleur); }

        // M�thodes
        void AfficherArbreRecherche(Console* _pConsole);
};

#endif // ARBRE_H_INCLUDED
