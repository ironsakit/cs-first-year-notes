#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int d;
    struct Node *next;
}Node;

typedef Node *Link;

// Creazione nodo (la conosciamo già)
Link creaNodo(int d)
{
    Link newNode = (Link) malloc(sizeof(Node));
    newNode->d = d;
    newNode->next = NULL;
    return newNode;
}

// Crea la lista ricorsivamente da testiera
Link buildList_r()
{
    Link newNode;
    int d;
    printf("Inserire un nuovo elemento in lista:\n");
    scanf("%d", &d);
    if (d >= 0)  // voglio mettere solo numero >= 0, se metto un numero negativo dico che voglio smettere di inserire numeri nella lista
    {
        newNode = creaNodo(d);   // Ogni volta crea il nodo
        newNode->next = buildList_r();  // il suo next sarà uguale al prossimo nodo che creiamo oppure a NULL se vogliamo smettere
        return newNode;
    }
    return NULL;
}

// Stampo la lista ricorivamente
void print_List_r(Link head)
{
    if (head != NULL)  // se non siamo arrivati alla fine
    {
        printf("|%d|->", head->d);  // stampo il nodo
        print_List_r(head->next);  // vado avanti
    }else
    {
        printf("NULL\n");  // puramente estetico
    }
}

// versione di print list però si ferma prima di una carta posizione (pos_max)
void print_List_r_partial(Link head, int pos, int max_pos)
{
    if (head != NULL)
    {
        if (pos < max_pos)
        {
            printf("|%d|->", head->d);
            print_List_r_partial(head->next, pos+1, max_pos);
        }
    }
}

// Libera la memoria in modo ricorsivo
void freeList_r(Link *head)
{
    Link nodo;
    if (*head != NULL)
    {
        nodo = *head;  // prendo il riferimento
        *head = (*head)->next;  // sposto la testa
        free(nodo);  // libero la memoria
        freeList_r(head);  // vado al prossimo nodo alla testa
    }
}

// ------------------------------- FUNZIONI AGGIUNTIVE ------------------------------- //

// duplica la lista inserita (fornendo una testa)
Link duplis_r(Link List)
{
    Link newList;
    int d;
    if (List != NULL)
    {
        newList = creaNodo(List->d);
        newList->next = duplis_r(List->next);
        return newList;
    }
    return NULL;
}

// duplica una lista con condizione x
// in questo caso la condizione è che lista->d > x
Link duplis_r_cond(Link List, int x)
{
    Link newList;
    int d;
    if (List != NULL)
    {
        if (List->d > x)  // se rispetta la condizione crea il nodo e va avanti
        {
            newList = creaNodo(List->d);
            newList->next = duplis_r(List->next);
            return newList;
        }else  // opzionale (ma visivamente più facile da capire)
        {
            return duplis_r(List->next);  // sennò va solo avanti (ovviamente dovrà sempre restituire qualcosa quindi scriveremo return + la funzione ricorsiva)
            // immagina che magari abbiamo già creato il nodo e stiamo andando avanti a cercare il suo next, allora dovremo restituire un nodo o almenio NULL
        }
    }
    return NULL;
}

// inserimento di un nuovo nodo x inserito dopo la prima occorrenza di y
void insertList_r(Link List, int x, int y)
{
    Link newNode;
    if (List != NULL)
    {
        if (List->d == y)
        {
            newNode = creaNodo(x);  // creo il nodo
            newNode->next = List->next;  // faccio puntare il nuovo nodo come il nodo che contiene y
            List->next = newNode;  // il nodo che contiene y punta al nuovo nodo  |y|->|x|->|...|
        }else
        {
            insertList_r(List->next, x, y);  // senno vado avanti
        }
    }
}

// stessa funziona di prima ma mette x ad OGNI occorrenza di y
void insertList_r_all(Link List, int x, int y)
{
    Link newNode;
    if (List != NULL)
    {
        if (List->d == y)
        {
            newNode = creaNodo(x);
            newNode->next = List->next;
            List->next = newNode;
            insertList_r_all(newNode->next, x, y);  // ho messo newNode->next perchè devo saltare il nodo appena inserito per evitare un loop in caso di x = y (avrei potuto mettere list->next->next)
        }else insertList_r_all(List->next, x, y);  // vado semplicemente avanti
    }
}

// Una funzione che elimina ogni occorrenza di x nella lista (dividiamo in due)
// 1) funzione che elimina dalla testa
// 2) funzione che elimina oltre alla testa

