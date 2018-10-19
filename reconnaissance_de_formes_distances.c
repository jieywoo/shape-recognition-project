#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculDistance(double* distance, double** lambda, double** lambda_ref, int p, int q)
{
    int i;
    int j;

    double somme=0;

    for(i=0; i<=p; i++)
    {
        for(j=0; j<=q; j++)
        {
            somme += ( lambda[i][j]-lambda_ref[i][j] )*( lambda[i][j]-lambda_ref[i][j] );
        }
    }
    *distance = sqrt(somme);
}
