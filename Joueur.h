#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

class Joueur
{
    private :
        bool m_couleur; // Couleur : true (blanc) / false (noir)
        int m_nombre_pions; // Nombre de pions sur le plateau d'un joueur donné
        bool m_IA; // Le joueur est-il un IA ? (true / false)
    public :
        // C & D
        Joueur(bool _couleur);
        ~Joueur();
};


#endif // JOUEUR_H_INCLUDED
