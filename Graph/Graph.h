/*
Name: Veena Kotha
Cruz ID: vkotha
Assignment Name: pa5
*/

#include <stdio.h>
#include <assert.h>
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

#define NIL -1
#define UNDEF -2

/*** Constructors-Destructors ***/
typedef struct GraphObj* Graph;
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);


/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List s);
void visit(int *time, Graph G, List s, int index);


/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif