#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fattoriale di un numero: Approccio iterativo (con for)
unsigned long long int iterative_factorial(const int n)
{
    unsigned long long int res = 1;
    for (int i = 1; i <= n; i++) res*=i;
    return res;
}

// Fattoriale di un numero: Approccio ricorsivo ( | spazio: O(n) | tempo: O(n) | )
unsigned long long int recursive_factorial(int n)
{
    if (n == 0) return 1;  // Passo base (mi permette di arrestare la ricorsione)
    return n * recursive_factorial(n - 1);  // Passo ricorsivo
}

// Numero di fibonacci: approccio ricorsivo: Altamente inefficiente
unsigned long long int recursive_fibonacci(const int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

// Numero di fibonacci: memoization, ovvero con la ricorsione scendo fino ai casi base e da li costruisco fibonacci con un array dove salvo i fibonacci intermedi
unsigned long long int efficient_fibonacci(const int n, unsigned long long int memo[])
{
    // Ho convertito -1 in (unsigned long long int) perchè ovviamente non esistono i negativi con unsigned ed è cattiva pratica non castarlo (compare il warning dal compilatore) anche se lo fa da solo il C (lo converte in ULLONG_MAX = 18.446.744.073.709.551.615)
    if (memo[n] != (unsigned long long int)-1) return memo[n];
    if (n == 0) return 0;
    if (n == 1) return 1;
    memo[n] = efficient_fibonacci(n - 1, memo) + efficient_fibonacci(n - 2, memo);
    return memo[n];
}

unsigned long long int recursive_efficient_fibonacci(const int n)
{
    unsigned long long int *memo = (unsigned long long int *)malloc((n + 1) * sizeof(unsigned long long int));
    if (memo != NULL)
    {
        memset(memo, -1, (n + 1) * sizeof(unsigned long long int));
        const unsigned long long int res = efficient_fibonacci(n, memo);
        free(memo);
        return res;
    }
    fprintf(stderr, "Problema di allocazione con l'array memo.\n");
    return -1;
}

// Numero di fibonacci: Approccio iterativo ( | spazio: O(1) | tempo: O(n) | )
unsigned long long int iterative_fibonacci(const int n)
{
    // Casi base
    if (n == 0 || n == 1) return n;
    unsigned long long int fib = 0, fibA = 0, fibB = 1;
    // Per calcolare il fibonacci n-esimo prendo i due numeri prima li sommo e mi sposto in avanti con la "finestra di fibonacci"
    for (int i = 2; i <= n; i++)
    {
        fib = fibA + fibB;  // 0 + 1 | 1 + 1 | 2 + 1 | 3 + 2
        fibA = fibB;  // 1 | 1 | 2 | 3
        fibB = fib;   // 1 | 2 | 3 | 5
    }
    return fib;
}