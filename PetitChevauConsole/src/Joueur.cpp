#include "Joueur.h"

Joueur::Joueur(int nombrePion, Couleur couleur, bool ia)
{
    m_nombreDeChevaux= nombrePion;
    m_couleur= couleur;
    m_ia= ia;

    for(int i(0); i < m_nombreDeChevaux; i++)
    {
        m_chevaux.push_back( new Pion( m_couleur, i)); //Les pions prennes place lors de la creation

    }

    switch(m_couleur)
    {
        case ROUGE: m_lettre= 'R' ;  break;
        case BLEU:  m_lettre= 'B' ; break;
        case VERT:  m_lettre= 'V' ; break;
        case JAUNE: m_lettre= 'J' ; break;
        default:    std::cout << "Erreur lors de l'associtaion de la couleur au pion." << std::endl;    break;
    }


}

Joueur::~Joueur()
{
    std::cout << "Desrtruction des pions" << std::endl;
    for(int i(0); i < m_nombreDeChevaux; i++)
        delete m_chevaux[i];
}


int Joueur::sortirCheval(int numeroCheval, char plateau[15][15])
{
    /** \brief
     *Si le cheval demander existe
     *Si le cheval demander n'est pas deja sortie
     *
     *On remplace le pion par l'ancienne case
     *On sort le cheval
     *On place le pion sur le plateau
     */

    if( numeroCheval > m_nombreDeChevaux-1)
        return -2;
    if( !m_chevaux[numeroCheval]->estRentrer())
        return -1;


    plateau[m_chevaux[numeroCheval]->getCoord().x][m_chevaux[numeroCheval]->getCoord().y]= m_chevaux[numeroCheval]->getMemoireSol();
    m_chevaux[numeroCheval]->sortir();

    switch(m_couleur)
    {
        case ROUGE: m_chevaux[numeroCheval]->goToXY(6,14);   break;
        case BLEU:  m_chevaux[numeroCheval]->goToXY(0,6);  break;
        case VERT:  m_chevaux[numeroCheval]->goToXY(8,0);  break;
        case JAUNE: m_chevaux[numeroCheval]->goToXY(14,8);  break;
        default:    std::cout << "Erreur lors de la sortie du pion." << std::endl;    break;
    }


    placerChevaux( plateau);
    return 1;
}

int Joueur::avancer(int nombreCase, int numeroCheval, char plateau[15][15])
{
    /** \brief
     *  On remet en place le sol  V
     *  pour chaque resultat du de    V
     *  On prend les coordones de la prochaine case V
     *  Verifier l'absence d'autre pion
     *  Verifier que l'on a pas fini le tour
     *  On deplace le pion  V
     *  On place le pion sur le plateau   V
     *
     *Probleme rencontre: lorsque l'on arrive a la fin d'un tour le cheval ne peut monter d'une case car la prochaine case est differente de '0'
     *                      de plus le pion disparait
     *Solution possible : utilisation d'un switch pour traiter les differentes valeur de la case
     *
     *  Le pion ne disparait plus V
     */

    Coordonnees caseSuivante={0,0};
    if( numeroCheval > m_nombreDeChevaux-1)
        return -2;
    if( m_chevaux[numeroCheval]->estRentrer())
        return -1;

    plateau[m_chevaux[numeroCheval]->getCoord().x][m_chevaux[numeroCheval]->getCoord().y]= m_chevaux[numeroCheval]->getMemoireSol();

    for(nombreCase; nombreCase>0 ; nombreCase--)
    {
        caseSuivante= caseDapres(m_chevaux[numeroCheval]->getCoord(), m_chevaux[numeroCheval]->getCaseCourante());
        if( plateau[caseSuivante.x][caseSuivante.y] == '0'  )//Si il n'y a pas d'autre cheval et que l'on a pas finis le tours on avance
        {
            m_chevaux[numeroCheval]->deplacer();
            m_chevaux[numeroCheval]->goToXY(caseSuivante);
        }
        else    //Si il y a un cheval de meme couleur ou que l'on ne peut pas manger le cheval qui nous gene
        {
            placerChevaux( plateau);
            return -3;
        }

    }

    placerChevaux( plateau);
    return 1;
}

/** \brief
*implementation de la fonction avancer avec boost multiArray au lieu d'un tableau de char
*
*/
int Joueur::avancer(int nombreCase, int numeroCheval, mon_array &plateau)
{
    Coordonnees caseSuivante={0,0};
    if( numeroCheval > m_nombreDeChevaux-1)
        return -2;
    if( m_chevaux[numeroCheval]->estRentrer())
        return -1;

    plateau[m_chevaux[numeroCheval]->getCoord().x][m_chevaux[numeroCheval]->getCoord().y].setType(m_chevaux[numeroCheval]->getMemoireSol());

    for(nombreCase; nombreCase>0 ; nombreCase--)
    {
        caseSuivante= caseDapres(m_chevaux[numeroCheval]->getCoord(), m_chevaux[numeroCheval]->getCaseCourante());
        if( plateau[caseSuivante.x][caseSuivante.y].getType() == '0'  )//Si il n'y a pas d'autre cheval et que l'on a pas finis le tours on avance
        {
            m_chevaux[numeroCheval]->deplacer();
            m_chevaux[numeroCheval]->goToXY(caseSuivante);
        }
        else    //Si il y a un cheval de meme couleur ou que l'on ne peut pas manger le cheval qui nous gene
        {
            //placerChevaux( plateau);
            return -3;
        }

    }

//    placerChevaux( plateau);
    return 1;
}



