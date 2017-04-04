#include "Damier.h"
#include "Pion.h"
#include "Constantes.h"
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

// Getters
std::vector<std::vector<Pion*> > Damier::getPlateau() const
{
    return m_plateau;
}

// Méthodes
/**********************************************************************************************
 * \brief Afficher : Affiche en console le plateau de jeu                                     *
 * \author Gaël                                                                               *
 *                                                                                            *
 **********************************************************************************************/
void Damier::Afficher()
{
    // Première ligne de bordures
    std::cout << BORDURE_ANGLE_HG << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    for(int i(0) ; i<m_taille-1 ; i++)
        std::cout << BORDURE_INTER3_BAS << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    std::cout << BORDURE_ANGLE_HD << std::endl;

    // Bordures des 64 cases
    for(int i(0) ; i<m_taille ; i++)
    {
        // Milieux de cases
        for(int j(0) ; j<m_taille ; j++)
            std::cout << BORDURE_BARRE_VERT << "   ";
        std::cout << BORDURE_BARRE_VERT << std::endl;

        // Barres horizontales
        if(i != m_taille-1)
        {
            std::cout << BORDURE_INTER3_DROITE << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
            for(int j(0) ; j<m_taille-1 ; j++)
                std::cout << BORDURE_INTER4 << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
            std::cout << BORDURE_INTER3_GAUCHE << std::endl;
        }
    }
    // Dernière ligne de bordures
    std::cout << BORDURE_ANGLE_BG << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    for(int i(0) ; i<m_taille-1 ; i++)
        std::cout << BORDURE_INTER3_HAUT << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    std::cout << BORDURE_ANGLE_BD << std::endl;
}
