// Sukhveer Karlcut
// skarlcut
// PA5

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// struct defining node
typedef struct NodeObj
{
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node; // private Node type

// struct defining list
typedef struct ListObj
{
    Node head;
    Node tail;
    Node cursor;
    int index;
    int length;
}ListObj;

// newNode()
// Node constructor
Node newNode(int data)
{
    Node temp = NULL;
    temp = malloc(sizeof(NodeObj));
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;
    return (temp);
}

// freeNode()
// frees heap memory associated with Node *pN
void freeNode(Node* pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// List constructor
List newList(void)
{
    List L = NULL;
    L = malloc(sizeof(ListObj));
    L->head = NULL;
    L->tail = NULL;
    L->cursor = NULL;
    L->index = -1;
    L->length = 0;
    return (L);
}

// freeList()
// frees all heap memory associated with List *pL
// and sets *pL to NULL
void freeList(List* pL)
{
    if (pL != NULL && *pL!= NULL) 
    { 
      while (length(*pL) > 0)
          deleteFront(*pL);
      free(*pL);
      *pL = NULL;
    }
}

// Access functions ---------------------------------------

// length()
// returns the length of the list
int length(List L)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    return L->length;
}

// index()
// returns the index of the cursor of the list
int index(List L)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (length(L) <= 0)
        return -1;
    return L->index;
}

// front()
// returns the front element. pre: length() > 0
int front(List L)
{
    if (L == NULL || length(L) <= 0)
    {
        printf("Error: NULL List");
        exit(1);
    }
    return L->head->data;
}

// back()
// returns the back element. pre: length() > 0
int back(List L)
{
    if (L == NULL || length(L) <= 0)
    {
        printf("Error: NULL List");
        exit(1);
    }
    return L->tail->data;
}

// get()
// Returns cursor element. Pre: length()>0, index()>=0
int get(List L)
{
    if (L == NULL || length(L) <= 0 || L->cursor == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    return L->cursor->data;
}

// equals
// Returns true if and only if this List and L are the same
// integer sequence. The states of the cursors in the two Lists
// are not used in determining equality.
int equals(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if(A->length != B-> length)
        return 0;
    Node temp1 = A->head;
    Node temp2 = B->head;
    while (temp1 != NULL)
    {
        if(temp1->data != temp2->data)
            return 0;
        temp1 = temp1->next;
        temp2 = temp2->next;  
    }
    return 1;
}

// Manipulation procedures ------------------------------------------------

// clear()
// Resets this List to its original empty state.
void clear(List L)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    while (length(L) > 0)
        deleteFront(L);
    L->head = NULL;
    L->tail = NULL;
    L->cursor = NULL;
    L->index = -1;
    L->length = 0;
}

// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (length(L) > 0)
    {
        L->cursor = L->head;
        L->index = 0;
    }
}

// moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (length(L) > 0)
    {
        L->cursor = L->tail;
        L->index = L->length - 1;
    }
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (L->cursor == L->head)
    {
        L->cursor = NULL;
        L->index = -1;
    }
    else
    {
        L->cursor = L->cursor->prev;
        L->index--;
    }
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing
void moveNext(List L)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (L->cursor == L->tail)
    {
        L->cursor = NULL;
        L->index = -1;
    }
    else
    {
        L->cursor = L->cursor->next;
        L->index++;
    }
}

// prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    Node temp = newNode(data);
    if (L->head == NULL)
    {
        L->head = temp;
        L->tail = temp;
        L->cursor = L->head;
    }
    else
    {
        L->head->prev = temp;
        temp->next = L->head;
        L->head = temp;
        L->index++;
    }
    L->length++;
}

// append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data)
{
    if (L == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    Node temp = newNode(data);
    if (L->tail == NULL)
    {
        L->head = temp;
        L->tail = temp;
        L->cursor = L->tail;
    }
    else
    {
        L->tail->next = temp;
        temp->prev = L->tail;
        L->tail = temp;
        temp->next = NULL;
    }
    L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
    if (L == NULL || L->cursor == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (L->cursor == L->head)
        prepend(L, data);
    else
    {
        Node temp = newNode(data);
        temp->prev = L->cursor->prev;
        temp->next = L->cursor;
        L->cursor->prev->next = temp;
        L->cursor->prev = temp;
        L->index++;
        L->length++;
    }
}

// insertAfter()
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
    if (L == NULL || length(L) <= 0)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (L->cursor == L->tail)
        append(L, data);
    else
    {
        Node temp = newNode(data);
        L->cursor->next->prev = temp;
        temp->next = L->cursor->next;
        temp->prev = L->cursor;
        L->cursor->next = temp;
        L->length++;
    }
}

// deleteFront()
// Deletes the front element. Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL || length(L) <= 0)
    {
        printf("Error: NULL List");
        exit(1);
    }
    else
    {
        if (L->length == 1)
        {
            Node temp = L->head;
            freeNode(&temp);
            L->cursor = NULL;
            L->head = L->tail = NULL;
            L->index = -1;
        }
        else 
        {
            Node temp = L->head;
            L->head = L->head->next;
            L->head->prev = NULL;
            if (L->cursor != NULL)
                L->index--;
            freeNode(&temp);
        }
        L->length--;
    }
}

// deleteBack()
// Deletes the back element. Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL || length(L) <= 0)
    {
        printf("Error: NULL List");
        exit(1);
    }
    else
    {
        if (L->length == 1)
        {
            Node temp = L->tail;
            freeNode(&temp);
            L->cursor = NULL;
            L->head = L->tail = NULL;
            L->index = -1;
        }
        else 
        {
            Node temp = L->tail;
            L->tail = L->tail->prev;
            L->tail->next = NULL;
            if (L->index == L->length - 1)
                L->index = -1;
            freeNode(&temp);
        }
        L->length--;
    }
}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
    if (L == NULL || length(L) <= 0 || L->cursor == NULL)
    {
        printf("Error: NULL List");
        exit(1);
    }
    if (L->cursor == L->head)
        deleteFront(L);
    else if (L->cursor == L->tail)
        deleteBack(L);
    else
    {
        Node temp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&temp);
        L->length--;
    }
    L->index = -1;
}

// printList()
// prints a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
void printList(FILE* out, List L) 
{
    Node temp = NULL;
    if(L == NULL) 
    {
        printf("Error: NULL List");
        exit(1);
    }
    for (temp = L->head; temp != NULL; temp = temp->next) 
    {
        fprintf(out, "%d", temp->data);
        fprintf(out, " ");
    }
}

// copyList()
// creates a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
 // state of the cursor in this List. This List is unchanged.
List copyList(List L)
{
    List l = newList();
    if (length(L) > 0)
    {
        Node temp = L->head;
        while (temp != NULL)
        {
            append(l, temp->data);
            temp = temp->next;
        }
    }
    l->cursor = NULL;
    l->index = -1;
    return l;
}

