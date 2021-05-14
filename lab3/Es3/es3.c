#include <stdio.h>
#define inFile "../numeri.txt"
#include <math.h>

void VerificaSequenza(FILE *fin);

int main() {
    FILE *fin;

    if((fin = fopen(inFile, "r")) == NULL){
        printf("Errore durante l'apertura del file\n");
        return 1;
    }

    VerificaSequenza(fin);
    fclose(fin);
    return 0;
}

void VerificaSequenza(FILE *fin){
    int numCorrente, numPrec1, numPrec2, numMax, numMin, scartati = 0;

    fscanf(fin, "%d", &numPrec1);
    fscanf(fin, "%d", &numPrec2);
    numMax = fmax(numPrec1, numPrec2);
    numMin = fmin(numPrec1, numPrec2);

    while(fscanf(fin, "%d", &numCorrente) != EOF){

        if((numCorrente == numPrec1 + numPrec2) || (numCorrente == numPrec1  - numPrec2) || (numCorrente == numPrec1 * numPrec2) || (numPrec2 != 0 && numCorrente == numPrec1 / numPrec2)){
            numMax = fmax(numMax, numCorrente);
            numMin = fmin(numMin, numCorrente);
            numPrec1 = numPrec2;
            numPrec2 = numCorrente;
        }

        else {scartati++;}
    }

    printf("Numero massimo: %d\n", numMax);
    printf("Numero minimo: %d\n", numMin);

    if (scartati == 0){
        printf("Tutti i dati rispettano la regola\n");
    }
    else{
        printf("Numeri scartati: %d\n", scartati);
    }
}