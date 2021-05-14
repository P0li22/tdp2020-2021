#include <stdio.h>
#define maxN 30

void sottoSequenze(int V[], int N);

int main() {
    int V[maxN];
    int N;

    printf("inserire la dimensione del vettore:\n");
    while(scanf("%d", &N) == 0 || N <= 0 || N > maxN){
        fflush(stdin); //in modo che lo scanf non legga il carattere newline o eventuali caratteri di troppo
        printf("inserire un valore valido (intero positivo <= 30): \n");
    }

    for(int i = 0; i < N; i++){
        printf("inserire il valore in posizione %d\n", i);
        scanf("%d", &V[i]);
    }

    sottoSequenze(V, N);
    return 0;
}


void sottoSequenze(int V[], int N){
    int maxLen = 0, count = 0, k = 0, j = 0, flagZero;
    int subV[maxN] = {0};

    //trovare la lunghezza massima
    for(int i = 0; i < N; i++){
        if(V[i] != 0){
            count++;
        }
        else{
            if(count > maxLen){
                maxLen = count;
            }
            count = 0;
        }
    }
    if(count > maxLen){
        maxLen = count;
    }

    printf("i sottovettori di dimensione massima contenenti dati non nulli sono:\n");

    //trovare e stampare i sottovettori di lunghezza maxLen che non contengano valori nulli
    while(k <= (N - maxLen)){
        flagZero = 1;
        while(flagZero && j < maxLen){
            if(V[k + j] != 0){
                subV[j] = V[k + j];
                j++;
            }
            else{
                j = 0;
                flagZero = 0;
            }
        }

        if(flagZero){
            printf("( ");
            for(int h = 0; h < maxLen; h++){
                printf("%d ", subV[h]);
            }
            printf(")\n");
            j = 0;
        }

        k++;
    }

}
