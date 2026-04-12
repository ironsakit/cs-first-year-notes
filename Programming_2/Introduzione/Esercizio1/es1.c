/*1) Scrivere un file di testo .txt contenente cognomi di persone (cognomi.txt)
  2) Scrivere una funzione che conta il numero di vocali all’interno del cognome e scrive un file contenente ("output_vocali.txt"), per ogni cognome, il numero di vocali.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prototipi di funzione */
int file_exists(char *filename);
int countVowels(char *s);
int isVowel(char c);
void rimuoviEstensione(char *s, char *p);

int main(int argc, char *argv[]){
  FILE *output, *input;  // I puntatori ai rispetti file di input (cognomi.txt) e output(output_vocali.txt)
  
  /* CONTROLLO ERRORE */
  if(argc != 3){
    printf("Errore: Numero di argomenti errato... Inserire: file_input.txt file_output.txt");
    exit(1);
  }
  /* FINE CONTROLLO ERRORE */

  if((input = fopen(argv[1], "r")) != NULL){  // Se il file di input esiste allora possiamo procedere
    int count = 1, error = 1;
    char *punt = NULL;
    char filename[50];
    strcpy(filename, argv[2]);
    do{
      if(file_exists(filename)){  // Se il file da noi inserito esiste ok usciamo dal ciclo 
	error = 0;
      }else{
	error = 1;
	strcpy(filename, argv[2]);  // Mi ricopio la stringa originale (perchè se ci sono più file che provo con lo stesso nome ho bisogno di riprendermi il valore originale)
	rimuoviEstensione(filename, punt);  // Rimuovo l'estensione .txt
	snprintf(filename, sizeof(filename), "%s_%d.txt", filename, count);  // Sennò cerchiamo di cambiarlo mettendoci un numerino davanti che è autoincrementante
	count++;  // Aumento il contatore (questo ci permette di non sovrascrivere possibili file txt che hanno informazioni vitali per il nostro "sistema" es: output.txt, output_1.txt, output_2.txt)
      }
    }while(error);
    
    output = fopen(filename, "w");  // Apriamo finalmente il file in modalità scrittura
    int vocali = 0;  // Numero di vocali all'interno di una stringa
    
    while(fscanf(input, "%s", filename) != EOF){  // Prendo dal file di input i cognomi
      vocali = countVowels(filename);   // Conto le vocali in ogni cognome
      fprintf(output, "Cognome: %s\nVocali: %d\n*****\n", filename, vocali);  // Scrivo nel file di output
    }
    /* Chiudo i file */
    fclose(input);
    fclose(output);
    
  }else{
    printf("ERRORE: il file di input \"%s\" non esiste.", argv[1]);
    exit(2);
  }
  return 0;
}
/* Rimuovo l'estensione .txt */
void rimuoviEstensione(char *s, char *p){
  if((p = strstr(s, ".txt")) != NULL){
    for(; s != p; s++);
    *s = '\0';
  }
  
}
/* Controlla se è una vocale oppure no */
int isVowel(char c){
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return 1;  // E' una vocale
  return 0;
} 
/* Conta le vocali in una stringa */
int countVowels(char *s){
  int count = 0;
  for(; *s != '\0'; s++){
    if(isVowel(*s)){
      count++; // Aumento il numero di vocali
    }
  }
  return count;
}
/* Controlla se un file esiste */
int file_exists(char *filename){
  FILE *check = fopen(filename, "r");  // Apriamo il file in lettura
  if(check != NULL){  // Se non è NULL allora esiste
    fclose(check);  // Chiudo sempre il file
    return 0;
  }
  return 1;  /// altrimenti non esiste
}
