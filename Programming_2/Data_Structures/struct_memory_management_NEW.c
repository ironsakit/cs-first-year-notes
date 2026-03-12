#include <stdio.h>
#include <stdlib.h>

#define PI 3.14
#define SIZE_MINIMA_LIBRO 5
#define OFFSET_LIBRI 5
#define SIZE_MINIMA_STRINGA 20
#define OFFSET_STRINGA 10

/* Strutture user-defined */
typedef struct{  // Con typedef possiamo definire un nuovo nome di un tipo di dato sia user-defined che "primitivo"
  char *titolo;  // puntatore a char che successivamente allocherò
  char *autore;
  int anno_pubblicazione;
} Libro;  // Struttura che descrive un libro

typedef struct{
  Libro *libri;  // Puntatore di libri
  int dimensione;  // Dimensione della struttura (quanti libri ho allocato)
  int numero_libri;  // Quanti libri ho nella liberia
} Libreria;

/* Qui la funzione è void perchè ho già un puntatore al puntatore di libri (è proprio la libreria) perciò posso subito allocare memoria puntando al puntatore libri */
void alloca_Libreria(Libreria *libreria, size_t size){
  Libro *tmp = (Libro *) calloc(size, sizeof(Libro));  // creo lo spazio minimo per contenere 5 libri (mi assicuro che siano vuoti con calloc)
  if(tmp != NULL){
    libreria->libri = tmp;
    libreria->dimensione = size;
    libreria->numero_libri = 0;
  }else{
    printf("ERRORE ALLOCAZIONE LIBRERIA");
    exit(1);
  }
}

int rialloca_libreria(Libreria *libreria, size_t size_nuova){
  Libro *tmp = (Libro *)realloc(libreria->libri, sizeof(Libro) * size_nuova);
  if(tmp != NULL){
    libreria->libri = tmp;
    libreria->dimensione = size_nuova;
    return 1;
  }
  return 0;
}

void libera_libreria(Libreria *libreria){
  for(int i = 0; i < libreria->numero_libri; i++){
    if(libreria->libri[i].titolo != NULL) free(libreria->libri[i].titolo);
    if(libreria->libri[i].autore != NULL) free(libreria->libri[i].autore);
  }
  free(libreria->libri);
  libreria->dimensione = 0;
  libreria->numero_libri = 0;
}
/* In questo caso visto che devo solo allocare e non restiuire alcun intero, posso tranquillemente resituire un puntatore a char (char *) ovvero la nuova locazione di memoria che ho ottenuto con malloc*/
char *alloca_Stringa(size_t size){
  return (char *) calloc(size, sizeof(char));
}

/* Uso un doppio puntatore, perchè se avessi passato solo (char *) alla funzione avrei passato una copia del puntatore non quello originale e sarebbe rimasto tutto all'interno del recordi di attivazione della funzione rialloca_stringa*/
int rialloca_stringa(char **s, size_t size_nuova){
  char *tmp = (char *)realloc(*s, sizeof(char) * size_nuova);  // Rialloco la stringa s con una nuova dimensione
  if(tmp != NULL){  // Se l'operazione è andata a buon fine realloc resituisce il puntatore alla nuova stringa
    *s = tmp;  // Quindi possiamo tranquillamente puntare a quello locazione di memoria
    return 1;
  }
  return 0;
}

char* scrivi(){
  int c;
  size_t i = 0, len = SIZE_MINIMA_STRINGA;
  char *s = alloca_Stringa(len);  // Alloco spazio minimo per la stringa

  if(s == NULL){  // Controllo se la malloc è andata a buon fine
    printf("ERRORE ALLOCAZIONE STRINGA");
    exit(1);
  }
  
  while((c = getchar()) != '\n' && c != EOF){
    if(i >= len - 1){
      len += OFFSET_STRINGA;
      if(!rialloca_stringa(&s, len)){  // Rialloco una nuova dimensione (+10 caratteri) per la stringa
        printf("ERRORE ALLOCAZIONE STRINGA");
        exit(1);
      }
    }
    s[i] = (char)c;
    i++;
  }
  s[i] = '\0';  // Chiudiamo la stringa
  return s;
}

void liberaBufferInput(){
  int c;
  while((c = getchar()) != '\n' && c != EOF);
}

void Choice(char *c){
  do{
    printf("Vuoi aggiungere un altro libro? (y/n): ");
    scanf(" %c", c);
    if(*c != 'n' && *c != 'N' && *c != 'y' && *c != 'Y'){
      printf("Errore...\n");
    }
    liberaBufferInput();  // Libero il buffer di input (Magari lo scanf prende il '\n' del printf di prima oppure una funzione dopo prende quello stesso '\n')
  }while(*c != 'n' && *c != 'N' && *c != 'y' && *c != 'Y');
}

void assegnaLibri(Libreria *libreria){
  int i = 0;  // Counter dei libri
  char scelta;
  
  do{
    if(i < libreria->dimensione){  // Controlliamo se possiamo mettere ancora libri

      printf("Inserisci le informazioni del %d libro:\n", i+1);

      printf("Titolo:\n");
      libreria->libri[i].titolo = scrivi();

      printf("Autore:\n");
      libreria->libri[i].autore = scrivi();
      
      char *line = NULL;
      int anno = 0;
      do{
	printf("Anno di pubblicazione:\n");
	line = scrivi();
	anno = atoi(line);
	if(anno == 0){
	  printf("Errore.\n");
	}
	free(line);
      }while(anno == 0);
      libreria->libri[i].anno_pubblicazione = anno;

      Choice(&scelta); // Pemette di fare la scelta all'utente
      
      i++;
      libreria->numero_libri++;  // Aumento il numero di libri attualemnte nella libreria
      
    }else{
      if(!rialloca_libreria(libreria, libreria->dimensione + OFFSET_LIBRI)){ // Sennò aggiungo spazio
        printf("ERRORE ALLOCAZIONE LIBRERIA");
        exit(2);
      }
    }
  }while((scelta == 'y' || scelta == 'Y'));
}

void stampa_libreria(Libreria *libreria){
  for(int i = 0; i < libreria->numero_libri; i ++){
    printf("Libro (%d):\n", i+1);
    printf("Titolo: %s\n", libreria->libri[i].titolo);
    printf("Autore: %s\n", libreria->libri[i].autore);
    printf("Data di pubblicazione: %d\n", libreria->libri[i].anno_pubblicazione);
    printf("******\n");
  }
}

int main(){

  Libreria libreria;  // la mia libreria

  alloca_Libreria(&libreria, SIZE_MINIMA_LIBRO);
  assegnaLibri(&libreria);
  printf("\n***I libri nella libreria:***\n\n");
  stampa_libreria(&libreria);
  libera_libreria(&libreria);

  return 0;
}
