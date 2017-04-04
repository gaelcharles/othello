#include "Pion.h"

// Constructeurs
// Surchargé
Pion::Pion(bool _couleur, int _x, int _y) :
    m_couleur(_couleur)
{
    m_pos.x = _x;
    m_pos.y = _y;
}

// Par défaut
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
