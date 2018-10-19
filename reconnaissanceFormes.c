#include "reconnaissanceFormes.h"

/**
    Cette fonction calcule la distance euclidienne entre les matrices de moment
    lambda (notre image) et lambda_ref (l'image de r�f�rence)
    On pr�cise que les matrices DOIVENT �tre de m�me dimension, et donc de m�me ordre.
    @param lambda : contient la matrice contenant les moments de Legendre centr�s et norm�s de l'image � tester
    @param lambda_ref : contien la matrice contenant les moments de Legendre de l'image de la base de donn�es
*/

double calculDistance(MATRIX* lambda, MATRIX* lambda_ref)
{
    printf("Appel de la fonction calculDistance\n");
    int i; // Compteur
    int j; // Compteur

    double somme=0;

    if (lambda->dimLigne>lambda_ref->dimLigne || lambda->dimColonne>lambda_ref->dimColonne)
    {
        printf("Erreur, les matrices n'ont pas les m�mes dimensions, estimation de la ressemblance impossible\n\n");
        exit(5);
    }

    printf("Application de la formule de la distance euclidienne\n");
    for(i=0; i<lambda_ref->dimLigne; i++)
    {
        for(j=0; j<lambda_ref->dimColonne-i; j++)
        {
            somme += ( lambda->matrice[i][j]-lambda_ref->matrice[i][j] )*( lambda->matrice[i][j]-lambda_ref->matrice[i][j] );
        }
    }

    printf("Fin de la fonction calculDistance\n");
    return sqrt(somme);
}
