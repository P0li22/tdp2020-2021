#include <stdio.h>
#include <math.h>
#define maxLen 20

void leggiMatrice(int matrice[maxLen][maxLen], FILE* fin, int nr, int nc);
void printMatriceMax(int matrice[maxLen][maxLen], int i, int j, int rigaF, int colonnaF, int somma);
void matriciQuadrate(int matrice[maxLen][maxLen], int nr, int nc, int dim);

int main() {
    FILE *fin;
    char inFile[21];
    int matrice[maxLen][maxLen];
    int nr, nc, dim, min;

    printf("inserire il nome del file: \n");
    scanf("%s", inFile);

    if((fin = fopen(inFile, "r")) == NULL){
        printf("errore durante l'apertura del file\n");
        return 1;
    }

    fscanf(fin, "%d%d", &nr, &nc);
    leggiMatrice(matrice, fin, nr, nc);

    printf("inserire la dimensione delle matrici quadrate: \n");
    scanf("%d", &dim);
    min = fmin(nr, nc);

    while(dim >= 1 && dim <= min){
        matriciQuadrate(matrice, nr, nc, dim);

        printf("inserire la nuova dimensione delle matrici quadrate: \n");
        scanf("%d", &dim);
        min = fmin(nr, nc);


    }
    fclose(fin);

    return 0;
}


void leggiMatrice(int matrice[maxLen][maxLen], FILE* fin, int nr, int nc){

    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            fscanf(fin, "%d", &matrice[i][j]);
        }
    }
}


void printMatriceMax(int matrice[maxLen][maxLen], int i, int j, int rigaF, int colonnaF, int somma){
    printf("la matrice con somma degli elementi massima (%d) e': \n", somma);

    for(int r = i; r < rigaF; r++){
        for(int c = j; c < colonnaF; c++){
            printf("%d ", matrice[r][c]);
        }
        printf("\n");
    }
}


void matriciQuadrate(int matrice[maxLen][maxLen], int nr, int nc, int dim){
    int somma = 0, maxSomma = 0, r, c, rigaI, colonnaI, rigaF, colonnaF;

    for(int i = 0; i + dim <= nr; i++){

        for(int j = 0; j + dim <= nc; j++){

            for(r = 0; r < dim; r++){

                for(c = 0; c < dim; c++){

                 printf("%d ", matrice[i + r][j + c]);
                 somma += matrice[i + r][j + c];
                }

                printf("\n");
            }

            printf("\n");

            if(somma > maxSomma){
                rigaI = i; colonnaI = j;
                rigaF = i + r, colonnaF = j + c;
                maxSomma = somma;
            }
            somma = 0;
        }

    }

    printMatriceMax(matrice, rigaI, colonnaI, rigaF, colonnaF, maxSomma);
}