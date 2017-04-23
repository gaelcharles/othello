#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include "Damier.h"
#include "Constantes.h"
#include "Console.h"
#include "Affichage.h"
#include "FenetreAllegro.h"
#include "Arbre.h"

#include <vector>
#include <iostream>
#include <allegro.h>
#include <winalleg.h>
#include <time.h>
#include <fstream>

namespace Curseur
{
    void deplacer(char _key, int& _ligneCurseurDamier, int& _colonneCurseurDamier, int& _ligneCurseurAffichage, int& _colonneCurseurAffichage,
                       int _origineCurseurLigne, int _origineCurseurColonne, int _ligneCurseurAffichageMax, int _colonneCurseurAffichageMax,
                       int _ligneCurseurDamierMax, int _colonneCurseurDamierMax);
}

namespace Partie
{
    int TourJoueur(int mode, Console* _pConsole, Damier* _pDamier, FenetreAllegro* pAllegro, char _couleur_tour);
    bool CoupExistant(Damier* _pDamier);
    void Sauvegarde(Damier* _pDamier, int mode, char _couleur_tour);

}


#endif // EVENEMENTS_H_INCLUDED
