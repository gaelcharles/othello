#include "Arbre.h"
#include "Constantes.h"

// Constructeur
Transition::Transition(int _posx, int _posy)
{
    m_pos.X = _posx;
    m_pos.Y = _posy;
}

// Destructeur
Transition::~Transition()
{
}

// Constructeur
Etat::Etat(Damier* _pDamierPrecedent, int _ligne, int _colonne, char _couleur_precedente)
{
    // Liste des coups jouables
    std::vector< std::vector<int> > coups_jouables;

    // Le damier de l'état est au départ une copie de celui de l'état précédent
    m_situation_damier = new Damier(_pDamierPrecedent); // Constructeur par copie

    // La couleur de l'état suivant
    m_couleur_tour = (_couleur_precedente == NOIR) ? BLANC : NOIR;

    // Changement de couleur de pions
    m_situation_damier->ChangerCouleurPions(_ligne, _colonne, _couleur_precedente);

    // On enlève les cases indiquant les coups jouables de l'ancien état
    m_situation_damier->ReinitialiserPossibilites();

    // On met à jour les cases indiquant les nouveaux coups jouables pour la couleur adverse
    for(int i(0) ; i<m_situation_damier->getTaille() ; i++)
    {
        for(int j(0) ; j<m_situation_damier->getTaille() ; j++)
        {
            if(m_situation_damier->getDamier()[i][j] == m_couleur_tour)
                m_situation_damier->CoupsPossibles(i, j, m_couleur_tour);
        }
    }

    // Récupère la liste des coups jouables (transitions) à partir de l'état actuel
    coups_jouables = m_situation_damier->CasesJouables();

    // Degré du noeud (état) actuel : nombre de transitions (arêtes) à partir de cet état
    m_degre = coups_jouables.size();

    // Initialisation de chaque transition à partir de cet état
    for(unsigned int i(0) ; i<m_degre ; i++)
        m_aretes.push_back(new Transition(coups_jouables[i][0], coups_jouables[i][1]));
}

// Destructeur
Etat::~Etat()
{
    delete m_situation_damier;
}

void Etat::AfficherArbreRecherche(Console* _pConsole)
{
    int ligne = 0, colonne = 0;
    Etat* pEtatTemporaire = NULL;

    _pConsole->gotoLigCol(1, 50);
    std::cout << "Simulation - Tour : " << m_couleur_tour << " - Score : " << getScore(NOIR) << "/" << getScore(BLANC) << std::endl;
    for(unsigned int i(0) ; i<m_aretes.size() ; i++)
    {
        ligne = m_aretes[i]->getPos().X;
        colonne = m_aretes[i]->getPos().Y;

        pEtatTemporaire = new Etat(m_situation_damier, ligne, colonne, m_couleur_tour);

        _pConsole->gotoLigCol(5+i, 50);
        _pConsole->setColor(COULEUR_BLANC, COULEUR_MARRON);
        std::cout << CARAC_CARRE << " [" << pEtatTemporaire->getSituationDamier()->getNomCase(ligne, colonne) << "], Score ";
        _pConsole->setColor(COULEUR_NOIR, COULEUR_MARRON);
        std::cout << pEtatTemporaire->getSituationDamier()->CompterPions(NOIR);
        _pConsole->setColor(COULEUR_BLANC, COULEUR_MARRON);
        std::cout << " - " << pEtatTemporaire->getSituationDamier()->CompterPions(BLANC);

        delete pEtatTemporaire;
        pEtatTemporaire = NULL;
    }
}

