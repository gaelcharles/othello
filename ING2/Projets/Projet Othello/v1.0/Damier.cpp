#include "Damier.h"
#include "console.h"
#include "Affichage.h"

#include <iostream>
#include <vector>

Damier::Damier(int _taille, int _ligneAffichage, int _colonneAffichage)
    :m_taille(_taille), m_ligneAffichage(_ligneAffichage), m_colonneAffichage(_colonneAffichage)
{
    //constructeur

    //on crée un vecteur tampon
    std::vector<char> tmp;
    for(int i=0; i<m_taille; i++)
    {
        for(int j=0; j<m_taille;j++)
        {
            tmp.push_back(' ');
        }
        m_damier.push_back(tmp);
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
    bool boucle=true;
    int i=ligne, j=colonne;

    if(i!=0 && m_damier[i-1][j]==adv)
    {
        i--;
        boucle=true;
    }
    else
    {
        boucle=false;
    }


    while(i>0 && boucle)
    {
        if(m_damier[i-1][j]==adv)
        {
            i--;
        }
        else
        {
            boucle=false;
            if(m_damier[i-1][j]==tour)
            {
                m_damier[ligne][colonne]='.';
            }
        }
    }

    if(i!=m_taille-1 && m_damier[i+1][j]==adv)
    {
        i++;
        boucle=true;
    }
    else
    {
        boucle=false;
    }

    while(i<m_taille-1 && boucle)
    {
        if(m_damier[i+1][j]==adv)
        {
            i++;
        }
        else
        {
            boucle=false;
            if(m_damier[i+1][j]==tour)
            {
                m_damier[ligne][colonne]='.';
            }
        }
    }

    if(j!=0 && m_damier[i][j-1]==adv)
    {
        j--;
        boucle=true;
    }
    else
    {
        boucle=false;
    }

    while(j>0 && boucle)
    {
        if(m_damier[i][j-1]==adv)
        {
            j--;
        }
        else
        {
            boucle=false;
            if(m_damier[i][j-1]==tour)
            {
                m_damier[ligne][colonne]='.';
            }
        }
    }

    if(j!=m_taille-1 && m_damier[i][j+1]==adv)
    {
        j++;
        boucle=true;
    }
    else
    {
        boucle=false;
    }


    while(j<m_taille-1 && boucle)
    {
        if(m_damier[i][j+1]==adv)
        {
            j++;
        }
        else
        {
            boucle=false;
            if(m_damier[i][j+1]==tour)
            {
                m_damier[ligne][colonne]='.';
            }
        }
    }

    if(i!=0 && j!=0 && m_damier[i-1][j-1]==adv)
    {
        i--;
        j--;
        boucle=true;
    }
    else
    {
        boucle=false;
    }


    while(i>0 && j>0 && boucle)
    {
        if(m_damier[i-1][j-1]==adv)
        {
            i--;
            j--;
        }
        else
        {
            boucle=false;
            if(m_damier[i-1][j-1]==tour)
            {
                m_damier[ligne][colonne]='.';
            }
        }
    }

    if(i!=0 && j!=m_taille-1 && m_damier[i-1][j+1]==adv)
    {
        i--;
        j++;
        boucle=true;
    }
    else
    {
        boucle=false;
    }


    while(i>0 && j<m_taille-1 && boucle)
    {
        if(m_damier[i-1][j+1]==adv)
        {
            i--;
            j++;
        }
        else
        {
            boucle=false;
            if(m_damier[i-1][j+1]==tour)
            {
                m_damier[ligne][colonne]='.';
            }
        }
    }

    if(i!=m_taille-1 && j!=0 && m_damier[i+1][j-1]==adv)
    {
        i++;
        j--;
        boucle=true;
    }
    else
    {
        boucle=false;
    }


    while(i<m_taille-1 && j>0 && boucle)
    {
        if(m_damier[i+1][j-1]==adv)
        {
            i++;
            j--;
        }
        else
        {
            boucle=false;
            if(m_damier[i+1][j-1]==tour)
            {
                m_damier[ligne][colonne]='.';
            }
        }
    }

    if(i!=m_taille-1 && j!=m_taille-1 && m_damier[i+1][j+1]==adv)
    {
        i++;
        j++;
        boucle=true;
    }
    else
    {
        boucle=false;
    }


    while(i<m_taille-1 && j<m_taille-1 && boucle)
    {
        if(m_damier[i+1][j+1]==adv)
        {
            i++;
            j++;
        }
        else
        {
            boucle=false;
            if(m_damier[i+1][j+1]==tour)
            {
                m_damier[ligne][colonne]='.';
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

int Damier::comptageNoir()
{
    int n=0;

    for(int i=0;i<m_taille;i++)
    {
        for(int j=0;j<m_taille;j++)
        {
            if(m_damier[i][j]=='N')
            {
                n++;
            }
        }
    }

    return n;
}

int Damier::comptageBlanc()
{
    int b=0;

    for(int i=0;i<m_taille;i++)
    {
        for(int j=0;j<m_taille;j++)
        {
            if(m_damier[i][j]=='B')
            {
                b++;
            }
        }
    }

    return b;
}
