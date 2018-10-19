#include <math.h>

#include "myBmpGris.c"

#define N 10

void freeMatrice( double** mat)
{
    if( mat != NULL )
    {
        int i;
        for( i = 0; i < N; i++ )
            free( mat[i] );
        free( mat );
    }
    mat = NULL;
}

double val_leg(double x,int p,double** a)
{
    if (!p) return 1;

    int i;
    double val = 0;

    for(i=0;i<=p;i++)
        val += (a[p][i] * pow(x,i));

    return val;
}

int main()
{

    int i,j,k,l;
    int incp,incq;
    int inc1,inc2;
    double x,y,h;
    double xm,ym,z;
    double somme=0;
    double res=0;

    double x_centre=0;
    double y_centre=0;
    double m_0=0;

    BmpImg fBin = readBmpImage("carre.bmp");

    double** tab = malloc(N*sizeof(double*));

    for(inc1=0;inc1<N;inc1++)
        tab[inc1] = calloc(N,sizeof(double));

    tab[0][0] = 1;
    tab[1][1] = 1;

    for(inc1=2;inc1<N;inc1++)
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

    double** mat_mom = malloc( N * sizeof(double*) );
    for( i = 0; i < N; i++ )
        mat_mom[i] = calloc( N, sizeof(double) );


    double** eta = malloc( N * sizeof(double*) );
    for( i = 0; i < N; i++ )
        eta[i] = calloc( N, sizeof(double) );

    double** lambda = malloc( N * sizeof(double*) );
    for( i = 0; i < N; i++ )
        lambda[i] = calloc( N, sizeof(double) );
    double** rekt = malloc( fBin.dimX * sizeof(double*) );
    for( i = 0; i < fBin.dimX; i++ )
        rekt[i] = calloc( fBin.dimY, sizeof(double) );

    double** Iy = malloc( (fBin.dimY) * sizeof(double*) );
    for( i = 0; i < fBin.dimY; i++ )
        Iy[i] = calloc( N, sizeof(double) );

    for (i = 0; i < fBin.dimY; i++)
        for (j = 0; j < N; j++)
            Iy[i][j] = pow(i,j);

    double** Ix = malloc( (fBin.dimX) * sizeof(double*) );
    for( i = 0; i < fBin.dimX; i++ )
        Ix[i] = calloc( N, sizeof(double) );


    for (i = 0; i < fBin.dimX; i++)
        for (j = 0; j < N; j++)
            Ix[i][j] = pow(i,j);

    for(i=0;i<fBin.dimX;i++)
        for(j=0;j<fBin.dimY;j++)
            if(fBin.img[i][j]) fBin.img[i][j] = 1;

    for (i = 0; i < N; i++)
        for (j = 0; j < N - i; j++)
        {
            somme = 0;

            for (k=0; k<fBin.dimX; k++)
                for (l=0; l<fBin.dimY; l++)
                    somme += Ix[k][i]*Iy[l][j]*fBin.img[k][l];
            mat_mom[i][j] = somme;
        }
    m_0 = mat_mom[0][0]; printf("M = %lf\n",m_0);
    x_centre=mat_mom[1][0]/m_0; printf("X = %lf\n",x_centre);
    y_centre=mat_mom[0][1]/m_0;printf("Y = %lf\n",y_centre);
////
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N - i; j++)
        {
            somme  = 0.0;
            for (k=0; k<fBin.dimX; k++)
            {
                xm = k - x_centre;
                for (l=0; l<fBin.dimY; l++)
                {
                    ym = l - y_centre;
                    somme += (pow(xm,i))*(pow(ym,j))*fBin.img[k][l]/(pow(m_0,0.5*(i+j+2)));
                }
            }
            eta[i][j] = somme;
        }
    }
//    FILE* fTxt21 = fopen("eta_mat.txt","r");
//
//    if(fTxt21)
//    {
//    do
//        {
//        for(i=0;i<N;i++)
//        {
//            printf("\n");
//            for(j=0;j < N - i;j++)
//                {
//                    printf("i = %d\tj = %d\tE = ",i,j);
//                    scanf("%lf",&(eta[i][j]));
//                }
//        }
//
//        scanf("%d",&i);}
//    while(i == -1);
//    fclose(fTxt21);
//    }

    FILE* fTxt = fopen("eta.txt","w");

    if(fTxt)
    {
        for(i=0;i<N;i++)
        {
            fprintf(fTxt,"\n");
            for(j=0;j < N - i;j++){
                fprintf(fTxt,"%.4e\t",eta[i][j]);}
        }
    fclose(fTxt);
    }

    for(incp = 0; incp < N ; incp++)
        for(incq = 0; incq < N - incp; incq++)
        {
            res = 0;
            for (i = 0; i <= incp; i++)
                for (j = 0; j <= incq; j++)
                    res += tab[incp][i] * tab[incq][j] * eta[i][j] *((2*incp + 1)*(2*incq + 1))/4.0;
            lambda[incp][incq] = res;
        }

    fTxt = fopen("lambda.txt","w");

    if(fTxt)
    {
        for(i=0;i<N;i++)
        {
            fprintf(fTxt,"\n");
            for(j=0;j < N - i;j++){
                fprintf(fTxt,"%.4e\t",lambda[i][j]);}
        }
    fclose(fTxt);
    }

    h = 2/127;
    x = -1 - h;
    for(i=0;i<fBin.dimX;i++)
    {
        x = x + h;
        y = -1 - h;
        for(j=0;j<fBin.dimY;j++)
        {
            y = y + h;
            res = 0;
            for(incp=0;incp < N;incp++)
                for(incq=0;incq < N - incp;incq++)
                    res += (lambda[incp][incq] * val_leg(x,incp,tab) * val_leg(y,incq,tab));
            rekt[i][j]=res;
        }
    }

    fBin.img = rekt;

    for(i=0;i<fBin.dimX;i++)
        for(j=0;j<fBin.dimY;j++)
            if(fBin.img[i][j]>= 0.5) fBin.img[i][j] = 255;
            else fBin.img[i][j]=0;

    fTxt = fopen("recon.txt","w");

    if(fTxt)
    {
        for(i=0;i<fBin.dimX;i++)
        {
            fprintf(fTxt,"\n");
            for(j=0;j < fBin.dimY;j++){
                fprintf(fTxt,"%d\t",fBin.img[i][j]);}
        }
    fclose(fTxt);
    }

    writeBmpImage("recons12.bmp",&fBin);

    for(i=0;i<fBin.dimY;i++)
        free(rekt[i]);
    free(rekt);

    freeMatrice(Ix);
    freeMatrice(Iy);
    freeMatrice(lambda);
    freeMatrice(eta);
    freeMatrice(mat_mom);
    freeMatrice(tab);

    return 0;
}

