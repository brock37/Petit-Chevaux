#include "Pion.h"

Pion::Pion(Couleur couleur, int nPion)
{
    m_nPion= nPion;

    m_caseCourante= -1;

    m_dansLeBox= true;

    switch(couleur)
    {
        case ROUGE: goToXY(5,14);   break;
        case BLEU:  goToXY(0,5);  break;
        case VERT:  goToXY(9,0);  break;
        case JAUNE: goToXY(14,9); break;
        default:    std::cout << "Erreur lors du placement des pion." << std::endl;    break;
    }
}

Pion::~Pion()
{
    //dtor
}

void Pion::deplacer()   //Fais avancer le pion sur le chemin de la victoire
{
    m_caseCourante++;
}

void Pion::goToXY(Coordonnees coord)    //Deplace virtuelement le pion au coordonees
{
    m_position.x= coord.x;
    m_position.y= coord.y;
}

void Pion::goToXY(int x, int y)
{
    m_position.x= x;
    m_position.y= y;
}

void Pion::memoireCaseSol(char sol) //Enregistre le symbole sous le cheval
{
    m_solCase=sol;
}
