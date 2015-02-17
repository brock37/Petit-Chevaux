#ifndef JOUEUR_H
#define JOUEUR_H

#include "constantes.h"
#include "Pion.h"

class Joueur
{
    public:
        /** Default constructor */
        Joueur(int nombrePion, Couleur couleur, bool ia= false);
        /** Default destructor */
        ~Joueur();
        int sortirCheval(int numeroCheval, char plateau[15][15]);
        int avancer(int nombreCase, int numeroCheval, char plateau[15][15]);
        void afficherEtatJoueur();
        void placerChevaux(char plateau[15][15]);
        bool estPartit();
        bool estUneIA(){return m_ia;}
        Coordonnees caseDapres(Coordonnees pion, unsigned int avancement);
    protected:
    private:
        std::vector<Pion*> m_chevaux;
        int m_nombreDeChevaux;
        Couleur m_couleur;
        char m_lettre;
        bool m_ia;
};

#endif // JOUEUR_H
