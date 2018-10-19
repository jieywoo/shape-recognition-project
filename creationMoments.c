#include "creationMoments.h"

/**
    Pour faciliter le debug, nous avons ajouté des printf partout ainsi que
    des fonctions exit qui retournent différentes valeurs en fonction de l'erreur.
    Voici le code arbitraire choisi pour notre débug :

    -2 : Choix d'une image non présente dans notre base de donnée
    -1 : Echec saisie utilisateur
    1 : Echec d'allocation d'une matrice
    2 : Echec de libération d'une matrice
    3 : Echec de la lecture d'une image
    4 : Echec d'ouverture d'un fichier
    5 : Echec de calcul d'une distance euclidienne entre 2 matrices lambda et lambda_ref
*/

int main()
{
    int choix=0; // Choix de l'image à tester

    double DIMX=0; // Dimension verticale de l'image
    double DIMY=0; // Dimension horizontale de l'image

    double distanceIm1=0; // Distance entre l'image test et l'image 1 de notre base de donnée
    double distanceIm2=0; // Distance entre l'image test et l'image 2 de notre base de donnée
    double distanceIm3=0; // Distance entre l'image test et l'image 3 de notre base de donnée
    double distanceIm4=0; // Distance entre l'image test et l'image 4 de notre base de donnée
    double distanceIm5=0; // Distance entre l'image test et l'image 5 de notre base de donnée

    printf("Bonjour et bienvenue dans le programme developpe au cadre du projet P5 Reconnaissance ");
    printf("de formes de l'UE 3E103. Ce programme a ete developpe par CHASSET Quentin, DALIPI Rea");
    printf(", TAHALOOHA Nimesh et WOO Jieyeon. Ce programme a pour but d'analyser et de reconnaitre ");
    printf("une forme contenue dans une image parmi une base de donnees prealablement constitue\n\n.");
    printf("Pour debuter l'analyse, veuillez choisir une image parmi les 5 proposees : \n");
    printf("1. Un carre\n");
    printf("2. Un A majuscule\n");
    printf("3. Un carre plus grand\n");
    printf("4. Un C majuscule\n");
    printf("5. Un I majuscule\n");

    if(scanf("%d", &choix)!=1) // Verification de la saisie utilisateur
    {
        printf("Erreur de saisie utilisateur\n\n");
        exit(-1);
    }

    printf("Lecture de l'image bmp\n\n");
    BmpImg ImTest; // Creation d'une structure qui acceuillera notre image à tester
    choixBmpImg(choix,&ImTest); // Récupérationd e l'image en fonction du choix utilisateur

    DIMX = ImTest.dimX; // Lecture de la dimension verticale
    DIMY = ImTest.dimY; // Lecture de la dimension horizontale

    printf("Recuperation des dimensions de l'image\n\n");
    printf("Lecture des dimensions de l'image\n\n");

    if(DIMX==0 || DIMY==0) // Verification de la bonne lecture des données
    {
    printf("Echec de la lecture de l'image\n\n");
    exit(3);
    }

    printf("Conversion de la structure BmpImg en structure MATRIX\n\n");
    MATRIX matImTest=convImg2Mat(&ImTest);

    printf("Creation des matrices Ix et Iy\n\n");
    MATRIX Ix = createMatrix(DIMX, ordre_N); // Matrice contenant les x à l'ordre p
    MATRIX Iy = createMatrix(DIMY, ordre_N); // Matrice contenant les y à l'ordre q

    printf("Initialisation des matrices Ix et Iy\n\n");
    initMatI(&Ix);
    initMatI(&Iy);

//    printf("Affichage des matrices Ix, Iy\n\n");
//    printMat(&Ix);
//    printMat(&Iy);

//    printf("Affichage de la matrice matImgTest\n\n");
//    printMat(&matImTest);

    printf("Creation de la matrice matM\n\n");
    MATRIX matM = createM(&Ix, &Iy, &matImTest); // Matrice de moments

    printf("Liberation des matrices Ix et Iy");
    freeMatrix(&Ix);
    freeMatrix(&Iy);

//    printf("Affichage de la matrice matM\n\n");
//    printMat(&matM);

    printf("Creation de la matrice matEta\n");
    MATRIX matEta = createEta(&matM, &matImTest); // Matrice de moments centrés et normés

    printf("Liberation de la matrice matM\n");
    freeMatrix(&matM);

//    printf("Affichage de la matrice matEta\n");
//    printMatScient(&matEta); // Affichage en écriture scientifique

    printf("Creation et initialisation de la matrice de coefficient\n");
    MATRIX coeff_A=CoeffLeg(ordre_N); // Matrice des coefficients des polynomes de Legendre

//    printf("Affichage des coefficients\n\n");
//    printMat(&coeff_A);
//    printf("\n\n");

    printf("Creation de la matrice matLambda\n\n");
    MATRIX matLambda = createLambda(&matEta, &coeff_A);

//    printf("Affichage de la matrice matLambda\n\n");
//    printMatScient(&matLambda);

    printf("Creation de la matrice imgRebuilt\n\n");
    MATRIX imgTestRebuilt = createImgRebuilt(DIMX, DIMY, &matLambda, &coeff_A);

    printf("Conversion de la matrice imgTestRebuilt en image imgOut\n\n");
    BmpImg imgOut=convMat2Img(&imgTestRebuilt);

    printf("Ecriture de l'image imgOut\n\n");
    writeBmpImage(ImgOut,&imgOut);

    printf("Liberation des matrices imgTestRebuilt et coeff_A\n\n");
    freeMatrix(&imgTestRebuilt);
    freeMatrix(&coeff_A);

    printf("Creation des matrices matLambdaRef\n\n");
    MATRIX matLambdaRef1=createMatrix(ordre_N,ordre_N);
    MATRIX matLambdaRef2=createMatrix(ordre_N,ordre_N);
    MATRIX matLambdaRef3=createMatrix(ordre_N,ordre_N);
    MATRIX matLambdaRef4=createMatrix(ordre_N,ordre_N);
    MATRIX matLambdaRef5=createMatrix(ordre_N,ordre_N);

    printf("Recuperaion des valeurs de references associees aux images\n\n");
    recupLambdaRef(fichierImg1,&matLambdaRef1);
    recupLambdaRef(fichierImg2,&matLambdaRef2);
    recupLambdaRef(fichierImg3,&matLambdaRef3);
    recupLambdaRef(fichierImg4,&matLambdaRef4);
    recupLambdaRef(fichierImg5,&matLambdaRef5);

    printf("Calcul de la distance entre la matrice reconstruite et la matrice de reference\n\n");
    distanceIm1 = calculDistance(&matLambda, &matLambdaRef1);
    distanceIm2 = calculDistance(&matLambda, &matLambdaRef2);
    distanceIm3 = calculDistance(&matLambda, &matLambdaRef3);
    distanceIm4 = calculDistance(&matLambda, &matLambdaRef4);
    distanceIm5 = calculDistance(&matLambda, &matLambdaRef5);

    printf("Distance entre les deux matrices : %le\n", distanceIm1);
    printf("Distance entre les deux matrices : %le\n", distanceIm2);
    printf("Distance entre les deux matrices : %le\n", distanceIm3);
    printf("Distance entre les deux matrices : %le\n", distanceIm4);
    printf("Distance entre les deux matrices : %le\n\n", distanceIm5);

    printf("Reconnaissance de l'image:\n\n");
    /* Nos deux carrés, bien que de tailles différentes, ont les mêmes distances, ce qui vérifie bien que notre programme
       est fonctionnel car nos moments sont bien invariants par changement de facteur d'échelle ou par rotation. On ne fera
       donc pas de test sur le minimum entre les distances distanceIm1 et distanceIm3 puisqu'elles sont égales. */
    if((distanceIm1<distanceIm2)&&(distanceIm1<distanceIm4)&&(distanceIm1<distanceIm5))
    {
        printf("L'image reconnue est un carre de petite taille\n\n");
    }
    else if((distanceIm2<distanceIm1)&&(distanceIm2<distanceIm3)&&(distanceIm2<distanceIm4)&&(distanceIm2<distanceIm5))
    {
        printf("L'image reconnue est un A\n\n");
    }
    else if((distanceIm4<distanceIm1)&&(distanceIm4<distanceIm3)&&(distanceIm4<distanceIm3)&&(distanceIm4<distanceIm5))
    {
        printf("L'image reconnue est un C\n\nn");
    }
    else if((distanceIm5<distanceIm1)&&(distanceIm5<distanceIm2)&&(distanceIm5<distanceIm3)&&(distanceIm5<distanceIm4))
    {
        printf("L'image reconnue est un I\n\n");
    }

    printf("Liberation de matLambda et des matLambdaRef\n\n");
    freeMatrix(&matLambda);
    freeMatrix(&matLambdaRef1);
    freeMatrix(&matLambdaRef2);
    freeMatrix(&matLambdaRef3);
    freeMatrix(&matLambdaRef4);
    freeMatrix(&matLambdaRef5);

    printf("Fin du programme. Nous vous souhaitons une bonne journee et une bonne continuation\n\n");
    return 0;
}

