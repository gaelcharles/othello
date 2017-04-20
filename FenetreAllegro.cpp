#include "FenetreAllegro.h"
#include "Constantes.h"

// Constructeur
FenetreAllegro::FenetreAllegro() :
    m_allegro_active(false), m_buffer(NULL)
{
}

// Destructeur
FenetreAllegro::~FenetreAllegro()
{
}

// Méthodes
void FenetreAllegro::OuvertureModeGraphique(int res_x, int res_y, bool usemouse)
{
    allegro_init();
    install_keyboard();
    if(usemouse)
        install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,res_x,res_y,0,0)!=0)
    {
        allegro_message("Probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    m_allegro_active = true;
    m_buffer = create_bitmap(SCREEN_W, SCREEN_H);
    bmp_plateau = ChargerBitmap("bitmaps/plateau.bmp");
}

void FenetreAllegro::FermetureModeGraphique()
{
    m_allegro_active = false;
    destroy_bitmap(m_buffer);
    allegro_exit();
}

bool FenetreAllegro::IsAllegroActive() const
{
    return m_allegro_active;
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

BITMAP* FenetreAllegro::buffer() const
{
    return m_buffer;
}

void FenetreAllegro::AfficherDamier(Damier* pDamier, char tour, int marge)
{
    // Fond vert
    clear_to_color(m_buffer, ALLEG_COULEUR_PALE);

    // Bordures
//    rectfill(m_buffer, marge-50, marge-50, marge+50+ALLEG_TCASE*TAILLE_PLATEAU, marge+50+ALLEG_TCASE*TAILLE_PLATEAU, ALLEG_COULEUR_MARRON);
//    rectfill(m_buffer, marge, marge, marge+ALLEG_TCASE*TAILLE_PLATEAU, marge+ALLEG_TCASE*TAILLE_PLATEAU, ALLEG_COULEUR_VERT);
    blit(bmp_plateau, m_buffer, 0, 0, 0, 0, bmp_plateau->w, bmp_plateau->h);

    // Lignes de plateau
    for(int i(0) ; i<=TAILLE_PLATEAU ; i++)
    {
        line(m_buffer, marge+i*ALLEG_TCASE, marge, marge+i*ALLEG_TCASE, marge+ALLEG_TCASE*TAILLE_PLATEAU, 0xFFFFFF);
        line(m_buffer, marge, marge+i*ALLEG_TCASE, marge+ALLEG_TCASE*TAILLE_PLATEAU, marge+i*ALLEG_TCASE, 0xFFFFFF);
    }

    for(int j(0) ; j<TAILLE_PLATEAU ; j++)
    {
        for(int i(0) ; i<TAILLE_PLATEAU ; i++)
        {
            switch(pDamier->getDamier()[i][j])
            {
            case NOIR:
                circlefill(m_buffer, marge+i*ALLEG_TCASE+ALLEG_TCASE/2, marge+j*ALLEG_TCASE+ALLEG_TCASE/2, 20, 0x000000);
                break;

            case BLANC:
                circlefill(m_buffer, marge+i*ALLEG_TCASE+ALLEG_TCASE/2, marge+j*ALLEG_TCASE+ALLEG_TCASE/2, 20, 0xFFFFFF);
                break;

            case COUP_JOUABLE:
                circlefill(m_buffer, marge+i*ALLEG_TCASE+ALLEG_TCASE/2, marge+j*ALLEG_TCASE+ALLEG_TCASE/2, 5, 0xFF0000);
                break;

            default : {}
            }

        }
    }
}
