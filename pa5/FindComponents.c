//Sukhveer Karlcut
//skarlcut
//pa5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"
#include <stdbool.h>

#define MAX_LEN 250

int main(int argc, char* argv[])
{
    FILE *input;
    FILE *output;
    char line[MAX_LEN];
    int size = 0;
    List S = newList();
    if( argc != 3 )
    {
        printf("Error:%s wrong number of arguments \n", argv[0]);
        exit(1);
    }
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    if(input == NULL)
    {
        printf("Cannot open file %s\n", argv[1]);
        exit(1);
    }
    if(output == NULL)
    {
        printf("Cannot open file to write output %s", argv[2]);
        exit(1);
    }
    fgets(line, MAX_LEN, input);
    sscanf(line, "%d", &size);
    for(int i = 1; i <= size; i++)
        append(S, i);
    Graph G = newGraph(size);
    Graph T;
    while( fgets(line, MAX_LEN, input) != NULL)  
    {
        int x = 0;
        int y = 0;
        sscanf(line, "%d %d", &x, &y);
        if(x == 0 && y == 0)
            break;
        addArc(G, x, y);
    }
    DFS(G, S);
    T = transpose(G);
    DFS(T, S);
    moveFront(S);
    int x = 0;
    while(index(S) >= 0)
    {
        if(getParent(T, get(S)) == NIL)
            x++;
        moveNext(S);
    }
    List L[x];
    for(int i = 0; i < x; i++)
        L[i] = newList();
    moveFront(S);
    int y = x;
    while(index(S) >= 0)
    {
        if(getParent(T, get(S)) == NIL)
            y--;
        if(y == x)
            break;
        append(L[y], get(S));
        moveNext(S);
    }
    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, G);
    fprintf(output, "\nG contains %d strongly connected components:", x);
    for(int i = 0; i < x; i++)
    {
        fprintf(output, "\nComponent %d: ", (i + 1));
        printList(output, L[i]);
        freeList(&(L[i]));
    }
    printf("Success, output file created \n");
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    fclose(input);
    fclose(output);
    return(0);
}
