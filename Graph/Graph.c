/*
Name: Veena Kotha
Cruz ID: vkotha
Assignment Name: pa5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define WHITE 0
#define BLACK 1
#define GRAY 2



/*** Constructors-Destructors ***/
typedef struct GraphObj{
	int order; //# of vertices
	int size; //# of edges
	
	int* parent;
	int* discover;
	int* finish; 
	int* color;
	List *adjacent;
	
} GraphObj;



Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));

	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
	G->color = calloc(n+1, sizeof(int));
	G->adjacent = calloc(n+1, sizeof(List));
	
	G->order = n;
	G->size = 0;

	for(int i = 1; i<=n; i++){
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		G->color[i] = WHITE;

		G->adjacent[i] = newList();
	}
	return G;
}

void freeGraph(Graph* pG){
	Graph G = *pG;
	for(int i = 0; i<=getOrder(G); i++){
		freeList(&(G->adjacent[i]));
	}
	free(G->parent);
	free(G->discover);
	free(G->finish);
	free(G->color);

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

int getParent(Graph G, int u){ //CAN BE NIL
	if(G==NULL){
		printf("Graph error: cannot getParent() on NULL Graph reference");
		exit(1);
	}
	if(((1 <= u) || (u <= getOrder(G)))){
		return G->parent[u];
	}
	else{
		printf("Graph error: cannot call getParent()");
		exit(1);
	}
}

int getDiscover(Graph G, int u){
	if(G==NULL){
		printf("Graph error: cannot getDiscover() on NULL Graph reference");
		exit(1);
	}
	
	if(((1 <= u) || (u <= getOrder(G)))){
		return G->discover[u];
	}
	else{
		printf("Graph error: cannot call getDiscover()");
		exit(1);
	}
}

int getFinish(Graph G, int u){
	if(G==NULL){
		printf("Graph error: cannot getFinish() on NULL Graph reference");
		exit(1);
	}
	if(((1 <= u) || (u <= getOrder(G)))){
		return G->finish[u];
	}
	else{
		printf("Graph error: cannot call getFinish()");
		exit(1);
	}
}

/*** Manipulation procedures ***/


void addArc(Graph G, int u, int v){ //insert new vertices into the correct locations
	if(G==NULL){
		printf("Graph error: cannot addArc() on NULL Graph reference");
		exit(1);
	}
	if(((1 <= u) || (u <= G->order)) && ((1 <= v) || (v <= G->order))){
		moveFront(G->adjacent[u]);
		while((index(G->adjacent[u]) != -1) && (v > get(G->adjacent[u]))){ //move the place so that you know to append the adjacent at the correct place in the list
			moveNext(G->adjacent[u]);
		}
		if(index(G->adjacent[u]) != -1){ //first element in the adjacent for a number or smaller than the rest of the values in adjacent
			insertBefore(G->adjacent[u], v);
		}
		else{ //add the element at the end - because it is the larges value (need to add numbers in ascending order)
			append(G->adjacent[u], v);
		}
		G->size = G->size + 1;
	}
	else{
		printf("Graph error: cannot call addArc()");
		exit(1);
	}
}

void addEdge(Graph G, int u, int v){
	if(G==NULL){
		printf("Graph error: cannot addEdge() on NULL Graph reference");
		exit(1);
	}
	if(((1 <= u) || (u <= G->order)) && ((1 <= v) || (v <= G->order))){
		G->size = G->size - 1;
		addArc(G, u, v);
		addArc(G, v, u);
	}
	else{
		printf("Graph error: cannot call addEdge()");
		exit(1);
	}
}

void DFS(Graph G, List s){
	if(G==NULL){
		printf("Graph error: cannot call DFS() on NULL Graph reference");
		exit(1);
	}
	else if(length(s) == G->order){
		for(int i = 1; i<=G->order; i++){
			G->parent[i] = NIL;
			G->discover[i] = UNDEF;
			G->finish[i] = UNDEF;
			G->color[i] = WHITE; 
		}
		int time = 0;
		moveFront(s);
		for(int j = 1; j<=G->order; j++){
			int k = get(s);
			if(G->color[k] == WHITE){
				visit(&time, G, s, k);
			}
			moveNext(s);
		}
		for(int l = 1; l<=G->order; l++){
			deleteBack(s);
		}
	}
	else{
		printf("Graph error: cannot call DFS()");
		exit(1);
	} 
}

void visit(int *time, Graph G, List s, int ind){ 
	*time += 1;
	G->discover[ind] = *time;
	G->color[ind] = GRAY;

	moveFront(G->adjacent[ind]);
	while(index(G->adjacent[ind]) != -1){
		int m = get(G->adjacent[ind]);
		if(G->color[m] == WHITE){
			G->parent[m] = ind;
			visit(time, G, s, m);
		}
		moveNext(G->adjacent[ind]);
	}
	G->color[ind] = BLACK;
	*time += 1;
	G->finish[ind] = *time;
	prepend(s, ind); //need to move to the front of the list
}



/*** Other operations ***/

//returns transpose of G
Graph transpose(Graph G){
	Graph gT = newGraph(G->order);
	for(int i = 1; i<=getOrder(G); i++){
		moveFront(G->adjacent[i]);
		while(index(G->adjacent[i]) != -1){
			addArc(gT, get(G->adjacent[i]), i); //transpose - opposite 
			moveNext(G->adjacent[i]);
		}
	}
	return gT;

}

Graph copyGraph(Graph G){
	Graph copyG = newGraph(G->order);
	for(int i = 1; i<=G->order; i++){
		moveFront(G->adjacent[i]);
		while(index(G->adjacent[i]) != -1){
			addArc(copyG, i, get(G->adjacent[i]));
			moveNext(G->adjacent[i]);
		}
	}
	return copyG;
}

void printGraph(FILE* out, Graph G){
	if(G==NULL){
		fprintf(stderr, "Error: calling printGraph() on a NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i=1; i<=getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adjacent[i]);
		fprintf(out, "\n");
	}
	
}