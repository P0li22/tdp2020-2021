#include <stdio.h>
#define MAXLEN 100

// utility functions
void leggiSequenza(FILE *fin, int sequenzaSelection[], int sequenzaInsertion[], int sequenzaShell[], int lenS);

// sorting functions
void SelectionSort(int A[], int N);
void InsertionSort(int A[], int N);
void ShellSort(int A[], int N);

int main(int argc, char *argv[]) {
    FILE *fin;
    int nS, lenS, sequenzaSelection[MAXLEN], sequenzaInsertion[MAXLEN], sequenzaShell[MAXLEN];

    if(argc != 2){
        printf("numero di argomenti non valido");
        return 1;
    }

    if((fin = fopen(argv[1], "r")) == NULL){
        printf("errore durante l'apertura del file");
        return 2;
    }

    fscanf(fin, "%d", &nS);

    for(int i = 0; i < nS; i++){
        printf("SEQUENZA %d\n", i + 1);
        fscanf(fin, "%d", &lenS);

        leggiSequenza(fin, sequenzaSelection, sequenzaInsertion, sequenzaShell, lenS);

        printf("Selection Sort: \n");
        SelectionSort(sequenzaSelection, lenS);

        printf("Insertion Sort: \n");
        InsertionSort(sequenzaInsertion, lenS);

        printf("Shell Sort: \n");
        ShellSort(sequenzaShell, lenS);

        printf("_______________________________________________________\n");
    }


    return 0;
}


void SelectionSort(int A[], int N) {
    int i, j, l = 0, r = N - 1, min, numScambi = 0, iCicloEsterno = 0, iCicloInterno, numI = 0;
    int temp;
    for (i = l; i < r; i++, numI++, iCicloEsterno++) {
        min = i;
        for (j = i + 1, iCicloInterno = 0; j <= r; j++, numI++, iCicloInterno++) {
            if (A[j] < A[min])
                min = j;
        }
        printf("|-Iterazioni ciclo interno (%d) : %d\n", i, iCicloInterno);
        if (min != i) {
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
            numScambi++;
        }
    }

    printf("|-Scambi = %d\n|-Iterazioni ciclo esterno: %d\n|-Iterazioni tot = %d\n\n", numScambi, iCicloEsterno, numI);


}


void InsertionSort(int A[], int N) {
    int i, j, l = 0, r = N - 1, x, numScambi = 0, iCicloEsterno = 0, iCicloInterno, numI = 0;
    for (i = l + 1; i <= r; i++, iCicloEsterno++, numI++) {
        x = A[i];
        j = i - 1;
        iCicloInterno = 0;
        while (j >= l && x < A[j]) {
            A[j + 1] = A[j];
            numScambi++;
            j--;
            iCicloInterno++;
            numI++;
        }
        printf("|-Iterazioni ciclo interno (%d) : %d\n", i, iCicloInterno);
        A[j + 1] = x;
    }
    printf("|-Scambi = %d\n|-Iterazioni ciclo esterno: %d\n|-Iterazioni tot = %d\n\n", numScambi, iCicloEsterno, numI);
}


void ShellSort(int A[], int N) {
    int i, j, x, l = 0, iter = 0, r = N - 1, h = 1, numScambi = 0, iCicloEsterno = 0, iCicloInterno, numI = 0;
    while (h < N / 3)
        h = 3 * h + 1;
    while (h >= 1) {
        for (i = l + h, iCicloInterno = 0; i <= r; i++, iCicloInterno++, numI++) {
            j = i;
            x = A[i];
            while (j >= l + h && x < A[j - h]) {
                A[j] = A[j - h];
                numScambi++;
                iCicloInterno++;
                numI++;
                j -= h;
            }
            A[j] = x;
        }
        h = h / 3;
        iter++;
        printf("|-Iterazioni ciclo interno (%d) : %d\n", iter, iCicloInterno);
        iCicloEsterno++;
        numI++;
    }
    printf("|-Scambi = %d\n|-Iterazioni ciclo esterno: %d\n|-Iterazioni tot = %d\n\n", numScambi, iCicloEsterno, numI);
}


void leggiSequenza(FILE *fin, int sequenzaSelection[], int sequenzaInsertion[], int sequenzaShell[], int lenS){
    for(int i = 0; i < lenS; i++){
        int val;
        fscanf(fin, "%d", &val);
        sequenzaSelection[i] = sequenzaInsertion[i] = sequenzaShell[i] = val;
    }
}