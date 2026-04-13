#include <stdio.h>
#include "ferro_fattoriale.h"

int main(void)
{
    int n = 10;
    printf("Il fattoriale iterativo di %d e' %llu\n\n", n, iterative_factorial(n));
    printf("Il fattoriale ricorsivo di %d e' %llu\n\n", n, recursive_factorial(n));

    int m = 45;
    // Gia dopo i 40 la seconda funzione di fibonacci va molto lentamente (provate a rimuoverla e vedere quanto va veloce la terza)
    printf("Il %d numero di fibonacci iterativo e' %llu\n\n", m, iterative_fibonacci(m));
    printf("Il %d numero di fibonacci ricorsivo inefficiente e' %llu\n\n", m, recursive_fibonacci(m));
    printf("Il %d numero di fibonacci ricorsivo efficiente e' %llu\n\n", m, recursive_efficient_fibonacci(m));
    return 0;
}