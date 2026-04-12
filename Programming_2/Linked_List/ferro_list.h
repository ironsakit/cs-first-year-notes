#ifndef FERRO_LIST_H
#define FERRO_LIST_H

typedef int DATA;
struct Node{DATA data;  struct Node *next;};
typedef struct Node Node;
typedef Node *Link;
Link newNode(const DATA x);
void printList(Link head);
void printList_greater(Link head, const int x);
int sumList(Link head);
int find_index(Link head, const int x);
Link findAt(Link head, const int x);
Link findPrevious(Link head, const int x);
void headInsert(Link *head, const int x);
void tailInsert(Link *head, const int x);
void removeFirst(Link *head);
void removeLast(Link *head);
void removeList(Link *head);
void removeX(Link *head, const int x);
Link duplicateList(Link list);
void dupList(Link list, Link *head);
int isListEquals(Link list1, Link list2);
int countBigger(Link list1, Link list2);
Link buildListSum(Link l1, Link l2);
Link buildListSumComplete(Link l1, Link l2);
Link concatenate(int n, int m, Link l1, Link l2);
Link inters(Link l1, Link l2);
void splitpardis(Link *list, Link *pari, Link *dispari);


#endif