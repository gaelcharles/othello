//bibliotheques standards
#include <cstdlib>
#include <windows.h>

//bibliotheques personnelles
#include "IA.h"
#include "Damier.h"
#include "Affichage.h"
#include "Constantes.h"

//constantes pour l'algorithme Minimax
#define PROFONDEUR_ALGO 5
#define INF_MIN -1000
#define INF_MAX 1000

IA::IA()
    : m_difficulte(0)
{
    // constructeur par defaut
}

IA::~IA()
{
    // destructeur
}

// Setters
void IA::setDifficulte(int _difficulte)
{
    m_difficulte = _difficulte;
}

// Méthodes de la classe
std::vector<std::vector<int>> IA::CasesJouables(Damier* _pDamier)
/**********************************************************************************************
 * \brief ChoisirCaseHasard : choisit au hasard une case jouable                              *
 * \author Gaël                                                                               *
 *                                                                                            *
 * \param _pDamier : pointeur sur le damier                                                   *
 * \return Liste des coordonnees de toutes les cases jouables                                 *
 *                                                                                            *
 **********************************************************************************************/
{
    //vecteur contenant les coordonnées de chaque case jouable
    std::vector<std::vector<int> > liste;

    //vecteur tampon regroupant les coordonnées d'une case jouable
    std::vector<int> tampon;

    //pour tous les coups jouables
    for(int i(0) ; i<_pDamier->getTaille() ; i++)
    {
        for(int j(0) ; j<_pDamier->getTaille() ; j++)
        {
            if(_pDamier->getDamier()[i][j] == COUP_JOUABLE) //si c'est une case jouable
            {
                tampon.push_back(i);
                tampon.push_back(j);
                liste.push_back(tampon);
                tampon.clear();
            }
        }
    }

    return liste; //retourne la liste de coordonnees des cases jouables
}

int IA::Min(Damier* _etat_actuel, int _profondeur, char _couleur_tour)
{
    int valeur_min = INF_MAX; // 1000
    int valeur; //valeur intermediaire

    //lorsque l'algorithme atteint la profondeur finale
    if(_profondeur == 0)
    {
        int evaluation = _etat_actuel->CompterPions(_couleur_tour); //evalue la valeur du coup
        std::cout << evaluation;
        return evaluation;
    }

    //pour tous les coups jouables
    for(int i(0) ; i<_etat_actuel->getTaille() ; i++)
    {
        for(int j(0) ; j<_etat_actuel->getTaille() ; j++)
        {
            if(_etat_actuel->getDamier()[i][j] == COUP_JOUABLE) //si un coup est jouable sur cette case
            {
                //sauvegarde de l'etat actuel dans un vecteur tampon
                Damier* tampon = new Damier(_etat_actuel);

                _etat_actuel->ChangerCouleurPions(i, j, _couleur_tour); //change la couleur des pions en fonction du pion joue
                char couleur_tour_suivant = (_couleur_tour == NOIR) ? BLANC : NOIR; //définit la couleur des pions du tour suivant

                //appelle l'algorithme donnant la valeur maximale du prochain coup
                valeur = Max(_etat_actuel, _profondeur-1, couleur_tour_suivant);

                //test pour obtenir la valeur minimale de chaque coup
                if(valeur < valeur_min)
                    valeur_min = valeur; //nouvelle valeure minimale

                _etat_actuel = tampon; //annule le coup
            }
        }
    }

    return valeur_min;
}

int IA::Max(Damier* _etat_actuel, int _profondeur, char _couleur_tour)
{
    int valeur_max = INF_MIN; // -1000
    int valeur; //valeur intermediaire

    //lorsque l'algorithme atteint la profondeur finale
    if(_profondeur == 0)
        return _etat_actuel->CompterPions(_couleur_tour); //evalue la valeur du coup

    //pour tous les coups jouables
    for(int i(0) ; i<_etat_actuel->getTaille() ; i++)
    {
        for(int j(0) ; j<_etat_actuel->getTaille() ; j++)
        {
            if(_etat_actuel->getDamier()[i][j] == COUP_JOUABLE) //si un coup est jouable sur cette case
            {
                //sauvegarde de l'etat actuel dans un vecteur tampon
                Damier* tampon = new Damier(_etat_actuel);

                _etat_actuel->ChangerCouleurPions(i, j, _couleur_tour); //change la couleur des pions en fonction du pion joue
                char couleur_tour_suivant = (_couleur_tour == NOIR) ? BLANC : NOIR; //définit la couleur des pions du tour suivant

                //appelle l'algorithme donnant la valeur maximale du prochain coup
                valeur = Min(_etat_actuel, _profondeur-1, couleur_tour_suivant);

                //test pour obtenir la valeur minimale de chaque coup
                if(valeur > valeur_max)
                    valeur_max = valeur; //nouvelle valeure minimale

                _etat_actuel = tampon; //annule le coup
            }
        }
    }

    return valeur_max;
}

