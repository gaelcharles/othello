#include <conio.h>

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

int Partie::TourJoueur(int mode, Console* _pConsole, Damier* _pDamier, FenetreAllegro* _pAllegro, char _couleur_tour)
{
    /// DECLARATION DES VARIABLES D'AFFICHAGE DU CURSEUR DU DAMIER

    //initialisation des valeurs constantes du sous-programme
    const int origineCurseurLigne = _pDamier->getLigneAffichage()+1;
    const int origineCurseurColonne = _pDamier->getColonneAffichage()+2;

    int ligneCurseurDamier, colonneCurseurDamier;
    int ligneCurseurAffichage, colonneCurseurAffichage;

    //ligne et colonne maximale d'affichage du curseur
    int ligneCurseurAffichageMax, colonneCurseurAffichageMax;
    int ligneCurseurDamierMax, colonneCurseurDamierMax;

    /// INITIALISATION DES VARIABLES

    /// DEBUT VARIABLES CURSEUR
    //coordonnées réelles de la case pointée par le curseur
    ligneCurseurDamier = 0;
    colonneCurseurDamier = 0;

    //coordonnées maximales de la case pointée par le curseur
    ligneCurseurDamierMax = _pDamier->getTaille()-1;
    colonneCurseurDamierMax = _pDamier->getTaille()-1;

    //ligne et colonne maximale d'affichage du curseur
    ligneCurseurAffichageMax = 2*_pDamier->getTaille() + origineCurseurLigne-2;
    colonneCurseurAffichageMax = 4*(_pDamier->getTaille() -1) + origineCurseurColonne;

    //coordonnées d'affichage du curseur
    ligneCurseurAffichage = origineCurseurLigne;
    colonneCurseurAffichage = origineCurseurColonne;

    bool rafraichir_ecran = true; //pour rentrer dès le début dans la boucle d'affichage
    bool continuer_tour=true;
    int quitter = 0;
    char touche = 0;

    GfxDamier::Afficher(_pConsole, _pDamier);

    while(continuer_tour)
    {
        continuer_tour = true;

        if(!_pAllegro->IsAllegroActive()) // Allegro désactivé
        {
            // GESTIONS DES EVENEMENTS CLAVIER
            if(_pConsole->isKeyboardPressed())
            {
                /// NOTE : faire un switch
                //récupération de la touche sur laquelle l'utilisateur a appuyé
                touche = _pConsole->getInputKey();

                if(touche=='z' || touche=='s' || touche=='q' || touche=='d') //commandes de déplacement du curseur
                {
                    Curseur::deplacer(touche, ligneCurseurDamier, colonneCurseurDamier, ligneCurseurAffichage, colonneCurseurAffichage,
                                      origineCurseurLigne, origineCurseurColonne, ligneCurseurAffichageMax, colonneCurseurAffichageMax,
                                      ligneCurseurDamierMax, colonneCurseurDamierMax);

                    _pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);
                }

                if(touche==13 && _pDamier->getDamier()[ligneCurseurDamier][colonneCurseurDamier]==COUP_JOUABLE)
                {
                    _pDamier->ChangerCouleurPions(ligneCurseurDamier, colonneCurseurDamier, _couleur_tour);
                    continuer_tour=false;
                    _pDamier->ReinitialiserPossibilites();
                    rafraichir_ecran = true;
                }

                if(touche == 27) //si on appuie sur ECHAP
                {
                    //ouvre le menu ECHAP
                    quitter=GfxMenu::Echap(_pConsole, mode, _pDamier, _couleur_tour);

                    //si le joueur veut quitter
                    if(quitter)
                    {
                        continuer_tour=false;
                        rafraichir_ecran=false;
                    }
                    else //s'il veut juste reprendre le jeu
                    {
                        continuer_tour=true;
                        rafraichir_ecran=true;
                    }
                }

                // Ouverture du mode graphique
                if((touche == 'g' || touche == 'G'))
                {
                    _pAllegro->OuvertureModeGraphique(1280, 720);
                }
            }
        }
        else // Allegro activé
        {
            // Gestion des événements clavier en mode graphique
            if(keypressed())
            {
                touche = (char)readkey();

                switch(touche)
                {
                // Z-Q-S-D : Déplacement du curseur
                case 'Z': case 'Q': case 'S': case 'D':
                case 'z': case 'q': case 's': case 'd':
                    _pAllegro->DeplacerCurseur(touche);
                    break;

                // G : Basculement mode graphique
                case 'G': case 'g':
                    _pAllegro->FermetureModeGraphique();
                    break;

                // Entree : Jouer le coup
                case 13:
                    if(_pDamier->getDamier()[_pAllegro->curseur().Y][_pAllegro->curseur().X] == COUP_JOUABLE)
                    {
                        _pDamier->ReinitialiserPossibilites();
                        _pDamier->ChangerCouleurPions(_pAllegro->curseur().Y, _pAllegro->curseur().X, _couleur_tour);
                        continuer_tour = false;
                        rafraichir_ecran = true;
                    }
                    break;

                default : {}
                }
            }
        }
        // Fin de boucle : affichages
        if(rafraichir_ecran) // Affichages
        {
            _pConsole->gotoLigCol(origineCurseurLigne-4, origineCurseurColonne);

            GfxInfos::AfficherTour(_pConsole, _couleur_tour);
            GfxInfos::AfficherScore(_pConsole, _pDamier);
            _pDamier->Afficher(_pConsole);

            _pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);

            rafraichir_ecran = false;
        }

        if(_pAllegro->IsAllegroActive())
            _pAllegro->AfficherFenetreGraphique(_pDamier, _couleur_tour);
    }
    system("cls");

    return quitter;
}

bool Partie::CoupExistant(Damier* _pDamier)
{
    bool coup_existant = false; //true: le joueur peut jouer | false: le joueur n'a aucun coup disponible

    for(int i=0 ; i<_pDamier->getTaille() ; i++)
    {
        for(int j=0 ; j<_pDamier->getTaille() ; j++)
        {
            if(_pDamier->getDamier()[i][j] == COUP_JOUABLE) //si il existe une case jouable pour le joueur
            {
                coup_existant = true;
                break; //sortie de la premiere boucle
            }
        }
        if(coup_existant) break; //sortie de la seconde boucle
    }

    return coup_existant;
}

void Partie::Sauvegarde(Damier* _pDamier, int mode, char _couleur_tour)
{

    std::ofstream fichier("partie.txt", std::ios::out | std::ios::trunc);

    if(fichier)
    {
        _pDamier->ReinitialiserPossibilites();

        fichier << mode << " " << _couleur_tour << " " << _pDamier->getTaille() << std::endl;

        for(int i=0; i<_pDamier->getTaille() ; i++)
        {
            for(int j=0; j<_pDamier->getTaille(); j++)
            {
                if(_pDamier->getDamier()[i][j]!=' ')
                    fichier << _pDamier->getDamier()[i][j] << " " ;
                else
                    fichier << '0' << " ";
            }
            fichier << std::endl;
        }
        fichier.close();
    }
    else
    {
        std::cerr << "Erreur : le fichier n'a pas pu etre lu." << std::endl;
    }
}
