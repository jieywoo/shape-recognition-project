#ifndef CREATIONMOMENTS_H_INCLUDED
#define CREATIONMOMENTS_H_INCLUDED

#include "reconnaissanceFormes.h"

/**
    choixBmpImg : Permet de choisir quelle image on souhaite tester dans notre
    base de données
    @param choix : choix de l'image a récupérer
*/

void choixBmpImg(int choix, BmpImg* img);

/**
    convValImg : Convertion des valeurs de l'image (0 ou 255) en 0 ou 1
    exploitables par nos fonctions.
    @param imgIn : structure image dont on veut récupérer les valeurs
*/

MATRIX convImg2Mat(BmpImg* imgIn);

/**
    convMat2Img : Convertion d'une matrice en une image
    @param imgIn : structure image dont on veut récupérer les valeurs
*/

BmpImg convMat2Img(MATRIX* imgIn);

/**
    createMatrix : retourne une struture de type MATRIX
    dont la matrice est de taille dimLigne * dimcolonne
    @param dimLigne : nombre de lignes de la matrice
    @param dimColonne : nombre de colonnes de la matrice
*/

MATRIX createMatrix(int dimLigne, int dimColonne);

/**
    freeMatrix : Cette fonction libère les matrices
    contenu dans les structures MATRIX
    @param mat : matrice à liberer
*/

void freeMatrix(MATRIX* mat);

/**
    initMatI : retourne une structure comprenant une matrice I
    @param mat : structure comprennant lamatrice I initialisée
*/

void initMatI(MATRIX* mat);

/**
    createM : retourne la matrice M contenant les moments
    @param Ix : matrice contenant les polynomes de x d'ordre 0 à p
    @param Iy : matrice contenant les polynomes de y d'ordre 0 à q
    @param Im : type BMP contenant l'image, dimX, dimY, et d'autres paramètres
*/

MATRIX createM(MATRIX* Ix, MATRIX* Iy, MATRIX* Im);

/**
    createEta : matrice contenant les moments centrés et normés
    @param matM : matrice contenant les moments
    @param Im : matrice contenant l'image (remplie de 0 et de 1)

*/

MATRIX createEta(MATRIX* matM, MATRIX* Im);

/**
    CoeffLeg : Cette fonction calcule les coefficients des polynomes de Legendre
    jusqu'à l'ordre n et renvoie une structure comprennant la matrice et ses dimensions
    @param n : ordre du polynome de Legendre
*/

MATRIX CoeffLeg(int n);

/**
    val_Leg : Cette fonction renvoie un polynome de Legendre en x d'ordre p
    @param x : valeur dont on veut le polynome de Legendre
    @param p : ordre associé au polynome souhaité
    @param a : structure contenant la matrice des coefficients
*/

double val_Leg(double x, int p, double** CoeffLeg);

/**
    createLambda : Cette fonction calcule les moments de Legendre
    @param eta : structure comprennant la matrice de moments centrés et normés
    @param coeff_A : structure contenant la matrice des coefficients
*/

MATRIX createLambda(MATRIX* eta, MATRIX* coeff_A);

/**
    createImgRebuilt : Cette fonction recréé l'image à partir de nos moments de Legendre
    @param dimX : dimension verticale de l'image
    @param dimY : dimension horizontale de l'image
    @param matLambda : structure contenant nos moments de Legendre
    @param coeff_A : structure contenant la matrice de coefficients
*/

MATRIX createImgRebuilt(double dimX, double dimY, MATRIX* matLambda, MATRIX* coeff_A);

/**
    recupLambdaRef : Permet de recuperer la matrice lambda_ref
    @param str : emplacement du fichier texte
    @param matLambdaRef : matrice qui contiendront les valeurs du fichier txt
*/

void recupLambdaRef(char* str, MATRIX* matLambdaRef);

/**
    printVect : affiche un vecteur
    @param x : taille du vecteur
    @param vect : vecteur

*/

void printVect(int x, double* vect);

/**
    printMat : Affiche la matrice M
    @param matM : structure comportant la matrice et ses dimensions

*/

void printMat(MATRIX* matM);

/**
    printMatScient : Affiche la matrice M en écriture scientifique
    @param matM : structure comportant la matrice et ses dimensions

*/

void printMatScient(MATRIX* matM);

/**
    printImg : Affiche la matrice M
    @param matM : structure comportant la matrice et ses dimensions

*/

void printImg(BmpImg* matImg);

/**
    testEtaManual : Cette fonction permet de tester des valeurs de Eta
    en les insérant manuellement dans la matrice. Uniquement pour test.
    @param matEta : structure contenant la matrice Eta
*/

void testEtaManual(MATRIX* matEta);

#endif // CREATIONMOMENTS_H_INCLUDED
