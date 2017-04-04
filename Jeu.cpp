#include "Jeu.h"

// Constructeur
Jeu::Jeu() :
    m_J1(NOIR), m_J2(BLANC), m_tour_id(0)
{

}

// Destructeur
Jeu::~Jeu()
{
}

// Getters
Damier Jeu::getDamier() const
{
    return m_damier;
}
