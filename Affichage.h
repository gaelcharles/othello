#include "Console.h"
#include "Damier.h"
#include "IA.h"

#include <iostream>

namespace GfxDamier
{
    void afficher(Console* _pConsole, Damier* _pDamier);
    void afficherContenu(Console* _pConsole, Damier* _pDamier);
}

namespace GfxInfos
{
    void afficherTour(Console* _pConsole, char tour);
    void afficherScore(Console* _pConsole, Damier* _pDamier);
}

namespace GfxFin
{
    void afficherFin(Damier* _pDamier);
}

namespace GfxMenu
{
    int afficher(Console* _pConsole, IA* _bot);
}
