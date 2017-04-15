#include "Console.h"
#include "Damier.h"

#include <iostream>
#include <stack>


namespace GfxDamier
{
void afficher(Console* _pConsole, Damier* _pDamier);

//void afficherColonnes(Console* _pConsole,  int _nbColonnes, int _ligneAffichage, int _colonneAffichage);
//
//void afficherLignes(Console* _pConsole, int _nbLignes, int _nbColonnes, int _ligneAffichage, int _colonneAffichage, int _origneAffichageLigne);
//
//void afficherBordSup(Console* _pConsole,  int _nbColonnes, int _ligneAffichage, int _colonneAffichage);
//
//void afficherBordInf(Console* _pConsole,  int _nbColonnes, int _ligneAffichage, int _colonneAffichage);

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
