#include <stdio.h>

int main() {
    char operatore;
    float op1, op2, risultato;

    printf("inserire l'operazione da effettuare (+ - * /): \n");
    operatore = getchar();
    printf("inserire i valori di op1 e op2 (float); l'operazione sara' eseguita secondo l'ordine (op1 <operatore> op2): \n");
    scanf("%f %f", &op1, &op2);

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

            if(op2 == 0){
                printf("operazione impossibile\n"); //nota al fondo
                return 1;
            }
            else{
                risultato = op1 / op2;
            }

            break;
        default:
            printf("operatore scelto non valido\n");
            return 1;

    }

    printf("operatore scelto: '%c'; risultato: %f\n", operatore, risultato);
    return 0;
}


//se op2 fosse uguale a zero il programma andrebbe in errore, dato che la divisione per 0 è impossibile considerando
//operazioni di base.