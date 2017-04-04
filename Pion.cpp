#include "Pion.h"

// Constructeurs
Pion::Pion(bool _couleur, Coords _coords) :
    m_couleur(_couleur), m_pos(_coords)
{
}

Pion::Pion() :
    m_couleur(false)
{
    m_pos.x = NONE;
    m_pos.y = NONE;
}

// Destructeur
Pion::~Pion()
{
}
