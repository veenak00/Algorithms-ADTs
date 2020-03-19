/*
Name: Veena Kotha
Cruz ID: vkotha
Assignment Name: pa4
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
    Graph nG = newGraph(n);

    int srcVer = 0;
    int destVer = 0;
    int src = 0;
    int dest = 0;

    while(fgets(line, MAX_LEN, in) != NULL){ //reading line feed
        fscanf(in, "%d %d", &srcVer, &destVer);
        if((srcVer == 0) && (destVer == 0)){
            break; //should stop adding edges when line in the input file is 0 0
        }
        else{
            addEdge(nG, srcVer, destVer);
        }
    }
    
    printGraph(out, nG);
    fprintf(out, "\n");

    //after line with 0 0
    while(fgets(line, MAX_LEN, in) != NULL){
        fscanf(in, "%d %d", &src, &dest);
        if((src == 0) && (dest == 0)){
            break;
        }
        else{
            List nL = newList();
            BFS(nG, src);
            getPath(nL, nG, dest);
            if(getDist(nG, dest) == INF){
                fprintf(out, "The distance from %d to %d is infinity", src, dest);
                fprintf(out, "\n");
                fprintf(out, "No %d-%d path exists", src, dest);
                fprintf(out, "\n");
                fprintf(out, "\n");
            }
            else{
                int dist = getDist(nG, dest);
                fprintf(out, "The distance from %d to %d is %d", src, dest, dist);
                fprintf(out, "\n");
                fprintf(out, "A shortest %d-%d path is: ", src, dest);
                printList(out, nL);
                fprintf(out, "\n\n");
            }
            free(nL);
        }
    }

    freeGraph(&nG);

    fclose(in);
    fclose(out);

    return(0);

}