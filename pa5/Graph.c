//Sukhveer Karlcut
//skarlcut
//pa5

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define WHITE 0
#define BLACK 1
#define GRAY  2

// private GraphObj type
typedef struct GraphObj
{
    List *L;
    int *color;
    int *parent;
    int *disc;  
    int *fin;  
    int order;
    int size;
} GraphObj;

// Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n)
{
    Graph G = malloc(sizeof(struct GraphObj));
    G->L = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->disc = calloc(n + 1, sizeof(int));
    G->fin = calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++)
    {
        G->L[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->disc[i] = UNDEF;
        G->fin[i] = UNDEF;
    }
    G->order = n;
    G->size = 0;
    return G;
}

// Frees all dynamic memory associated with the Graph *pG, then sets *pG to NULL
void freeGraph(Graph* pG)
{
    Graph temp = *pG;
    for (int i = 1; i <= getOrder(temp); i++)
        freeList(&(temp->L[i]));
    free(temp->L);
    free(temp->color);
    free(temp->parent);
    free(temp->disc);
    free(temp->fin);
    free(*pG);
    *pG = NULL;
}

// Returns the number of vertices in G
int getOrder(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: getOrder() cannot be called for a NULL Graph G\n");
        exit(1);
    }
    return G->order;
}

// Returns the number of edges in G
int getSize(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: getSize() cannot be called for a NULL Graph G\n");
        exit(1);
    }
    return G->size;
}

// Returns the parent of vertex u in the DFS Forest created by DFS(), or NIL if DFS() has not yet been called.
// Precondition: 1 <= u <= getOrder(G)
int getParent(Graph G, int u)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: getParent() cannot be called for a NULL Graph G\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        fprintf(stderr, "Graph Error: getParent() called on an invalid vertex number\n");
        exit(1);
    }
    return G->parent[u];
}

// Returns the discover time of vertex u as determined by the call to DFS upon Graph G
// Precondition: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: getDiscover() cannot be called for a NULL Graph G\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        fprintf(stderr, "Graph Error: getDiscover() called on an invalid vertex number\n");
        exit(1);
    }
    return G->disc[u];
}

// Returns the finish time of vertex u as determined by the call to DFS upon Graph G
// Precondition: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: addEdge() cannot manipulate a NULL Graph G\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        fprintf(stderr, "Graph Error: getFinish() cannot be called for a NULL Graph G\n");
        exit(1);
    }
    return G->fin[u];
}

// Performs the Insertion Sort algorithm upon list with vertex x
void IS(List list, int x)
{
    if (length(list) == 0)
    {
        append(list, x);
        return;
    }
    for (moveFront(list); index(list) != -1; moveNext(list))
    {
        if(x < get(list))
        {
            insertBefore(list, x);
            break;
        }
    }
    if(index(list) == -1)
        append(list, x);
}

// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u in sorted order.
// Precondition: 1 <= u <= n = getOrder(G)
void addEdge(Graph G, int u, int v)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: addEdge() cannot manipulate a NULL Graph G\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        fprintf(stderr, "Graph Error: addEdge() called on an invalid vertex number, %d\n", u);
        exit(1);
    }
    if (!(1 <= v && v <= getOrder(G)))
    {
        fprintf(stderr, "Graph Error: addEdge() called on an invalid vertex number, %d\n", v);
        exit(1);
    }
    List A = G->L[u];
    List B = G->L[v];
    IS(A, v);
    IS(B, u);
    G->size++;
}

// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
// Precondition: 1 <= u <= n = getOrder(G)
void addArc(Graph G, int u, int v)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: addArc() cannot manipulate a NULL Graph G\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        fprintf(stderr, "Graph Error: addArc() called on an invalid vertex number, %d\n", u);
        exit(1);
    }
    if (!(1 <= v && v <= getOrder(G)))
    {
        fprintf(stderr, "Graph Error: addArc() called on an invalid vertex number, %d\n", v);
        exit(1);
    }
    List l = G->L[u];
    IS(l, v);
    G->size++;
}

// Performs the depth first search algorithm on G
// Precondition: length(S) == getOrder(G)
void DFS(Graph G, List S)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: DFS() cannot be performed upon a NULL Graph G\n");
        exit(1);
    }
    if (length(S) != getOrder(G))
    {
        fprintf(stderr, "Graph Error: DFS() cannot be performed if the length of List S does not equal the number of vertices in Graph G\n");
        exit(1);
    }
    int time = 0;
    // Recursive function that visits vertex x
    void visit(int x)
    {
        G->color[x] = GRAY;
        G->disc[x] = (++time);
        List adj = G->L[x];
        for (moveFront(adj); index(adj) != -1; moveNext(adj))
        {
            int y = get(adj);
            if (G->color[y] == WHITE)
            {
                G->parent[y] = x;
                visit(y);
            }
        }
        G->color[x] = BLACK;
        G->fin[x] = (++time);
        prepend(S, x);
    }
   
    for (moveFront(S); index(S) != -1; moveNext(S))
    {
        int x = get(S);
        G->color[x] = WHITE;
        G->parent[x] = NIL;
    }
    for (moveFront(S); index(S) != -1; moveNext(S))
    {
        int x = get(S);
        if (G->color[x] == WHITE)
            visit(x);
    }
    for (int i = 0; i < getOrder(G); i++)
        deleteBack(S);
}

// Returns the transpose of Graph G
Graph transpose(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: Transpose() cannot create the transpose of a NULL Graph G\n");
        exit(1);
    }
    Graph g = newGraph(getOrder(G));
    for(int i = 1; i <= getOrder(G); i++)
    {
        List temp = G->L[i];
        moveFront(temp);
        if (length(temp) == 0)
            continue;
        else
        {   
            while(index(temp) != -1)
            {
                addArc(g, get(temp), i);
                moveNext(temp);
            }
        }
    }
    return g;
}

// Returns a copy of Graph G
Graph copyGraph(Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: copyGraph() cannot create the copy of a NULL Graph G\n");
        exit(1);
    }
    int x = G->order;
    Graph temp = malloc(sizeof(struct GraphObj));
    temp->L = calloc(x + 1, sizeof(List));
    temp->color = calloc(x + 1, sizeof(int));
    temp->parent = calloc(x + 1, sizeof(int));
    temp->disc = calloc(x + 1, sizeof(int));
    temp->fin = calloc(x + 1, sizeof(int));
    for (int i = 1; i <= x; i++)
    {
        temp->L[i] = newList();
        List l = G->L[i];
        for(moveFront(l); index(l) >= 0; moveNext(l))
            append(temp->L[i], get(l));
        temp->color[i] = WHITE;
        temp->parent[i] = NIL;
        temp->disc[i] = UNDEF;
        temp->fin[i] = UNDEF;
    }
    temp->order = G->order;
    temp->size = G->size;
    return temp;
}

void printGraph(FILE* out, Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "Graph Error: printGraph() cannot print a NULL Graph G\n");
        exit(1);
    }
    for (int i = 1; i <= getOrder(G); i++){
        List list = G->L[i];
        fprintf(out, "%d:", i);
        for (moveFront(list); index(list) != -1; moveNext(list))
            fprintf(out, " %d", get(list));
        fprintf(out, "\n");
    }
}
