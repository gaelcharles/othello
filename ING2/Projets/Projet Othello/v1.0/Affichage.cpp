#include "Affichage.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <MMsystem.h>

/// FONCTIONS D'AFFICHAGE DU DAMIER

void GfxDamier::afficher(Console* _pConsole, Damier* _pDamier)
{
    /// DECLARATION DES VARIABLES

    //initialisation des valeurs constantes du sous-programme
    const int origineAffichageLigne = _pDamier->getLigneAffichage();
    const int origineAffichageColonne = _pDamier->getColonneAffichage();

    const int nbLignes = _pDamier->getTaille();
    const int nbColonnes = _pDamier->getTaille();

    //entiers liés à la position du curseur d'affichage
    int ligneAffichage;
    int colonneAffichage;

    /// INITIALISATION DES VALEURS DES VARIABLES

    //affectation des valeur des coordonnées d'affichage des bordures des cases du damier
    ligneAffichage = origineAffichageLigne;
    colonneAffichage = origineAffichageColonne;

    /// DEBUT DE L'AFFICHAGE DU DAMIER

    /// -> Affichage des colonnes du damier
    afficherColonnes(_pConsole, nbColonnes, origineAffichageLigne, origineAffichageColonne);

    //on saute une ligne pour l'affichage
    ligneAffichage++;
    //positionnement du curseur
    _pConsole->gotoLigCol(ligneAffichage, colonneAffichage);

    /// -> Affichage de la bordure supérieure

    afficherBordSup(_pConsole,  nbColonnes, ligneAffichage, colonneAffichage);

    //on saute une ligne pour l'affichage
    ligneAffichage++;
    //on réinitialise la colonne d'affichage
    colonneAffichage = origineAffichageColonne;
    //positionnement du curseur
    _pConsole->gotoLigCol(ligneAffichage, colonneAffichage);

    /// -> Affichage des lignes du damier

    //affichage des lignes génériques du damier

    afficherLignes(_pConsole, nbLignes, nbColonnes, ligneAffichage, colonneAffichage, origineAffichageColonne);

    //on saute une ligne pour l'affichage
    ligneAffichage+=nbLignes*2-1;
    //on réinitialise la colonne d'affichage
    colonneAffichage = origineAffichageColonne;
    //positionnement du curseur
    _pConsole->gotoLigCol(ligneAffichage, colonneAffichage);

    /// -> Affichage de la bordure inférieure du damier

    //positionement du curseur
    _pConsole->gotoLigCol(ligneAffichage, colonneAffichage);

    afficherBordInf(_pConsole, nbColonnes, ligneAffichage, colonneAffichage);

    /// FIN DE L'AFFICHAGE DU DAMIER
}

void GfxDamier::afficherColonnes(Console* _pConsole,  int _nbColonnes, int _ligneAffichage, int _colonneAffichage)
{
    //affichage du nombre de lignes du damier
    std::ostringstream oss;

    for(char i='A'; i<'A'+_nbColonnes; i++)
    {
        oss << "  " << i;
    }
    //positionnement du curseur
    _pConsole->gotoLigCol(_ligneAffichage, _colonneAffichage);
    //affichage des numéros des colonnes
    std::cout << oss.str();
}

void GfxDamier::afficherLignes(Console* _pConsole, int _nbLignes, int _nbColonnes, int _ligneAffichage, int _colonneAffichage, int _origineAffichageColonne)
{
    int lettreLigne;
     //lettre correspodant à la première ligne de cases du damier
    lettreLigne = 1;

    for(int i=2; i<_nbLignes*2+1;  i++)
    {
        if(i%2 == 0) //ligne paire
        {
            //positionnement du curseur
            _pConsole->gotoLigCol(_ligneAffichage, _colonneAffichage);

            //affichage de la lettre et de la bordure gauche de la premiere case de la ligne
            std::cout << lettreLigne << char(179);
            //repositionnement du curseur
            _colonneAffichage+=2;

            for(int j=1; j<=_nbColonnes; j++)
            {
                //positionnement du curseur
                _pConsole->gotoLigCol(_ligneAffichage, _colonneAffichage);

                std::cout << " " << " " << char(179);
                _colonneAffichage+=3;
            }

            //on réinitialise la valeur de la colonne d'affichage
            _colonneAffichage = _origineAffichageColonne;
            //on saute une ligne pour l'affichage
            _ligneAffichage++;

            //on change la lettre de la ligne correspondante
            lettreLigne++;
        }
        else //ligne impaire
        {
            //positionnement du curseur
            _pConsole->gotoLigCol(_ligneAffichage, _colonneAffichage);

            //affichage de la lettre et de la bordure gauche de la premiere case de la ligne
            std::cout << " " << char(195);
            //repositionnement du curseur
            _colonneAffichage+=2;

            for(int k=1; k<=_nbColonnes; k++)
            {
                //positionnement du curseur
                _pConsole->gotoLigCol(_ligneAffichage, _colonneAffichage);

                std::cout << char(196) << char(196);
                //si on doit afficher la case de la dernière colonne
                if(k==_nbColonnes) std::cout << char(180);
                else std::cout << char(197);

                _colonneAffichage+=3;

            }

            //on réinitialise la valeur de la colonne d'affichage
            _colonneAffichage = _origineAffichageColonne;
            //on saute une ligne pour l'affichage
            _ligneAffichage++;
        }
    }
}

