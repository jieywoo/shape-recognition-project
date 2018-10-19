#include <stdio.h>
#include <time.h>

#include "myBmpGris.c"

/**
    CoeffLeg : Cette fonction calcule les coefficients des polynomes de Legendre
    jusqu'à l'ordre n et renvoie une structure comprennant la matrice et ses dimensions
    @param n : ordre du polynome de Legendre
*/

MATRIX CoeffLeg(int n)
{
    int inc1,inc2;

    MATRIX coeff_A;
    double** tab = malloc(n*sizeof(double*));

    for(inc1=0;inc1<n;inc1++)
        tab[inc1] = calloc(n,sizeof(double));

    tab[0][0] = 1;
    tab[1][1] = 1;

    for(inc1=2;inc1<n;inc1++)
    {
        for(inc2=0;inc2<=inc1;inc2++)
        {
            if  (!inc2)
                tab[inc1][inc2] = -((inc1-1)*tab[inc1-2][0])/inc1;
            else
                if (inc2 == inc1)
                    tab[inc1][inc2] = ((2*inc1-1)*tab[inc1-1][inc1-1])/inc1;
                else
                    tab[inc1][inc2] = ((2*inc1-1)*tab[inc1-1][inc2-1])/inc1 -((inc1-1)*tab[inc1-2][inc2])/inc1;
        }
    }

    coeff_A.matrice = tab;
    coeff_A.dimLigne = inc1;
    coeff_A.dimColonne = inc1;

    return coeff_A;
}

/**
    lambda : Cette fonction calcule les moments de Legendre
    @param eta : structure comprennant la matrice de moments centrés et normés
*/

MATRIX lambda(MATRIX* eta)
{
    int incp,incq,inci,inj;

    double** a = CoeffLeg(N);

    MATRIX matLambda;
    matLambda.matrice=createMatrix(eta->dimLigne,eta->dimColonne);

    for(incp = 0; incp < N ; incp++)
        for(incq = 0; incq < N - incp; incq++)
        {
            for (inci = 0; inci <= p; inci++)
                for (incj = 0; incj <= q; incj++)
                    res += a[incp][inci] * a[incq][incj] * eta.matrice[i][j];
            res *= ((2*incp + 1)*(2*incq + 1))/4;
            matLambda.matrice[incp][incq] = res;
        }

    freeMatrice(a,N);

    return matLambda;
}

/**
    freeMatrice : Cette fonction libère les matrices
    @param mat : matrice carrée à libérer
    @param N : dimension de la matrice
*/

void freeMatrice( double** mat, int N) {
    if( mat != NULL ){
        int i;
        for( i = 0; i < N; i++ )
            free( mat[i] );
        free( mat );
    }
    mat = NULL;
}
