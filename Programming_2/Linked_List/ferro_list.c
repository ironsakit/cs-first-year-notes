#pragma region Includes_e_Strutture

#include <stdio.h>
#include <stdlib.h>

typedef int DATA;  // Creo questo typedef per poter rendere il codice portatile
// Struttura di un nodo
struct Node
{
    DATA data;  // Dato
    struct Node *next;  // Puntatore al prossimo nodo
};

// Ridefinizione dei tipi per non complicarci la vita
typedef struct Node Node;  // Chiamo struct Node semplicemente Node
typedef Node *Link;  // Chiamo il puntatore a Node semplicemente Link

#pragma endregion Includes_e_Strutture

#pragma region Creazione_Nodo

// Creazione di un nodo della lista, assegnando a esso un valore X
Link newNode(const DATA x)
{
    Link A = (Link)malloc(sizeof(Node));
    A->data = x;
    A->next = NULL;
    return A;
}

#pragma endregion Creazione_Nodo


#pragma region Stampa_Lista_e_Somma

// Stampa della lista (Complessità nel tempo O(n) e nello spazio O(1))
void printList(Link head)  // <-- utilizzo un Link e non un puntatore a Link perchè non devo modificare la lista
{
    while (head != NULL)  // Finché non arrivo alla fine
    {
        printf("|%2d| ->", head->data);  // Stampo il dato al suo interno
        head = head->next;  // vado avanti con la testa (tanto è una copia)
    }
    printf("NULL\n");
}

// Stampa della lista CONDIZIONATA (Complessità nel tempo O(n) e nello spazio O(1))
void printList_greater(Link head, const int x)  // <-- utilizzo un Link e non un puntatore a Link perchè non devo modificare la lista
{
    while (head != NULL)  // Finché non arrivo alla fine
    {
        if (head->data > x) printf("|%2d| ->", head->data);  // Stampo il dato al suo interno solo se rispetto una condizione
        head = head->next;  // vado avanti con la testa (tanto è una copia)
    }
    printf("NULL\n");
}

// Somma i nodi (Complessità nel tempo O(n) e O(1))
int sumList(Link head)
{
    int sum = 0;
    while (head != NULL)
    {
        sum += head->data;  // Somma
        head = head->next;  // Vado avanti
    }
    return sum;  // Restituisce la somma oppure zero se la lista è vuota
}

#pragma endregion Stampa_Lista_e_Somma


#pragma region Ricerca_nella_Lista

// Restituisce la posizione dell'elemento da cercare (Complessità nel tempo O(n) e nello spazio O(1))
int find_index(Link head, const int x)  // <-- utilizzo un Link e non un puntatore a Link perchè non devo modificare la lista
{
    int index = 0;  // facciamo che il primo elemento è alla posizione 0 (come nei vettori)
    while (head != NULL)  // Finché non arrivo alla fine
    {
        if (head->data == x) return index;  // Se lo trovo restituisco il suo indice
        head = head->next;  // vado avanti con la testa (tanto è una copia)
        index++;  // Aumento l'indice
    }
    return -1;  // Sennò restituisce -1
}

// Trova un nodo alla posizione x (Complessità nel tempo O(min(x,n)) e O(1))
Link findAt(Link head, const int x)
{
    int pos = 0;  // Mettiamo caso
    while (head != NULL && pos < x)
    {
        head = head->next;
        pos++;
    }
    if (head == NULL) return NULL;
    return head;
}

// Trovo il nodo prima di un nodo contenente un dato X
Link findPrevious(Link head, const int x)
{
    Link curr = head;
    if (head != NULL)  // Se la testa è piena allora possiamo trovare il nodo precedente
    {
        if (curr->data == x)  // Se l'elemento che cerchiamo si trova in testa non esiste alcun nodo precedente
        {
            return NULL;
        }
        int trovato = 0;
        while (curr->next->next != NULL && trovato == 0)
        {
            if (curr->next->data == x)  // Se trovo X al nodo prossimo al corrente
            {
                trovato = 1;  // Ho trovato
            }else
            {
                curr = curr->next;  // Sennò vado avanti
            }
        }
        if (trovato == 1)
        {
            return curr;  // Se ho trovato il nodo restituisco il nodo prima
        }
    }
    return NULL;  // Sennò nulla non l'ho trovato
}

#pragma endregion Ricerca_nella_Lista


#pragma region Inserimento_nella_Lista

