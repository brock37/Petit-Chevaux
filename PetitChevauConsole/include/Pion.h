#ifndef PION_H
#define PION_H

#include "constantes.h"

class Pion
{
    public:
        /** Default constructor */
        Pion(Couleur couleur, int nPion);
        /** Default destructor */
        ~Pion();
        void deplacer();
        void goToXY(Coordonnees coord);
        void goToXY(int x, int y);
        void memoireCaseSol(char sol);
        void sortir(){m_dansLeBox = false; m_caseCourante++;}

        bool estRentrer(){return m_dansLeBox;}
        Coordonnees getCoord(){return m_position;}
        char getMemoireSol(){return m_solCase;}
        int getCaseCourante(){return m_caseCourante;}

    protected:
    private:
        int m_caseCourante;
        int m_nPion;
        Couleur m_couleurPion;
        Coordonnees m_position;
        char m_solCase;
        bool m_dansLeBox;
};

#endif // PION_H
