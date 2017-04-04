#include "Damier.h"
#include "Pion.h"
#include <vector>
#include <iostream>

// Constructeur
Damier::Damier() :
    m_taille(8)
{
    std::vector<Pion*> vecteur_tampon;

    // Remplissage du plateau par des pointeurs vides
    for(int i(0) ; i<m_taille ; i++)
    {
        for(int j(0) ; j<m_taille ; j++)
        {
            vecteur_tampon.push_back(NULL);
        }

        m_plateau.push_back(vecteur_tampon);
        vecteur_tampon.clear();
    }

    // Remplissage des quatre cases du milieu du plateau
    m_plateau[3][3] = new Pion(BLANC, 3, 3);
    m_plateau[4][4] = new Pion(BLANC, 4, 4);
    m_plateau[3][4] = new Pion(NOIR,  3, 4);
    m_plateau[4][3] = new Pion(NOIR,  4, 3);
}

// Destructeur
Damier::~Damier()
{
    for(int i(0) ; i<m_taille ; i++)
    {
        for(int j(0) ; j<m_taille ; j++)
        {
            if(m_plateau[i][j])
                delete m_plateau[i][j];
        }
    }
}
