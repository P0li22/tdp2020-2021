#include <stdio.h>
#include <ctype.h>
#define inFile "../input.txt"
#define outFile "../testo.txt"

void codifica(FILE *fin, FILE *fout);

int main() {
    FILE *fin;
    FILE *fout;

    if((fin = fopen(inFile, "r")) == NULL){
        printf("errore durante l'apertura del file\n");
        return 1;
    }

    fout = fopen(outFile, "w");
    codifica(fin, fout);
    fclose(fin);
    fclose(fout);
    return 0;
}


void codifica(FILE *fin, FILE *fout){
    char charCorrente, charSuccessivo;
    int flagUpper = 0, count = 0, charOriginali = 0;

    charCorrente = getc(fin);
    charSuccessivo = getc(fin);

    while(charCorrente != EOF) {

        if (count < 25) {

            if (isdigit(charCorrente)) {
                fprintf(fout, "%c", '*');
            }

            else if (ispunct(charCorrente)) {
                fprintf(fout, "%c", charCorrente);

                if (!isspace(charSuccessivo)) {
                    fprintf(fout, "%c", ' ');
                    count++;
                }

                if (charCorrente == '!' || charCorrente == '?' || charCorrente == '.') {
                    flagUpper = 1;
                }
                charOriginali++;
            }

            else if (isalpha(charCorrente) && flagUpper) {
                fprintf(fout, "%c", toupper(charCorrente));
                flagUpper = 0;
                charOriginali++;
            }

            else if (charCorrente == '\n') {
                while (count < 25) {
                    fprintf(fout, "%c", ' ');
                    count++;
                }
                fprintf(fout, "| c: %d\n", charOriginali);
                charOriginali = 0;
                count = -1;
            }

            else {
                fprintf(fout, "%c", charCorrente);
                charOriginali++;
            }

            charCorrente = charSuccessivo;
            charSuccessivo = getc(fin);
            count++;
        }

        else {

            fprintf(fout, "| c: %d\n", charOriginali);
            charOriginali = 0;
            count = 0;
        }

    }

    while (count < 25) {
        fprintf(fout, "%c", ' ');
        count++;
    }

    fprintf(fout, "| c: %d\n", charOriginali);

}