/**
    choixBmpImg : Permet de choisir quelle image on souhaite tester dans notre
    base de données
    @param choix : choix de l'image a récupérer
    @param img : structure d'une image bmp
*/

void choixBmpImg(int choix, BmpImg* img)
{
    printf("Appel de la fonction choixBmpImg\n");
    printf("Choix de l'image a recuperer : %d\n", choix);

    if (choix==1) // Image 1 : un petit carré
    {
        *img=readBmpImage(Img1_test);
    }
    else if (choix==2) // Image 2 : un A majuscule
    {
        *img=readBmpImage(Img2_test);
    }
    else if (choix==3) // Image 3 : un grand carré
    {
        *img=readBmpImage(Img3_test);
    }
    else if (choix==4) // Image 4 : un C majuscule
    {
        *img=readBmpImage(Img4_test);
    }
    else if (choix==5) // Image 5 : un I majuscule
    {
        *img=readBmpImage(Img5_test);
    }
    else
    {
        printf("Cette image n'existe pas dans notre base de donnee.Veuillez nous excusez");
        printf("pour la gene occasionnee.\n\n");
        exit(-2);
    }
    printf("Fin de la fonction choixBmpImg\n\n");
}

/**
    convImg2Mat : Convertion d'une image en matrice exploitable
    @param imgIn : structure image dont on veut récupérer les valeurs
*/

