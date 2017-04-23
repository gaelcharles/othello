#include "IA.h"
#include "Affichage.h"
#include "Constantes.h"
#include <cstdlib>
#include <allegro.h>
#include <winalleg.h>

//Valeurs pour l'algorithme Minimax
#define PROFONDEUR 3
#define INF_MAX 100
#define INF_MIN -100

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

int IA::Min(Damier* _pEtat, int _profondeur)
{
    if(_profondeur == 0)
    {
        //Evaluation du poids du plateau de jeu
        int valeur = _pEtat->CompterPions(BLANC) - _pEtat->CompterPions(NOIR);
        return valeur; //pions blancs - pions noirs
    }

    int meilleur_score = INF_MAX; //valeur initiale du meilleur score : 100
    int score; //valeur intermediaire pour determiner le meilleur score
    Damier* pCopie = NULL; //copie du damier

    //Cherche tous les coups possibles pour les pions noirs
    for(int i(0) ; i<_pEtat->getTaille() ; i++)
    {
        for(int j(0) ; j<_pEtat->getTaille() ; j++)
        {
            if(_pEtat->getDamier()[i][j] == NOIR) //pour chaque case avec un pion noir on regarde les coups possibles
                _pEtat->CoupsPossibles(i, j, NOIR); //transforme la valeur des cases jouables
        }
    }

    //Pour tous les coups jouables sur le plateau
    for(int i(0) ; i<_pEtat->getTaille() ; i++)
    {
        for(int j(0) ; j<_pEtat->getTaille() ; j++)
        {
            if(_pEtat->getDamier()[i][j] == COUP_JOUABLE) //si un coup est jouable sur cette case
            {
                //Simule le coup
                pCopie = new Damier(_pEtat);
                pCopie->ChangerCouleurPions(i, j, NOIR);

                score = Max(pCopie, _profondeur-1);

                //Définit le meilleur score minimal ou un score deja egal au meilleur score
                if(score < meilleur_score || (score==meilleur_score && rand()%2 == 0)) //si le score est plus petit que le meilleur score minimal
                {
                    meilleur_score = score; //alors on met a jour le meilleur score

                }


                //Annuler le coup
                pCopie = _pEtat; //la copie du damier prend la valeur du damier avant le coup joue
                _pEtat->setCaseDamier(i, j, ' ');  //on supprime la possibilite de jouer a nouveau sur la meme case
            }
        }
    }

    return meilleur_score;
}

int IA::Max(Damier* _pEtat, int _profondeur)
{
    if(_profondeur == 0)
    {
        //Evaluation du poids du plateau de jeu
        int valeur = _pEtat->CompterPions(BLANC) - _pEtat->CompterPions(NOIR);
        //std::cout << "Min : " << valeur << std::endl;
        return valeur; //pions blancs - pions noirs
    }

    int meilleur_score = INF_MIN; //valeur initiale du meilleur score : -100
    int score; //valeur intermediaire pour determiner le meilleur score
    Damier* pCopie = NULL; //copie du damier

    //Cherche tous les coups possibles pour les pions blancs
    for(int i(0) ; i<_pEtat->getTaille() ; i++)
    {
        for(int j(0) ; j<_pEtat->getTaille() ; j++)
        {
            if(_pEtat->getDamier()[i][j] == BLANC) //pour chaque case avec un pion blanc on regarde les coups possibles
                _pEtat->CoupsPossibles(i, j, BLANC); //transforme la valeur des cases jouables
        }
    }

    //Pour tous les coups jouables sur le plateau
    for(int i(0) ; i<_pEtat->getTaille() ; i++)
    {
        for(int j(0) ; j<_pEtat->getTaille() ; j++)
        {
            if(_pEtat->getDamier()[i][j] == COUP_JOUABLE) //si un coup est jouable sur cette case
            {
                //Simuler le coup
                pCopie = new Damier(_pEtat);
                pCopie->ChangerCouleurPions(i, j, BLANC);

                score = Min(pCopie, _profondeur-1);

                //Définit le meilleur score maximal ou un score deja egal au meilleur score
                if(score > meilleur_score || (score==meilleur_score && rand()%2 == 0)) //si le score est plus grand que le meilleur score maximal
                    meilleur_score = score; //alors on met a jour le meilleur score

                //Annuler le coup
                pCopie = _pEtat; //la copie du damier prend la valeur du damier avant le coup joue
                _pEtat->setCaseDamier(i, j, ' ');  //on supprime la possibilite de jouer a nouveau sur la meme case
            }
        }
    }

    return meilleur_score;
}

