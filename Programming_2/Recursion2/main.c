#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Ricorsione Array

// Somma di un array (somma partendo dall'ultimo elemento e arriva al primo elemento)
int sum_array_r(int a[], int n)  // TEMPO: O(n) | SPAZIO = O(n)
{
    if (n == 0) return a[0];  // quando arriva a n == 0 vuol dire che sono arrivato dall'ultimo elemento fino al primo
    return a[n] + sum_array_r(a, n-1);
}

// Stampa dell'array in modo diretto
void print_array_r(int a[], int n)  // TEMPO: O(n) | SPAZIO = O(n)
{
    if (n != -1) // appena n == -1 non ha più senso continuare la ricorsione
    {
        print_array_r(a, n-1);  // richiama (così arrivo fino all'inizio e ritorno indietro)
        printf("%d ",a[n]);
    }
}

// Stampa dell'array in modo inverso
void print_array_r_reverse(int a[], int n)  // TEMPO: O(n) | SPAZIO = O(n)
{
    if (n != -1)  // appena n == -1 non ha più senso continuare la ricorsione
    {
        printf("%d ",a[n]);  // questa volta stampo prima e poi richiamo (così stampo dal fondo fino all'inizio)
        print_array_r_reverse(a, n-1);
    }
}

// trova il minimo in generale tra due numeri
int min(int a, int b)
{
    return a < b ? a : b;
}

// Trovare il minimo in un array
int min_array_r (int a[], int n)
{
    if (n == 0) return a[0];
    return min(a[n], min_array_r(a, n-1));  // ricorsivamente andiamo il minimo in un array è tra l'ultimo elemento e il resto dell'array
}
// STESSA COSA SI PUO' FARE CON IL MASSIMO

// trova l'indice di un elemento in un array
int trova_indice_array_r (int a[], int n, int x)
{
    if (n == -1) return -1;  // se esco dall'array allora restituisco -1
    if (a[n] == x) return n;  // se lo trovo restituisco l'indice
    return trova_indice_array_r(a, n-1, x);  // sennò continuo a cercare
}

// Controlla se un array è palindromo o no (ovvero se si legge uguale da sinistra verso destra e da destra verso sinistra)
int is_palindrome_array_r (int a[], int left, int right)
{
    if (a[left] != a[right]) return 0;
    if (left < right)
    {
        return is_palindrome_array_r(a, left+1, right-1);
    }
    return 1;
}

// Conta le occorrenze di x nell'array
int count_occ_r(int a[], int n, int x)
{
    if (n == -1) return 0;  // se esco dall'array nulla restituisco 0
    if (a[n] == x) return 1 + count_occ_r(a, n-1, x);  // se ne trovo uno aggiungo 1 e vado avanti
    return count_occ_r(a, n-1, x);  // sennò vado semplicemente avanti
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

    // Ricorsione Array

    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int dim = 10;

    print_array_r(array, dim-1);
    printf("\n");

    print_array_r_reverse(array, dim-1);
    printf("\n");

    int n = 4, pos;
    pos = trova_indice_array_r(array, dim-1, n);
    if (pos != -1) printf("Il numero %d si trova alla posizione %d.", n, pos);
    else printf("L'elemento %d non e' presenten nell'array.\n", n);

    int array2[] = {1,2, 2, 1};
    int dim2 = 4;
    printf("\nl'array %s palindromo.", is_palindrome_array_r(array2, 0, dim2 - 1) == 1 ? "e'" : "non e'");

    return 0;
}