MATRIX convImg2Mat(BmpImg* imgIn)
{
    printf("Appel de la fonction convImg2Mat\n");
    int i; // Compteur sur dimLigne
    int j; // Compteur sur dimColonne

    printf("Creation de imgOut\n");
    MATRIX imgOut= createMatrix(imgIn->dimX,imgIn->dimY);

    printf("Recuperation des valeurs de l'image et conversion\n");
    for(i=0; i<imgOut.dimLigne; i++)
    {
        for(j=0; j<imgOut.dimColonne; j++)
        {
            if(imgIn->img[i][j]==255) // Seuil : on remplace 255 par 1
            {
                imgOut.matrice[i][j]=1;
            }
            else // et le reste par 0
            {
                imgOut.matrice[i][j]=0;
            }
        }
    }
    printf("Valeurs recuperees\n");
    printf("Fin de la fonction convImg2Mat\n\n");
    return imgOut;
}

/**
    convMat2Img : Convertion d'une matrice en une image
    @param imgIn : structure image dont on veut récupérer les valeurs
*/

BmpImg convMat2Img(MATRIX* imgIn)
{
    printf("Appel de la fonction convMat2Img\n");
    int i; // Compteur
    int j; // Compteur

    printf("Creation de imgOut\n");
    BmpImg imgOut = createBmpImg(ImgOut, imgIn->dimLigne, imgIn->dimColonne);

    printf("Parcours de l'image et conversion des valeurs\n");
    for(i=0; i<imgOut.dimX; i++) // Parcours sur dimLigne
    {
        for(j=0; j<imgOut.dimY; j++) // Parcours sur dimColonne
        {
            if(imgIn->matrice[i][j]==1) // Seuil : on remplace 1 par 255
            {
                imgOut.img[i][j]=255;
            }
            else // et 0 par 0
            {
                imgOut.img[i][j]=0;
            }
        }
    }

    printf("Valeurs recuperees\n");
    printf("Fin de la fonction convMat2Img\n\n");
    return imgOut;
}

