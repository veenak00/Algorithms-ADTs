/*
Name: Veena Kotha
Cruz ID: vkotha
Assignment Name: pa5
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
    FILE *in, *out;
    char line[MAX_LEN];

   // check command line for correct number of arguments
    if( argc != 3 ){
    	printf("Usage: %s <input file> <output file>\n", argv[0]);
    	exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
    	printf("Unable to open file %s for reading\n", argv[1]);
    	exit(1);
    }
    if( out==NULL ){
    	printf("Unable to open file %s for writing\n", argv[2]);
        fclose(in);
    	exit(1);
    }


    int n;
	fscanf(in, "%d", &n);
    Graph nG = newGraph(n); //freed
    List nL = newList(); //freed

    for(int i = 1; i<=n; i++){
        append(nL, i);
    }

    int x = 0;
    int y = 0;

    while(fgets(line, MAX_LEN, in) != NULL){ //reading line feed
        fscanf(in, "%d %d", &x, &y);
        if((x == 0) && (y == 0)){
            break; //should stop adding edges when line in the input file is 0 0
        }
        else{
            addArc(nG, x, y);
        }
    }
    
    DFS(nG, nL);
    Graph gT = newGraph(n); //freed
    gT = transpose(nG);
    DFS(gT, nL);

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, nG);
    fprintf(out, "\n");

    //find number of connected components : numSCC
    int numSCC = 0; //number of strongly connected components
    moveFront(nL);
    
    for(int i = 1; i<=getOrder(nG); i++){
        if(getParent(gT, get(nL)) == NIL){
            numSCC = numSCC + 1;
        }
        moveNext(nL);
    }
    


    fprintf(out, "G contains %d strongly connected components:\n", numSCC);
    List componentL[numSCC];
    for(int j = 0; j<=numSCC; j++){
        componentL[j] = newList();
    }
    moveBack(nL);
    int copynumSCC = 1;
    while(index(nL) != -1){
        prepend(componentL[copynumSCC], get(nL));
        if(getParent(gT, get(nL)) == NIL){
            copynumSCC = copynumSCC + 1;
        }
        if(copynumSCC > numSCC){
            break;
        }
        movePrev(nL);
    }

    for(int k=1; k<=numSCC; k++){
        fprintf(out, "Component %d:", k);
        printList(out, componentL[k]);
        fprintf(out, "\n");
    }


    freeGraph(&nG);
    freeGraph(&gT);
    freeList(&nL);
    for(int l = 0; l<numSCC; l++){
        freeList(&componentL[l]);
    }
    //freeList(&componentL);

    fclose(in);
    fclose(out);

    return(0);

}