void headInsert(Link *head, const int x)  // Inserisce dalla testa  |x| -> |1| -> |2| -> |3| -> NULL
{
    Link new = newNode(x);  // Creo il nodo
    new->next = *head;  // Collego il nuovo nodo alla testa
    *head = new;  // Il nuovo nodo diventa la testa
}

void tailInsert(Link *head, const int x)  // Inserisce dalla coda |1| -> |2| -> |3| -> |x| -> NULL
{
    Link new = newNode(x);  // Creo il nodo
    if (*head == NULL) *head = new;  // Se la testa è vuota allora la testa diventa il nuovo nodo fine
    else
    {
        Link curr = *head;  // Prendo la reference della testa
        while (curr->next != NULL) curr = curr->next; // Scorro la lista finché non ci fermiamo di un nodo prima di NULL
        curr->next = new;  // Mettiamo new come ultimo nodo prima di NULL
    }
}

#pragma endregion Inserimento_nella_Lista


#pragma region Rimozione_dalla_Lista

void removeFirst(Link *head)  // Rimuovo il primo nodo della lista
{
    if (*head != NULL)  // Se la lista non è vuota
    {
        Link curr = *head;  // Prendo il riferimento alla testa
        *head = (*head)->next;  // Sposto la testa
        free(curr);  // Libero la memoria riservata al vecchio nodo
    }else
    {
        printf("La lista e' vuota.\n");
    }
}

void removeLast(Link *head)  // Rimuovo l'ultimo nodo dalla lista
{
    Link curr = *head;  // Mi salvo il riferimento dalla testa
    if (*head != NULL)  // Se la lista non è vuota
    {
        if (curr->next == NULL)  // Se ho un solo elemento
        {
            *head = NULL;  // Scollego head dalla lista
            free(curr);   // Rimuovo il nodo a cui puntavo con la testa
        }else
        {
            while (curr->next->next != NULL) curr = curr->next;  // Sennò scorro fino al nodo prima dell'ultimo nodo
            Link temp = curr->next;  // Mi salvo il riferimento al nodo che voglio eliminare
            curr->next = NULL;  // scollego il nodo dalla lista
            free(temp);  // Libero la memoria del nodo scollegato
        }
    }
}

void removeList(Link *head)  // Rimuovo tutta la lista
{
    while (*head != NULL)
    {
        Link curr = *head;  // Memorizzo il riferimento della testa
        *head = (*head)->next;  // Sposto la testa in avanti
        free(curr);  // Libero/rimuovo definitivamente il nodo a cui puntava la testa
    }
}

void removeX(Link *head, const int x)  // Rimuovo un nodo contenente un dato X
{
    if (*head != NULL)  // Ovviamente la lista deve essere piena
    {
        Link curr;
        if ((*head)->data == x)  // Se l'elemento si trova proprio in testa, facciamo una rimozione in testa
        {
            curr = *head;  // Prendo la reference dalla testa
            *head = (*head)->next;  // Porto avanti la testa
            free(curr);  // Libero la memoria del vecchio nodo
        }else
        {
            Link prev = findPrevious(*head, x);  // Sennò cerco il nodo precedente al nodo con il valore X al suo interno
            if (prev != NULL)  // Vedo se la funzione mi ha dato un nodo
            {
                curr = prev->next;  // Ora prendiamo il nodo che vogliamo rimuovere
                prev->next = curr->next;  // Il nodo prima lo facciamo puntare al prossimo del nodo che vogliamo rimuovere
                free(curr);  // Ora possiamo liberare la memoria per il vecchio nodo
            }
        }
    }
}

#pragma endregion Rimozione_dalla_Lista


#pragma region Duplicazione_della_Lista

Link duplicateList(Link list)  // Duplica la lista passata
{
    Link curr, head = NULL, tail;
    while (list != NULL)  // Scorriamo tutta la lista
    {
        curr = newNode(list->data);  // Creo un nuovo nodo identico a quello della lista
        if (head == NULL)   // Se la testa è ancora vuota
        {
            head = curr;  // La testa punta al primo nodo
            tail = curr;  // La coda punta al primo nodo
        }else  // Se ci sono altri nodi già
        {
            tail->next = curr;  // Facciamo una tail insert praticamente
            tail = curr;  // e la coda diventa il nuovo nodo
        }
        list = list->next;
    }
    return head;
}

