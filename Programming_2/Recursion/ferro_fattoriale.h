#ifndef FERRO_FATTORIALE_H
#define FERRO_FATTORIALE_H

unsigned long long int iterative_factorial(int n);

unsigned long long int recursive_factorial(int n);

// Numero di fibonacci: approccio ricorsivo: Altamente inefficiente
unsigned long long int recursive_fibonacci(int n);

// Numero di fibonacci: memoization, ovvero con la ricorsione scendo fino ai casi base e da li costruisco fibonacci con un array dove salvo i fibonacci intermedi
unsigned long long int recursive_efficient_fibonacci(int n);

// Numero di fibonacci: Approccio iterativo ( | spazio: O(1) | tempo: O(n) | )
unsigned long long int iterative_fibonacci(int n);

#endif