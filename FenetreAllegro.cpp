#include "FenetreAllegro.h"
#include "Constantes.h"

// Constructeur
FenetreAllegro::FenetreAllegro() :
    m_allegro_active(false), m_buffer(NULL)
{
    m_curseur.X = 0;
    m_curseur.Y = 0;
}

// Destructeur
FenetreAllegro::~FenetreAllegro()
{
}

// Méthodes
void FenetreAllegro::OuvertureModeGraphique(int res_x, int res_y)
{
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,res_x,res_y,0,0)!=0)
    {
        allegro_message("Probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
    set_keyboard_rate(400, 80);

    m_allegro_active = true;
    m_buffer = create_bitmap(SCREEN_W, SCREEN_H);
    m_plateau = ChargerBitmap("bitmaps/plateau.bmp");
}

void FenetreAllegro::FermetureModeGraphique()
{
    m_allegro_active = false;
    destroy_bitmap(m_buffer);
    allegro_exit();
}

BITMAP* FenetreAllegro::ChargerBitmap(const char* filename)
{
    BITMAP* bmp = NULL;
    bmp = load_bitmap(filename, NULL);
    if(!bmp)
    {
        allegro_message("Impossible d'ouvrir le fichier %s", filename);
        allegro_exit();
        exit(1);
    }

    return bmp;
}

bool FenetreAllegro::IsAllegroActive() const
{
    return m_allegro_active;
}

BITMAP* FenetreAllegro::buffer() const
{
    return m_buffer;
}

COORD FenetreAllegro::curseur() const
{
    return m_curseur;
}

void FenetreAllegro::DeplacerCurseur(char direction)
{
    switch(direction)
    {
    case 'Z':
    case 'z':
        m_curseur.Y--;
        if(m_curseur.Y < 0) m_curseur.Y = 0;
        break;

    case 'Q':
    case 'q':
        m_curseur.X--;
        if(m_curseur.X < 0) m_curseur.X = 0;
        break;

    case 'S':
    case 's':
        m_curseur.Y++;
        if(m_curseur.Y >= TAILLE_PLATEAU) m_curseur.Y = TAILLE_PLATEAU-1;
        break;

    case 'D':
    case 'd':
        m_curseur.X++;
        if(m_curseur.X >= TAILLE_PLATEAU) m_curseur.X = TAILLE_PLATEAU-1;
        break;

    default : {}
    }

}

void FenetreAllegro::AfficherCurseur(int marge)
{
    rectfill(m_buffer, marge+m_curseur.X*ALLEG_TCASE+1, marge+m_curseur.Y*ALLEG_TCASE+1, marge+m_curseur.X*ALLEG_TCASE+ALLEG_TCASE-1, marge+m_curseur.Y*ALLEG_TCASE+ALLEG_TCASE-1, 0x00FF00);
}

void FenetreAllegro::AfficherDamier(Damier* pDamier, char tour, int marge)
{
    // Bordures
    masked_blit(m_plateau, m_buffer, 0, 0, marge-50, marge-50, m_plateau->w, m_plateau->h);

    // Lignes de plateau
    for(int ligne(0) ; ligne<=TAILLE_PLATEAU ; ligne++)
    {
        line(m_buffer, marge+ligne*ALLEG_TCASE, marge, marge+ligne*ALLEG_TCASE, marge+ALLEG_TCASE*TAILLE_PLATEAU, 0xFFFFFF);
        line(m_buffer, marge, marge+ligne*ALLEG_TCASE, marge+ALLEG_TCASE*TAILLE_PLATEAU, marge+ligne*ALLEG_TCASE, 0xFFFFFF);
    }

    for(int ligne(0) ; ligne<TAILLE_PLATEAU ; ligne++)
    {
        for(int colonne(0) ; colonne<TAILLE_PLATEAU ; colonne++)
        {
            switch(pDamier->getDamier()[ligne][colonne])
            {
            case NOIR:
                circlefill(m_buffer, marge+colonne*ALLEG_TCASE+ALLEG_TCASE/2, marge+ligne*ALLEG_TCASE+ALLEG_TCASE/2, 20, 0x000000);
                break;

            case BLANC:
                circlefill(m_buffer, marge+colonne*ALLEG_TCASE+ALLEG_TCASE/2, marge+ligne*ALLEG_TCASE+ALLEG_TCASE/2, 20, 0xFFFFFF);
                circle(m_buffer, marge+colonne*ALLEG_TCASE+ALLEG_TCASE/2, marge+ligne*ALLEG_TCASE+ALLEG_TCASE/2, 20, 0x000000);
                break;

            case COUP_JOUABLE:
                circlefill(m_buffer, marge+colonne*ALLEG_TCASE+ALLEG_TCASE/2, marge+ligne*ALLEG_TCASE+ALLEG_TCASE/2, 5, 0xFF0000);
                break;

            default : {}
            }
        }
    }
}

void FenetreAllegro::AfficherInfos(Damier* pDamier, char tour, int marge)
{
    textprintf_ex(m_buffer, font, marge-20, marge+TAILLE_PLATEAU*ALLEG_TCASE+90, 0x000000, -1, "Tour : ");
    circlefill(m_buffer, marge+75, marge+TAILLE_PLATEAU*ALLEG_TCASE+90, 15, (tour == NOIR) ? 0x000000 : 0xFFFFFF);
    circle(m_buffer, marge+75, marge+TAILLE_PLATEAU*ALLEG_TCASE+90, 15, 0x000000);

    textprintf_ex(m_buffer, font, marge-20, marge+TAILLE_PLATEAU*ALLEG_TCASE+120, 0xFFFFFF, 0x000000, "%d pions noirs",  pDamier->comptagePions(NOIR));
    textprintf_ex(m_buffer, font, marge-20, marge+TAILLE_PLATEAU*ALLEG_TCASE+135, 0x000000, 0xFFFFFF, "%d pions blancs", pDamier->comptagePions(BLANC));
}

void FenetreAllegro::AfficherFenetreGraphique(Damier* pDamier, char tour, int marge_plateau)
{
    // Reset buffer
    clear_bitmap(m_buffer);

    // Fond vert pâle
    clear_to_color(m_buffer, ALLEG_COULEUR_PALE);

    // Fond du plateau (sous le curseur)
    rectfill(m_buffer, marge_plateau, marge_plateau, marge_plateau+TAILLE_PLATEAU*ALLEG_TCASE, marge_plateau+TAILLE_PLATEAU*ALLEG_TCASE, ALLEG_COULEUR_VERT);

    AfficherCurseur();
    AfficherDamier(pDamier, tour, marge_plateau);
    AfficherInfos(pDamier, tour, marge_plateau);
    blit(m_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
