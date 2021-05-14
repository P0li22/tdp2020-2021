#include <stdio.h>
#include <string.h>
#define MAXLEN 26
#define MAXSEQLEN 6


void ricercaParole(char sequenza[], FILE *testo);

int main(int argc, char *argv[]) {
    FILE *fseq, *testo;
    char sequenza[MAXSEQLEN];
    int ns;

    if(argc != 3){
        printf("numero di argomenti non valido");
        return 1;
    }

    if((testo = fopen(argv[1], "r")) == NULL|| (fseq = fopen(argv[2], "r")) == NULL){
        printf("errore durante l'apertura del file");
        return 2;
    }

    fscanf(fseq, "%d", &ns);
    for(int i = 0; i < ns; i++){
        fscanf(fseq, "%s", sequenza);
        printf("La sequenza %s e' contenuta in:\n", sequenza);
        ricercaParole(strlwr(sequenza), testo);
    }




    return 0;
}


void ricercaParole(char sequenza[], FILE *testo){
    char parola[MAXLEN];
    int i = 1;

    while(fscanf(testo, "%25[a-zA-Z0-9]%*[^a-zA-Z0-9]", parola) == 1){
        if(strstr(strlwr(parola), sequenza)){
            printf("%s (posizione %d)\n", parola, i);
        }
        i++;
    }

    printf("------------------------------------------------------------------------------\n");
    rewind(testo);
}