void GfxDamier::afficherBordSup(Console* _pConsole,  int _nbColonnes, int _ligneAffichage, int _colonneAffichage)
{
    //affichage des deux premiers caractères de la bordure
    std::cout << " " << char(218);
    //positionnement la colonne d'affichage
    _colonneAffichage+=2;

    //boucle d'affichage du reste de la bordure supérieure
    for(int i=1; i<=_nbColonnes; i++)
    {
        //positionement du curseur
        _pConsole->gotoLigCol(_ligneAffichage, _colonneAffichage);
        std::cout << char(196) << char(196);
        //fin de bordure de case differente si c'est la derniere de la ligne
        if(i==_nbColonnes) std::cout << char(191);
        else std::cout << char(194);
        //on repositionne la colonne d'affichage
        _colonneAffichage +=3;
    }
}

void GfxDamier::afficherBordInf(Console* _pConsole,  int _nbColonnes, int _ligneAffichage, int _colonneAffichage)
{
    std::cout << " " << char(192);
    //positionnement la colonne d'affichage
    _colonneAffichage+=2;

    for(int i=1; i<=_nbColonnes; i++)
    {
        //positionement du curseur
        _pConsole->gotoLigCol(_ligneAffichage, _colonneAffichage);
        std::cout << char(196) << char(196);
        //fin de bordure de case differente si c'est la derniere de la ligne
        if(i==_nbColonnes) std::cout << char(217);
        else std::cout << char(193);
        //on repositionne la colonne d'affichage
        _colonneAffichage +=3;
    }
}

void GfxDamier::afficherContenu(Console* _pConsole, Damier* _pDamier)
{

    /// DECLARATION DES VARIABLES

    //initialisation des valeurs constantes du sous-programme
    const int origineAffichageLigne = _pDamier->getLigneAffichage()+2;
    const int origineAffichageColonne = _pDamier->getColonneAffichage()+2;

    const int nbLignes = _pDamier->getTaille();
    const int nbColonnes = _pDamier->getTaille();

    std::vector< std::vector<char> > damier;

    //entiers liés à la position du curseur d'affichage
    int ligneAffichage;
    int colonneAffichage;

    /// INITIALISATION DES VALEURS DES VARIABLES

    //on récupère le contenu du damier
    damier = _pDamier->getDamier();

    //affectation des valeur des coordonées d'affichage du contenu des cases du damier
    ligneAffichage = origineAffichageLigne;
    colonneAffichage = origineAffichageColonne;

    /// AFFICHAGE DU CONTENU DES CASES DU DAMIER

    //positionnement du curseur
    _pConsole->gotoLigCol(ligneAffichage, colonneAffichage);

    for(int i=0; i<nbLignes; i++)
    {
        for(int j=0; j<nbColonnes; j++)
        {
            //affichage avec gotoligcol et couleur
            _pConsole->gotoLigCol(ligneAffichage, colonneAffichage);

            std::cout << damier[i][j];

            colonneAffichage+=3;
        }

        ligneAffichage+=2;
        colonneAffichage = origineAffichageColonne;
    }
}

void GfxInfos::afficherTour(Console* _pConsole, char tour)
{
    _pConsole->gotoLigCol(2, 10);

    std::cout << "Tour des ";
    if(tour=='N') std::cout << "noirs.";
    else std::cout << "blancs.";
}

void GfxInfos::afficherScore(Console* _pConsole, Damier* _pDamier)
{
    int n=_pDamier->comptageNoir();
    int b=_pDamier->comptageBlanc();

    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()+20,_pDamier->getColonneAffichage()+2);
    std::cout << n << " noirs contre " << b << " blancs." ;
}

void GfxFin::afficherFin(Damier* _pDamier)
{
    int n=_pDamier->comptageNoir();
    int b=_pDamier->comptageBlanc();

    std::cout << "Partie terminee " << std::endl;

    if(n>b)
    {
        std::cout << "Les pions noirs gagnent !" << std::endl;
        system("pause");
    }
    else
    {
        if(n<b)
        {
            std::cout << "Les pions blancs gagnent !" << std::endl;
            system("pause");
        }
        else
        {
            std::cout << "Match nul !" << std::endl;
            system("pause");
        }
    }


}
