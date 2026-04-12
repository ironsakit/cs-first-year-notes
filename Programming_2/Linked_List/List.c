#include <stdio.h>
#include <stdlib.h>
#include "ferro_list.h"

int main(void)
{
    Link head = NULL;
    for (int i = 1; i <= 10; i++) headInsert(&head, i);
    removeX(&head, 7);
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

    Link new = duplicateList(head);
    printf("\nLista 1 duplicata: \n");
    printList(new);

    removeList(&head);
    removeList(&head2);
    removeList(&new);

    return 0;
}