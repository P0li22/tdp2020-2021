#include <stdio.h>
#define NR 50
#define NC 50

typedef enum {
    false, true
}boolean;

// struttura per memorizzare le regioni con alt/lar/area maggiore;
typedef struct {
    int x, y, h, b, area;
}infoRegioni;

// il vettore di strutture conterrà 3 regioni: alt max, lar max, sup max
typedef enum {
    alt, lar, sup
}criteri;

// utility functions
void leggiMatrice(FILE *fin, int regioni[][NC], int nr, int nc);
boolean checkRegione(int regioni[][NC], int nr, int nc, int i, int j, int *larPtr, int *altPtr);
void printInfo(infoRegioni maxRegioni[]);

// feature functions
void individua(int regioni[][NC], int nr, int nc);


int main(int argc, char *argv[]) {
    FILE *fin;
    int regioni[NR][NC], nr, nc;

    if(argc != 2){
        printf("numero di argomenti non valido");
        return 1;
    }

    if((fin = fopen(argv[1], "r")) == NULL){
        printf("errore durante l'apertura del file");
        return 2;
    }

    fscanf(fin, "%d %d", &nr, &nc);
    leggiMatrice(fin, regioni, nr, nc);

    individua(regioni, nr, nc);

    fclose(fin);


    return 0;
}


void leggiMatrice(FILE *fin, int regioni[][NC], int nr, int nc){
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            fscanf(fin, "%d", &regioni[i][j]);
        }
    }
}



boolean checkRegione(int regioni[][NC], int nr, int nc, int i, int j, int *larPtr, int *altPtr){
    /* riceve in input gli indici di una casella della matrice regioni e restituisce true se
       tale casella rappresenta l'estremo superiore sx di una regione, false altrimenti.
       nel caso true restituisce anche la larghezza e l'altezza della regione trovata */

    //i due flag assumono il valore 0 quando viene trovata una casella bianca
    int flagColonne, flagRighe, countR, countC;
    boolean trovato = false;

    /* se almeno uno tra l'elemento a sx di (i, j) e l'elemento sopra (i, j) è == 1 oppure regioni(i, j) == 0
       allora si salta alla prossima iterazione, perchè di sicuro l'elemento (i, j) non è un estremo superiore
       sx. */

    if ((regioni[i][j] != 0) && ((i - 1 >= 0 && regioni[i - 1][j] == 0) || i == 0) && ((j - 1 >= 0 && regioni[i][j - 1] == 0) || j == 0)) {

        trovato = true;

        // calcola l'altezza della regione con estremo superiore sinistro in (i, j)
        for (countR = 0, flagRighe = 1; flagRighe && (i + countR) < nr;) {

            if (regioni[i + countR][j] == 0) {
                flagRighe = 0;
            }
            else {
                countR++;
            }
        }

        // calcola la larghezza della regione con estremo superiore sinistro in (i, j)
        for (countC = 0, flagColonne = 1; flagColonne && (j + countC) < nc;) {

            if (regioni[i][j + countC] == 0) {
                flagColonne = 0;
            }
            else {
                countC++;
            }
        }

        *larPtr = countR;
        *altPtr = countC;
    }

    return trovato;


}


void individua(int regioni[][NC], int nr, int nc){
    /*
       individua le regioni nere più grandi,
       rispettivamente in termini di:
       (1) alt, (2) lar e (3) area.
    */

    int altezza, larghezza, area, hMax = 0, bMax = 0, aMax = 0;
    infoRegioni maxRegioni[3];

    // itera sugli elementi contenuti nella matrice
    for(int i = 0; i < nr; i++){

        for(int j = 0; j < nc; j++) {

            if (checkRegione(regioni, nr, nc, i, j, &altezza, &larghezza)) {

                area = altezza * larghezza; // area della regione

                /* confronti: il vettore maxRegioni conterrà:
                   - la regione con altezza max in posizione 1
                   - la regione con larghezza max in posizione 2
                   - la regione con area max in posizione 3
                */

                if (altezza > hMax) {
                    maxRegioni[alt].x = i;
                    maxRegioni[alt].y = j;
                    maxRegioni[alt].h = altezza;
                    maxRegioni[alt].b = larghezza;
                    maxRegioni[alt].area = area;
                    hMax = altezza;
                }

                if (larghezza > bMax) {
                    maxRegioni[lar].x = i;
                    maxRegioni[lar].y = j;
                    maxRegioni[lar].h = altezza;
                    maxRegioni[lar].b = larghezza;
                    maxRegioni[lar].area = area;
                    bMax = larghezza;
                }

                if (area > aMax) {
                    maxRegioni[sup].x = i;
                    maxRegioni[sup].y = j;
                    maxRegioni[sup].h = altezza;
                    maxRegioni[sup].b = larghezza;
                    maxRegioni[sup].area = area;
                    aMax = area;
                }
            }
        }

}
    printInfo(maxRegioni);
}


void printInfo(infoRegioni maxRegioni[]){
    printf("(1) Max Altezza: estremo = (%d, %d), alt = %d, lar = %d, area = %d \n", maxRegioni[alt].x, maxRegioni[alt].y, maxRegioni[alt].h, maxRegioni[alt].b, maxRegioni[alt].area);
    printf("(2) Max Larghezza: estremo = (%d, %d), alt = %d, lar = %d, area = %d \n", maxRegioni[lar].x, maxRegioni[lar].y, maxRegioni[lar].h, maxRegioni[lar].b, maxRegioni[lar].area);
    printf("(3) Max Area: estremo = (%d, %d), alt = %d, lar = %d, area = %d \n", maxRegioni[sup].x, maxRegioni[sup].y, maxRegioni[sup].h, maxRegioni[sup].b, maxRegioni[sup].area);
}