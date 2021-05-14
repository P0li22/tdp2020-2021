#include <stdio.h>
#include <math.h>

int MCD(int max, int min);

int main() {
    int n1, n2, max, min;

    printf("Inserimento valori (INTERI POSITIVI):\n");

    do{
        printf("inserire il primo numero:\n");
        scanf("%d", &n1);
    } while(n1 < 0);

    do{
        printf("inserire il secondo numero:\n");
        scanf("%d", &n2);
    } while(n2 < 0);

    max = fmax(n1, n2);
    min = fmin(n1, n2);

    printf("il massimo comun divisore e': %d", MCD(max, min));
    return 0;
}


int MCD(int max, int min){
    int resto;

    resto = max % min;

    if (resto == 0){
        return min;
    }
    else{
        return MCD(min, resto);
    }
}