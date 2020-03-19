/* 
Name: Veena Kotha
CruzID: vkotha
Assignment name: pa4
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* previous;
} NodeObj;

typedef NodeObj* Node;

//constructors & destructors
Node newNode(int d){
	Node N = malloc(sizeof(NodeObj));
	//assert(N!=NULL);
	N->data = d;
	N->next = NULL;
	N->previous = NULL;
	return (N);
}

void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}

//The private (non-exported) struct ListObj
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int ind_c;
} ListObj;

List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	//assert(L!=NULL);
	L->front = L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->ind_c = -1;
	return L;
}

void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL) { 
		Node N = (*pL)->front;
      	while(N != 0) { 
      		Node M = N;
      		N = N->next;
         	free(M); 
    }
    free(*pL);
    *pL = NULL;
      
   }
}


// Access functions -----------------------------------------------------------

int length(List L){     // Returns the number of elements in L.
	return L->length;
} 

int index(List L){		// Returns index of cursor element if defined, -1 otherwise.
	if(L->cursor != NULL){
		return L->ind_c;
	}
	else{
		return -1;
	}
} 

int front(List L){		// Returns front element of L. Pre: length()>0
	if((L!= NULL) && (length(L)>0)){
		return L->front->data;
	}
	return -1;
} 

int back(List L){		// Returns back element of L. Pre: length()>0
	if(length(L)>0){
		return L->back->data;
	}
	return -1;
}

int get(List L){		// Returns cursor element of L. Pre: length()>0, index()>=0
	if(length(L)>0 && index(L)>=0){
		return L->cursor->data;
	}
	else{
		return -1;
	}
} 

int equals(List A, List B){
	if(length(A) == length(B)){
		Node aT = A->front;
		Node bT = B->front;
		for(int j=0; j<length(A); j++){
			if(aT->data != bT->data){
				return 0;
			}
			aT = aT->next;
			bT = bT->next;
		}
		return 1;
	}
	else{
		return 0;
	}
}


// Manipulation procedures ----------------------------------------------------


void clear(List L){		//Resets L to its original empty state.
	Node N = L->front;
	while(N!=NULL){
		Node M = N;
		N = N->next;
		freeNode(&M);
	}
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->ind_c = -1;
} 

void moveFront(List L){		// If L is non-empty, sets cursor under the front element
	if(length(L)>0){
		L->cursor = L->front;
		L->ind_c = 0;
	}
} 

void moveBack(List L){ // If L is non-empty, sets cursor under the back element,
	if(length(L) > 0){
		L->ind_c = length(L)-1;
		L->cursor = L->back;
	}
	else{

	}
}

void movePrev(List L){
	
	if((L->cursor != L->front) && (L->cursor != NULL) && (L->ind_c != 0)){
		L->cursor = L->cursor->previous;
		L->ind_c = L->ind_c - 1;
	}
	else{
		L->cursor = NULL; //cursor becomes undefined if at the front
		L->ind_c = -1;
	}
} 

void moveNext(List L){
	if(L->cursor != NULL && L->ind_c != L->length-1){
		L->cursor = L->cursor->next;
		L->ind_c = L->ind_c + 1;
	}
	else if(L->cursor != NULL && L->ind_c == L->length-1){
		L->cursor = NULL;
		L->ind_c = -1;
	}
} 

void prepend(List L, int data){		// Insert new element into L. If L is non-empty,
									// insertion takes place before front element.
	Node N = newNode(data);
	if(length(L) > 0){ //if list is not empty
		L->front->previous = N;
		N->next = L->front;
		L->front = N;
		L->ind_c = L->ind_c + 1;
		L->length = L->length + 1;
	}
	else{ 
		L->back = N;
		L->front = N;
		L->cursor = L->front;
		L->length = L->length + 1;
	}
} 
 
void append(List L, int data){		// Insert new element into L. If L is non-empty,
 									// insertion takes place after back element.
	Node N = newNode(data);
	if(L->front == NULL && L->back == NULL){
		L->front = N;
		L->back = N;
		L->cursor = L->back;
		L->length = L->length + 1;
	}
	else{
		L->back->next = N;
		N->previous = L->back;
		L->back = N;
		L->length = L->length + 1;
	}
} 

void insertBefore(List L, int data){		// Insert new element before cursor.
	Node N = newNode(data);
	
	if(L->cursor->previous == NULL){
		N->previous = L->cursor->previous;
		N->next = L->cursor;
		L->front = N;
		L->cursor->previous = N;
		L->length = L->length + 1;
		L->ind_c = L->ind_c + 1;
	}
	else{
		N->previous = L->cursor->previous;
		N->next = L->cursor;
		L->cursor->previous->next = N;
		L->cursor->previous = N;
		L->length = L->length + 1;
		L->ind_c = L->ind_c + 1;
	}
}

void insertAfter(List L, int data){		// Insert new element after cursor.							// Pre: length()>0, index()>=0
	if(index(L) != -1 && length(L) > 0){
		Node N = newNode(data);
		
		if(L->cursor->next == NULL){
			N->previous = L->cursor;
			N->next = L->cursor->next;
			L->back = N; 
			L->cursor->next = N;
			L->length = L->length + 1;
		}
		else{
			N->previous = L->cursor;
			N->next = L->cursor->next;
			L->cursor->next->previous = N;
			L->cursor->next = N;
			L->length = L->length + 1;
		}
        
	}
}

void deleteFront(List L){		// Delete the front element. Pre: length()>0
	if(length(L)>0){
		if(L->cursor == L->front){
			L->ind_c = -1; //make it undefined because then list is empty
			L->cursor = NULL;
		}
			
		Node N = L->front;
		L->front = L->front->next;
		if(L->front != NULL){
			L->front->previous = NULL;
		}
		else{
			L->back = NULL;
		}
		L->length = L->length-1;
		L->ind_c = L->ind_c - 1;
		freeNode(&N);

	}
} 

//test failed 1 
void deleteBack(List L){		// Delete the back element. Pre: length()>0
	if(length(L) > 0){
		//L->back = L->back->previous;
		if(L->cursor == L->back){ //makes this list empty
			L->cursor = NULL;
			L->ind_c = L->ind_c - 1;
		}
		if(L->front == L->back){
			L->front = NULL;
			L->back = NULL;
			L->length = 0;
			freeNode(&L->front);
			//freeList(&L);
		}	
		else{
			Node N = L->back;
			L->back = L->back->previous;
			L->back->next = NULL;
			L->length = L->length - 1;
			freeNode(&N);
		}
		
	}
} 

//fix index test 2
void delete(List L){		// Delete cursor element, making cursor undefined.
	if(index(L) != -1 && length(L) >= 1){
		if(L->cursor == L->front){
			deleteFront(L);
		}
		else if (L->cursor == L->back){
			deleteBack(L);
		}
		else{
			Node N = L->cursor;
			N->previous->next = N->next;
			N->next->previous = N->previous;
			freeNode(&N);
			L->cursor = NULL;
			L->ind_c = -1;
			L->length = L->length - 1;
		}
	}
} 

// Other operations -----------------------------------------------------------


void printList(FILE* out, List sL){
	Node N;
	if(sL==NULL){
		fprintf(stderr, "Error: calling printList() on a NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	for(N = sL->front; N !=  NULL; N = N->next){
		fprintf(out, "%d ", N->data); 
	} 
} 

List copyList(List L){
	List nL = newList();
	Node N;
	for(N = L->front; N != NULL; N = N->next){
		append(nL, N->data);
	}
	return nL;
} 

List concatList(List A, List B){
	List nL = newList();
	Node N;
	Node M;
	for(N = A->front; N != NULL; N = N->next){
		append(nL, N->data);
	}
	for(M = B->front; M != NULL; M = M->next){
		append(nL, M->data);
	}
	return (nL);
}  