

#include "constantes.h"
#include "Pion.h"
#include "Joueur.h"



using namespace std;


void initialisation( char plateau[15][15])
{
    ifstream fichier("plateau.txt", ios::in);
    while( !fichier.eof())
    {
        for(int i(0); i < 15; i++ )
        {
        for(int j(0); j < 15; j++ )
            fichier >> plateau[j][i];

        }
    }

}

void afficherPlateau(char plateau[15][15])
{
    for(int i(0); i < 15; i++ )
    {
        for(int j(0); j < 15; j++ )
        {
            switch(plateau[j][i])
            {
            case 'R':

                std::cout << "\033[1;31m" << plateau[j][i] << "\033[0m" <<" " ;
            break;
            case 'V':

                std::cout << "\033[1;32m" << plateau[j][i] << "\033[0m" <<" " ;
            break;
            case 'B':

                std::cout << "\033[1;34m" << plateau[j][i] << "\033[0m" <<" " ;
            break;
            case 'J':

                std::cout << "\033[1;33m" << plateau[j][i] << "\033[0m" <<" " ;
            break;
            default:
                std::cout << plateau[j][i] << " " ;
            break;
            }
        }
        std::cout << std::endl;
    }
}



int de(int dernierLancer)
{
    int res= (rand() + dernierLancer) % 6 + 1;
    std::cout << "Resultat du lance: "<<res << std::endl;
    return res;
}



int main()
{
    /**< Initialisation des variables */
    char plateau[15][15];
    initialisation( plateau);
    unsigned int nombrePion=0, nombreAdversaire=0, tourJoueur=0, resDe=0, dernierResDe=0;
    bool gagne= false;
    //mon_array array2D(boost::extents[15][15]);
    int waiting;

    /* initialize random */
    srand (time(NULL));


    /**< Demande du nombre de pion , de joueur et choix couleur */
    cout << "Jeu des petits chevaux" << endl;
    std::cout << "Avec combien de pion voulez-vous jouer? " ;
    nombrePion= 1;//cin >> nombrePion;
    std::cout << "Avec combien de joueur voulez-vous jouer? " ;
    nombreAdversaire= 1;//cin >> nombreAdversaire;

    cin >> waiting;

    /**< Creation de joueurs avec leur pion  */
    Joueur joueurRouge(nombrePion, ROUGE);
    Joueur joueurVert(nombrePion, VERT, true);
    Joueur joueurBleu(nombrePion, BLEU, true);
    Joueur joueurJaune(nombrePion, JAUNE, true);

    std::vector<Joueur*> joueur;
    joueur.push_back(&joueurRouge);
    //joueur.push_back(&joueurVert);
    //joueur.push_back(&joueurBleu);
    //joueur.push_back(&joueurJaune);

    for(unsigned int i(0); i < joueur.size(); i++) joueur[i]->placerChevaux(plateau);



    do
    {
        system("clear");
        resDe= de(dernierResDe);    // On lance le dé est on affiche son resultat
        dernierResDe= resDe;
        afficherPlateau(plateau);
        joueur[tourJoueur]->afficherEtatJoueur();

        if( joueur[tourJoueur]->estUneIA())    //Si le joueur est une ia
        {
            if(resDe == 6 && joueur[tourJoueur]->estPartit() == false)
            {

            }
            else if(resDe == 6 && joueur[tourJoueur]->estPartit() == true)
            {

            }
        }
        else    //Si le joueur est un humain
        {
            if(resDe == 6 )
            {
                unsigned int pionDeplacer=0;
                int retour=0, choix= 0;

                do
                {
                    std::cout << "1.AVANCER / 2.SORTIR" << std::endl;
                    cin >> choix;
                }while(choix!=1 && choix != 2);


                if( choix == 1)
                {
                    //on laisse le joueur choisir quel pion on sort ou auto si 1 seul pion
                    if( nombrePion != 1)
                    {
                        std::cout << "Quel pion avancer?(0-3)";
                        cin >> pionDeplacer;
                    }
                    else
                    {
                        pionDeplacer= 0;
                    }

                    retour= joueur[tourJoueur]->avancer( resDe, pionDeplacer, plateau);

                    switch(retour)
                    {
                        case 1: std::cout << "Le pion avance" << std::endl; break;
                        case -1: std::cout << "Le pion est encore dans l'enclos" << std::endl; break;
                        case -2: std::cout << "Le pion n'existe pas" << std::endl; break;
                    }
                }
                else if(choix == 2)
                {
                    if( nombrePion != 1)
                    {
                        std::cout << "Quel cheval sortir du box?(0-3)" << std::endl;
                        cin >> pionDeplacer;
                    }
                    else
                    {
                        pionDeplacer= 0;
                    }

                    retour=joueur[tourJoueur]->sortirCheval(pionDeplacer, plateau);

                    switch(retour)
                    {
                        case 1: std::cout << "Le pion est sortie" << std::endl; break;
                        case -1: std::cout << "Le pion est deja sortie" << std::endl; break;
                        case -2: std::cout << "Le pion n'existe pas" << std::endl; break;
                    }
                }

            }
            else    /**< Si le dé a fais autre que 6  */
            {
                if(joueur[tourJoueur]->estPartit())
                {
                    unsigned int pionDeplacer=0;
                    int retour=0;

                    if( nombrePion != 1)
                    {
                        std::cout << "Quel pion avancer?(0-3)";
                        cin >> pionDeplacer;
                    }
                    else
                    {
                        pionDeplacer= 0;
                    }

                    retour= joueur[tourJoueur]->avancer( resDe, pionDeplacer, plateau);

                    switch(retour)
                    {
                        case 1: std::cout << "Le pion avance" << std::endl; break;
                        case -1: std::cout << "Le pion est encore dans l'enclos" << std::endl; break;
                        case -2: std::cout << "Le pion n'existe pas" << std::endl; break;
                        case -3: std::cout << "Le pion est bloquer" << std::endl; break;
                    }
                }

            }
        }


        std::cin >> waiting;
        system("clear");
        std::cout << "Fin du tour!" <<std::endl;
        afficherPlateau(plateau);
        joueur[tourJoueur]->afficherEtatJoueur();
        std::cin >> waiting;

        if(tourJoueur < joueur.size()-1)    {tourJoueur++;}
        else                                {tourJoueur=0;}


    }while(!gagne);

    return 0;
}