void Joueur::afficherEtatJoueur()
{
/** \brief
*Affiche:le nombre de pions total
*        le nombre de pion sortie
*        le nombre de pion rentree
*        la position de chaque pion
*/
    int nombreChevauxSortie=0;

    std::cout << "Etat Joueur ";
    switch(m_couleur)
    {
        case ROUGE: std::cout << "ROUGE" << std::endl;   break;
        case BLEU:  std::cout << "BLEU" << std::endl;  break;
        case VERT:  std::cout << "VERT" << std::endl;  break;
        case JAUNE: std::cout << "JAUNE" << std::endl; break;
        default:    std::cout << "Erreur lors de la lecture de la couleur au pion." << std::endl;    break;
    }

    std::cout << "Nombre de pion total:" << m_nombreDeChevaux << std::endl;

    for(int i(0); i < m_nombreDeChevaux; i++)
    {
        if(!m_chevaux[i]->estRentrer())
            nombreChevauxSortie++;
    }

    std::cout << "Nombre de pion sortie:" << nombreChevauxSortie << std::endl;
    for(int i(0); i < m_nombreDeChevaux; i++)
    {
        std::cout << "position pion n" << i << ":" << m_chevaux[i]->getCoord().x << " " << m_chevaux[i]->getCoord().y << std::endl;
    }

    std::cout << "Nombre de pion rentre:" << m_nombreDeChevaux - nombreChevauxSortie << std::endl;
}

void Joueur::placerChevaux(char plateau[15][15])
{

    for(int i(0); i < m_nombreDeChevaux; i++)
    {
        m_chevaux[i]->memoireCaseSol(plateau[m_chevaux[i]->getCoord().x][m_chevaux[i]->getCoord().y]);
        plateau[m_chevaux[i]->getCoord().x][m_chevaux[i]->getCoord().y]= m_lettre;
    }
}

bool Joueur::estPartit()
{
    for(unsigned int i(0); i < m_chevaux.size(); i++)
    {
        if(!m_chevaux[i]->estRentrer())
            return true;
    }
    return false;
}


Coordonnees Joueur::caseDapres(Coordonnees pion, unsigned int avancement)
{
    //Definis la case suivante a patir de la position du pion sur le plateau
    //Commence a la ligne de la sortue du cheval rouge puis dans le sens du jeu
    Coordonnees prochaineCase= {pion.x,pion.y};
    if( avancement < 55)
    {
        if( pion.x == 6 && (pion.y > 8 && pion.y < 14))          {prochaineCase.y--;}
        else if( pion.x == 6 && pion.y == 8)    {prochaineCase.x--;}
        else if( (pion.x > 0 && pion.x < 6)  && pion.y == 8)    {prochaineCase.x--;}
        else if( pion.x == 0 && pion.y == 8)    {prochaineCase.y--;}
        else if( pion.x == 0 && pion.y > 6)     {prochaineCase.y--;}
        else if( pion.x == 0 && pion.y == 6)    {prochaineCase.x++;}
        else if( pion.x < 6 && pion.y == 6)     {prochaineCase.x++;}
        else if( pion.x == 6 && pion.y == 6)    {prochaineCase.y--;}
        else if( pion.x == 6 && pion.y > 0)     {prochaineCase.y--;}
        else if( pion.x == 6 && pion.y == 0)    {prochaineCase.x++;}
        else if( pion.x < 8 && pion.y == 0)     {prochaineCase.x++;}
        else if( pion.x == 8 && pion.y == 0)    {prochaineCase.y++;}
        else if( pion.x == 8 && pion.y < 6)     {prochaineCase.y++;}
        else if( pion.x == 8 && pion.y == 6)    {prochaineCase.x++;}
        else if( pion.x < 14 && pion.y == 6)    {prochaineCase.x++;}
        else if( pion.x == 14 && pion.y == 6)   {prochaineCase.y++;}
        else if( pion.x == 14 && pion.y < 8)    {prochaineCase.y++;}
        else if( pion.x == 14 && pion.y == 8)   {prochaineCase.x--;}
        else if( pion.x > 8 && pion.y == 8)     {prochaineCase.x--;}
        else if( pion.x == 8 && pion.y == 8)    {prochaineCase.y++;}
        else if( pion.x == 8 && pion.y < 14)    {prochaineCase.y++;}
        else if( pion.x == 8 && pion.y == 14)   {prochaineCase.x--;}
        else if( pion.x > 6 && pion.y == 14)    {prochaineCase.x--;}
    }
    else
    {
        if( pion.x == 7 && pion.y == 14)        { prochaineCase.y--;}
        else if( pion.x == 7 && pion.y == 0)    { prochaineCase.y++;}
        else if( pion.x == 0 && pion.y == 7)    { prochaineCase.x--;}
        else if( pion.x == 14 && pion.y == 7)   { prochaineCase.x++;}
    }

    std::cout << pion.x << " " << pion.y << std::endl;
    std::cout << prochaineCase.x << " " << prochaineCase.y << std::endl;

    return prochaineCase;
}
