#include <stdio.h>
#include <string.h>
#define maxLen 31
#define maxRighe 1000

//possibili opzioni menù
typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
}comando_e;

//struttura dati che salva le info presenti nel file
typedef struct{
    char codice_tratta[maxLen], partenza[maxLen], destinazione[maxLen];
    char data[11];
    int ritardo;
}infoTratte;

//dichiarazione funzioni
comando_e leggiComando();
void leggiFile(FILE *fin, int numTratte, infoTratte info[]);
void menuParola(int numTratte, infoTratte info[]);
void date(int numTratte, infoTratte info[]);
void partenze(int numTratte, infoTratte info[]);
void destinazioni(int numTratte, infoTratte info[]);
void ritardi(int numTratte, infoTratte info[]);
void ritardi_tot(int numTratte, infoTratte info[]);

//main
int main() {
    FILE *fin;
    infoTratte info[maxRighe];
    int numTratte;

    if((fin = fopen("../log.txt", "r")) == NULL){
        printf("errore durante l'apertura del file \n");
        return 1;
    }

    fscanf(fin, "%d", &numTratte);
    leggiFile(fin, numTratte, info);
    fclose(fin);
    menuParola(numTratte, info);

    return 0;
}


comando_e leggiComando(){
    comando_e c;
    char cmd[12];

    char tabella[r_err][12] = {
            "date", "partenza", "capolinea", "ritardo", "ritardo_tot" , "fine"
    };

    printf("inserire comando (date, partenza, capolinea, ritardo, ritardo_tot, fine) seguito dalle informazioni necessarie: \n");
    scanf("%s", cmd);
    strlwr(cmd);

    c = r_date;
    while(c < r_err && strcmp(cmd, tabella[c]) != 0) {
        c++;
    }

    return c;
}


void menuParola(int numTratte, infoTratte info[]) {
    comando_e comando;
    int continua = 1;

    while (continua) {

        comando = leggiComando();

        switch (comando) {
            case r_date:
                date(numTratte, info);
                break;
            case r_partenza:
                partenze(numTratte, info);
                break;
            case r_capolinea:
                destinazioni(numTratte, info);
                break;
            case r_ritardo:
                ritardi(numTratte, info); break;
            case r_ritardo_tot:
                ritardi_tot(numTratte, info); break;
            case r_fine:
                continua = 0; break;
            default:
                printf("comando digitato non valido\n");
        }

        fflush(stdin);

    }
}


void leggiFile(FILE *fin, int numTratte, infoTratte info[]){
    for(int i = 0; i < numTratte; i++){
        fscanf(fin,"%s%s%s%s%*s%*s%d", info[i].codice_tratta, info[i].partenza, info[i].destinazione, info[i].data, &info[i].ritardo);
    }
}

void date(int numTratte, infoTratte info[]){
    char dataI[11], dataF[11];

    scanf("%s", dataI);
    scanf("%s", dataF);

    printf("le corse nell'intervallo di date selezionato sono: \n");

    for(int i = 0; i < numTratte; i++){
        if(strcmp(info[i].data, dataI) != -1 && strcmp(dataF, info[i].data) != -1 ){
            printf("%s %s %s %s %d\n", info[i].codice_tratta, info[i].partenza, info[i].destinazione, info[i].data, info[i].ritardo);
        }
    }
}


void partenze(int numTratte, infoTratte info[]){
    char part[maxLen];

    scanf("%s", part);

    printf("le corse partite da %s sono: \n", part);

    for(int i = 0; i < numTratte; i++){
        if(strcmp(part, info[i].partenza) == 0){
            printf("%s %s %s %s %d\n", info[i].codice_tratta, info[i].partenza, info[i].destinazione, info[i].data, info[i].ritardo);
        }
    }
}


void destinazioni(int numTratte, infoTratte info[]){
    char dest[maxLen];

    scanf("%s", dest);

    printf("le corse arrivate a %s sono: \n", dest);

    for(int i = 0; i < numTratte; i++){
        if(strcmp(dest, info[i].destinazione) == 0){
            printf("%s %s %s %s %d\n", info[i].codice_tratta, info[i].partenza, info[i].destinazione, info[i].data, info[i].ritardo);
        }
    }
}


void ritardi(int numTratte, infoTratte info[]){
    char dataI[11], dataF[11];

    scanf("%s", dataI);
    scanf("%s", dataF);

    printf("le corse nell'intervallo di date selezionato che sono arrivate in ritardo sono: \n");

    for(int i = 0; i < numTratte; i++){
        if(info[i].ritardo != 0 && strcmp(info[i].data, dataI) != -1 && strcmp(dataF, info[i].data) != -1){
            printf("%s %s %s %s %d\n", info[i].codice_tratta, info[i].partenza, info[i].destinazione, info[i].data, info[i].ritardo);
        }
    }

}



void ritardi_tot(int numTratte, infoTratte info[]){
    int ritardo_tot = 0;
    char codice[maxLen];

    scanf("%s", codice);

    for(int i = 0; i < numTratte; i++){
        if(strcmp(codice, info[i].codice_tratta) == 0){
            ritardo_tot += info[i].ritardo;
        }
    }

    printf("il ritardo totale delle corse %s e': %d\n", codice, ritardo_tot);
}