void dupList(Link list, Link *head)  // Duplica una lista passando il recipiente in cui copiarla
{
    Link new, tail;
    removeList(head);  // Prima svuoto la lista in cui dobbiamo mettere il duplicato
    while (list != NULL)  // Attraversiamo tutta la lista a cui dobbiamo copiare gli elementi
    {
        new = newNode(list->data);  // Creiamo un nodo uguale al nodo corrente della lista
        if (*head == NULL)  // Se dobbiamo ancora mettere il primo nodo
        {
            *head = new;
            tail = new;
        }else  // Se ci sono altri nodi
        {
            tail->next = new;  // Facciamo una tail insert praticamente
            tail = new;
        }
        list = list->next;  // Andiamo avanti con la lista
    }
}

int isListEquals(Link list1, Link list2)
{
    int noEquals = 0;
    while (list1 != NULL && list2 != NULL && noEquals == 0)  // Scorro entrambe le liste
    {
        if (list1->data != list2->data) noEquals = 1;  // Se trovo due nodi che non sono uguali esce dal while
        else
        {
            list1 = list1->next;  // Vado avanti con le liste
            list2 = list2->next;
        }
    }
    // Se la variabile sentinella non è stata toccata ed entrambe le liste hanno raggiunto la fine (sono lunghe uguali) allora sono uguali
    if (noEquals == 0 && list1 == NULL && list2 == NULL) return 0;
    return 1;  // Sennò non sono uguali (o perchè hanno nodi diversi o perchè hanno lunghezze diverse)
}

#pragma endregion Duplicazione_della_Lista


#pragma region Confronto_in_parallelo

// Questa funzione conta quanti elementi della lista 1 sono più grandi della lista 2 e se una delle liste è più lungo di contare i nodi mancanti come zeri
int countBigger(Link list1, Link list2)
{
    int bigger = 0;
    while (list1 != NULL && list2 != NULL)  // Scorro entrambe le liste
    {
        if (list1->data > list2->data) bigger++;  // Ho trovato un nodo della lista 1 corrente più grande del nodo della lista 2 corrente, quindi aumento il contatore
        list1 = list1->next;
        list2 = list2->next;
    }
    while (list1 != NULL)  // Se nella lista 1 ci sono ancora elementi vuol dire che la lista 2 è finita quindi i nodi mancanti li conto come zeri
    {
        if (list1->data > 0) bigger++;  // Se lista 1 ha nodi più grandi di zero allora aumento il contatore
        list1 = list1->next;
    }
    while (list2 != NULL)  // Stessa cosa per list 2
    {
        if (list2->data < 0) bigger++;  // Solo che aumento il contatore sempre e solo se gli elementi di list 1 (in questo caso 0) sono più grandi degli elementi di list 2
        list2 = list2->next;
    }
    return bigger;  // Restituisco il conteggio
}

Link buildListSum(Link l1, Link l2)  // Questa funzione deve costruire una lista che sia la somma dei nodi delle due liste ma si deve fermare non appena una della due liste finisce
{
    Link new, head = NULL, tail;
    while (l1 != NULL && l2 != NULL)  // Scorro entrambe le liste
    {
        new = newNode(l1->data + l2->data);  // Creo il nuovo nodo dalla somma dei due nodi delle due liste
        if (head == NULL)  // Come sempre se devo mettere il primo nodo
        {
            head = new;
            tail = new;
        }else  // Se ci sono altri nodi già
        {
            tail->next = new;  // Inserimento in coda
            tail = new;
        }
        l1 = l1->next;  // Vado avanti con le liste
        l2 = l2->next;
    }
    return head;  // Restituisco la nuova lista
}

// Questa funzione deve costruire una lista che sia la somma dei nodi delle due liste ma non si ferma, continua finchè non finisce entrambe le stringhe e conta come zero i nodi mancanti
Link buildListSumComplete(Link l1, Link l2)
{
    Link new, head = NULL, tail;
    while (l1 != NULL && l2 != NULL)  // Scorro entrambe le liste
    {
        new = newNode(l1->data + l2->data);  // Creo il nuovo nodo dalla somma dei due nodi delle due liste
        if (head == NULL)  // Come sempre se devo mettere il primo nodo
        {
            head = new;
            tail = new;
        }else  // Se ci sono altri nodi già
        {
            tail->next = new;  // Inserimento in coda
            tail = new;
        }
        l1 = l1->next;  // Vado avanti con le liste
        l2 = l2->next;
    }
    while (l1 != NULL)
    {
        new = newNode(l1->data);
        if (head == NULL)  // Come sempre se devo mettere il primo nodo
        {
            head = new;
            tail = new;
        }else  // Se ci sono altri nodi già
        {
            tail->next = new;  // Inserimento in coda
            tail = new;
        }
        l1 = l1->next;  // Vado avanti con la lista
    }
    while (l2 != NULL)
    {
        new = newNode(l2->data);
        if (head == NULL)  // Come sempre se devo mettere il primo nodo
        {
            head = new;
            tail = new;
        }else  // Se ci sono altri nodi già
        {
            tail->next = new;  // Inserimento in coda
            tail = new;
        }
        l2 = l2->next;  // Vado avanti con la lista
    }
    return head;  // Restituisco la nuova lista
}

