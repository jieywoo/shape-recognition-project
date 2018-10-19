#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
    createPolynomeL : Retourne un vecteur contenant les polynomes de Legendre en x
    à l'ordre n.
    @param pln_r : vecteur contenant les polynomes de Legendre
    @param coeff_A : strucutre contenant la matrice de coefficient du polynome de Legendre
    @param matI : structure contenant la matrice avec les valeurs de x normalisés entre [-1;1]
*/

void createPolynomeL(double* pln_r, MATRIX *coeff_A, MATRIX* matI)
{
    printf("Appel de la fonction createPolynomeL\n");
    int i; // Compteur sur i
    int j; // Compteur sur n

    printf("Parcours du vecteur contenant les polynomes pour chaque valeur de x\n");
    for(j=0; j<coeff_A->dimLigne; j++)
    {
        for(i=0; i<coeff_A->dimColonne; i++)
        {
            pln_r[j] += coeff_A->matrice[j][i]*pow(matI->matrice[j][i],i);
        }
    }

    printf("Fin de la fonction createPolynomeL\n");
}

/**
    createImgRebuilt : Cette fonction recréé l'image à partir de nos moments de Legendre
    @param matLambda : structure contenant nos moments de Legendre
    @param dimX : Dimension en X de l'image
    @param dimY : Dimension en Y de l'image
    @param polyLeg_P : vecteur contenant les polynomes de Legendre de x à l'ordre P
    @param polyLeg_Q : vecteur contenant les polynomes de Legendre de y à l'ordre Q
*/

MATRIX createImgRebuilt(MATRIX* matLambda, int dimX, int dimY, double* polyLeg_P, double* polyLeg_Q)
{
    int p;
    int i,j,x,y;

    double somme=0;

    MATRIX imgRebuilt = createMatrix(dimX, dimY);

    for(x=0; x<dimX; x++)
    {
        for(y=0; y<dimY; y++)
        {
            for (i=0;i<p;i++)
            {
                for(j=0;j<N-p;j++)
                {
                    somme += matLambda->matrice[i][j]*polyLeg_P[i]*polyLeg_Q[j];
                }
            }
            imgRebuilt.matrice[x][y]=somme;
            somme=0;
        }
    }

    return im_r;
}