/**
    createMatrix : retourne une struture de type MATRIX
    dont la matrice est de taille dimLigne * dimcolonne
    @param dimLigne : nombre de lignes de la matrice
    @param dimColonne : nombre de colonnes de la matrice
*/

MATRIX createMatrix(int dimLigne, int dimColonne)
{
    printf("Appel de la fonction createMatrix\n");
    MATRIX mat;
    int i; // Compteur

    printf("Initialisation de la matrice\n");
    mat.matrice = NULL;

    printf("Attribution des dimensions de la matrice\n");
    mat.dimLigne = dimLigne;
    mat.dimColonne = dimColonne;

    printf("Matrice correctement initialisee\n");

    printf("Allocation de la matrice\n");
    mat.matrice = malloc((dimLigne)*sizeof(double*));
    for(i=0; i<dimLigne; i++)
    {
        mat.matrice[i] = calloc(dimColonne, sizeof(double));
    }

    if(mat.matrice==NULL)
    {
        printf("Echec de l'allocation de la matrice\n");
        exit(1);
    }

    printf("Matrice correctement allouee\n");
    printf("Fin de la fonction createMatrix\n\n");
    return mat;
}

/**
    freeMatrix : Cette fonction libère les matrices
    contenu dans les structures MATRIX
    @param mat : matrice à liberer
*/

void freeMatrix(MATRIX* mat)
{
    printf("Appel de la fonction freeMatrix\n");
    int i; // Compteur

    printf("Liberation de la matrice\n");
    for(i=0; i<mat->dimColonne; i++)
    {
        free(mat->matrice[i]);
    }
    free(mat->matrice);
    mat->matrice = NULL;

    if(mat->matrice != NULL)
    {
        printf("Echec de la liberation de la matrice\n");
        exit(2);
    }

    mat->dimLigne = 0;
    mat->dimColonne = 0;
    printf("Matrice correctement liberee\n");
    printf("Fin de la fonction freeMatrix\n\n");
}

/**
    initMatI : retourne une structure comprenant une matrice I
    @param mat : structure comprennant lamatrice I initialisée
*/

void initMatI(MATRIX* mat)
{
    printf("Appel de la fonction initMatI\n");
    int i; // Compteur sur dimLigne
    int j; // Compteur sur dimcolonne

    int dimLigne = mat->dimLigne; // Nombre de lignes
    int dimColonne = mat->dimColonne; // Nombre de colonnes

    printf("Initialisation de la matrice\n");

    for(i=0; i<dimLigne; i++) // Parcours sur dimLigne
    {
        for(j=0; j<dimColonne; j++) // Parcours sur dimColonne
        {
            mat->matrice[i][j] = pow(i,j);
        }
    }
    printf("Fin de la fonction InitMatI\n\n");
}

/**
    createM : retourne la matrice M contenant les moments
    @param Ix : matrice contenant les polynomes de x d'ordre 0 à p
    @param Iy : matrice contenant les polynomes de y d'ordre 0 à q
    @param Im : type BMP contenant l'image, dimX, dimY, et d'autres paramètres
*/

