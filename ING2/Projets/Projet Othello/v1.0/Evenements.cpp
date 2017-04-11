#include <conio.h>
#include <time.h>

#include "Evenements.h"

void Curseur::deplacer(char _key, int& _ligneCurseurDamier, int& _colonneCurseurDamier, int& _ligneCurseurAffichage, int& _colonneCurseurAffichage,
                       int _origineCurseurLigne, int _origineCurseurColonne, int _ligneCurseurAffichageMax, int _colonneCurseurAffichageMax,
                       int _ligneCurseurDamierMax, int _colonneCurseurDamierMax)
{
    switch(_key)
    {

    case 'z': //z : haut
        _ligneCurseurDamier--; //remonte le curseur
        if(_ligneCurseurDamier < 0) _ligneCurseurDamier = 0; //ne peut pas dépasser le damier

        _ligneCurseurAffichage-=2; //le curseur affiché remonte de 2
        if(_ligneCurseurAffichage < _origineCurseurLigne) _ligneCurseurAffichage = _origineCurseurLigne; //ne peut pas dépasser
        break;

    case 's': //bas
        _ligneCurseurDamier++;
        if(_ligneCurseurDamier > _ligneCurseurDamierMax) _ligneCurseurDamier = _ligneCurseurDamierMax; // nbLignes-1 car l'indice va de 0 à 4

        _ligneCurseurAffichage+=2;
        if(_ligneCurseurAffichage > _ligneCurseurAffichageMax) _ligneCurseurAffichage = _ligneCurseurAffichageMax;
        break;

    case 'q': //gauche
        _colonneCurseurDamier--;
        if(_colonneCurseurDamier < 0) _colonneCurseurDamier = 0;

        _colonneCurseurAffichage-=3;
        if(_colonneCurseurAffichage < _origineCurseurColonne) _colonneCurseurAffichage = _origineCurseurColonne;
        break;

    case 'd': //droite
        _colonneCurseurDamier++;
        if(_colonneCurseurDamier > _colonneCurseurDamierMax) _colonneCurseurDamier = _colonneCurseurDamierMax; //nbColonnes-1 car l'indice va de 0 à 4


        _colonneCurseurAffichage+=3;
        if(_colonneCurseurAffichage > _colonneCurseurAffichageMax) _colonneCurseurAffichage = _colonneCurseurAffichageMax;
        break;
    }
}

bool Partie::deroulement(Console* pConsole, Damier* damier, char tour, char adv)
{


    /// DECLARATION DES VARIABLES D'AFFICHAGE DU CURSEUR DU DAMIER

    //initialisation des valeurs constantes du sous-programme
    const int origineCurseurLigne = damier->getLigneAffichage()+2;
    const int origineCurseurColonne = damier->getColonneAffichage()+2;

    int ligneCurseurDamier, colonneCurseurDamier;
    int ligneCurseurAffichage, colonneCurseurAffichage;

    //ligne et colonne maximale d'affichage du curseur
    int ligneCurseurAffichageMax, colonneCurseurAffichageMax;
    int ligneCurseurDamierMax, colonneCurseurDamierMax;

    /// INITIALISATION DES VARIABLES

    ///DEBUT VARIABLES CURSEUR
    //coordonnées réelles de la case pointée par le curseur
    ligneCurseurDamier = 0;
    colonneCurseurDamier = 0;

    //coordonnées maximales de la case pointée par le curseur
    ligneCurseurDamierMax = damier->getTaille()-1;
    colonneCurseurDamierMax = damier->getTaille()-1;

    //ligne et colonne maximale d'affichage du curseur
    ligneCurseurAffichageMax = 2*damier->getTaille() + origineCurseurLigne-2;
    colonneCurseurAffichageMax = 3*(damier->getTaille() -1) + origineCurseurColonne;

    //coordonnées d'affichage du curseur
    ligneCurseurAffichage = origineCurseurLigne;
    colonneCurseurAffichage = origineCurseurColonne;


    bool rafraichirEcran = true; //pour rentrer dès le début dans la boucle d'affichage
    bool quitter=false;

    while(!quitter)
    {



        // GESTIONS DES EVENEMENTS CLAVIER
        if(pConsole->isKeyboardPressed())
        {
            //récupération de la touche sur laquelle l'utilisateur a appuyé
            char touche = pConsole->getInputKey();


            if(touche=='z'||touche=='s'||touche=='q'||touche=='d') //commandes de déplacement du curseur
            {
                Curseur::deplacer(touche, ligneCurseurDamier, colonneCurseurDamier, ligneCurseurAffichage, colonneCurseurAffichage,
                                  origineCurseurLigne, origineCurseurColonne, ligneCurseurAffichageMax, colonneCurseurAffichageMax,
                                  ligneCurseurDamierMax, colonneCurseurDamierMax);

                rafraichirEcran = true;
            }

            if(touche==32)
            {
                if(damier->getDamier()[ligneCurseurDamier][colonneCurseurDamier]=='.')
                {
                    damier->changement(tour, adv, ligneCurseurDamier, colonneCurseurDamier);
                    quitter=true;
                    damier->reset();
                }
            }

        }


        if(rafraichirEcran)
        {
            system("cls");

            pConsole->gotoLigCol(0, 0);



            pConsole->gotoLigCol(origineCurseurLigne-4, origineCurseurColonne);

            GfxInfos::afficherTour(pConsole, tour);
            GfxInfos::afficherScore(pConsole, damier);
            damier->afficher(pConsole);

            pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);

            rafraichirEcran = false;
        }

            //quitter=false;

    }

    system("cls");

return false;
}

bool Partie::verification(Damier* damier)
{
    bool ok=false;

    for(int i=0;i<damier->getTaille();i++)
    {
        for(int j=0;j<damier->getTaille();j++)
        {
            if(damier->getDamier()[i][j]=='.')
            {
                ok=true;
            }
        }
    }

    return ok;
}
