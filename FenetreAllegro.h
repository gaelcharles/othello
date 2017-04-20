#ifndef FENETREALLEGRO_H_INCLUDED
#define FENETREALLEGRO_H_INCLUDED

#include <allegro.h>
#include "Damier.h"

class FenetreAllegro
{
    private :
        bool m_allegro_active;
        BITMAP* m_buffer;
        BITMAP* bmp_plateau;

    public :
        // C & D
        FenetreAllegro();
        ~FenetreAllegro();

        // Méthodes
        void OuvertureModeGraphique(int res_x, int res_y, bool usemouse);
        void FermetureModeGraphique();
        bool IsAllegroActive() const;
        BITMAP* ChargerBitmap(const char* filename);
        BITMAP* buffer() const;

        void AfficherDamier(Damier* pDamier, char tour, int marge = 50);
};


#endif // FENETREALLEGRO_H_INCLUDED
