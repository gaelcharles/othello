#include "Joueur.h"

// Constructeur
Joueur::Joueur(bool _couleur) :
    m_couleur(_couleur), m_nombre_pions(0), m_IA(false) // Valeurs par défaut
{
}

// Destructeur
Joueur::~Joueur()
{
}
