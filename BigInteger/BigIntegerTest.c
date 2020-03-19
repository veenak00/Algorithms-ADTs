/*	Name: Veena Kotha
	Cruz ID: vkotha
	Assignment: pa3
*/
#include "BigInteger.h"
#include<stdlib.h>
#include<stdio.h>
#include "List.h"

int main(int argc, char * argv[]){
	

	BigInteger A = newBigInteger();
	BigInteger B = newBigInteger();
	BigInteger C = newBigInteger();
	BigInteger D = newBigInteger();
	BigInteger E = newBigInteger();
	BigInteger F = newBigInteger();
	BigInteger G = newBigInteger();
	BigInteger Z = newBigInteger();
	BigInteger Y = newBigInteger();
	BigInteger X = newBigInteger();
	BigInteger W = newBigInteger();
	BigInteger V = newBigInteger();
	BigInteger U = newBigInteger();
	BigInteger T = newBigInteger();
	BigInteger Y1 = newBigInteger();
	BigInteger X1 = newBigInteger();
	BigInteger W1 = newBigInteger();
	BigInteger V1 = newBigInteger();
	BigInteger U1 = newBigInteger();
	BigInteger T1 = newBigInteger();
	BigInteger Y2 = newBigInteger();
	BigInteger X2 = newBigInteger();
	BigInteger W2 = newBigInteger();
	BigInteger V2 = newBigInteger();
	BigInteger U2 = newBigInteger();
	BigInteger T2 = newBigInteger();

	char Aa[1000] = "-3";
	char Bb[1000] = "3";
	char Cc[1000] = "-5";
	char Dd[1000] = "5";
	char Ee[1000] = "1234567";
	char Ff[1000] = "123456";
	char Gg[1000] = "1234567";

	A = stringToBigInteger(Aa);
	B = stringToBigInteger(Bb);
	C = stringToBigInteger(Cc);
	D = stringToBigInteger(Dd);
	E = stringToBigInteger(Ee);
	F = stringToBigInteger(Ff);
	G = stringToBigInteger(Gg);

	G = copy(E);
	printBigInteger(stdout, G);

	Y = sum(A, B); //0
	X = sum(A, C); //-8
	W = sum(C, A); //-8
	V = sum(C, B); //-2
	U = sum(D, A); //2
	T = sum(A, D); //2

	printBigInteger(stdout, Y);
	printBigInteger(stdout, X);
	printBigInteger(stdout, W);
	printBigInteger(stdout, V);
	printBigInteger(stdout, U);
	printBigInteger(stdout, T);


	Y1 = diff(A, B); //-6
	X1 = diff(A, C); //2
	W1 = diff(C, A); //-2
	V1 = diff(C, B); //-8
	U1 = diff(D, A); //8
	T1 = diff(A, D); //-8

	printBigInteger(stdout, Y1);
	printBigInteger(stdout, X1);
	printBigInteger(stdout, W1);
	printBigInteger(stdout, V1);
	printBigInteger(stdout, U1);
	printBigInteger(stdout, T1);

	Y2 = prod(A, B); //-9
	X2 = prod(A, C); //15
	W2 = prod(C, A); //15
	V2 = prod(C, B); //15
	U2 = prod(D, A); //-15
	T2 = prod(A, D); //-15

	printBigInteger(stdout, Y2);
	printBigInteger(stdout, X2);
	printBigInteger(stdout, W2);
	printBigInteger(stdout, V2);
	printBigInteger(stdout, U2);
	printBigInteger(stdout, T2);



	printBigInteger(stdout, A);
	printf("\n");
	printBigInteger(stdout, B);
	printf("\n");
	Z = sum(A, B);
	Z = diff(A, B);
	Z = prod(A, B);

	printBigInteger(stdout, Z);

	printBigInteger(stdout, C);
	printf("\n");
	printBigInteger(stdout, D);
	printf("\n");
	printBigInteger(stdout, E);
	printf("\n");
	printBigInteger(stdout, F);
	printf("\n");
	printBigInteger(stdout, G);
	printf("\n");


//testing compare
	 int a = (compare(D, B)); //1
	 int b = (compare(B, D)); //-1
	 int c = (compare(C, A)); //-1
	 int d = (compare(A, C)); //1
	 int g = (compare(A, D)); // -1
	 int h = (compare(B, C)); // 1
	 int v = (compare(C, B)); // -1
	 int e = (compare(A, A)); //0
	 int f = (compare(B, B)); //0

	 printf("%d %d %d %d %d %d %d %d %d", a, b, c, d, g, h, v, e, f);
	 printf("\n");

//testing sign
	int f = sign(A);
	printf("%d", f);

//testing negate
	negate(B);
	negate(C);
	printBigInteger(stdout, B);
	printf("\n");
	printBigInteger(stdout, C);

	printBigInteger(stdout, A);

	

}