void removeFromHead_r(Link *List, int x)
{
    Link tmp;
    if (*List != NULL)
    {
        if ((*List)->d == x)
        {
            tmp = *List;
            *List = (*List)->next;
            free(tmp);
            removeFromHead_r(List, x);
        }
    }
}

void removeInternList_r(Link List, int x)
{
    Link tmp;
    if (List != NULL)
    {
        if (List->next != NULL)
        {
            if (List->next->d == x)
            {
                tmp = List->next;
                List->next = List->next->next;  // salto il nodo con x al suo interno
                free(tmp);  // libero quel nodo
                removeInternList_r(List, x);  // richiamo la funzione con lo stessa "testa" (magari ci sono più nodi x di seguito)
            } else removeInternList_r(List->next, x);  // se non c'è vado avanti
        }
    }
}

void removeAllX(Link *List, int x)  // Ora posso combinarle insieme
{
    removeFromHead_r(List, x);
    removeInternList_r(*List, x);
}

// ------------------ FUNZIONI DEL CAVOLO --------------------------

// funzione che stampa i numeri della lista in posizione multipla di x
void printPos_r(Link List, int pos, int x)
{
    if (List != NULL)
    {
        if (List->d % x == 0) printf("|%d|->", List->d);
        printPos_r(List->next, pos+1, x);
    }else{ printf("NULL\n"); }
}

// Funzione che somma gli elementi della lista
int sumList_r(Link List)
{
    if (List == NULL) return 0;
    return List->d + sumList_r(List->next);
}

// versione di coda
void sumList_r_coda(Link List, int *acc)
{
    if (List != NULL)
    {
        (*acc) += List->d;  // si utilizza un puntatore esterno per salvare il valore
        sumList_r_coda(List->next, acc);  // la chiamata ricorsiva è l'ultimo passo
    }
}

// sum list con condizione, ovvero somma i nodi in posizione multipla di x
int sumList_r_cond(Link List, int pos, int x)
{
    if (List != NULL)
    {
        if ((pos % x) == 0) return List->d + sumList_r_cond(List->next, pos+1, x);  // se troviamo la posizione che rispetta la condizione continuiamo a sommare List->d di quel nodo con la prossima chiamata
        else return sumList_r_cond(List->next, pos+1, x);  // se in quel momento la posizione è sbagliata allora procediamo con la ricorsione (ovviamente dobbiamo sempre restituire qualcosa)
    }
    return 0;
}

// somma dei primi n nodi della lista
int sumList_r_partial(Link list, int pos, int pos_max)
{
    if (list == NULL) return 0;
    if (pos < pos_max)
    {
        return list->d + sumList_r_partial(list->next, pos+1, pos_max);
    }else return 0;
}

// restiruire la somma dei numeri compresi tra n e m (con n < m e n, m > 0) della lista
int sumList_r_between(Link list, int n, int m)
{
    if (list == NULL) return 0;  // ho finito la lista (caso base)
    if (m == 0) return list->d;   // sono arrivato all'ultimo elemento restituisco solo quello
    if (n == 0) return list->d + sumList_r_between(list->next, n, m-1);  // sono arrivato al primo elemento quindi posso iniziare a sommare
    return sumList_r_between(list->next, n-1, m-1);  // non sono ancora arrivato al primo elemento da sommare
}

// visita con finestra, restituisce in output il numero di nodi della lista che sono la somma dei due predecessori immediati
int sumPrefix_r(Link list)
{
    if (list == NULL) return 0;
    if (list->next == NULL) return 0;
    if (list->next->next == NULL) return 0;
    if (list->next->next->d == list->d + list->next->d) return 1 + sumPrefix_r(list->next);
    else return sumPrefix_r(list->next);
}

// restituzione n-esimo elemento
Link nth_r(Link list, int n)
{
    if (list == NULL) return NULL;  // se non lo trova restituisce NULL
    if (n == 0) return list; // se lo trova restituisce il nodo trovato
    nth_r(list->next, n-1);  // sennò va avanti a cercarlo decrementando n (in modo tale da trovare la posizione giusta)
}

// restituire la media dei valori di una lista
double averageList_r(Link List, double sum, double num)  // sum e num sono da inizializzare a zero
{
    if (List == NULL)
    {
        printf("Somma: %.2lf, numero: %.2lf\n", sum, num);
        return sum / num;
    }
    averageList_r(List->next, sum + List->d, num+1);
}

// ---------------------------- RICORSIONE SU PIU' LISTE --------------------------------

