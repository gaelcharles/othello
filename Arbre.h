#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include "Damier.h"
#include <allegro.h>
#include <winalleg.h>
#include <vector>

class Transition
/**********************************************************************************************
 * \class Transition                                                                          *
 * \brief Une transition est une arête de l'arbre de recherche. Elle relie deux états (deux   *
 *        noeuds) entre eux.                                                                  *
 * \author Gaël                                                                               *
 *                                                                                            *
 **********************************************************************************************/
{
    private :
        COORD m_pos; // Coordonnées de la case qui mène à cette transition
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
 * \brief Un état est un noeud de l'arbre de recherche. C'est la situation du plateau de jeu  *
 *        à un moment donné.                                                                  *
 * \author Gaël                                                                               *
 *                                                                                            *
 **********************************************************************************************/
{
    private :
        Damier* m_situation_damier; // Situation du damier dans cet état
        std::vector<Transition*> m_aretes; // Vecteur d'arêtes reliées à ce noeud : correspond à la liste des transitions possibles à partir de cet état
        unsigned int m_degre; // Degré du noeud : nombre de transitions possibles (nombre de coups jouables) à partir de cet état
        char m_couleur_tour; // La couleur du joueur qui prend son tour lors de cet état
    public :
        // C & D
        Etat(Damier* _pDamierPrecedent, int _ligne, int _colonne, char _couleur_precedente);
        ~Etat();

        // Getters
        unsigned int getDegre() const { return m_degre; }
        Damier* getSituationDamier() const { return m_situation_damier; }
        char getTour() const { return m_couleur_tour; }
        int getScore(char _couleur) const { return m_situation_damier->CompterPions(_couleur); }

        // Méthodes
        void AfficherArbreRecherche(Console* _pConsole);
};

#endif // ARBRE_H_INCLUDED
