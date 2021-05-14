#include <stdio.h>
#include <ctype.h>

#define LEN 21

int codifica(FILE *fin, FILE *fout);

int decodifica(FILE *fin, FILE *fout);


int main() {
    FILE *inFile;
    FILE *outFile;
    char scelta;
    char nomeFin[LEN], nomeFout[LEN];

    printf("inserire il nome del file di input(max 20 caratteri): \n");
    gets(nomeFin);

    if ((inFile = fopen(nomeFin, "r")) == NULL) { //da correggere
        printf("file input non trovato");
        return 1;
    }

    printf("inserire il nome del file di output(max 20 caratteri): \n");
    gets(nomeFout);
    outFile = fopen(nomeFout, "w");

    printf("inserire operazione da effettuare: [C]odifica o [D]ecodifica? \n");
    scelta = toupper(getc(stdin));

    switch (scelta) {
        case 'C':
            printf("numero di caratteri scritti nel file di output: %d\n", codifica(inFile, outFile));
            break;
        case 'D':
            printf("numero di caratteri scritti nel file di output: %d\n", decodifica(inFile, outFile));
            break;
        default:
            printf("operazione non valida");
            fclose(inFile);
            return 2;
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}


int codifica(FILE *fin, FILE *fout) {

    char charPrecedente, charCorrente;
    int k = 0, caratteriScritti = 0;
    int num, h, carattere;

    charCorrente = getc(fin);

    while (charCorrente != EOF) {

        if (isalpha(charCorrente) && isalpha(charPrecedente)) {
            h = toupper(charPrecedente) - 'A';
            carattere = charCorrente + h;
            if(carattere > 'Z' && isupper(charCorrente)){
                while(carattere >'Z'){
                    carattere -= 26;
                }
            }
            else if(carattere > 'z' && islower(charCorrente)){
                while(carattere > 'z'){
                    carattere -= 26;
                }
            }
            fprintf(fout, "%c", carattere);
            caratteriScritti++;
            charPrecedente = carattere;

        }

        else if (isdigit(charCorrente)) {
            num = (charCorrente - '0') + k;
            while (num >= 10) {
                num -= 10;
            }
            fprintf(fout, "%d", num);
            k++;
            caratteriScritti++;
            charPrecedente = num;
        }

        else {
            fprintf(fout, "%c", charCorrente);
            charPrecedente = charCorrente;
        }

        charCorrente = getc(fin);
    }

    return caratteriScritti;
}


int decodifica(FILE *fin, FILE *fout) {
    char charPrecedente, charCorrente;
    int k = 0, caratteriScritti = 0;
    int num, h, carattere;

    charCorrente = getc(fin);

    while(charCorrente != EOF){

        if (isalpha(charCorrente) && isalpha(charPrecedente)){
            h =toupper(charPrecedente) - 'A';
            carattere = charCorrente - h;
            if(carattere < 'A' && isupper(charCorrente)){
                while(carattere < 'A'){
                    carattere += 26;
                }
            }
            else if(carattere < 'a' && islower(charPrecedente)){
                while(carattere < 'a'){
                    carattere += 26;
                }
            }
            fprintf(fout, "%c", carattere);
            caratteriScritti++;
            charPrecedente = charCorrente;
        }

        else if(isdigit(charCorrente)){
            num = (charCorrente - '0') - k;
            while(num < 0){
                num += 10;
            }
            fprintf(fout, "%d", num);
            k++;
            caratteriScritti++;
            charPrecedente = num;
        }

        else{
            fprintf(fout, "%c", charCorrente);
            charPrecedente = charCorrente;
        }
        charCorrente = getc(fin);

    }

    return caratteriScritti;
}
