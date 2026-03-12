#include <stdio.h>

#define DIM_ARRAY 30
#define DIM 1
#define PI 3.14

/* Strutture user-defined */
typedef struct{  // Con typedef possiamo definire un nuovo nome di un tipo di dato sia user-defined che "primitivo"
  char titolo[DIM_ARRAY];
  char autore[DIM_ARRAY];
  int anno_pubblicazione;
} Libro;  // Struttura che descrive un libro

typedef struct{
  float x, y;
}Punto;  // Struttura che contiene le coordinate di un punto

typedef struct{
  Punto centro;  // Possiamo annidare al suo interno altre strutture (come il centro che è anche un punto)
  float raggio;
} Cerchio;  // Struttura che descrive un cerchio

float calcolaArea(Cerchio *cerchio){
  return PI * cerchio->raggio * cerchio->raggio;  // Per scorrere gli attributi di un puntatore a struttura bisogna dereferenziare quindi usando (*struct).attributo oppure struct->attributo
}

void stampa_titolo(Libro libro[]){
  for(int i = 0; i < DIM; i ++){
    printf("Libro (%d) -> titolo: %s\n", i, libro[i].titolo);  // Per scorrere gli attributi di un struttura bisogna usare la notazione punto 
  }
}

int main(){

  Libro libro = {"Harry Potter", "Mattia", 2006};
  Punto centro = {3.0, 6.0};
  Cerchio cerchio = {centro, 3.0};

  stampa_titolo(&libro);
  printf("L'area del cerchio e' %.2f\n", calcolaArea(&cerchio));

  return 0;
}
