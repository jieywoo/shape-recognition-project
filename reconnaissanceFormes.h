#ifndef RECONNAISSANCEFORMES_H_INCLUDED
#define RECONNAISSANCEFORMES_H_INCLUDED

#include "myBmpGris.h"

/**
    Cette fonction calcule la distance euclidienne entre les matrices de moment
    lambda (notre image) et lambda_ref (l'image de r�f�rence)
    On pr�cise que les matrices DOIVENT �tre de m�me dimension, et donc de m�me ordre.
    @param lambda : matrice contenant les moments de Legendre centr�s et norm�s de l'image � tester
    @param lambda_ref : matrice contenant les moments de Legendre de l'image de la base de donn�es
*/

double calculDistance(MATRIX* lambda, MATRIX* lambda_ref);

#endif // RECONNAISSANCEFORMES_H_INCLUDED
