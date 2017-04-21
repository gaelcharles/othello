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

    // Instances du jeu
    Console* pConsole = NULL; //pointeur sur une instance de la console
    Damier* pDamier = new Damier(TAILLE_PLATEAU, LIGNE_AFFICHAGE, COLONNE_AFFICHAGE); //pointeur sur une instance du damier
    IA* pOrdinateur = new IA; //pointeur sur une instance de l'ordinateur
    FenetreAllegro* pAllegro = new FenetreAllegro();

    char couleur_tour; //couleur des pions du joueur actuel
    const int origineCurseurLigne = 7, origineCurseurColonne = 8; //coordonnees d'origine pour l'affichage du pointeur
    int quitter = 0; //booleen de dectection de fin de partie
    int choix; //choix de l'utilisateur pour le menu
    bool verif = false;

    pConsole = Console::getInstance();

    choix = GfxMenu::Afficher(pDamier, pConsole, pOrdinateur); //affiche le menu

    if(choix == 3) //si l'utilisateur quitte le programme
        exit(0);

    // Passe la console en texte blanc sur fond vert
    pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
    system("cls");

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

        if(Partie::CoupExistant(pDamier)) //si le joueur peut jouer un coup
        {
            verif = false;

            pConsole->gotoLigCol(origineCurseurLigne, origineCurseurColonne);

            //Deroulement du tour
            if(choix == 2) //mode deux joueurs
                quitter = Partie::TourJoueur(choix, pConsole, pDamier, pAllegro, couleur_tour);
            else if(choix == 1) //mode joueur contre ordinateur
            {
                if(couleur_tour == BLANC) //tour de l'ordinateur
                    quitter = pOrdinateur->TourOrdinateur(pConsole, pDamier, couleur_tour);
                else
                    quitter = Partie::TourJoueur(choix, pConsole, pDamier, pAllegro, couleur_tour);
            }
        }
        else
        {
            if(!verif)
            {
                pConsole->gotoLigCol(0,0);
                std::cout << "Aucun coup possible, vous passez votre tour !" << std::endl;
                system("pause");
                system("cls");
                verif = true;
            }
            else
                quitter = 1; //quitte le programme
        }

        couleur_tour = (couleur_tour == NOIR) ? BLANC : NOIR; //change la couleur des pions pour le tour suivant

    }

    // Fin de partie
    if(quitter == 1) //si la partie se termine parce que l'un des deux a gagne, on affiche le score
        GfxFin::AfficherFin(pDamier);

    // Fin de programme
    Console::deleteInstance();
    delete pDamier;
    delete pOrdinateur;
    delete pAllegro;

    return 0;
}
END_OF_MAIN();