MATRIX createM(MATRIX* Ix, MATRIX* Iy, MATRIX* Im) /* Fonction vérifiée, testée et fonctionnelle */
{
    printf("Appel de la fonction createM\n");
    int i; // Compteur sur p
    int j; // Compteur sur q
    int k; // Compteur sur dimLigne
    int l; // Compteur sur dimColonne

    double somme=0;

    printf("Creation et initialisation de la matrice M\n");
    MATRIX matM = createMatrix(ordre_N, ordre_N);

    printf("Parcours de la matrice M et application de la formule des moments\n");
    for (i=0; i<ordre_N; i++) // Parcours de la matrice sur p
    {
        for (j=0; j<ordre_N-i; j++) // Parcours de la matrice sur q
        {
            for (k=0; k<Im->dimLigne; k++) // Calcul sur dimLigne
            {
                for (l=0; l<Im->dimColonne; l++) // calcul sur dimColonne
                {
                    somme += Ix->matrice[k][i] * Iy->matrice[l][j] * Im->matrice[k][l];
                }
            }
            matM.matrice[i][j] = somme;
            somme = 0;
        }
    }
    printf("Matrice M complete\n");
    printf("Fin de la fonction createM\n\n");
    return matM;
}


/**
    createEta : matrice contenant les moments centrés et normés
    @param matM : matrice contenant les moments
    @param Im : matrice contenant l'image (remplie de 0 et de 1)

*/

MATRIX createEta(MATRIX* matM, MATRIX* Im)
{
    printf("Appel de la fonction createEta\n");
    int i; // Compteur sur p
    int j; // Compteur sur q
    int k; // Compteur sur dimLigne
    int l; // Compteur sur dimColonne

    double somme=0;
    double x_centre=0; // Valeur pour centrer x
    double y_centre=0; // Valeur pour centrer y
    double m_0=0; // Aire de l'image

    printf("Attribution des valeurs des centres et de la surface initiale a partir de la matrice M\n");
    m_0 = matM->matrice[0][0];
    x_centre = matM->matrice[1][0]/m_0;
    y_centre = matM->matrice[0][1]/m_0;

    printf("Surface initiale : %lf\n\n", m_0);
    printf("Centre en x : %lf\n\n", x_centre);
    printf("Centre en y : %lf\n\n", y_centre);

    printf("Creation et initialisation de la matrice eta\n");
    MATRIX eta = createMatrix(ordre_N,ordre_N);

    printf("Parcours de la matrice eta et application de la formule des moments centres et normes\n");
    for (i=0; i<ordre_N; i++) // Parcours de la matrice sur p
    {
        for (j=0; j<ordre_N-i; j++) // Parcours de la matrice sur q
        {
            for (k=0; k<Im->dimLigne; k++) // Parcours sur dimLigne
            {
                for (l=0; l<Im->dimColonne; l++) // Calcul sur dimColonne
                {
                    somme += ( pow(k - x_centre,i)*pow(l - y_centre,j)*Im->matrice[k][l])/pow(m_0,(i+j+2)/2.0);
                }
            }
            eta.matrice[i][j] = somme;
            somme = 0;
        }
    }
    printf("Matrice eta complete\n");
    printf("Fin de la fonction createEta\n\n");
    return eta;
}

/**
    CoeffLeg : Cette fonction calcule les coefficients des polynomes de Legendre
    jusqu'à l'ordre n et renvoie une structure comprennant la matrice et ses dimensions
    @param n : ordre du polynome de Legendre
*/

MATRIX CoeffLeg(int n)
{
    printf("Appel de la fonction CoeffLeg\n");
    int inc1,inc2;

    printf("Creation et initialisation de la matrice A contenant les coefficients de Legendre\n");
    MATRIX coeff_A;
    double** tab = malloc(n*sizeof(double*));

    for(inc1=0;inc1<n;inc1++)
        tab[inc1] = calloc(n,sizeof(double));

    tab[0][0] = 1;
    tab[1][1] = 1;

    printf("Parcours de la matrice et attribution des valeurs\n");
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

    printf("Matrice A complete\n");
    printf("Attribution des valeurs a coeff_A (structure type MATRIX)\n");
    coeff_A.matrice = tab;
    coeff_A.dimLigne = n;
    coeff_A.dimColonne = n;

    printf("Fin de la fonction CoeffLeg\n\n");
    return coeff_A;
}

