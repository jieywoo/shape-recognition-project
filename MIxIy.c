#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIMX 5
#define DIMY 5

/**
    createIxIy : retourne les matrice Ix ou Iy
    @param pq : ordre p de x ou ordre q de y
    @param dimXY : taille maximale de l'image en x ou en y
*/

double** createIxIy(int pq, int dimXY)
{
    int i; // Compteur sur pq
    int j; // Compteur sur dimXY

    double** Ixy = malloc( pq * sizeof(double*) );
    for( i = 0; i < pq; i++ )
    {
        Ixy[i] = calloc( dimXY, sizeof(double) );
    }

    for (j = 0; j< dimXY; j++)
    {
        for (i = 0; i< pq; i++)
        {
            Ixy[j][i] = pow((j+1),i);
        }
    }
    return Ixy;
}

/**
    createM : retourne la matrice M contenant les moments
    @param p : ordre p de x
    @param q : ordre q de y
    @param Ix : matrice contenant les polynomes de x d'ordre 0 à p
    @param Iy : matrice contenant les polynomes de y d'ordre 0 à q
    @param Im : type BMP contenant l'image, dimX, dimY, et d'autres paramètres
*/

double** createM(int p, int q, double** Ix, double** Iy, BmpImg* Im)
{
    int i; // Compteur sur p
    int j; // Compteur sur q
    int k; // Compteur sur dimX
    int l; // Compteur sur dimY

    double somme=0; // Element de la matrice M

    double** M = malloc( p * sizeof(double*) );
    for( j = 0; j < q; j++ )
    {
        M[j] = calloc( q, sizeof(double) );
    }
    for (i = 0; i< p; i++)
    {
        for (j = 0; j< q; j++)
        {
            for (k=0; k<Im->dimX; k++)
            {
                for (l=0; l<Im->dimY; l++)
                {
                    somme += Ix[k][i]*Iy[l][j]*Im->img[k][l];
                }
            }
            M[i][j] = somme;
            somme = 0;
        }
    }
    return M;
}

/**
    createEta : matrice contenant les moments centrés et normés
    @param M : matrice contenant les moments
    @param Ix_centre : matrice contenant les polynomes de x d'ordre 0 à p centrés
    @param Iy_centre : matrice contenant les polynomes de y d'ordre 0 à q centrés
    @param Im : matrice contenant l'image (remplie de 0 et de 1)
    @param p : ordre p de x
    @param q : ordre q de y

*/

double** createEta(double** M, BmpImg* Im, int p, int q)
{
    int i; // Compteur sur p
    int j; // Compteur sur q
    int k; // Compteur sur dimX
    int l; // Compteur sur dimY

    double x_centre=0; // Valeur pour centrer x
    double y_centre=0; // Valeur pour centrer y
    double somme=0; // Element de la matrice M
    double m_0=0; // Aire de l'image

    m_0 = M[0][0];
    x_centre=M[1][0]/m_0;
    y_centre=M[0][1]/m_0;

    double** eta = malloc( p * sizeof(double*) );
    for( j = 0; j < q; j++ )
    {
        eta[j] = calloc( q, sizeof(double) );
    }
    for (i = 0; i< p; i++)
    {
        for (j = 0; j< q; j++)
        {
            for (k=0; k<Im->dimX; k++)
            {
                for (l=0; l<Im->dimY; l++)
                {
                    somme += ( (Im->img[k][i] - x_centre)*(Im->img[l][j] - y_centre)*Im->img[k][l])/pow(m_0,(p+q+2)/2);
                }
            }
            eta[i][j] = somme;
            somme = 0;
        }
    }
    return eta;
}



/**
    printM : print la matrice M
    @param x : taille maximale de la matrice en x
    @param y : taille maximale de la matrice en y
    @param M : matrice

*/

void printM(int x, int y, double** M){
    int i; // Compteur sur x
    int j; // Compteur sur y

    for (i = 0; i < x; i++)
    {
        for (j = 0; j< y; j++)
        {
            printf("%.0lf \t", M[i][j]);
        }
        printf("\n");
    }
}

int main(){

int p=5, q=5, i,j,t;

double** Ix = createIxIy(p, DIMX);
double** Iy = createIxIy(q, DIMY);

double** ImT = malloc( 5 * sizeof(double*) );
for( t = 0; t < 5; t++ ){
	ImT[t] = calloc( 5, sizeof(double) );
}

ImT[1][1]=1; ImT[1][2]=1; ImT[1][3]=1; ImT[2][2]=1; ImT[3][2]=1;

//printM(5, 5, ImT);

double** M = createM(p,q,DIMX,DIMY,Ix,Iy,ImT);


double** Ix_centre = createIxIy_centre(p, DIMX, M);
double** Iy_centre = createIxIy_centre(q, DIMY, M);

//printM(p, DIMX, Ix);
//printM(q, DIMY, Iy);

//printM(p, q, M);

printM(p, DIMX, Ix_centre);
//printM(q, DIMY, Iy_centre);

double** M_new = createEta(M, Ix_centre, Iy_centre, ImT, p, q, DIMX, DIMY);

//printM(p, q, M_new);

return 0;
}

