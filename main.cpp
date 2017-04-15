/// BIBLIOTHEQUES STANDARDS ///

#include <iostream>
#include <Windows.h>
#include <MMsystem.h>

/// BIBLIOTHEQUES PERSONNELLES ///

#include "Damier.h"
#include "Console.h"
#include "Affichage.h"
#include "Evenements.h"
#include "Constantes.h"

int main()
{
    /// DECLARATION DE LA CONSOLE D'AFFICHAGE
    Console* pConsole = NULL;

    Damier* damier = new Damier(TAILLE_PLATEAU, LIGNE_AFFICHAGE, COLONNE_AFFICHAGE);
    char tour='N', adv='B';
    bool ok;

    pConsole = Console::getInstance();
    pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);

    const int origineCurseur = 7;
    const int finCurseur = 11;


    bool quitter = false;
    bool verif=false;

    system("cls");

    while(!quitter)
    {

        for(int i=0;i<damier->getTaille();i++)
        {
            for(int j=0;j<damier->getTaille();j++)
            {
                if(damier->getDamier()[i][j]==' ')
                    damier->coups(tour,adv,i,j);
            }
        }

        ok=Partie::verification(damier);

        if(ok)
        {
            verif=false;
            pConsole->gotoLigCol(origineCurseur,8);
            quitter=Partie::deroulement(pConsole, damier, tour, adv);
        }
        else
        {
            if(!verif)
            {
                pConsole->gotoLigCol(0,0);
                std::cout << "Aucun coup possible, vous passez votre tour !" << std::endl ;
                system("pause");
                verif=true;
            }
            else
            {
                quitter=true;
            }
        }

        if(tour=='B')
        {
             tour='N';
             adv='B';
        }
        else
        {
             tour='B';
             adv='N';
        }

    }

    GfxFin::afficherFin(damier);
    Console::deleteInstance();

    return 0;

}