/**
    val_Leg : Cette fonction renvoie un polynome de Legendre en x d'ordre p
    @param x : valeur dont on veut le polynome de Legendre
    @param p : ordre associé au polynome souhaité
    @param a : structure contenant la matrice des coefficients
*/

double val_Leg(double x, int p, double** CoeffLeg)
{
    if (!p) return 1;

    int i;
    double val = 0;

    for(i=0;i<=p;i++)
        val += (CoeffLeg[p][i] * pow(x,i));

    return val;
}

/**
    createLambda : Cette fonction calcule les moments de Legendre
    @param eta : structure comprennant la matrice de moments centrés et normés
    @param coeff_A : structure contenant la matrice des coefficients
*/

MATRIX createLambda(MATRIX* eta, MATRIX* coeff_A)
{
    printf("Appel de la fonction createLambda\n");
    int incp; // Compteur sur l'ordre p
    int incq; // Compteur sur l'ordre q
    int inci; // Compteur sur la dimension p de eta
    int incj; // Compteur sur la dimension q de eta

    double res=0;

    printf("Creation et initialisation de la matrice lambda\n");
    MATRIX matLambda = createMatrix(ordre_N,ordre_N);

    printf("Parcours de la matrice et application de la formule des moments de Legendre\n");
    /* NB : Ici, on ne calcule que les moments dont les ordres respectent p + q <= N */
    for(incp=0; incp<ordre_N; incp++) // Parcours en p
    {
        for(incq=0; incq< ordre_N-incp; incq++) // Parcours en q
        {
            for (inci=0; inci<=incp; inci++) // Parcours de eta sur p
            {
                for (incj=0; incj<= incq; incj++) // Parcours de eta sur q
                {
                    res += coeff_A->matrice[incp][inci] * coeff_A->matrice[incq][incj] * eta->matrice[inci][incj];
                }
            }
            res *= ((2.0*(double)incp + 1.0)*(2.0*(double)incq + 1.0))/4.0; // Multiplication par le coefficient
            matLambda.matrice[incp][incq] = res;
            res=0;
        }
    }
    printf("Matrice lambda complete\n");

    printf("Fin de la fonction createLambda\n\n");
    return matLambda;
}

/**
    createImgRebuilt : Cette fonction recréé l'image à partir de nos moments de Legendre
    @param dimX : dimension verticale de l'image
    @param dimY : dimension horizontale de l'image
    @param matLambda : structure contenant nos moments de Legendre
    @param coeff_A : structure contenant la matrice de coefficients
*/

MATRIX createImgRebuilt(double dimX, double dimY, MATRIX* matLambda, MATRIX* coeff_A)
{
    printf("Appel de la fonction createImgRebuilt\n");
    int i; // Compteur sur p
    int j; // Compteur sur q
    int incx; // Compteur sur dimX
    int incy; // Compteur sur dimY

    double somme=0;

    double valX=0; // Variable intermédiaire
    double x=0; // Valeur de x entre -1 et 1
    double y=0; // Valeur de y entre -1 et 1
    double h_x = 2.0/(dimX-1.0); // Pas sur x
    double h_y = 2.0/(dimY-1.0); // Pas sur y

    printf("Creation de la matrice imgRebuilt\n");
    MATRIX imgRebuilt = createMatrix(dimX, dimY);

    printf("Parcours de la matrice et attribution des valeurs\n");
    printf("Veuillez patienter pendant que la reconstruction s'effectue. Il n'y a pas de bug");
    printf(", la fonction est juste assez longue pour certaines images (notamment le I) a cause ");
    printf("des dimensions des images. Le calcul peut prendre entre 1 a 4 minutes suivant les");
    printf(" materiels que vous utilisez.\n\n");

    for(incx=0; incx<dimX; incx++) // Parcours de l'image reconstruite sur x
    {
        x = -1.0 + incx*h_x;
        for(incy=0; incy<dimY; incy++) // Parcours de l'image reconstruite sur y
        {
            y = -1.0 + incy*h_y;
            for (i=0;i<ordre_N;i++) // Parcours de matLambda en p
            {
                valX = val_Leg(x,i,coeff_A->matrice);
                for(j=0;j<ordre_N-i;j++) // Parcours de matLambda en q
                {
                    somme += matLambda->matrice[i][j]*valX*val_Leg(y,j,coeff_A->matrice);
                }
            }
            if(somme>0.5) // Application d'un seuil pour avoir une image composée de 0 et de 1
            {
                imgRebuilt.matrice[incx][incy]=1;
            }
            else
            {
                imgRebuilt.matrice[incx][incy]=0;
            }
            somme=0;
        }
    }

    printf("Fin de la fonction createImgRebuilt\n\n");
    return imgRebuilt;
}

