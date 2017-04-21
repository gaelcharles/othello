#include "IA.h"
#include "Affichage.h"
#include "Constantes.h"
#include <cstdlib>
#include <allegro.h>
#include <winalleg.h>

// Constructeur
IA::IA() :
    m_difficulte(0)
{
}

// Destructeur
IA::~IA()
{
}

// Setters
void IA::setDifficulte(int _difficulte)
{
    m_difficulte = _difficulte;
}

std::vector<int> IA::ChooseRandomCell(Damier* _pDamier)
/**********************************************************************************************
 * \brief ChooseRandomCell : choisit au hasard une case où un coup est jouable                *
 * \author Gaël                                                                               *
 *                                                                                            *
 * \param _pDamier : pointeur sur le damier                                                   *
 * \return Un vecteur de 2 int représentant les coordonnées i,j de la case choisie            *
 *                                                                                            *
 **********************************************************************************************/
{
    // Ensemble des coordonnées donnant un coup jouable
    std::vector<std::vector<int> > liste;

    // Vecteur tampon regroupant les coordonnées d'un coup jouable donné
    std::vector<int> tampon;

    for(int i(0) ; i<_pDamier->getTaille() ; i++)
    {
        for(int j(0) ; j<_pDamier->getTaille() ; j++)
        {
            if(_pDamier->getDamier()[i][j] == COUP_JOUABLE) // Si un coup est jouable sur cette case
            {
                tampon.push_back(i);
                tampon.push_back(j);
                liste.push_back(tampon);
                tampon.clear();
            }
        }
    }

    return liste[rand() % (liste.size())]; // Un coup jouable aléatoire parmi tous ceux de la liste
}

bool IA::deroulement(Console* _pConsole, Damier* _pDamier, char _tour, char _adv)
{
    std::vector<int> cell;

    _pDamier->afficher(_pConsole);
    GfxInfos::afficherTour(_pConsole, _tour);
    GfxInfos::afficherScore(_pConsole, _pDamier);
    GfxDamier::afficherContenu(_pConsole, _pDamier);

    /// IA NIVEAU 1 : JOUE AU HASARD
    if(m_difficulte == 1)
    {
        cell = ChooseRandomCell(_pDamier);
        _pDamier->changement(_tour, _adv, cell[0], cell[1]);
        _pDamier->reset();
    }

    // Simulation de rélfexion
    _pConsole->gotoLigCol(12, 45);
    std::cout << "L'IA reflechit";
    for(int i(0) ; i<3 ; i++)
    {
        Sleep(200);
        std::cout << '.';
    }

    // Le pion clignote juste avant d'être joué par l'IA
    for(int i(0) ; i<4 ; i++)
    {
        _pConsole->gotoLigCol(2*cell[0]+_pDamier->getLigneAffichage()+1, 4*cell[1]+_pDamier->getColonneAffichage()+1);
        _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
        (i%2 == 0) ? std::cout << " O " : std::cout << "   ";
        _pConsole->gotoLigCol(12, 62);
        Sleep(250);
    }

    // Effacement de la réflexion de l'IA
    _pConsole->gotoLigCol(12, 45);
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
    std::cout << "                 ";

    // Affichage du coup joué
    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()-3, _pDamier->getColonneAffichage()+2);
    GfxInfos::afficherTour(_pConsole, _tour);
    GfxInfos::afficherScore(_pConsole, _pDamier);
    GfxDamier::afficherContenu(_pConsole, _pDamier);

    return false;
}
