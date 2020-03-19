/*
Name: Veena Kotha
Cruz ID: vkotha
Assignment Name: pa4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "List.h"
#include "Graph.h"
#define WHITE 0
#define BLACK 1
#define GRAY 2





/*** Constructors-Destructors ***/
typedef struct GraphObj{
	int order; //# of vertices
	int size; //# of edges
	int source; //label of vertex most recently used as source
	
	int* parent;
	int* color;
	int* distance; 
	List *adjacent;
	
} GraphObj;



Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));

	G->parent = calloc(n+1, sizeof(int));
	G->color = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->adjacent = calloc(n+1, sizeof(List));
	
	
	G->order = n;
	G->size = 0;
	G->source = NIL;

	for(int i = 1; i<=n; i++){
		G->parent[i] = NIL;
		G->color[i] = WHITE;
		G->distance[i] = INF;

		G->adjacent[i] = newList();
	}
	return G;
}

void freeGraph(Graph* pG){
	Graph G = *pG;
	for(int i = 0; i<=getOrder(*pG); i++){
		freeList(&(G->adjacent[i]));
	}
	
	free(G->parent);
	free(G->color);
	free(G->distance);

	free(G->adjacent);

	free(*pG);
	*pG = NULL;
}


/*** Access functions ***/
int getOrder(Graph G){
	if(G == NULL){
		printf("Graph error: cannot getOrder() on NULL Graph reference");
		exit(1);
	}
	return G->order;
}

int getSize(Graph G){
	if(G==NULL){
		printf("Graph error: cannot getSize() on NULL Graph reference");
		exit(1);
	}
	return G->size;
}

int getSource(Graph G){
	//returns source vertex most recently used in functions 
	//BFS() or NIL if BFS () has not been called
	if(G==NULL){
		printf("Graph error: cannot getSource() on NULL Graph reference");
		exit(1);
	}
	return G->source;

}

//precondition 1<= u <= getOrder(G)
int getParent(Graph G, int u){
	//return the parent of vertex u in the BreadthFirst tree
	//created by BFS(), or NIL if BFS() has not yet been called
	if(G==NULL){
		printf("Graph error: cannot getParent() on NULL Graph reference");
		exit(1);
	}
	if((1 <= u) || (u <= getOrder(G))){
		return G->parent[u];
	}
	else{
		printf("Graph error: cannot call getParent()");
		exit(1);
	}
}

//precondition 1<= u <= getOrder(G)
int getDist(Graph G, int u){
	//distance from the most recent BFS source to vertex u, 
	//or INF if BFS() has not yet been called
	if(G==NULL){
		printf("Graph error: cannot getDist() on NULL Graph reference");
		exit(1);
	}
	if(getSource(G) == NIL){
		return INF;
	}
	if((1 <= u) || (u <= getOrder(G))){
		return G->distance[u];
	}
	else{
		printf("Graph error: cannot call getDist()");
		exit(1);
	}
}

void getPath(List L, Graph G, int u){
	if(G==NULL){
		printf("Graph error: cannot getDist() on NULL Graph reference");
		exit(1);
	}
	if(getSource(G) == NIL){ 
		printf("Graph error: cannot call getPath()");
		exit(1);
	}

	if((1 <= u) || (u <= getOrder(G))){
		if(G->source == u){
			append(L, G->source); 
		}
		else if(G->parent[u] == NIL){
			append(L, NIL); //appends to L the value NIL
		}
		else{
			getPath(L, G, G->parent[u]);
			append(L, u);
		}
	}
	else{
		printf("Graph error: cannot call getPath()");
		exit(1);
	}
}


/*** Manipulation procedures ***/


void makeNull(Graph G){
	// deletes all edges of G, restoring it to its original
	//(no edge) state - size
	if(G==NULL){
		printf("Graph error: cannot makeNull() on NULL Graph reference");
		exit(1);
	}
	for(int i=1; i<=getOrder(G); i++){
		clear(G->adjacent[i]);
	}
	G->size = 0;
}

//precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v){
	if(G==NULL){
		printf("Graph error: cannot addEdge() on NULL Graph reference");
		exit(1);
	}
	if(((1 <= u) || (u <= getOrder(G))) && ((1 <= v) || (v <= getOrder(G)))){
		G->size = G->size - 1;
		addArc(G, u, v);
		addArc(G, v, u);
	}
	else{
		printf("Graph error: cannot call addEdge()");
		exit(1);
	}
}

//inserts a new directed edge from u to v, 
//i.e. v is added to the adjacency List of u 
void addArc(Graph G, int u, int v){
	//inserts a new directed edge
	if(G==NULL){
		printf("Graph error: cannot addArc() on NULL Graph reference");
		exit(1);
	}
	if(((1 <= u) || (u <= getOrder(G))) && ((1 <= v) || (v <= getOrder(G)))){
		moveFront(G->adjacent[u]);
		while((index(G->adjacent[u]) != -1) && (v > get(G->adjacent[u]))){
			moveNext(G->adjacent[u]);
		}
		if(index(G->adjacent[u]) != -1){
			insertBefore(G->adjacent[u], v);
		}
		else{
			append(G->adjacent[u], v);
		}
		G->size = G->size + 1;
	}
	else{
		printf("Graph error: cannot call addArc()");
		exit(1);
	}
}
void BFS(Graph G, int s){

	if(G==NULL){
		printf("Graph error: cannot call BFS() on NULL Graph reference");
		exit(1);
	}

	else if((1 <= s) || (s <= getOrder(G))){
		for(int i = 1; i<=G->order; i++){
			G->color[i] = WHITE;
			G->distance[i] = INF;
			G->parent[i] = NIL;
		}

		G->source = s;
		G->color[s] = GRAY;
		G->distance[s] = 0;
		G->parent[s] = NIL; 
		List l = newList();
		append(l, s);
		int x = 0;

		while(length(l) > 0){
			moveFront(l);
		  	x = get(l); 
		 	
		  	moveFront(G->adjacent[x]);
		  	deleteFront(l);
		
		  	moveFront(G->adjacent[x]);

		 	while(index(G->adjacent[x]) != -1){
		 	 	int y = get(G->adjacent[x]);
		 	 	if(G->color[y] == WHITE){
					G->color[y] = GRAY;
					G->distance[y] = G->distance[x] + 1;
					G->parent[y] = x;
					append(l, y);
				}
				moveNext(G->adjacent[x]);
			}
			G->color[x] = BLACK;
		}
		freeList(&l);
	}
	else{
		printf("Graph error: cannot call BFS()");
		exit(1);
	} 
	
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	if(G==NULL){
		fprintf(stderr, "Error: calling printBigInteger() on a NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i=1; i<=getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adjacent[i]);
		fprintf(out, "\n");
	}
	
}