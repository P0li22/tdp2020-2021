#include <stdio.h>
#include <ctype.h>

int comprimi(FILE *fin, FILE *fout);

int decomprimi(FILE *fin, FILE *fout);


int main() {
    FILE *inFile;
    FILE *outFile;
    char scelta;

    printf("inserire operazione da effettuare: [C]ompressione o [D]ecompressione? \n");
    scelta = toupper(getc(stdin));

    switch (scelta) {
        case 'C':

            if ((inFile = fopen("../sorgente.txt", "r")) == NULL) {
                printf("errore durante l'apertura del file\n");
                return 1;
            }

            outFile = fopen("../compresso.txt", "w");
            printf("numero di caratteri scritti nel file di output: %d\n", comprimi(inFile, outFile));
            break;

        case 'D':

            if ((inFile = fopen("../compresso.txt", "r")) == NULL) {
                printf("errore durante l'apertura del file\n");
                return 1;
            }

            outFile = fopen("../decompresso.txt", "w");
            printf("numero di caratteri scritti nel file di output: %d\n", decomprimi(inFile, outFile));
            break;

        default:
            printf("operazione non valida");
            return 2;
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}


int comprimi(FILE *fin, FILE *fout) {
    int count = 0, caratteriScritti = 0;
    char c1, c2;

    c1 = getc(fin);
    c2 = getc(fin);

    while (c2 != EOF) {
        while (c1 == c2 && count < 9) {
            count += 1;
            c1 = c2;
            c2 = getc(fin);
        }

        if (count > 1) {
            fprintf(fout, "%c$%d", c1, count);
            caratteriScritti += 3;
        }

        else if(count == 1){
            fprintf(fout, "%c%c", c1, c1);
            caratteriScritti += 2;
        }

        else {
            fprintf(fout, "%c", c1);
            caratteriScritti += 1;
        }

        c1 = c2;
        c2 = getc(fin);
        count = 0;
    }

    return caratteriScritti;
}


int decomprimi(FILE *fin, FILE *fout) {
    int caratteriScritti = 0;
    char charCorrente, charPrecedente = '\0', ripetizioni;

    charCorrente = getc(fin);

    while (charCorrente != EOF) {

        if (charCorrente == '$') {
            ripetizioni = getc(fin) - '0';
            for (int i = 0; i < ripetizioni; i++) {
                fprintf(fout, "%c", charPrecedente);
                caratteriScritti += 1;
            }
        }
        else{
            fprintf(fout, "%c", charCorrente);
            caratteriScritti += 1;
        }

        charPrecedente = charCorrente;
        charCorrente = getc(fin);
    }
    return caratteriScritti;
}