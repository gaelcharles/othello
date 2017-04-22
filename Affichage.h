#include "Console.h"
#include "Damier.h"
#include "IA.h"

#include <iostream>

namespace GfxDamier
{
    void Afficher(Console* _pConsole, Damier* _pDamier);
    void AfficherContenu(Console* _pConsole, Damier* _pDamier);
}

namespace GfxInfos
{
    void AfficherTour(Console* _pConsole, char tour);
    void AfficherScore(Console* _pConsole, Damier* _pDamier);
}

namespace GfxFin
{
    void AfficherFin(Damier* _pDamier);
}

namespace GfxMenu
{
    int Afficher(Damier* damier, Console* _pConsole, IA* _bot, char& _couleur_tour);
    int Echap(Console* _pConsole, int mode, Damier* d, char _couleur_tour);
}
