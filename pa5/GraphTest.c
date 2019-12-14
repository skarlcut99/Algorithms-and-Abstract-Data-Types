//Sukhveer Karlcut
//skarlcut
//pa5

#include<stdio.h>
#include "List.h"
#include "Graph.h"

int main(void){
    Graph G = newGraph(8);
    Graph T;
    Graph C;
    List S = newList();
    printf("Graph order : %d\n",getOrder(G));
    printf("Graph size : %d\n",getSize(G));
    addArc(G,9,4);
    addArc(G,8,3);
    addArc(G,7,2);
    addArc(G,6,1);
    addArc(G,5,2);
    addArc(G,4,3);
    addArc(G,3,4);
    addArc(G,2,5);
    addArc(G,1,6);
    addArc(G,2,7);
    addArc(G,3,8);
    addArc(G,4,9);
    addArc(G,5,8);
    addArc(G,6,7);

    printf("\nAfter adding arcs..");
    printf("\nGraph order :  %d\n",getOrder(G));
    printf("Graph size :%d\n",getSize(G));
    printGraph(stdout,G);

    T = transpose(G);
    printf("\nTranspose of G\n");
    printGraph(stdout,T);

    C = copyGraph(G);
    printf("\nCopy of G\n");
    printGraph(stdout,C);

    i = back(S);
    printf("\nBack of List S: %d\n",i);
    i = front(S);
    printf("\nFront of List S: %d\n",i);

    int i;
    for(i =1;i<=getOrder(G);i++)
        append(S,i);
    printf("\nList S\n");
    printList(stdout,S);

    DFS(G,S);
    printf("\nafter DFS\n");
    printf("List S\n");
    printList(stdout,S);

    advanceTo(S,length(S)-1);
    i = get(S);
    printf("\nCurrent last element: %d\n",i);

    printf("\nDFS with Tranpose(G)\n");
    DFS(T,S);
    printf("\nafter DFS\n");
    printList(stdout,S);
    return 0;
}