Link concatenate(int n, int m, Link l1, Link l2)   // Copio n elementi di l1 e m elementi di l2 in una nuova lista
{
    Link new, head = NULL, tail;
    int posl1 = 0, posl2 = 0;  // Partiamo da zero come la notazione array
    while (l1 != NULL)
    {
        if (posl1 < n)  // Finché siamo tra il range 0 < posl1 < n prendiamo gli elementi di l1
        {
            new = newNode(l1->data);
            if (head == NULL)  // Come sempre se devo mettere il primo nodo
            {
                head = new;
                tail = new;
            }else  // Se ci sono altri nodi già
            {
                tail->next = new;  // Inserimento in coda
                tail = new;
            }
        }
        posl1++;
        l1 = l1->next;  // Vado avanti con la lista
    }
    while (l2 != NULL)
    {
        if (posl2 > m)  // Finché siamo tra il range m < posl2 < dimensione di lista 2 prendiamo gli elementi di l2
        {
            new = newNode(l2->data);
            if (head == NULL)  // Come sempre se devo mettere il primo nodo
            {
                head = new;
                tail = new;
            }else  // Se ci sono altri nodi già
            {
                tail->next = new;  // Inserimento in coda
                tail = new;
            }
        }
        posl2++;
        l2 = l2->next;  // Vado avanti con la lista
    }
    return head;  // Restituisco la nuova lista
}

Link inters(Link l1, Link l2)  // Crea una nuova lista i cui elementi sono l'intersezione tra le due liste ""ordinate""
{
    Link new, head = NULL, tail;
    while (l1 != NULL && l2 != NULL)  // Scorro entrambe le liste
    {
       if (l1->data == l2->data)  // Se trovo due elementi uguali allora ho trovato un elemento che fa parte dell'intersezione
       {
           new = newNode(l1->data);  // Creo il nodo e lo aggiungo come sempre con le logiche precedenti
           if (head == NULL){ head = new; tail = new; }
           else{ tail->next = new; tail = new; }
           l1 = l1->next;
           l2 = l2->next;
       }else if (l1->data > l2->data)   // Se l1 ha un elemento più grande di l2 allora l2 deve andare avanti (ricordando sempre che le due liste sono ordinate) perchè più avanti potrebbe essere l'elemento uguale a quello corrente di l1
       {
           l2 = l2->next;
       }else  // Stessa cosa ma al contrario con l2
       {
           l1 = l1->next;
       }
    }
    return head;  // Restituisco la nuova lista
}

// Questa funzione spezza una lista in modo tale da mettere i numeri dispari in una lista e in numeri pari in un altra (senza dover allocare nuova memoria, smembrando la vecchia lista)
void splitpardis(Link *list, Link *pari, Link *dispari)
{
    Link tmp, tailP, tailD;
    // Svuoto le liste per sicurezza
    removeList(pari);
    removeList(dispari);
    while (*list != NULL)
    {
        if ((*list)->data % 2 == 0)  // Se l'elemento della lista è pari allora lo metta nella lista dei pari
        {
            if (*pari == NULL){ *pari = *list; tailP = *list; }
            else{ tailP->next = *list; tailP = *list; }
        }else
        {
            if (*dispari == NULL){ *dispari = *list; tailD = *list; }
            else{ tailD->next = *list; tailD = *list;}
        }
        // Stacco il nodo appena inserito dal resto della lista (sennò il nodo inserito in dispari o pari avrebbe tutti gli altri nodi)
        tmp = *list;  // Punto al nodo appena inserito
        *list = (*list)->next;  // Vado avanti con la lista
        tmp->next = NULL;  // Stacco il nodo dalla lista
    }
}


#pragma endregion Confronto_in_parallelo