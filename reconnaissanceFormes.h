#ifndef RECONNAISSANCEFORMES_H_INCLUDED
#define RECONNAISSANCEFORMES_H_INCLUDED

#include "myBmpGris.h"

/**
    Cette fonction calcule la distance euclidienne entre les matrices de moment
    lambda (notre image) et lambda_ref (l'image de référence)
    On précise que les matrices DOIVENT être de même dimension, et donc de même ordre.
    @param lambda : matrice contenant les moments de Legendre centrés et normés de l'image à tester
    @param lambda_ref : matrice contenant les moments de Legendre de l'image de la base de données
*/

double calculDistance(MATRIX* lambda, MATRIX* lambda_ref);

#endif // RECONNAISSANCEFORMES_H_INCLUDED
