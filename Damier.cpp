#include "Damier.h"
#include "console.h"
#include "Affichage.h"
#include "Constantes.h"

#include <iostream>
#include <vector>
#include <fstream>

Damier::Damier(int _taille, int _ligneAffichage, int _colonneAffichage)
    :m_taille(_taille), m_ligneAffichage(_ligneAffichage), m_colonneAffichage(_colonneAffichage)
{
    //on crée un vecteur tampon
    std::vector<char> tmp;
    for(int i=0; i<m_taille; i++)
    {
        for(int j=0; j<m_taille;j++)
        {
            tmp.push_back(' ');
        }
        m_damier.push_back(tmp);
        tmp.clear();
    }

    m_damier[3][3]=BLANC;
    m_damier[3][4]=NOIR;
    m_damier[4][3]=NOIR;
    m_damier[4][4]=BLANC;
}

Damier::Damier(Damier* _pCopie)
{
    //Constructeur par copie
    m_taille = _pCopie->getTaille();
    m_ligneAffichage = _pCopie->getLigneAffichage();
    m_colonneAffichage = _pCopie->getColonneAffichage();
    m_damier = _pCopie->getDamier();
}

Damier::~Damier()
{
    //destructeur
}

void Damier::setCaseDamier(int _ligne, int _colonne, char _valeur)
{
    if(_valeur == ' ' || _valeur == COUP_JOUABLE || _valeur == NOIR || _valeur == BLANC) //cases possibles du damier
        m_damier[_ligne][_colonne] = _valeur; //change la valeur de la case aux coordonnees (_ligne, _colonne)
}

void Damier::CoupsPossibles(int _ligne, int _colonne, char _couleur_tour)
{
    // Reference des deplacements elementaires selon les directions : N,S,E,W,NE,NW,SE,SW
    const int directions[8][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}, {-1,1}, {-1,-1}, {1,1}, {1,-1}};

    int dl = 0, dc = 0; // Deplacements elementaires (ligne et colonne)
    char couleur_adversaire = (_couleur_tour == NOIR) ? BLANC : NOIR; //couleur des pions de l'adversaire

    // Pour chacune des 8 directions
    for(auto delta : directions)
    {
        // Mise a jour des deplacements elementaires
        dl = delta[0];
        dc = delta[1];

        if(_ligne   + dl >= 0 && _ligne   + dl < TAILLE_PLATEAU &&
           _colonne + dc >= 0 && _colonne + dc < TAILLE_PLATEAU) // Si la case adjacente est dans le plateau
        {
            // Tant qu'un pion ennemi est adjacent
            while(m_damier[_ligne+dl][_colonne+dc] == couleur_adversaire)
            {
                // Incrementation des deplacements elementaires
                dl += delta[0];
                dc += delta[1];

                // Si hors du plateau, on sort de la boucle directement
                if(_ligne+dl < 0 || _ligne+dl >= TAILLE_PLATEAU || _colonne+dc < 0 || _colonne+dc >= TAILLE_PLATEAU)
                    break;

                // Si la case d'apres est vide, c'est un coup jouable
                else if(m_damier[_ligne+dl][_colonne+dc] == ' ')
                    m_damier[_ligne+dl][_colonne+dc] = COUP_JOUABLE;
            }
        }
    }
}

void Damier::Afficher(Console* _pConsole)
{
    GfxDamier::Afficher(_pConsole, this);
    GfxDamier::AfficherContenu(_pConsole, this);
}

void Damier::ChangerCouleurPions(int _ligne, int _colonne, char _couleur_tour)
{
    // Référence des déplacements élémentaires selon les directions : N,S,E,W,NE,NW,SE,SW
    const int directions[8][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}, {-1,1}, {-1,-1}, {1,1}, {1,-1}};

    int dl = 0, dc = 0, x = 0, y = 0; //deplacements elementaires & coordonnees
    char couleur_adversaire = (_couleur_tour == NOIR) ? BLANC : NOIR; //couleur des pions de l'adversaire

    // Vecteur indiquant les pions à retourner
    std::vector<std::vector<int> > pions_a_retourner;

    // Vecteur tampon
    std::vector<int> coords;

    // On place un pion sur la case sélectionnée
    m_damier[_ligne][_colonne] = _couleur_tour;

    // Pour chacune des 8 directions
    for(auto delta : directions)
    {
        // Mise à jour des déplacements élémentaires
        dl = delta[0];
        dc = delta[1];

        if(_ligne   + dl >= 0 && _ligne   + dl < TAILLE_PLATEAU &&
           _colonne + dc >= 0 && _colonne + dc < TAILLE_PLATEAU) // Si la case adjacente est dans le plateau
        {
            // Tant qu'un pion ennemi est adjacent
            while(m_damier[_ligne+dl][_colonne+dc] == couleur_adversaire)
            {
                // On retient les coordonnées du pion adjacent pour changer sa couleur plus tard
                coords.push_back(_ligne+dl);
                coords.push_back(_colonne+dc);
                pions_a_retourner.push_back(coords);
                coords.clear();

                // Incrémentation des déplacements élémentaires
                dl += delta[0];
                dc += delta[1];

                // Si hors du plateau, on sort de la boucle
                if(_ligne+dl < 0 || _ligne+dl >= TAILLE_PLATEAU || _colonne+dc < 0 || _colonne+dc >= TAILLE_PLATEAU)
                    break;

                // Si la case d'après est un pion allié, on change de couleur les pions alignés
                else if(m_damier[_ligne+dl][_colonne+dc] == _couleur_tour)
                {
                    for(unsigned int id(0) ; id<pions_a_retourner.size() ; id++)
                    {
                        x = pions_a_retourner[id][0];
                        y = pions_a_retourner[id][1];
                        m_damier[x][y] = _couleur_tour; // La couleur du pion devient celle du joueur dont c'est le tour
                    }
                }
            }
            // Reset quand on sort du while
            pions_a_retourner.clear();
        }
    }
}

void Damier::ReinitialiserPossibilites()
{
    for(int i=0;i<m_taille;i++)
    {
        for(int j=0;j<m_taille;j++)
        {
            if(m_damier[i][j]==COUP_JOUABLE)
            {
                m_damier[i][j]=' ';
            }
        }
    }
}

int Damier::CompterPions(char _couleur)
{
    int n=0;

    for(int i=0;i<m_taille;i++)
    {
        for(int j=0;j<m_taille;j++)
        {
            if(m_damier[i][j]==_couleur)
            {
                n++;
            }
        }
    }

    return n;
}

int Damier::Chargement(char& _couleur_tour)
{
    std::ifstream fichier ("partie.txt", std::ios::in);

    // Si l'ouverture du fichier a réussi
    if(fichier)
    {
        int mode = 0, taille = 0;
        char pion = 0;

        // Lecture : D'abord de mode de jeu, puis le joueur, puis la taille du plateau
        fichier >> mode >> _couleur_tour >> taille;

        // Pour chaque case dans le fichier
        for(int i=0; i<taille; i++)
        {
            for(int j=0; j<taille; j++)
            {
                // Lecture du caractère+ associé et enregistrement
                fichier >> pion;
                if(pion == NOIR || pion == BLANC)
                    m_damier[i][j]=pion;
                else
                    m_damier[i][j]=' ';

            }
        }
        return mode;
    }
    // Erreur
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        return 3;
    }


}
