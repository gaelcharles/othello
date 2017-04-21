#include "Damier.h"
#include "console.h"
#include "Affichage.h"
#include "Evenements.h"
#include "IA.h"
#include "FenetreAllegro.h"

#include <iostream>
#include <allegro.h>
#include <winalleg.h>
#include <MMsystem.h> // ???


int main()
{
    srand(time(NULL));

    // Variables
    Console* pConsole = NULL;
    Damier* damier = new Damier(TAILLE_PLATEAU, LIGNE_AFFICHAGE, COLONNE_AFFICHAGE);
    FenetreAllegro* pAllegro = new FenetreAllegro();

    char tour=NOIR, adv=BLANC;
    const int origineCurseurL = 7, origineCurseurC = 8;
    int quitter = 0;

    bool verif=false;
    int choix;
    IA* bot = new IA;

    pConsole = Console::getInstance();

    choix = GfxMenu::afficher(damier, pConsole, bot);
    if(choix == 3) exit(0);

    // Passe la console en texte blanc sur fond vert
    pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
    system("cls");

    while(!quitter)
    {
        // On cherche les coups jouables
        for(int i=0 ; i<damier->getTaille() ; i++)
        {
            for(int j=0 ; j<damier->getTaille() ; j++)
            {
                if(damier->getDamier()[i][j] == tour)
                    damier->coups(tour, adv, i, j);
            }
        }

        if(Partie::verification(damier))
        {
            verif = false;
            pConsole->gotoLigCol(origineCurseurL, origineCurseurC);
            if(choix == 2) // Deux joueurs
                quitter=Partie::deroulement(choix, pConsole, damier, pAllegro, tour, adv);
            else if(choix == 1) // Un joueur
            {
                if(tour == BLANC) // Tour de l'IA
                    quitter = bot->deroulement(pConsole, damier, tour, adv);
                else
                    quitter = Partie::deroulement(choix, pConsole, damier, pAllegro, tour, adv);
            }
        }
        else
        {
            if(!verif)
            {
                pConsole->gotoLigCol(0,0);
                std::cout << "Aucun coup possible, vous passez votre tour !" << std::endl ;
                system("pause");
                system("cls");
                verif=true;
            }
            else
            {
                quitter=1;
            }
        }

        if(tour==BLANC)
        {
             tour=NOIR;
             adv=BLANC;
        }
        else
        {
             tour=BLANC;
             adv=NOIR;
        }

    }

    // Fin de partie
    //Si la partie se termine parce que l'un des deux a gagné, on affiche le score
    if(quitter == 1) GfxFin::afficherFin(damier);

    // Fin de programme
    Console::deleteInstance();
    delete damier;
    delete bot;
    delete pAllegro;
    return 0;
}
END_OF_MAIN();
