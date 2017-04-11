#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include "Damier.h"

#include "console.h"
#include "Affichage.h"

#include <iostream>
#include <windows.h>
#include <time.h>

#define LIGNE_AFFICHAGE 8
#define COLONNE_AFFICHAGE 7

namespace Curseur
{
    void deplacer(char _key, int& _ligneCurseurDamier, int& _colonneCurseurDamier, int& _ligneCurseurAffichage, int& _colonneCurseurAffichage,
                       int _origineCurseurLigne, int _origineCurseurColonne, int _ligneCurseurAffichageMax, int _colonneCurseurAffichageMax,
                       int _ligneCurseurDamierMax, int _colonneCurseurDamierMax);
}

namespace Partie
{
    bool deroulement(Console* pConsole, Damier* damier, char tour, char adv);
    bool verification(Damier* damier);
}


#endif // EVENEMENTS_H_INCLUDED