bool IA::TourOrdinateur(Console* _pConsole, Damier* _pDamier, char _couleur_tour)
/**********************************************************************************************
 * \brief TourOrdinateur : déroulement du tour de l'ordinateur en fonction de la difficulté   *
 * \author Gaël + Tom                                                                         *
 *                                                                                            *
 * \param _pConsole : pointeur sur la console                                                 *
 * \param _pDamier : pointeur sur le damier                                                   *
 * \return Booléen pour tester si la partie est finie                                         *
 *                                                                                            *
 **********************************************************************************************/
{
    std::vector<int> case_choisie; //case choisie par l'ordinateur

    _pDamier->Afficher(_pConsole);
    GfxInfos::AfficherTour(_pConsole, _couleur_tour);
    GfxInfos::AfficherScore(_pConsole, _pDamier);
    GfxDamier::AfficherContenu(_pConsole, _pDamier);

    // IA NIVEAU 1 : L'ORDINATEUR JOUE AU HASARD
    if(m_difficulte == 1)
    {
        //vecteur contenant les coordonnées de chaque case jouable
        std::vector<std::vector<int> > cases_jouables = CasesJouables(_pDamier);

        case_choisie = cases_jouables[rand() % (cases_jouables.size())]; //choisit une case jouable aléatoire parmi tous celle de la liste
        _pDamier->ChangerCouleurPions(case_choisie[0], case_choisie[1], _couleur_tour); //change la couleur des pions en fonction du coup joue
        _pDamier->ReinitialiserPossibilites(); //reinitialise le type des cases ou l'ordinateur pouvait jouer
    }
    // IA NIVEAU 2 : ALGORITHME MINIMAX
    else if(m_difficulte == 2)
    {
        int valeur_max = INF_MIN; // -1000
        int valeur; //valeur intermediaire

        Damier* etat_actuel = new Damier(_pDamier); //vecteur tampon de stockage du damier a un instant t

        int profondeur = PROFONDEUR_ALGO;
        bool coup_possible = false; //si l'ordinateur peut jouer a l'issu de l'algorithme

        for(int i(0) ; i<etat_actuel->getTaille() ; i++)
        {
            for(int j(0) ; j<etat_actuel->getTaille() ; j++)
            {
                if(etat_actuel->getDamier()[i][j] == COUP_JOUABLE) //si un coup est jouable sur cette case
                {
                    //sauvegarde de l'etat actuel dans un vecteur tampon
                    Damier* tampon = new Damier(etat_actuel);

                    etat_actuel->ChangerCouleurPions(i, j, _couleur_tour); //change la couleur des pions en fonction du pion joue
                    char couleur_tour_suivant = (_couleur_tour == NOIR) ? BLANC : NOIR; //définit la couleur des pions du tour suivant

                    //appelle l'algorithme donnant la valeur minimale du prochain coup
                    valeur = Min(etat_actuel, profondeur, couleur_tour_suivant);

                    if(valeur > valeur_max)
                    {
                        valeur_max = valeur; //nouvelle valeure maximale

                        //coordonnes de la meilleure case jouable
                        case_choisie.push_back(i);
                        case_choisie.push_back(j);

                        coup_possible = true;
                    }

                    etat_actuel = tampon; //efface le coup en changeant le damier precedent par celui avant le coup

                }
            }
        }

        if(coup_possible) //si l'ordinateur peut jouer un pion
        {
            //alors iljoue le meileur coup possible
            _pDamier->ChangerCouleurPions(case_choisie[0], case_choisie[1], _couleur_tour); //change la couleur des pions en fonction du coup joue
            _pDamier->ReinitialiserPossibilites(); //reinitialise le type des cases ou l'ordinateur pouvait jouer
        }

    }

    // Animation : affiche puis efface réflexion de l'ordinateur
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

    // Affichage du coup joué
    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()-3, _pDamier->getColonneAffichage()+2);
    GfxInfos::AfficherTour(_pConsole, _couleur_tour);
    GfxInfos::AfficherScore(_pConsole, _pDamier);
    GfxDamier::AfficherContenu(_pConsole, _pDamier);

    return false;
}
