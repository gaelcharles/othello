#include "Arbre.h"
#include "Constantes.h"

// Constructeur
Transition::Transition(int _posx, int _posy)
{
    m_pos.X = _posx;
    m_pos.Y = _posy;
    m_selectionne = false;
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

    for(unsigned int i(0) ; i<m_degre ; i++)
        delete m_aretes[i];
}

int Etat::getIndiceTransitionSelectionnee() const
{
    int i(0);
    std::vector<Transition*>::const_iterator it;
    for(it = m_aretes.begin() ; it != m_aretes.end() ; it++, i++)
    {
        if((*it)->estSelectionne())
            break;
    }

    return it != m_aretes.end() ? i : -1;
}

void Etat::AfficherEtat(Console* _pConsole, int _decalage_colonne)
{
    const int largeur_graphique_etat = 22,
              origine_arbre_ligne = 11,
              origine_arbre_colonne = 45;
    int ligne = 0, colonne = 0;
    Etat* pEtatTemporaire = NULL;
    const e_color fond = COULEUR_OR;

    _pConsole->gotoLigCol(origine_arbre_ligne, origine_arbre_colonne+largeur_graphique_etat*_decalage_colonne);
    std::cout << "Coups possibles";
    _pConsole->gotoLigCol(origine_arbre_ligne+1, origine_arbre_colonne+largeur_graphique_etat*_decalage_colonne);
    std::cout << "pour les ";
    (m_couleur_tour == NOIR) ? std::cout << "Noirs :" : std::cout << "Blancs :";

    for(unsigned int i(0) ; i<m_aretes.size() ; i++)
    {
        ligne = m_aretes[i]->getPos().X;
        colonne = m_aretes[i]->getPos().Y;
//        fond = m_aretes[i]->estSelectionne() ? COULEUR_MARRON : COULEUR_OR;

        pEtatTemporaire = new Etat(m_situation_damier, ligne, colonne, m_couleur_tour);

        _pConsole->gotoLigCol(origine_arbre_ligne+3+i, origine_arbre_colonne+largeur_graphique_etat*_decalage_colonne);
        _pConsole->setColor(m_aretes[i]->estSelectionne() ? COULEUR_NOIR : COULEUR_BLANC, fond);
        std::cout << CARAC_CARRE;
        _pConsole->setColor(COULEUR_BLANC, fond);
        std::cout << " [" << pEtatTemporaire->getSituationDamier()->getNomCase(ligne, colonne) << "], Score ";
        _pConsole->setColor(COULEUR_NOIR, fond);
        std::cout << pEtatTemporaire->getSituationDamier()->CompterPions(NOIR);
        _pConsole->setColor(COULEUR_BLANC, fond);
        std::cout << " - " << pEtatTemporaire->getSituationDamier()->CompterPions(BLANC);

        delete pEtatTemporaire;
        pEtatTemporaire = NULL;
    }
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
}

void Etat::DesafficherEtat(Console* _pConsole, int _decalage_colonne)
// Enlève l'affichage de l'état actuel sans passer par system("cls")
{
    const int largeur_graphique_etat = 22,
              origine_arbre_ligne = 11,
              origine_arbre_colonne = 45;

    for(unsigned int ligne(0) ; ligne<m_aretes.size()+4 ; ligne++)
    {
        _pConsole->gotoLigCol(ligne+origine_arbre_ligne, origine_arbre_colonne+largeur_graphique_etat*_decalage_colonne);
        _pConsole->espacer(largeur_graphique_etat);
    }
}
