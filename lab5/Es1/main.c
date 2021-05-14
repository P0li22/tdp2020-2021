#include <stdio.h>
#define maxSquadre 20
#define maxGiornate 20

void leggiTabella(FILE *fin, int tabella[maxSquadre][maxGiornate], int numSquadre, int numGiornate);
void classifica(int tabella[maxSquadre][maxGiornate], int numSquadre, int numGiornate);

int main() {
    FILE *fin;
    char inFile[21];
    int tabella[maxSquadre][maxGiornate], numSquadre, numGiornate;

    printf("inserire il nome del file: \n");
    gets(inFile);

    if((fin = fopen(inFile, "r")) == NULL){
        printf("errore durante l'apertura del file \n");
        return 1;
    }

    fscanf(fin, "%d%d", &numSquadre, &numGiornate);
    leggiTabella(fin, tabella, numSquadre, numGiornate);
    classifica(tabella, numSquadre, numGiornate);
    fclose(fin);



    return 0;
}


void leggiTabella(FILE *fin, int tabella[maxSquadre][maxGiornate], int numSquadre, int numGiornate){

    for(int i = 0; i < numSquadre; i++){
        for(int j = 0; j < numGiornate; j++){
            fscanf(fin, "%d", &tabella[i][j]);
        }
    }
}


void classifica(int tabella[maxSquadre][maxGiornate], int numSquadre, int numGiornate){
    int sommaPunteggio = 0, maxPunteggio = 0, squadra1 = 0;

    for(int j = 0; j < numGiornate; j++){
        for(int i = 0; i < numSquadre; i++){
            for(int k = 0; k <= j; k++){
                sommaPunteggio += tabella[i][k];
            }

            if(sommaPunteggio > maxPunteggio){
                squadra1 = i;
                maxPunteggio = sommaPunteggio;
            }

            sommaPunteggio = 0;
        }

        printf("alla %d^ giornata la prima in classifica e' la squadra %d\n", j+1, squadra1+1);
    }
}