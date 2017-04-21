#include <conio.h>
#include <time.h>

#include "Evenements.h"

void Curseur::deplacer(char _key, int& _ligneCurseurDamier, int& _colonneCurseurDamier, int& _ligneCurseurAffichage, int& _colonneCurseurAffichage,
                       int _origineCurseurLigne, int _origineCurseurColonne, int _ligneCurseurAffichageMax, int _colonneCurseurAffichageMax,
                       int _ligneCurseurDamierMax, int _colonneCurseurDamierMax)
{
    switch(_key)
    {
    case 'Z': // Z : Haut
    case 'z':
        _ligneCurseurDamier--; //remonte le curseur
        if(_ligneCurseurDamier < 0) _ligneCurseurDamier = 0; //ne peut pas dépasser le damier

        _ligneCurseurAffichage-=2; //le curseur affiché remonte de 2
        if(_ligneCurseurAffichage < _origineCurseurLigne) _ligneCurseurAffichage = _origineCurseurLigne; //ne peut pas dépasser
        break;

    case 'S': // S : Bas
    case 's':
        _ligneCurseurDamier++;
        if(_ligneCurseurDamier > _ligneCurseurDamierMax) _ligneCurseurDamier = _ligneCurseurDamierMax; // nbLignes-1 car l'indice va de 0 à 4

        _ligneCurseurAffichage+=2;
        if(_ligneCurseurAffichage > _ligneCurseurAffichageMax) _ligneCurseurAffichage = _ligneCurseurAffichageMax;
        break;

    case 'Q': // Q : Gauche
    case 'q':
        _colonneCurseurDamier--;
        if(_colonneCurseurDamier < 0) _colonneCurseurDamier = 0;

        _colonneCurseurAffichage-=4;
        if(_colonneCurseurAffichage < _origineCurseurColonne) _colonneCurseurAffichage = _origineCurseurColonne;
        break;

    case 'D': // D : Droite
    case 'd':
        _colonneCurseurDamier++;
        if(_colonneCurseurDamier > _colonneCurseurDamierMax) _colonneCurseurDamier = _colonneCurseurDamierMax; //nbColonnes-1 car l'indice va de 0 à 4


        _colonneCurseurAffichage+=4;
        if(_colonneCurseurAffichage > _colonneCurseurAffichageMax) _colonneCurseurAffichage = _colonneCurseurAffichageMax;
        break;
    }
}

bool Partie::TourJoueur(Console* pConsole, Damier* damier, char couleur_tour)
{
    // DECLARATION DES VARIABLES D'AFFICHAGE DU CURSEUR DU DAMIER

    //initialisation des valeurs constantes du sous-programme
    const int origineCurseurLigne = damier->getLigneAffichage()+1;
    const int origineCurseurColonne = damier->getColonneAffichage()+2;

    int ligneCurseurDamier, colonneCurseurDamier;
    int ligneCurseurAffichage, colonneCurseurAffichage;

    //ligne et colonne maximale d'affichage du curseur
    int ligneCurseurAffichageMax, colonneCurseurAffichageMax;
    int ligneCurseurDamierMax, colonneCurseurDamierMax;

    // INITIALISATION DES VARIABLES

    //coordonnées réelles de la case pointée par le curseur
    ligneCurseurDamier = 0;
    colonneCurseurDamier = 0;

    //coordonnées maximales de la case pointée par le curseur
    ligneCurseurDamierMax = damier->getTaille()-1;
    colonneCurseurDamierMax = damier->getTaille()-1;

    //ligne et colonne maximale d'affichage du curseur
    ligneCurseurAffichageMax = 2*damier->getTaille() + origineCurseurLigne-2;
    colonneCurseurAffichageMax = 4*(damier->getTaille() -1) + origineCurseurColonne;

    //coordonnées d'affichage du curseur
    ligneCurseurAffichage = origineCurseurLigne;
    colonneCurseurAffichage = origineCurseurColonne;

    // Couleur de l'adversaire pendant ce tour
//    char couleur_adversaire = (couleur_tour == NOIR)? BLANC : NOIR;

    bool rafraichirEcran = true; //pour rentrer dès le début dans la boucle d'affichage
    bool quitter=false;

    GfxDamier::Afficher(pConsole, damier);

    while(!quitter)
    {
        // GESTIONS DES EVENEMENTS CLAVIER
        if(pConsole->isKeyboardPressed())
        {
            //récupération de la touche sur laquelle l'utilisateur a appuyé
            char touche = pConsole->getInputKey();

            if(touche=='z' || touche=='s' || touche=='q' || touche=='d') //commandes de déplacement du curseur
            {
                Curseur::deplacer(touche, ligneCurseurDamier, colonneCurseurDamier, ligneCurseurAffichage, colonneCurseurAffichage,
                                  origineCurseurLigne, origineCurseurColonne, ligneCurseurAffichageMax, colonneCurseurAffichageMax,
                                  ligneCurseurDamierMax, colonneCurseurDamierMax);

                pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);
            }

            if(touche==13 && damier->getDamier()[ligneCurseurDamier][colonneCurseurDamier]==COUP_JOUABLE)
            {
                damier->ChangerCouleurPions(ligneCurseurDamier, colonneCurseurDamier, couleur_tour);
                quitter=true;
                damier->ReinitialiserPossibilites();
                rafraichirEcran = true;
            }
        }

        if(rafraichirEcran)
        {
            pConsole->gotoLigCol(origineCurseurLigne-4, origineCurseurColonne);

            GfxInfos::AfficherTour(pConsole, couleur_tour);
            GfxInfos::AfficherScore(pConsole, damier);
            GfxDamier::AfficherContenu(pConsole, damier);

            pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);

            rafraichirEcran = false;
        }
    }
    system("cls");

return false;
}

bool Partie::CoupExistant(Damier* damier)
{
    bool coup_existant = false; //true : le joueur peut jouer un coup | false : le joueur n'a aucun coup possible

    for(int i=0 ; i<damier->getTaille() ; i++)
    {
        for(int j=0 ; j<damier->getTaille() ; j++)
        {
            if(damier->getDamier()[i][j] == COUP_JOUABLE)
            {
                coup_existant = true;
                break; //sortie de la premiere boucle pour
            }
        }
        if(coup_existant) break; //sortie de la seconde boucle pour
    }

    return coup_existant;
}
