#include <stdio.h>

int sum_r (int x, int y){
    if(y == 0) return x;
    return 1 + sum_r(x, y-1);
}

void sum_r_coda (int x, int y, int *acc){
    if(y == 0) (*acc)+=x;
    else{
        (*acc)++;
        sum_r_coda(x, y-1, acc);
    }
}

int prodotto_r (int x, int y){
    if(y == 1) return x;
    return x + prodotto_r(x, y-1);
}

void prodotto_r_coda (int x, int y, int *acc){
    if(y != 0){
        (*acc)+= x;
        prodotto_r_coda(x, y-1, acc);
    }
}

int potenza_r (int x, int y){
    if(y == 1) return x;
    return x * potenza_r(x, y-1);
}

void potenza_r_coda (int x, int y, int *acc){
    if(y != 0){
        (*acc)*= x;
        potenza_r_coda(x, y-1, acc);
    }
}

int divisione_intera_r (int x, int y){
    if(x < y) return 0;
    return 1 + divisione_intera_r(x-y, y);
}

void divisione_intera_r_coda (int x, int y, int *acc){
    if(x > y){
        (*acc)++;
        divisione_intera_r_coda(x-y, y, acc);
    }
}

int modulo_r (int x, int y){
    if(x < y) return x;
    return divisione_intera_r(x-y, y);
}

void modulo_r_coda (int x, int y, int *acc){
    if(x > y){
        (*acc) = x-y;
        modulo_r_coda(*acc, y, acc);
    }
}

int main(){
    printf("La somma tra 5 e 5 e': %d\n", sum_r(5, 5));
    int acc = 0;
    sum_r_coda(5, 5, &acc);
    printf("La somma tra 5 e 5 e': %d\n", acc);
    printf("Il prodotto tra 5 e 10 e': %d\n", prodotto_r(5, 10));
    acc = 0;
    prodotto_r_coda(5, 10, &acc);
    printf("Il prodotto tra 5 e 10 e': %d\n", acc);
    printf("La potenza di 5 alla 3 e' %d\n", potenza_r(5, 3));
    acc = 1;
    potenza_r_coda(5, 3, &acc);
    printf("La potenza di 5 alla 3 e': %d\n", acc);
    printf("La divisione intera tra 5 e 2 e': %d\n", divisione_intera_r(5, 2));
    acc = 0;
    divisione_intera_r_coda(5, 2, &acc);
    printf("La divisione intera tra 5 e 2 e': %d\n", acc);
    printf("Il modulo di 5 e 2 e': %d\n", modulo_r(5, 2));
    acc = 0;
    modulo_r_coda(5, 2, &acc);
    printf("Il modulo di 5 e 2 e': %d\n", acc);
    return 0;
}