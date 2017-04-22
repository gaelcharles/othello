#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <iostream>

typedef enum EnumColors
{
    COULEUR_NOIR,
    COULEUR_BLEU_FONCE,
    COULEUR_VERT,
    COULEUR_BLEU_VERT,
    COULEUR_MARRON,
    COULEUR_VIOLET,
    COULEUR_OR,
    COULEUR_GRIS_CLAIR,
    COULEUR_GRIS,
    COULEUR_BLEU,
    COULEUR_VERT_CLAIR,
    COULEUR_CYAN,
    COULEUR_ROUGE,
    COULEUR_ROSE,
    COULEUR_JAUNE,
    COULEUR_BLANC
}e_color;

class Console
{
    private:
        // Empecher la création
        Console();
        ~Console();

        // Empecher la copie d'objet...
        Console& operator= (const Console&){ return *this;}
        Console (const Console&){}

        // Attributs
        static Console* m_instance;

    public:
        // Méthodes statiques (publiques)
        static Console* getInstance();
        static void deleteInstance();

        // Méthodes publiques
        void gotoLigCol(int lig, int col);
        void gotoDamierXY(int x, int y);

        bool isKeyboardPressed();
        int getInputKey();

        void setColor(e_color texte, e_color fond);
        void espacer(int espacement);
//        void

};

#endif // CONSOLE_H_INCLUDED
