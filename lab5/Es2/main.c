#include <stdio.h>
#include <string.h>
#define numRicodifiche 30
#define maxLen 200

typedef struct{
    char ricodifica[maxLen + 1]; //ricodifica forse conviene salvarlo in un intero e al momento del print stampare "$%d$", in tal caso occorre modicare leggiDizionario
    char originale[maxLen + 1];

}sost;

void leggiDizionario(FILE *dizionario, int num, sost sostituzioni[]);
void ricodificaFile(FILE *sorgente,FILE *fout, int num, sost sostituzioni[]);

int main() {

    sost sostituzioni[numRicodifiche];
    FILE *sorgente, *dizionario, *fout;
    int num;

    if((sorgente = fopen("../sorgente.txt", "r")) == NULL || (dizionario = fopen("../dizionario.txt", "r")) == NULL){
        printf("errore durante l'apertura del file");
        return 1;
    }

    fout = fopen("../ricodificato.txt", "w");

    fscanf(dizionario, "%d", &num);
    leggiDizionario(dizionario, num, sostituzioni);
    ricodificaFile(sorgente, fout, num, sostituzioni);

    fclose(sorgente);
    fclose(dizionario);
    fclose(fout);

    return 0;
}


void leggiDizionario(FILE *dizionario, int num, sost sostituzioni[]){

    for(int i = 0; i < num; i++){
        fscanf(dizionario, "%s", sostituzioni[i].ricodifica);
        fscanf(dizionario, "%s", sostituzioni[i].originale);
    }

}

void ricodificaFile(FILE *sorgente, FILE *fout, int num, sost sostituzioni[]){

    char riga[maxLen + 1];
    int flagQuit, flagTrovato;

    while(fgets(riga, maxLen,sorgente) != NULL){

        //itera sui caratteri della riga letta
        for(int i = 0; i < strlen(riga); i++){
            flagTrovato = 0;

            //itera sul dizionario
            for(int j =0; flagTrovato == 0 && j < num; j++){
                flagQuit = 0;

                //controlla se "originale" corrisponde a una parte della stringa
                for(int k = 0; flagQuit == 0 && k < strlen(sostituzioni[j].originale); k++){
                    if(riga[i + k] != sostituzioni[j].originale[k]){
                        flagQuit = 1;
                    }
                }

                //se flagQuit == 0 allora è stata trovata una parte del testo da ricodificare
                if(!flagQuit){
                    fprintf(fout, "%s", sostituzioni[j].ricodifica);
                    i += (int)strlen(sostituzioni[j].originale) - 1; //salto i caratteri della stringa che ho ricodificato
                    flagTrovato = 1;
                }

            }

            //stampa i caratteri che non vanno ricodificati
            if(!flagTrovato){
                fprintf(fout, "%c", riga[i]);
            }
        }
    }

}