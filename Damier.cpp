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

    m_damier[3][3]='B';
    m_damier[3][4]='N';
    m_damier[4][3]='N';
    m_damier[4][4]='B';
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
                    m_damier[ligne+dl][colonne+dc] = '.';
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
    m_damier[ligne][colonne]=tour;
    int i=ligne, j=colonne;
    std::vector<int> lig;
    std::vector<int> col;

    if(ligne+1<m_taille && m_damier[ligne+1][colonne]==adv)
    {
        i++;
        while(i<m_taille && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            i++;
        }
        if(i<m_taille && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }

    i=ligne;
    j=colonne;

    if(colonne+1<m_taille && m_damier[ligne][colonne+1]==adv)
    {
        j++;
        while(j<m_taille && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            j++;
        }
        if(j<m_taille && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }

    i=ligne;
    j=colonne;

    if(ligne-1>=0 && m_damier[ligne-1][colonne]==adv)
    {
        i--;
        while(i>=0 && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            i--;
        }
        if(i>=0 && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }

    i=ligne;
    j=colonne;

    if(colonne-1>=0 && m_damier[ligne][colonne-1]==adv)
    {
        j--;
        while(j>=0 && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            j--;
        }
        if(j>=0 && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }

    i=ligne;
    j=colonne;

    if(ligne+1<m_taille && colonne+1<m_taille && m_damier[ligne+1][colonne+1]==adv)
    {
        i++;
        j++;
        while(i<m_taille && j<m_taille && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            i++;
            j++;
        }
        if(i<m_taille && j<m_taille && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }

    i=ligne;
    j=colonne;

    if(ligne-1>=0 && colonne+1<m_taille && m_damier[ligne-1][colonne+1]==adv)
    {
        i--;
        j++;
        while(i>=0 && j<m_taille && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            i--;
            j++;
        }
        if(i>=0 && j<m_taille && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }

    i=ligne;
    j=colonne;

    if(ligne+1<m_taille && colonne-1>=0 && m_damier[ligne+1][colonne-1]==adv)
    {
        i++;
        j--;
        while(i<m_taille && j>=0 && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            i++;
            j--;
        }
        if(i<m_taille && j>=0 && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }

    i=ligne;
    j=colonne;

    if(ligne-1>=0 && colonne-1>=0 && m_damier[ligne-1][colonne-1]==adv)
    {
        i--;
        j--;
        while(i>=0 && j>=0 && m_damier[i][j]==adv)
        {
            lig.push_back(i);
            col.push_back(j);
            i--;
            j--;
        }
        if(i>=0 && j>=0 && m_damier[i][j]==tour)
        {
            for(int k=0;k<lig.size();k++)
            {
                m_damier[lig[k]][col[k]]=tour;
            }
        }
        for(int k=0;k<lig.size();k++)
        {
            lig.pop_back();
            col.pop_back();
        }
    }
}

void Damier::reset()
{
    for(int i=0;i<m_taille;i++)
    {
        for(int j=0;j<m_taille;j++)
        {
            if(m_damier[i][j]=='.')
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
