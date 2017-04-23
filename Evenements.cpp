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

    /// INITIALISATION DES VARIABLES DU CURSEUR DU DAMIER
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

    /// VARIABLES POUR L'ARBRE DE RECHERCHES
    std::vector<Etat*> arbre_recherche;

    int curseur_indice_etat = 0,
        curseur_indice_transition = 0;
    int delta_y = 0;

    int decalage_ligne = 0;
    Etat* pEtatTemporaire = NULL;

    /// VARIABLES DIVERSES
    bool rafraichir_ecran = true; //pour rentrer dès le début dans la boucle d'affichage
    bool continuer_tour=true;
    bool arbre_affiche = false; // L'arbre des possibilités doit-il être affiché ?
    int quitter = 0;
    char touche = 0;

    // Affichage du damier
    GfxDamier::Afficher(_pConsole, _pDamier);

    // Boucle de tour de jeu (sortie de boucle à la fin du tour)
    while(continuer_tour)
    {
        continuer_tour = true;

        if(!_pAllegro->IsAllegroActive()) // Si Allegro désactivé
        {
            // GESTIONS DES EVENEMENTS CLAVIER
            if(_pConsole->isKeyboardPressed())
            {
                //récupération de la touche sur laquelle l'utilisateur a appuyé
                touche = _pConsole->getInputKey();

                switch(touche)
                {
                // Appui sur Z/Q/S/D : Déplacement du curseur de plateau
                case 'Z': case 'Q': case 'S': case 'D':
                case 'z': case 'q': case 's': case 'd':

                    Curseur::deplacer(touche, ligneCurseurDamier, colonneCurseurDamier, ligneCurseurAffichage, colonneCurseurAffichage,
                                      origineCurseurLigne, origineCurseurColonne, ligneCurseurAffichageMax, colonneCurseurAffichageMax,
                                      ligneCurseurDamierMax, colonneCurseurDamierMax);

                    // Si lors d'une partie contre l'IA
                    if(mode >= 1)
                    {
                        // Si le curseur est placé sur un coup jouable, on affiche l'arbre
                        if(_pDamier->getDamier()[ligneCurseurDamier][colonneCurseurDamier] == COUP_JOUABLE)
                        {
                            arbre_affiche = true;
                            rafraichir_ecran = true;
                            system("cls");

                            curseur_indice_etat = 0;
                            curseur_indice_transition = 0;

                            // Reset de l'arbre affiché à chaque fois qu'on place le curseur sur un coup jouable
                            arbre_recherche.clear();

                            // Création de la racine de l'arbre à partir de ce nouvel état
                            arbre_recherche.push_back(new Etat(_pDamier, ligneCurseurDamier, colonneCurseurDamier, _couleur_tour));

                            // Sélection de la première arête de la racine
                            if(!arbre_recherche[0]->getAretes().empty())
                                arbre_recherche[0]->getAretes()[0]->selectionner(true); // On sélectionne la première arête (indice 0)

                            // Affichage de l'arbre
                            GfxInfos::AfficherArbreRecherche(_pConsole, arbre_recherche);
                        }
                        // Si on bouge le curseur sur une case voisine alors qu'on était sur un coup jouable, on enlève l'arbre
                        else if(_pDamier->getDamier()[ligneCurseurDamier][colonneCurseurDamier] != COUP_JOUABLE && arbre_affiche)
                        {
                            arbre_affiche = false;
                            rafraichir_ecran = true;
                            arbre_recherche.clear(); // Appelle également le destructeur de chaque état
                            system("cls");
                        }
                    }

                    _pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);
                    break;

                // Appui sur entrée : on veut jouer un coup
                case 13:
                    if(_pDamier->getDamier()[ligneCurseurDamier][colonneCurseurDamier]==COUP_JOUABLE)
                    {
                        _pDamier->ChangerCouleurPions(ligneCurseurDamier, colonneCurseurDamier, _couleur_tour);
                        continuer_tour=false;
                        _pDamier->ReinitialiserPossibilites();
                        rafraichir_ecran = true;
                    }
                    break;

                // Appui sur échap : menu pause
                case 27:
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
                    break;

                // Appui sur les flèches directionnelles : déplacement du curseur de l'arbre de recherche
                case FLECHE_HAUT: case FLECHE_BAS: case FLECHE_GAUCHE: case FLECHE_DROITE:
                    // Si l'arbre est affiché
                    if(!arbre_recherche.empty() && arbre_affiche)
                    {
                        // Flèche haut ou bas : déplacement du curseur parmi les transitions possibles
                        if(touche == FLECHE_HAUT || touche == FLECHE_BAS)
                        {
                            switch(touche)
                            {
                            case FLECHE_HAUT: delta_y = -1; break;
                            case FLECHE_BAS : delta_y =  1; break;
                            }

                            // On récupère l'indice de l'arête sélectionnée
                            curseur_indice_transition = arbre_recherche[curseur_indice_etat]->getIndiceTransitionSelectionnee();

                            if(curseur_indice_transition+delta_y >= 0 && (unsigned int)(curseur_indice_transition+delta_y) < arbre_recherche[curseur_indice_etat]->getAretes().size())
                            {
                                // On déselectionne cette arête
                                arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition]->selectionner(false);

                                // On sélectionne l'arête adjacente
                                arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition+delta_y]->selectionner(true);

                                // On incrémente
                                curseur_indice_transition += delta_y;

                                // On met à jour graphiquement
                                arbre_recherche[curseur_indice_etat]->AfficherEtat(_pConsole, curseur_indice_etat);
                            }
                        }
                        // Flèche droite : génération d'un nouvel état à partir de la transition actuellement sélectionnée
                        else if(touche == FLECHE_DROITE && curseur_indice_etat+1 < 3 && mode == 2)
                        {
                            // On crée l'état généré par la transition sélectionnée (le noeud relié à l'arête sélectionnée)
                            // On l'ajoute comme étant une feuille de l'arbre de recherche
                            arbre_recherche.push_back(new Etat(arbre_recherche[curseur_indice_etat]->getSituationDamier(),
                                                          (int)arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition]->getPos().X,
                                                          (int)arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition]->getPos().Y,
                                                               arbre_recherche[curseur_indice_etat]->getTour()));

                            // On déplace le curseur sur ce nouvel état
                            curseur_indice_etat++;
                            curseur_indice_transition = 0;

                            if(arbre_recherche.size() % 3 == 0) // Tous les 3 états, retour à la ligne
                                decalage_ligne++;

                            // On sélectionne la première transition de ce nouvel état
                            arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition]->selectionner(true);
                            arbre_recherche[curseur_indice_etat]->AfficherEtat(_pConsole, curseur_indice_etat);
                        }
                        // Flèche gauche : Retour à l'état précédent
                        else if(touche == FLECHE_GAUCHE && curseur_indice_etat-1 >= 0 && mode == 2)
                        {
                            // Suppression de la feuille de l'arbre de recherches
                            arbre_recherche.pop_back(); // Appelle également le destructeur de Etat

                            // On déselectionne l'ancienne transition
                            arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition]->selectionner(false);

                            // On enlève l'affichage de cet état
                            arbre_recherche[curseur_indice_etat]->DesafficherEtat(_pConsole, curseur_indice_etat);

                            // Décrémentation du curseur
                            curseur_indice_etat--;
                            curseur_indice_transition = 0;

                            if(arbre_recherche.size() % 3 == 0) // Tous les 3 états, on remonte à la ligne d'avant
                                decalage_ligne--;

                            // On sélectionne l'ancienne arête sélectionnée
                            arbre_recherche[curseur_indice_etat]->getAretes()[arbre_recherche[curseur_indice_etat]->getIndiceTransitionSelectionnee()]->selectionner(true);

                            // On réaffiche l'état d'avant pour mettre à jour
                            arbre_recherche[curseur_indice_etat]->AfficherEtat(_pConsole, curseur_indice_etat);
                        }
                        rafraichir_ecran = true;

                        // Affichage du damier de la transition sélectionnée
                        pEtatTemporaire = new Etat(arbre_recherche[curseur_indice_etat]->getSituationDamier(),
                                                          (int)arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition]->getPos().X,
                                                          (int)arbre_recherche[curseur_indice_etat]->getAretes()[curseur_indice_transition]->getPos().Y,
                                                               arbre_recherche[curseur_indice_etat]->getTour());

                        pEtatTemporaire->getSituationDamier()->AfficherPetitDamier(_pConsole, 1, 45);
                    }
                    break;

                // Appui sur G : ouverture du mode graphique
                case 'G': case 'g':
                    _pAllegro->OuvertureModeGraphique(1280, 720);
                    break;

                default : {}
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
