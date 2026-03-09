/*1) Scrivere un file di testo .txt contenente nomi e cognomi di persone (nomi_cognomi.txt)
  2) Scrivere una funzione che conta tutti i parenti di Mario Rossi
  3) Scrivere in output il file ”parenti.txt” secondo il formato
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prototipi di funzione */
int file_exists(char *filename);
int isParent(char *s, char *surname);
void rimuoviEstensione(char *s, char *p);
void scriviFile(FILE *ptr, char *s, int bool);

int main(int argc, char *argv[]){
  FILE *output, *input;  // I puntatori ai rispetti file di input (cognomi.txt) e output(output_vocali.txt)
  
  /* CONTROLLO ERRORE */
  if(argc != 4){
    printf("Errore: Numero di argomenti errato... Inserire: file_input.txt file_output.txt \"Parente\"");
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
    int parente = 0;  // E' parente oppure no?
    
    while(fgets(filename, sizeof(filename), input)){  // Prendo dal file di input i cognomi
      parente = isParent(filename, argv[3]);  // Controllo se la stringa presa è parente di cognome (argv[3])
      scriviFile(output, filename, parente);
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

void scriviFile(FILE *ptr, char *s, int bool){
  int i = 0;
  fprintf(ptr, "%10s", "Nome:\t");
  for(; s[i] != '\0'; i++){
    if(s[i] != ' '){
      fprintf(ptr, "%c", s[i]);
    }else{
      fprintf(ptr, "%c", '\n');
      i++;
      break;
    }
  }
  fprintf(ptr, "%10s", "Cognome:\t");
  for(; s[i] != '\0' && s[i] != '\n'; i++){
    fprintf(ptr, "%c", s[i]);
  }
  fprintf(ptr, "%c", '\n');
  fprintf(ptr, "%10s%s", "Parente?\t", (bool)? "SI" : "NO");
  fprintf(ptr, "%10s", "\n*****\n\n");
}

/* Controlla se è una vocale oppure no */
int isParent(char *s, char *surname){
  if(strstr(s, surname)) return 1;  // Se è presente la sottostringa ad esempio Rossi allora la stringa s è parente
  return 0;
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
