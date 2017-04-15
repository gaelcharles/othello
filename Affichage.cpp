#include "Affichage.h"
#include "Constantes.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <MMsystem.h>

void GfxDamier::afficher(Console* _pConsole, Damier* _pDamier)
/**********************************************************************************************
 * \brief Afficher : Affiche en console le plateau de jeu                                     *
 * \author Gaël                                                                               *
 *                                                                                            *
 * \param _pConsole : Pointeur sur l'instance de console                                      *
 * \param _pDamier : Pointeur sur le damier à afficher                                        *
 * \return (void)                                                                             *
 *                                                                                            *
 **********************************************************************************************/
{
    // Variables
    const int origineLig = _pDamier->getLigneAffichage();
    const int origineCol = _pDamier->getColonneAffichage();

    // Positionnement initial
    _pConsole->gotoLigCol(origineLig, origineCol);

    // Première ligne de bordures
    std::cout << BORDURE_ANGLE_HG << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    for(int i(0) ; i<_pDamier->getTaille()-1 ; i++)
        std::cout << BORDURE_INTER3_BAS << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    std::cout << BORDURE_ANGLE_HD;
    _pConsole->gotoLigCol(origineLig+1, origineCol); // Retour à la ligne

    // Bordures des 64 cases
    for(int i(0) ; i<=_pDamier->getTaille() ; i++)
    {
        // Milieux de cases
        for(int j(0) ; j<_pDamier->getTaille() ; j++)
            std::cout << BORDURE_BARRE_VERT << "   ";
        std::cout << BORDURE_BARRE_VERT;
        _pConsole->gotoLigCol(origineLig+2*i+1, origineCol); // Retour à la ligne

        // Barres horizontales
        if(i != _pDamier->getTaille())
        {
            _pConsole->gotoLigCol(origineLig+2*i+2, origineCol); // Retour à la ligne
            std::cout << BORDURE_INTER3_DROITE << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
            for(int j(0) ; j<_pDamier->getTaille()-1 ; j++)
                std::cout << BORDURE_INTER4 << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
            std::cout << BORDURE_INTER3_GAUCHE;
            _pConsole->gotoLigCol(origineLig+2*i+1, origineCol); // Retour à la ligne
        }
    }
    // Dernière ligne de bordures
    _pConsole->gotoLigCol(origineLig+2*_pDamier->getTaille(), origineCol); // Retour à la ligne
    std::cout << BORDURE_ANGLE_BG << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    for(int i(0) ; i<_pDamier->getTaille()-1 ; i++)
        std::cout << BORDURE_INTER3_HAUT << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    std::cout << BORDURE_ANGLE_BD;
}

void GfxDamier::afficherContenu(Console* _pConsole, Damier* _pDamier)
/**********************************************************************************************
 * \brief afficherContenu : Affiche le contenu des cases du damier                            *
 * \author Camille, Gaël                                                                      *
 *                                                                                            *
 * \param _pConsole : Pointeur sur l'instance de console                                      *
 * \param _pDamier : Pointeur sur le damier à afficher                                        *
 * \return (void)                                                                             *
 *                                                                                            *
 **********************************************************************************************/
{
    // Variables
    const int origineLig = _pDamier->getLigneAffichage()+1;
    const int origineCol = _pDamier->getColonneAffichage()+2;

    for(int i(0) ; i<_pDamier->getTaille() ; i++)
    {
        for(int j(0) ; j<_pDamier->getTaille() ; j++)
        {
            // Déplacement à la case associée
            _pConsole->gotoLigCol(2*i+origineLig, 4*j+origineCol);

            // Affichage du contenu
            switch(_pDamier->getDamier()[i][j])
            {
            case 'B':
                _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
                std::cout << 'O';
                break;

            case 'N':
                _pConsole->setColor(COULEUR_NOIR, COULEUR_VERT);
                std::cout << 'O';
                break;

            case '.':
                _pConsole->setColor(COULEUR_MARRON, COULEUR_VERT);
                std::cout << '.';
                break;

            default :
                {
                    std::cout << ' ';
                    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT); // Défaut
                }
            }
        }
    }
}

void GfxInfos::afficherTour(Console* _pConsole, char tour)
{
    _pConsole->gotoLigCol(2, 6);
    std::cout << "C\'est au tour des";

    _pConsole->gotoLigCol(3, 6);
    if(tour == 'N')
    {
        _pConsole->setColor(COULEUR_NOIR, COULEUR_VERT);
        std::cout << CARAC_CARRE << " noirs " << CARAC_CARRE;
    }
    else
    {
        _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
        std::cout << CARAC_CARRE << " blancs " << CARAC_CARRE;
    }
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT); // Par défaut
}

void GfxInfos::afficherScore(Console* _pConsole, Damier* _pDamier)
{
    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()+20, _pDamier->getColonneAffichage()+2);
    _pConsole->setColor(COULEUR_NOIR, COULEUR_VERT);
    std::cout << CARAC_CARRE << ' ' << _pDamier->comptagePions('N') << " pions noirs";

    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()+21, _pDamier->getColonneAffichage()+2);
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
    std::cout << CARAC_CARRE << ' ' << _pDamier->comptagePions('B') << " pions blancs";
}

void GfxFin::afficherFin(Damier* _pDamier)
{
    int n = _pDamier->comptagePions('N');
    int b = _pDamier->comptagePions('B');

    std::cout << "Partie terminee " << std::endl;

    if(n > b)
    {
        std::cout << "Les pions noirs gagnent !" << std::endl;
        system("pause");
    }
    else if(n < b)
    {
        std::cout << "Les pions blancs gagnent !" << std::endl;
        system("pause");
    }
    else
    {
        std::cout << "Match nul !" << std::endl;
        system("pause");
    }


}