/**
    recupLambdaRef : Permet de recuperer la matrice lambda_ref
    @param str : emplacement du fichier texte
    @param matLambdaRef : matrice qui contient les valeurs du fichier txt apres récupération
*/

void recupLambdaRef(char* str, MATRIX* matLambdaRef)
{
    FILE* fichier=NULL;
    int i; // Compteur sur p
    int j; // Compteur sur q

    printf("Appel de la fonction recupLambdaRef\n");
    fichier = fopen(str,"r"); // Ouverture du fichier

    if(fichier==NULL)
    {
        printf("Erreur d'ouverture du fichier\n\n");
        exit(4);
    }

    printf("Recuperation des valeurs depuis le fichier texte\n\n");
    for(i=0; i<ordre_N; i++) // Parcours sur p
    {
        for(j=0; j<ordre_N; j++) // Parcours sur q
        {
            if(j>ordre_N-1-i) // Le fichier ne contient pas les valeurs ne respectant pas p + q <= N
            {
                matLambdaRef->matrice[i][j]=0;
            }
            else // Sinon on lit simplement les valeurs
            {
                fscanf(fichier,"%lf",&(matLambdaRef->matrice[i][j]));
            }
        }
    }

    fclose(fichier);
    printf("Fin de la fonction recupLambdaRef\n\n");
}

/**
    printMat : Affiche la matrice M
    @param matM : structure comportant la matrice et ses dimensions

*/

void printMat(MATRIX* matM)
{
    printf("Appel de la fonction printMat\n");
    int i; // Compteur sur x
    int j; // Compteur sur y

    printf("Affichage de la matrice\n");
    for (i=0; i<matM->dimLigne; i++)
    {
        for (j=0; j<matM->dimColonne; j++)
        {
            printf("%lf\t", matM->matrice[i][j]);
        }
        printf("\n");
    }

    printf("Fin de la fonction printMat\n\n");
}

/**
    printMatScient : Affiche la matrice M en écriture scientifique
    @param matM : structure comportant la matrice et ses dimensions

*/

void printMatScient(MATRIX* matM)
{
    printf("Appel de la fonction printMat\n");
    int i; // Compteur sur x
    int j; // Compteur sur y

    printf("Affichage de la matrice\n");
    for (i=0; i<matM->dimLigne; i++)
    {
        for (j=0; j<matM->dimColonne; j++)
        {
            printf("%le\t", matM->matrice[i][j]);
        }
        printf("\n");
    }

    printf("Fin de la fonction printMat\n\n");
}

/**
    printImg : Affiche la matrice M
    @param matM : structure comportant la matrice et ses dimensions

*/

void printImg(BmpImg* matImg)
{
    printf("Appel de la fonction printImg\n");
    int i; // Compteur sur x
    int j; // Compteur sur y

    printf("Affichage de la matrice contenant l'image\n");
    for (i=0; i<matImg->dimX; i++)
    {
        for (j=0; j<matImg->dimY; j++)
        {
            printf("%d\t", matImg->img[i][j]);
        }
        printf("\n");
    }

    printf("Fin de la fonction printImg\n\n");
}
