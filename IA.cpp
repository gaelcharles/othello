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

std::vector< std::vector<int> > IA::CasesJouables(Damier* _pDamier)
/**********************************************************************************************
 * \brief CasesJouables : retourne la liste des coordonnees de toutes les cases jouables      *
 * \author Gaël + Tom                                                                         *
 *                                                                                            *
 * \param _pDamier : pointeur sur le damier                                                   *
 * \return Liste des coordonnees de toutes les cases jouables                                 *
 *                                                                                            *
 **********************************************************************************************/
{
    // Ensemble des coordonnées donnant un coup jouable
    std::vector<std::vector<int> > cases_jouables;

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
                cases_jouables.push_back(tampon);
                tampon.clear();
            }
        }
    }

    return cases_jouables; //retourne la liste des coordonnees de toutes les cases jouables
}

bool IA::TourOrdinateur(Console* _pConsole, Damier* _pDamier, char _couleur_tour)
{
    std::vector<int> case_choisie; //case choisie par l'ordinateur

    //Affichage des differents modules
    _pDamier->Afficher(_pConsole);
    GfxInfos::AfficherTour(_pConsole, _couleur_tour);
    GfxInfos::AfficherScore(_pConsole, _pDamier);
    GfxDamier::AfficherContenu(_pConsole, _pDamier);

    /// IA NIVEAU 1 : JOUE AU HASARD
    if(m_difficulte == 1)
    {
        //vecteur contenant l'ensemble de chaque case jouable
        std::vector< std::vector<int> > cases_jouables = CasesJouables(_pDamier);

        case_choisie = cases_jouables[rand() % (cases_jouables.size()) ]; //choisit une case aleatoire parmi celles de la liste
        _pDamier->ChangerCouleurPions(case_choisie[0], case_choisie[1], _couleur_tour); //retourne les pions selon le pion joue aux coordonnees en parametres
        _pDamier->ReinitialiserPossibilites(); //retourne le nombre de pions de la couleur du joueur en parametre
    }

    //Animation : reflexion de l'ordinateur
    _pConsole->gotoLigCol(12, 45);
    std::cout << "L'IA reflechit";
    for(int i(0) ; i<3 ; i++)
    {
        Sleep(200);
        std::cout << '.';
    }
    _pConsole->gotoLigCol(12, 45);
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
    std::cout << "                 ";

    //Affiche le coup joue
    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()-3, _pDamier->getColonneAffichage()+2);
    GfxInfos::AfficherTour(_pConsole, _couleur_tour);
    GfxInfos::AfficherScore(_pConsole, _pDamier);
    GfxDamier::AfficherContenu(_pConsole, _pDamier);

    return false;
}
