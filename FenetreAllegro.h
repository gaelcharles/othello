#ifndef FENETREALLEGRO_H_INCLUDED
#define FENETREALLEGRO_H_INCLUDED

#include <allegro.h>
#include <winalleg.h>
#include "Damier.h"

class FenetreAllegro
{
    private :
        bool m_allegro_active;
        BITMAP* m_buffer;
        BITMAP* m_plateau;
        COORD m_curseur;

    public :
        // C & D
        FenetreAllegro();
        ~FenetreAllegro();

        // Getters
        bool IsAllegroActive() const;
        BITMAP* buffer() const;
        COORD curseur() const;

        // Méthodes
        void OuvertureModeGraphique(int res_x, int res_y);
        void FermetureModeGraphique();
        BITMAP* ChargerBitmap(const char* filename);
        void DeplacerCurseur(char direction);

        void AfficherDamier(Damier* pDamier, char tour);
        void AfficherCurseur();
        void AfficherInfos(Damier* pDamier, char tour);
        void AfficherFenetreGraphique(Damier* pDamier, char tour);
};


#endif // FENETREALLEGRO_H_INCLUDED
