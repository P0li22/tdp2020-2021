#include <stdio.h>

//non conviene usare la ricorsione perchè iterare normalmente è più efficiente (il programma è corto e scrivere tutta l'iterazione non è sconveniente)
int main() {
    int n;
    unsigned int xi = 0, x1 = 0, x2 = 1;

    printf("inserire il valore di N: \n");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        printf("%d ", xi);
        xi = x1 + x2;
        x1 = x2;
        x2 = xi;
    }
    return 0;
}
