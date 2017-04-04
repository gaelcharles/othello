/// BIBLIOTHEQUES INITIALES ///

#include <iostream>
#include <windows.h>

/// BIBLIOTHEQUES PERSONNELLES ///

#include "Jeu.h"
#include "Graphics.h"
#include "Constantes.h"

using namespace std;

int main()
{
    // Variables du main
    Jeu g;

    DEFAULT_COLOR;
    system("cls");

    // Boucle de jeu
    g.getDamier().Afficher();
    system("pause");
    return 0;
}
