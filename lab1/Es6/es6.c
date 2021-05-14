#include <stdio.h>

void StampaRisultati(float op1, float op2, float risultato, char operatore, FILE *outFile);

int main() {
    FILE *inFile;
    FILE *outFile;
    char operatore;
    float op1, op2, risultato;

    if((inFile = fopen("../operazioni.txt", "r")) == NULL){
        printf("file input non trovato");
        return 1;
    }

    outFile = fopen("../risultati.txt", "w"); //controllo == NULL non necessario perchè il file verrebbe creato se non esistesse

    while ((operatore = fgetc(inFile)) != EOF) {
        fscanf(inFile, "%f", &op1);
        fscanf(inFile, "%f", &op2);

        StampaRisultati(op1, op2, risultato, operatore, outFile);
        operatore = fgetc(inFile);
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}


void StampaRisultati(float op1, float op2, float risultato, char operatore, FILE *outFile) {

    switch (operatore) {
        case '+':
            risultato = op1 + op2;
            break;
        case '-':
            risultato = op1 - op2;
            break;
        case '*':
            risultato = op1 * op2;
            break;
        case '/':

            if (op2 == 0) {
                fprintf(outFile, "operazione impossibile\n"); //divisione per 0
                return;
            }
            else {
                risultato = op1 / op2;
            }

            break;
        default:
            fprintf(outFile, "operazione non valida\n");
            return;

    }

    fprintf(outFile, "%c %.2f\n", operatore, risultato);
}