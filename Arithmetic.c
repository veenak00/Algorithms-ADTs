/*
Name: Veena Kotha
CruzID: vkotha
Assignment: pa3
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
    FILE *in, *out;
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

    int a;
	fscanf(in, "%d\n", &a);

    char *A = malloc(a+1);
	fscanf(in, "%s\n", A);

    int b;
	fscanf(in, "%d\n", &b);

    char *B = malloc(b+1);
    fscanf(in, "%s\n", B);

    
    BigInteger bA = newBigInteger();
    BigInteger bB = newBigInteger();
    BigInteger bC = newBigInteger();
    BigInteger bD = newBigInteger();
    BigInteger bE = newBigInteger();
    BigInteger bF = newBigInteger();
    BigInteger bG = newBigInteger();
    BigInteger bH = newBigInteger();
    BigInteger bI = newBigInteger();
    BigInteger bJ = newBigInteger();
    BigInteger bL = newBigInteger();
    BigInteger bM = newBigInteger();
    BigInteger bN = newBigInteger();
    BigInteger bO = newBigInteger();
    BigInteger bP = newBigInteger();
    BigInteger bQ = newBigInteger();
    BigInteger bR = newBigInteger();
    BigInteger bS = newBigInteger();
    BigInteger bT = newBigInteger();
    BigInteger bU = newBigInteger();
    BigInteger bV = newBigInteger();

    //A
    bA = stringToBigInteger(A);
    printBigInteger(out, bA);
    fprintf(out, "\n\n");


    //B
    bB = stringToBigInteger(B);
    printBigInteger(out, bB);
    fprintf(out, "\n\n");


    //A+B
    BigInteger bA2 = copy(bA);
    BigInteger bB2 = copy(bB);
    bC = sum(bA2, bB2);
    printBigInteger(out, bC);
    fprintf(out, "\n\n");


    //A-B
    BigInteger bA3 = copy(bA);
    BigInteger bB3 = copy(bB);
    bD = diff(bA3, bB3);
    printBigInteger(out, bD);
    fprintf(out, "\n\n");


    //A-A
    BigInteger bA4 = copy(bA);
    BigInteger bA5 = copy(bA);
    bE = diff(bA4, bA5);
    printBigInteger(out, bE);
    fprintf(out, "\n\n");


    //3A - 2B
    bS = stringToBigInteger("3");
    BigInteger bA6 = copy(bA);
    bF = prod(bA6, bS); //3*A

    bT = stringToBigInteger("2");
    BigInteger bB4 = copy(bB);
    bU = prod(bB4, bT); //2*B

    bV = diff(bF, bU);     
    printBigInteger(out, bV);
    fprintf(out, "\n\n");

    //A*B
    BigInteger bA7 = copy(bA);
    BigInteger bB5 = copy(bB);
    bG = prod(bA7, bB5);
    printBigInteger(out, bG);
    fprintf(out, "\n\n");
    

    //A^2
    BigInteger bA8 = copy(bA);
    BigInteger bA9 = copy(bA);
    bH = prod(bA8, bA9);
    printBigInteger(out, bH);
    fprintf(out, "\n\n");


    //B^2
    BigInteger bB6 = copy(bB);
    BigInteger bB7 = copy(bB);
    bI = prod(bB6, bB7);
    printBigInteger(out, bI);
    fprintf(out, "\n\n");


    //9A^4 + 16B^5
    BigInteger bH2 = copy(bH);
    BigInteger bH3 = copy(bH);
    bJ = prod(bH2, bH3); //A^4
    bP = stringToBigInteger("9");
    BigInteger bJ2 = copy(bJ);
    bQ = prod(bJ2, bP); //9A^4

    BigInteger bI2 = copy(bI);
    BigInteger bI3 = copy(bI);
    bL = prod(bI2, bI3);
    BigInteger bL2 = copy(bL);
    BigInteger bB8 = copy(bB);
    bM = prod(bL2, bB8); //B^5
    bN = stringToBigInteger("16");
    BigInteger bM2 = copy(bM);
    bO = prod(bM2, bN); //16B^5

    BigInteger bQ2 = copy(bQ);
    BigInteger bO2 = copy(bO);
    bR = sum(bQ2, bO2);
    printBigInteger(out, bR);

    free(A);
    free(B);

    fclose(in);
    fclose(out);

    return(0);
}