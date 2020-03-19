/* 
Name: Veena Kotha
CruzID: vkotha
Assignment name: pa3
*/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
	long data;
	struct NodeObj* next;
	struct NodeObj* previous;
}  NodeObj;

typedef NodeObj* Node;

Node newNode(long d){
    Node N = malloc(sizeof(NodeObj));
    N->data = d;
    N->previous = NULL;
    N->next = NULL;
    return N;
}

void freeNode(Node* pN) {
    if(pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int ind_c;
}   ListObj;

List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->length = 0;
    L->ind_c = -1;
    return L;
}

void freeList(List* pL) {
    if(pL != NULL && *pL != NULL) {
        Node N = (*pL)->front;
        while(N != NULL) {
            Node M = N;
            N = N->next;
            free(M);
        }
    free(*pL);
    *pL = NULL;
  }
}


//  Action operations---------------------------


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

long front(List L){		// Returns front element of L. Pre: length()>0
	if(length(L)>0){
		return L->front->data;
	}
	return -1;
} 

long back(List L){		// Returns back element of L. Pre: length()>0
	if(length(L)>0){
		return L->back->data;
	}
	return -1;
}

long get(List L){		// Returns cursor element of L. Pre: length()>0, index()>=0
	if(length(L)>0 && index(L)>=0){
		return L->cursor->data;
	}
	return -1;
} 

/*int equals(List A, List B){
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
}*/


//  Manipulation procedures -------------------------------------------


void clear(List L){			//Resets L to its original empty state.
    Node N = L->front;
    while(N != NULL){
        Node current = N;
        N = N->next;
        free(current);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->ind_c = -1;
}

void moveFront(List L){		// If L is non-empty, sets cursor under the front element
    if(length(L) > 0){
        L->cursor = L->front;
        L->ind_c = 0;
    }
}

void moveBack(List L){		// If L is non-empty, sets cursor under the back element
    if(length(L) > 0){
        L->ind_c = L->length - 1;
        L->cursor = L->back;
    }
    else{

    }
}

void movePrev(List L){
    if(L->cursor != NULL && L->ind_c != 0){
        L->cursor = L->cursor->previous;
        L->ind_c = L->ind_c - 1;
    }
    else if(L->cursor != NULL && L->ind_c == 0){
        L->cursor = NULL; //cursor becomes undefined
        L->ind_c = -1;
    }
}

void moveNext(List L){
    if(L->cursor != NULL && L->ind_c != L->length - 1){
        L->cursor = L->cursor->next;
        L->ind_c = L->ind_c + 1;
    }
    else if(L->cursor != NULL && L->ind_c == L->length - 1){
        L->cursor = NULL;
        L->ind_c = -1;
    }
}

void prepend(List L, long data){
    Node N = newNode(data);
    N->previous = NULL;
    N->next = L->front;
    if(L->front == NULL){
        L->back = N;
   	    L->front = N;
   	    L->length = L->length + 1;
    }
    else{
        L->front->previous = N;
        L->front = N;
   	    L->length = L->length + 1;
    }
   	
}

void append(List L, long data){
    Node N = newNode(data);
    N->previous = L->back;
    N->next = NULL;
    if(L->front == NULL){
   	    L->front = N;
   	    L->back = N;
        L->length = L->length + 1;
    }
    else{
        L->back->next = N;
        L->back = N;
        L->length = L->length + 1;
    }
    
}

void insertBefore(List L, long data){
    Node N = newNode(data);
    N->previous = L->cursor->previous;
    N->next = L->cursor;
    if(L->cursor->previous != NULL){
        L->cursor->previous->next = N;
        L->cursor->previous = N;
        L->length = L->length + 1;
    }
    else{
        L->front = N;
        L->cursor->previous = N;
        L->length = L->length + 1;
    }   
}

void insertAfter(List L, long data){
    Node N = newNode(data);
    N->previous = L->cursor;
    N->next = L->cursor->next;
    if(L->cursor->next == NULL){
       	L->back = N;
        L->cursor->next = N;
        L->length = L->length + 1;
    }
    else{
        L->cursor->next->previous = N;
       	L->cursor->next = N;
        L->length = L->length + 1;
    }   
}

void deleteFront(List L){ //need to free Node when deleting
	if(length(L)>0){
	    if(L->cursor == L->front){
	       L->cursor = NULL;
	       L->ind_c = -1;
	    }
        Node N = L->front;
	    N = N->next;
	    N->previous = NULL;
	    L->length = L->length - 1;
	    freeNode(&N);
	}
}

void deleteBack(List L){ //need to free Node when deleting
	if(length(L)>0){
        if(L->cursor == L->back){
            L->cursor = NULL;
            L->ind_c = L->ind_c - 1;
	    }
        Node N = L->back;
        N = N->previous;
        N->next = NULL;
        L->length = L->length - 1;
        freeNode(&N);
	}
}

void delete(List L){ //need to free Node when deleting
	if(index(L) != -1 && length(L) >= 1){
	    if(L->cursor == L->front){
	       deleteFront(L);
	    }
	    else if(L->cursor == L->back){
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


//  Other procedures -------------------------------------------
void set(List L, long x){
    //overwrites the cursor element w/ x
    if(index(L)>=0 && length(L)>0){
        L->cursor->data = x;
    } 
}

void printList(FILE* out, List sL){
    Node N;
    if(sL==NULL){
	   fprintf(stderr, "Error: calling printList() on a NULL List reference\n");
	   exit(EXIT_FAILURE);
	}
    for(N = sL->front; N != NULL; N = N->next){
        fprintf(out, "%ld ", N->data);
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
