#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "Damier.h"
#include "Joueur.h"

class Jeu
{
    private :
        Damier m_damier; // Le damier de jeu
        Joueur m_J1; // Premier joueur
        Joueur m_J2; // Deuxième joueur
        int m_tour_id; // Indice du tour
    public :
        // C & D
        Jeu();
        ~Jeu();
};


#endif // JEU_H_INCLUDED
