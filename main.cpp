#include "console.h"
#include "Affichage.h"
#include "Evenements.h"
#include "Damier.h"
#include "IA.h"

#include <iostream>
#include <Windows.h>

int main()
{
    srand(time(NULL));

    // Variables du main
    Console* pConsole = NULL; //pointeur sur une instance de console

    Damier* pDamier = new Damier(TAILLE_PLATEAU, LIGNE_AFFICHAGE, COLONNE_AFFICHAGE); //pointeur sur une instance du damier

    char couleur_tour = NOIR; //couleur du joueur pendant le tour (les pions noirs commencent)

    const int origineCurseur = 7; //origine d'affichage du curseur

    bool quitter = false; //bool�en de d�tection de fin de partie
    bool verif = false;
    int choix; //contient la valeur du choix de l'utilisateur pour le menu

    IA* ordinateur = new IA; //pointeur sur une instance de l'ordinateur (IA)

    pConsole = Console::getInstance(); //on r�cup�re le pointeur sur l'instance console

    choix = GfxMenu::Afficher(pConsole, ordinateur);

    if(choix == 3)
        exit(0);

    pConsole->setColor(COULEUR_BLANC, COULEUR_VERT); //passe la console en texte blanc sur fond vert
    system("cls"); //on efface la console

    while(!quitter)
    {
        //pour tous les coups jouables
        for(int i=0 ; i<pDamier->getTaille() ; i++)
        {
            for(int j=0 ; j<pDamier->getTaille() ; j++)
            {
                if(pDamier->getDamier()[i][j] == couleur_tour)
                    pDamier->CoupsPossibles(i, j, couleur_tour);
            }
        }

        if(Partie::CoupExistant(pDamier)) //si l'utilisateur peut jouer un coup
        {
            verif = false;
          
            pConsole->gotoLigCol(origineCurseur, 8);

            //d�roulement du tour du joueur actuel
            if(choix == 2) //deux joueurs
                quitter=Partie::TourJoueur(pConsole, pDamier, couleur_tour);
            else if(choix == 1) //un joueur
            {
                if(couleur_tour == BLANC) //si c'est au tour de l'ordinateur
                    quitter = ordinateur->TourOrdinateur(pConsole, pDamier, couleur_tour); //l'ordinateur effectue son tour
                else
                    quitter = Partie::TourJoueur(pConsole, pDamier, couleur_tour); //sinon le joueur effectue son tour
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
                quitter=true;
        }

        //d�finit la couleur des pions du joueur pour le tour suivant
        if(couleur_tour == NOIR)
             couleur_tour = BLANC;
        else
             couleur_tour = NOIR;
    }

    // Fin de partie
    GfxFin::AfficherFin(pDamier);

    // On efface les allocations m�moires
    Console::deleteInstance();
    delete pDamier;

    // Fin du programme
    return 0;
}
