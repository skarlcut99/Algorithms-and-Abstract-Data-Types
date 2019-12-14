//Sukhveer Karlcut
//skarlcut
//pa5

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define UNDEF -1
#define NIL 0

#include <stdio.h>
#include "List.h"

//Exported type
typedef struct GraphObj* Graph;

//Constructors/Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);

//Access Functions
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

//Manipulation Procedures
void IS(List list, int x);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

//Other functions
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif
