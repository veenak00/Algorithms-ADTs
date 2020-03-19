/*
Name: Veena Kotha
CruzID: vkotha
Assignment: pa3
*/

#include <stdio.h>
#include <assert.h>
// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj* BigInteger;

BigInteger newBigInteger();
void freeBigInteger(BigInteger* pN);


// Access functions -----------------------------------------------------------

int sign(BigInteger N);
int compare(BigInteger A, BigInteger B);
int equals(BigInteger A, BigInteger B);


// Manipulation procedures ----------------------------------------------------

void makeZero(BigInteger N);
void negate(BigInteger N);


// BigInteger Arithmetic operations -----------------------------------------------

BigInteger stringToBigInteger(char* s);

BigInteger copy(BigInteger N);

void add(BigInteger S, BigInteger A, BigInteger B);

BigInteger sum(BigInteger A, BigInteger B);

void subtract(BigInteger D, BigInteger A, BigInteger B);

BigInteger diff(BigInteger A, BigInteger B);
void multiply(BigInteger P, BigInteger A, BigInteger B);

BigInteger prod(BigInteger A, BigInteger B);


// Other operations -----------------------------------------------------------

void printBigInteger(FILE* out, BigInteger N);