bool IA::TourOrdinateur(Console* _pConsole, Damier* _pDamier, char _couleur_tour)
{
    std::vector<int> case_choisie; //case choisie par l'ordinateur

    //Affichage des differents modules
    _pDamier->Afficher(_pConsole);
    GfxInfos::AfficherTour(_pConsole, _couleur_tour);
    GfxInfos::AfficherScore(_pConsole, _pDamier);
    GfxDamier::AfficherContenu(_pConsole, _pDamier);

    //Animation : reflexion de l'ordinateur
    _pConsole->gotoLigCol(12, 45);
    std::cout << "L'IA reflechit";
    for(int i(0) ; i<3 ; i++)
    {
        Sleep(200);
        std::cout << '.';
    }

    if(m_difficulte == 1) // IA NIVEAU 1 : JOUE AU HASARD
    {
        //vecteur contenant l'ensemble de chaque case jouable
        std::vector< std::vector<int> > cases_jouables = _pDamier->CasesJouables();

        case_choisie = cases_jouables[rand() % (cases_jouables.size()) ]; //choisit une case aleatoire parmi celles de la liste
        _pDamier->ChangerCouleurPions(case_choisie[0], case_choisie[1], _couleur_tour); //retourne les pions selon le pion joue aux coordonnees en parametres
        _pDamier->ReinitialiserPossibilites();
    }
    else if(m_difficulte == 2) // IA NIVEAU 2 : ALGO MINIMAX
    {
        int profondeur = PROFONDEUR; //profondeur de recherche de coups de l'algorithme
        int meilleur_score = INF_MIN; //valeur initiale du meilleur score : -100
        int meilleure_ligne, meilleure_colonne;
        int score; //valeur intermediaire pour determiner le meilleur score

        Damier* pCopie = NULL; //copie du damier

        //Cherche tous les coups possibles pour les pions blancs
        for(int i(0) ; i<_pDamier->getTaille() ; i++)
        {
            for(int j(0) ; j<_pDamier->getTaille() ; j++)
            {
                if(_pDamier->getDamier()[i][j] == BLANC) //pour chaque case avec un pion blanc on regarde les coups possibles
                    _pDamier->CoupsPossibles(i, j, BLANC); //transforme la valeur des cases jouables
            }
        }

        //Pour tous les coups jouables sur le plateau
        for(int i(0) ; i<_pDamier->getTaille() ; i++)
        {
            for(int j(0) ; j<_pDamier->getTaille() ; j++)
            {
                if(_pDamier->getDamier()[i][j] == COUP_JOUABLE) //si un coup est jouable sur cette case
                {
                    //Simuler le coup
                    pCopie = new Damier(_pDamier);
                    pCopie->ChangerCouleurPions(i, j, BLANC);

                    score = Min(pCopie, profondeur);

                    //Définit le meilleur score maximal ou un score deja egal au meilleur score
                    if(score > meilleur_score || (score==meilleur_score && rand()%2 == 0)) //si le score est plus grand que le meilleur score maximal
                    {
                        meilleur_score = score; //alors on met a jour le meilleur score
                        meilleure_ligne = i, meilleure_colonne = j; //nouvelles coordonnees du meilleur coup
                    }

                    //Annuler le coup
                    pCopie = _pDamier; //la copie du damier prend la valeur du damier avant le coup joue
                    _pDamier->setCaseDamier(i, j, ' ');  //on supprime la possibilite de jouer a nouveau sur la meme case
                }
            }
        }

        case_choisie.push_back(meilleure_ligne);
        case_choisie.push_back(meilleure_colonne);

        _pDamier->ChangerCouleurPions(meilleure_ligne, meilleure_colonne, BLANC);
        _pDamier->ReinitialiserPossibilites();

    }

    // Le pion clignote juste avant d'être joué par l'IA
    for(int i(0) ; i<4 ; i++)
    {
        _pConsole->gotoLigCol(2*case_choisie[0]+_pDamier->getLigneAffichage()+1, 4*case_choisie[1]+_pDamier->getColonneAffichage()+1);
        _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
        (i%2 == 0) ? std::cout << " O " : std::cout << "   ";
        _pConsole->gotoLigCol(12, 62);
        Sleep(250);
    }

    //Animation : efface la reflexion de l'ordinateur
    _pConsole->gotoLigCol(12, 45);
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
    _pConsole->espacer(17);

    //Affiche le coup joue
    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()-3, _pDamier->getColonneAffichage()+2);
    GfxInfos::AfficherTour(_pConsole, _couleur_tour);
    GfxInfos::AfficherScore(_pConsole, _pDamier);
    GfxDamier::AfficherContenu(_pConsole, _pDamier);

    return false;
}