// funzione che confronta due liste, che conta quanti elementi della prima lista sono maggiori della seconda lista (contando i nodi mancanti come zero)
int checkGreaterBetweenLists(Link list, Link list2)
{
    if (list == NULL && list2 == NULL) return 0;  // se entrambe le liste sono vuote allora ritorno 0 (caso base)
    if (list != NULL && list2 != NULL)  // se sono ancora piene continuo i controlli normalemente
    {
        if (list->d > list2->d) return 1 + checkGreaterBetweenLists(list->next, list2 ->next);
        else return checkGreaterBetweenLists(list->next, list2 ->next);
    }
    // se una delle due listre ha ancora elementi divido in due casi (lista 1 piena e lista 2 vuota e viceversa)
    if (list != NULL && list2 == NULL)
    {
        if (list->d > 0) return 1 + checkGreaterBetweenLists(list->next, list2);  // visto che i nodi mancanti sono zero, controllo se i nodi della prima lista sono > 0 (che sono i nodi della seconda lista mancanti)
        else return checkGreaterBetweenLists(list->next, list2);
    }
    if (list == NULL && list2 != NULL)
    {
        if (list2->d < 0) return 1 + checkGreaterBetweenLists(list, list2->next);  // visto che i nodi mancanti sono zero, controllo se i nodi della seconda lista sono < 0 (che sono i nodi della prima lista mancanti)
        else return checkGreaterBetweenLists(list, list2->next);
    }
}

// Date due liste, costruire la lista "somma", posizione per posizione (considerando il valore zero per i nodi “mancanti” nella lista piu’ corta).
Link sumBetweenLists(Link list1, Link list2)  // Tempo & Spaziow: O(max(len(list1), len(list2)))
{
    if (list1 == NULL && list2 == NULL) return NULL;
    if (list1 != NULL && list2 != NULL)
    {
        Link newNode = creaNodo(list1->d + list2->d);
        newNode->next = sumBetweenLists(list1->next, list2->next);
        return newNode;
    }else if (list1 != NULL && list2 == NULL)
    {
        Link newNode = creaNodo(list1->d);
        newNode->next = sumBetweenLists(list1->next, list2);
        return newNode;
    }else if (list1 == NULL && list2 != NULL)  // anche se non serve specificarlo lo facciamo per completezza
    {
        Link newNode = creaNodo(list2->d);
        newNode->next = sumBetweenLists(list1, list2->next);
        return newNode;
    }
}

// versione di coda
void sumBetweenListsCoda(Link List1, Link List2, Link *head, Link *tail)  // ovviamente con head e tail = NULL
{
    if (List1 != NULL && List2 != NULL)
    {
        Link newNode = creaNodo(List1->d + List2->d);
        if (*head == NULL) { *head = newNode; *tail = newNode; } else { (*tail)->next = newNode; *tail = newNode; }
        sumBetweenListsCoda(List1->next, List2->next, head, tail);
    }else if (List1 != NULL && List2 == NULL)
    {
        Link newNode = creaNodo(List1->d);
        if (*head == NULL) { *head = newNode; *tail = newNode; } else { (*tail)->next = newNode; *tail = newNode; }
        sumBetweenListsCoda(List1->next, List2, head, tail);
    }else if (List1 == NULL && List2 != NULL){
        Link newNode = creaNodo(List2->d);
        if (*head == NULL) { *head = newNode; *tail = newNode; } else { (*tail)->next = newNode; *tail = newNode; }
        sumBetweenListsCoda(List1, List2->next, head, tail);
    }
}

//Date due liste ordinate e senza duplicati, generare la lista unione (senza duplicati), SENZA generare nuovi nodi
Link unione_rn(Link list1, Link list2)
{
    // caso base
    if (list1 == NULL && list2 == NULL) return NULL;
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    if (list1->d == list2->d){ list1->next = unione_rn(list1->next, list2->next); return list1; }
    if (list1->d < list2->d) { list1->next = unione_rn(list1->next, list2); return list1; } else { list2->next = unione_rn(list1, list2->next); return list2; }
}

int main()
{
    Link List = buildList_r();
    print_List_r(List);

    // duplichiamo la lista
    Link newList = duplis_r(List);
    print_List_r(newList);

    printPos_r(List, 0, 2);
    printf("La somma degli elementi della lista sono: %d\n", sumList_r(List));
    int somma = 0;
    sumList_r_coda(List, &somma);
    printf("La somma degli elementi della lista sono: %d\n", somma);

    printf("La somma tra l'elemento 1 e 4 e' %d\n", sumList_r_between(List, 1, 4));

    printf("La media dei valori nella lista vale: %.2lf\n", averageList_r(List, 0, 0));

    freeList_r(&List);  // Libero la memoria (evito il memory leak)
}