#include <stdio.h>
#include <stdlib.h>

typedef int DATA;  // Creo questo typedef per poter rendere il codice portatile

// Definizione di lista
typedef struct Node Node;  // Chiamo struct Node semplicemente Node
typedef Node *Link;  // Chiamo il puntatore a Node semplicemente Link

struct Node
{
    DATA data;  // Dato
    Node *next;  // Puntatore al prossimo nodo
};

// Redifinizioni dei tipi per non complicarci la vita

// Creazione Node
Link newNode(const DATA x)
{
    Link A = (Link)malloc(sizeof(Node));
    A->data = x;
    A->next = NULL;
    return A;
}

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
        if (head->data > x) printf("|%d|->", head->data);  // Stampo il dato al suo interno solo se rispetto una condizione
        head = head->next;  // vado avanti con la testa (tanto è una copia)
    }
    printf("NULL");
}

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

// trova un nodo alla posizione x (Complessità nel tempo O(min(x,n)) e O(1))
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

// Inserisce dalla testa  |x| -> |1| -> |2| -> |3| -> NULL
void headInsert(Link *head, const int x)
{
    Link new = newNode(x);  // Creo il nodo
    new->next = *head;  // Collego il nuovo nodo alla testa
    *head = new;  // Il nuovo nodo diventa la testa
}

// Inserisce dalla coda |1| -> |2| -> |3| -> |x| -> NULL
void tailInsert(Link *head, const int x)
{
    Link new = newNode(x);
    if (*head == NULL) *head = new;  // Se la testa è vuota allora la testa diventa il nuovo nodo fine
    else
    {
        Link curr = *head;
        while (curr->next != NULL) curr = curr->next; // Scorro la lista finché non ci fermiamo di un nodo prima di NULL
        curr->next = new;  // Mettiamo new come ultimo nodo prima di NULL
    }
}

int main(void)
{
    Link head = NULL;
    for (int i = 1; i <= 10; i++) headInsert(&head, i);
    printList(head);
    Link head2 = NULL;
    for (int i = 1; i <= 10; i++) tailInsert(&head2, i);
    printList(head2);

    printf("\nLa somma di tutti i nodi della prima lista %d.\n", sumList(head));
    printf("La somma di tutti i nodi della seconda lista %d.\n", sumList(head2));

    printf("\nL'elemento |5| si trova alla posizione %d della prima lista.\n", find_index(head, 5));
    printf("L'elemento |5| si trova alla posizione %d della seconda lista.\n", find_index(head2, 5));

    Link node1 = findAt(head, 5), node2 = findAt(head2, 5);

    if (node1 != NULL) printf("\nL'elemento alla posizione 5 della prima lista e' |%d|.\n", node1->data);
    else printf("\nL'elemento alla posizione 5 della prima lista non esiste.\n");
    if (node2 != NULL) printf("L'elemento alla posizione 4 della seconda lista e' |%d|.\n", node2->data);
    else printf("L'elemento alla posizione 5 della seconda lista non esiste.\n");

    printf("\nGli elementi piu' grandi di 5 della prima lista sono:\n");
    printList_greater(head, 5);
    printf("\nGli elementi piu' grandi di 5 della seconda lista sono:\n");
    printList_greater(head2, 5);

    return 0;
}