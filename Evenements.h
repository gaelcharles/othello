#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include "Damier.h"
#include "Constantes.h"
#include "Console.h"
#include "Affichage.h"

#include <iostream>
#include <windows.h>
#include <time.h>

namespace Curseur
{
    void deplacer(char _key, int& _ligneCurseurDamier, int& _colonneCurseurDamier, int& _ligneCurseurAffichage, int& _colonneCurseurAffichage,
                       int _origineCurseurLigne, int _origineCurseurColonne, int _ligneCurseurAffichageMax, int _colonneCurseurAffichageMax,
                       int _ligneCurseurDamierMax, int _colonneCurseurDamierMax);
}

namespace Partie
{
    bool TourJoueur(Console* pConsole, Damier* damier, char couleur_tour);
    bool CoupExistant(Damier* damier);
}


#endif // EVENEMENTS_H_INCLUDED
