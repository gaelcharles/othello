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

Damier::~Damier()
{
    //destructeur
}

void Damier::coups(char tour, char adv, int ligne, int colonne)
{
    // Référence des déplacements élémentaires selon les directions : N,S,E,W,NE,NW,SE,SW
    const int directions[8][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}, {-1,1}, {-1,-1}, {1,1}, {1,-1}};

    // Déplacements élémentaires
    int dl = 0, dc = 0;

    // Pour chacune des 8 directions
    for(auto delta : directions)
    {
        // Mise à jour des déplacements élémentaires
        dl = delta[0];
        dc = delta[1];

        if(ligne   + dl >= 0 && ligne   + dl < TAILLE_PLATEAU &&
           colonne + dc >= 0 && colonne + dc < TAILLE_PLATEAU) // Si la case adjacente est dans le plateau
        {
            // Tant qu'un pion ennemi est adjacent
            while(m_damier[ligne+dl][colonne+dc] == adv)
            {
                // Incrémentation des déplacements élémentaires
                dl += delta[0];
                dc += delta[1];

                // Si hors du plateau, on sort de la boucle directement
                if(ligne+dl < 0 || ligne+dl >= TAILLE_PLATEAU || colonne+dc < 0 || colonne+dc >= TAILLE_PLATEAU)
                    break;

                // Si la case d'après est vide, c'est un coup jouable
                else if(m_damier[ligne+dl][colonne+dc] == ' ')
                    m_damier[ligne+dl][colonne+dc] = COUP_JOUABLE;
            }
        }
    }
}

void Damier::afficher(Console* _pConsole)
{
    GfxDamier::afficher(_pConsole, this);
    GfxDamier::afficherContenu(_pConsole, this);
}

void Damier::changement(char tour, char adv, int ligne, int colonne)
{
    // Référence des déplacements élémentaires selon les directions : N,S,E,W,NE,NW,SE,SW
    const int directions[8][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}, {-1,1}, {-1,-1}, {1,1}, {1,-1}};

    // Déplacements élémentaires & coordonnées
    int dl = 0, dc = 0, x = 0, y = 0;

    // Vecteur indiquant les pions à retourner
    std::vector<std::vector<int> > pions_a_retourner;

    // Vecteur tampon
    std::vector<int> coords;

    // On place un pion sur la case sélectionnée
    m_damier[ligne][colonne] = tour;

    // Pour chacune des 8 directions
    for(auto delta : directions)
    {
        // Mise à jour des déplacements élémentaires
        dl = delta[0];
        dc = delta[1];

        if(ligne   + dl >= 0 && ligne   + dl < TAILLE_PLATEAU &&
           colonne + dc >= 0 && colonne + dc < TAILLE_PLATEAU) // Si la case adjacente est dans le plateau
        {
            // Tant qu'un pion ennemi est adjacent
            while(m_damier[ligne+dl][colonne+dc] == adv)
            {
                // On retient les coordonnées du pion adjacent pour changer sa couleur plus tard
                coords.push_back(ligne+dl);
                coords.push_back(colonne+dc);
                pions_a_retourner.push_back(coords);
                coords.clear();

                // Incrémentation des déplacements élémentaires
                dl += delta[0];
                dc += delta[1];

                // Si hors du plateau, on sort de la boucle
                if(ligne+dl < 0 || ligne+dl >= TAILLE_PLATEAU || colonne+dc < 0 || colonne+dc >= TAILLE_PLATEAU)
                    break;

                // Si la case d'après est un pion allié, on change de couleur les pions alignés
                else if(m_damier[ligne+dl][colonne+dc] == tour)
                {
                    for(unsigned int id(0) ; id<pions_a_retourner.size() ; id++)
                    {
                        x = pions_a_retourner[id][0];
                        y = pions_a_retourner[id][1];
                        m_damier[x][y] = tour; // La couleur du pion devient celle du joueur dont c'est le tour
                    }
                }
            }
            // Reset quand on sort du while
            pions_a_retourner.clear();
        }
    }
}

void Damier::reset()
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

int Damier::comptagePions(char _color)
{
    int n=0;

    for(int i=0;i<m_taille;i++)
    {
        for(int j=0;j<m_taille;j++)
        {
            if(m_damier[i][j]==_color)
            {
                n++;
            }
        }
    }

    return n;
}

int Damier::chargement()
{
    std::ifstream fichier ("partie.txt", std::ios::in);


    if(fichier)
    {
        int choix, taille;
        fichier >> choix >> taille;

        char pion;

        for(int i=0; i<taille; i++)
        {
            for(int j=0; j<taille; j++)
            {
                fichier >> pion;
                if(pion!='0')
                    m_damier[i][j]=pion;
                else
                    m_damier[i][j]=' ' ;
            }
        }
        return choix;
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        return 3;
    }


}
