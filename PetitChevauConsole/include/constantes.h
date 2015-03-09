#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <boost/multi_array.hpp>
#include "Case.h"


#define LARGEUR_PLATEAU 15
#define HAUTEUR_PLATEAU 15

class Case;

typedef boost::multi_array<Case, 2> mon_array;

enum Couleur{ROUGE, BLEU, VERT, JAUNE};

typedef struct Coordonnees Coordonnees;
struct Coordonnees
{
    int x;
    int y;
};

#endif // CONSTANTES_H_INCLUDED
