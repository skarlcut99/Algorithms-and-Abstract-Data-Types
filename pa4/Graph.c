//Sukhveer Karlcut
//skarlcut
//PA4

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
	int *dist;
	int order;
	int size;
	int src;
} GraphObj;

// Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n)
{
	Graph G = malloc(sizeof(struct GraphObj));
	G->L = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	G->dist = calloc(n + 1, sizeof(int));
	for (int i = 1; i < n + 1; i++)
	{
		G->L[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->dist[i] = INF;
	}
	G->order = n;
	G->size = 0;
	G->src = NIL;
	return G;
}

// Frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG)
{
	Graph g = *pG;
	for (int i = 1; i <= getOrder(g); i++)
		freeList(&(g->L[i]));
	free(g->L);
	free(g->color);
	free(g->parent);
	free(g->dist);
	free(*pG);
	*pG = NULL;
}

// Returns the order of G
int getOrder(Graph G)
{
	return G->order;
}

// Returns the size of G
int getSize(Graph G)
{
	return G->size;
}

// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G)
{
	return G->src;
}

// Returns the parent of vertex u in the Breadth-First tree created by BFS(), or NIL if BFS() has not yet been called.
// Precondition: 1 <= u <= getOrder(G)
int getParent(Graph G, int u)
{
	if (!(1 <= u && u <= getOrder(G)))
	{
		printf("Graph Error: invalid vertex number\n");
		exit(1);
	}
	return G->parent[u];
}

// Returns the distance from the most recent BFS source to vertex u, or INF if BFS()has not yet been called.
// Precondition: 1 <= u <= getOrder(G)
int getDist(Graph G, int u)
{
	if (!(1 <= u && u <= getOrder(G)))
	{
		printf("Graph Error: invalid vertex number\n");
		exit(1);
	}
	if (getSource(G) == NIL)
		return INF;
	return G->dist[u];
}

// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists
// Precondition: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u)
{
	int src = getSource(G);
	int p = G->parent[u];
	if (!(1 <= u && u <= getOrder(G)))
	{
		printf("Graph Error: getPath() called on an invalid vertex number\n");
		exit(1);
	}
	if (src == NIL)
	{
		printf("Graph Error: getPath() called on a Graph with an invalid source\n");
		exit(1);
	}
	if (u == src)
		append(L, src);
	else if (p == NIL)
		append(L, NIL);
	else
	{
		getPath(L, G, p);
		append(L, u);
	}
}

// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G)
{
	for (int i = 1; i <= getOrder(G); i++)
		clear(G->L[i]);
	G->size = 0;
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

// Inserts a new edge joining u to v,
// Precondition: int arguments must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v){
	if ((!(1 <= u && u <= getOrder(G))) || (!(1 <= v && v <= getOrder(G))))
	{
		printf("Graph Error: addEdge() called on an invalid vertex number, %d\n", u);
		exit(1);
	}
	List A = G->L[u];
	List B = G->L[v];
	IS(A, v);
	IS(B, u);
	G->size++;
}

// Inserts a new directed edge from u to v
// Precondition: int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v)
{
	if ((!(1 <= u && u <= getOrder(G))) || (!(1 <= v && v <= getOrder(G))))
	{
		printf("Graph Error: addArc() called on an invalid vertex number, %d\n", u);
		exit(1);
	}
	IS(G->L[u], v);
	G->size++;
}

// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s){
	for (int x = 1; x <= getOrder(G); x++)
	{
		G->color[x] = WHITE;
		G->dist[x] = INF;
		G->parent[x] = NIL;
	}
	G->src = s;
	G->color[s] = GRAY;
	G->dist[s] = 0;
	G->parent[s] = NIL;
	List y = newList();
	append(y, s);
	while (length(y) > 0)
	{
		int temp = front(y);
		deleteFront(y);
		List l = G->L[temp];
		for (moveFront(l); index(l) != -1; moveNext(l))
		{
			int x = get(l);
			if (G->color[x] == WHITE)
			{
				G->color[x] = GRAY;
				G->dist[x] = G->dist[temp] + 1;
				G->parent[x] = temp;
				append(y, x);
			}
		}
		G->color[temp] = BLACK;
	}
	freeList(&y);
}

// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G)
{
	for (int i = 1; i <= getOrder(G); i++)
	{
		List l = G->L[i]; 
		fprintf(out, "%d:", i);
		for (moveFront(l); index(l) != -1; moveNext(l))
			fprintf(out, " %d", get(l));
		fprintf(out, "\n");
	}
}
