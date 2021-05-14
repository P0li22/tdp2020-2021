#include <stdio.h>
#define maxN 30

void ruota(int V[maxN], int N, int P, int dir);

int main() {
    int N, P, dir, flagQuit = 0;
    int V[maxN];

    printf("inserire il numero N di valori contenuti nel vettore: \n");

    while(scanf("%d", &N) == 0 || N <= 0 || N > maxN){
        fflush(stdin); //in modo che lo scanf non legga il carattere newline o eventuali caratteri di troppo
        printf("inserire un valore valido (intero positivo <= 30): \n");
    }

    for(int i = 0; i < N; i++){
        fflush(stdin);
        printf("inserire il valore %d: \n", i);
        scanf("%d", &V[i]);
    }

    while(!flagQuit){

        fflush(stdin);
        printf("inserire il numero di posizioni : \n");

        while(scanf("%d", &P) == 0 || P < 0 || P >= N){
            fflush(stdin);
            printf("inserire un valore valido (intero positivo < N): \n");
        }

        if(P == 0){
            flagQuit = 1;
        }
        else{
            printf("ruotare verso destra [-1] o verso sinistra [1]? : \n");

            fflush(stdin);
            while(scanf("%d", &dir) == 0 || (dir != -1 && dir != 1)){
                fflush(stdin);
                printf("inserire un valore valido (1 o -1): \n");
            }

            ruota(V, N, P, dir);

        }
    }


    return 0;
}


void ruota(int V[maxN], int N, int P, int dir){
    int tmp;

    if(dir == -1){

        for(int k = 0; k < P; k++) { //ripete lo shift P volte
            tmp = V[N -1];

            for (int i = N - 1; i > 0; i--) { //shift valori di una posizione
                V[i] = V[i - 1];
            }
            V[0] = tmp;
        }
    }

    else{

        for(int k = 0; k < P; k++){ //ripete lo shift P volte
            tmp = V[0];

            for(int i = 0; i < N; i++){ //shift valori di una posizione
                V[i] = V[i + 1];
            }
            V[N - 1] = tmp;
        }
    }

    printf("il vettore ruotato e' : \n");

    for(int j = 0; j < N; j++){
        printf("%d ", V[j]);
    }

    printf("\n");

}

