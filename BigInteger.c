/*	
	Name: Veena Kotha
	Cruz ID: vkotha
	Assignment: pa3
*/

#include "BigInteger.h"
#include "List.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define POWER 9
#define BASE 1000000000

// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj{
	int sign;
	List longs; 
} BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

BigInteger newBigInteger(){
	BigInteger B;
	B = malloc(sizeof(BigIntegerObj));
	B->sign = 0;
	B->longs = newList();
	return B;
}

void freeBigInteger(BigInteger* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero 
// state.


int sign(BigInteger N){
	if(N->sign == -1){
		return -1;
	}
	else if(N->sign == 1){
		return 1;
	}
	else{
		return 0;
	}

}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B. 
int compare(BigInteger A, BigInteger B){
	if(sign(A) > sign(B)){
		return 1;
	}
	else if(sign(B) > sign(A)){
		return -1;
	}
	else{
		if(length(A->longs) == length(B->longs)){
			moveFront(A->longs);
			moveFront(B->longs);
			while(get(A->longs)!= -1){
				if(get(A->longs) > get(B->longs)){
					if(A->sign == -1){
						return -1;
					}
					else{
						return 1;
					}
				}
				else if(get(A->longs) < get(B->longs)){
					if(A->sign == -1){
						return 1;
					}
					else{
						return -1;
					}
				}
	        	else{
	        		moveNext(A->longs);
	        		moveNext(B->longs);
	        	}
			}
			return 0; //it is equal
		}
		//check which length is longer - that is greater
		else{
			if(length(A->longs) > length(B->longs)){
				if(A->sign == 1){
					return 1;
				}
				else{
					return -1;
				}
			}
			else{
				if(A->sign == 1){
					return -1;
				}
				else{
					return 1;
				}
			}
		}
	}
}


// equals()
// Return true (1) if A and B are equal, false (0) otherwise. 
int equals(BigInteger A, BigInteger B){
	if(length(A->longs)==length(B->longs) && sign(A) == sign(B)){
		moveFront(A->longs);
		moveFront(B->longs);
		while(get(A->longs)!= -1){
			if(get(A->longs) != get(B->longs)){
				return 0;
			}
        	else{
        		moveNext(A->longs);
        		moveNext(B->longs);
        	}
		}
		return 1;
	}
	else{
		return 0;
	}
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
	N->sign = 0;
	moveFront(N->longs);
	while(get(N->longs)!= -1){
		delete(N->longs);
        moveNext(N->longs);
	}
	N->longs = NULL;
	free(N->longs);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the 
// zero state.
void negate(BigInteger N){
	if(sign(N) == 1){
		N->sign = -1;
	}
	else if(sign(N) == -1){
		N->sign = 1;
	}
	else if(sign(N) == 0 || N == NULL){
		
	}
}



// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s. 
BigInteger stringToBigInteger(char* s){
	if(s != NULL){
		BigInteger bI = newBigInteger();
		bI->sign = 1;
		int len = strlen(s);

		if(s[0] == '-'){
			bI->sign = -1;
			len = strlen(s)-1;
			s = s + 1;
		}
		else if(s[0] == '+'){
			bI->sign = 1;
			len = strlen(s)-1;
			s = s + 1;
		}
		else if(s[0] != '-' || s[0] != '+'){
			bI->sign = 1;
			len = strlen(s);
		}
		int counters = 0;
		while(s[counters] == '0'){
			counters = counters + 1;
			len = len - 1;
		}
		s = s + counters;

		if(counters == len){
			bI->sign = 0;
		}
		else if(len<POWER){
			char z[POWER];
			strncpy(z, s, len);
			int c = len;
			z[c] = '\0';
			append(bI->longs, atol(z));
		}
		else if(len % POWER != 0){
			int i = len % POWER;
			char x[POWER];
			strncpy(x, s, i);
			int copied = i;
			if(len < i){
				copied = len;
			}
			x[copied] = '\0';
			append(bI->longs, atol(x));
			s = s + i;
			len = len - i;
			while(len>0){
				char t[POWER];
				strncpy(t, s, POWER);
				t[POWER] = '\0';
				append(bI->longs, atol(t));
				len = len - POWER;
				s = s + POWER;
			}

		}
		else{
			while(len>0){ 
				char t[POWER];
				strncpy(t, s, POWER);
				int copy = POWER;
				if(len < POWER){
					copy = POWER;
				}
				t[copy] = '\0';
				append(bI->longs, atol(t));
				s = s + POWER;
				len = len - POWER;
			}		
		}
		return bI;
	}
	return NULL;
}



// copy()
// Returns a reference to a new BigInteger
BigInteger copy(BigInteger N){
	BigInteger c = newBigInteger();
	c->sign = N->sign;
	moveFront(N->longs);
	while(get(N->longs)!= -1){
		append(c->longs, get(N->longs));
        moveNext(N->longs);
        moveNext(c->longs);
	}
	return c;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its 
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){ 
	BigInteger A1 = copy(A);
	BigInteger B1 = copy(B);
	if(A1->sign == 0 || B1->sign == 0){ 
		
		if(A1->sign == 0){ 
			moveBack(B1->longs);
			while(get(B1->longs) != -1){ 
				prepend(S->longs, get(B1->longs));
				movePrev(B1->longs);
			} 
			
		} 
		else if(B1->sign == 0){ 
			moveBack(A1->longs);
			while(get(A1->longs) != -1){ 
				prepend(S->longs, get(A1->longs));
				movePrev(A1->longs);
			} 
		} 
	} 
    else if(A1->sign == B1->sign){ 
		
		if(A1->sign == -1){ 
			S->sign = -1;
		} 
		else{ 
			S->sign = 1;
		} 
		long carry = 0;
		moveBack(A1->longs);
		moveBack(B1->longs);
		long l;
		while(get(A1->longs) != -1 && get(B1->longs) != -1){ 
			l = get(A1->longs) + get(B1->longs);
			l = l + carry;
			if(l >= BASE){ 
				l = l - BASE;
				carry = 1;
			} 
			else{
				carry = 0;
			} 
			prepend(S->longs, l);
			movePrev(A1->longs);
			movePrev(B1->longs);
		} 
		if(get(A1->longs) != -1){ 
			while(get(A1->longs) != -1){ 
				prepend(S->longs, get(A1->longs) + carry);
				carry = 0;
				movePrev(A1->longs);
			} 
		} 
		else if(get(B1->longs) != -1){ 
			while(get(B1->longs) != -1){ 
				prepend(S->longs, get(B1->longs) + carry);
				carry = 0;
				movePrev(B1->longs);
			} 
		} 
	} 

	else if((A1->sign == -1 && B1->sign == 1) || (A1->sign == 1 && B1->sign == -1)){
		switch (A1->sign){
			case 1: {
			if(B1->sign == -1) { 
				negate(B1);
				
				if(compare(B1,A1)!=1) { 
					S->sign=1;
					moveBack(A1->longs);
					moveBack(B1->longs);
					int carry = 0;
					long l;
					
					while(get(A1->longs) != -1 && get(B1->longs) != -1){ 
						l = get(A1->longs) - get(B1->longs) - carry;
						if(get(A1->longs)-get(B1->longs) < 0){ 
							l = l + BASE;
							carry = 1;
						} 
						else{ 
							carry = 0;
						} 
						prepend(S->longs, l);	
						
						movePrev(B1->longs);
						movePrev(A1->longs);
					} 

					if(get(B1->longs) != -1){  
						while(get(B1->longs) != -1){ 
							prepend(S->longs, get(B1->longs) - carry);
							carry = 0;
							movePrev(B1->longs);
						}
					} 
					else if(get(A1->longs) != -1){ 
						while(get(A1->longs) != -1){ 
							prepend(S->longs, get(A1->longs) - carry);
							carry = 0;
							movePrev(A1->longs);
						}
					} 
				} 
				
				else if(compare(B1,A1)==1) {
					negate(B1);
					negate(A1);
					S->sign=-1;
					moveBack(A1->longs);
					moveBack(B1->longs);
					int carry = 0;
					long l;
					while(get(A1->longs) != -1 && get(B1->longs) != -1){ 
						l = get(B1->longs) - get(A1->longs) - carry;
						if(get(B1->longs)-get(A1->longs) < 0){
							l = l + BASE;
							carry = 1;
						} 
						else{ 
							carry = 0;
						} 
						prepend(S->longs, l);		
						movePrev(B1->longs);
						movePrev(A1->longs);
					} 
					if(get(B1->longs) != -1){ 
						while(get(B1->longs) != -1){
							prepend(S->longs, get(B1->longs) - carry);
							carry = 0;
							movePrev(B1->longs);
						}
					} 
					else if(get(A1->longs) != -1){ 
						while(get(A1->longs) != -1){ 
							prepend(S->longs, get(A1->longs) - carry);
							carry = 0;
							movePrev(A1->longs);
						} 
					} 
				} 
		
			}
			break;
		};

		default: {
			if(A1->sign == -1) { 
				negate(A1);
				if(compare(A1,B1)!=1) { 
					S->sign=1;
					 moveBack(A1->longs);
					moveBack(B1->longs);
					int carry = 0;
					long l;
					
					while(get(A1->longs) != -1 && get(B1->longs) != -1){ 
						l = get(B1->longs) - get(A1->longs) - carry;
						if(get(B1->longs)-get(A1->longs) < 0){ 
							l = l + BASE;
							carry = 1;
						} 
						else{
							carry = 0;
						} 
						prepend(S->longs, l);		
						movePrev(B1->longs);
						movePrev(A1->longs);
					} 

					if(get(B1->longs) != -1){  
						while(get(B1->longs) != -1){ 
							prepend(S->longs, get(B1->longs) - carry);
							carry = 0;
							movePrev(B1->longs);
						}
					} 
					else if(get(A1->longs) != -1){ 
						while(get(A1->longs) != -1){ 
						prepend(S->longs, get(A1->longs) - carry);
						carry = 0;
						movePrev(A1->longs);
						}
					} 
				}  
				else if(compare(A1,B1)==1) {
					negate(B1);
					negate(A1);
					S->sign=-1;
					moveBack(A1->longs);
					moveBack(B1->longs);
					int carry = 0;
					long l;
		
					while(get(A1->longs) != -1 && get(B1->longs) != -1){ 
						l = get(A1->longs) - get(B1->longs) - carry;
						if(get(A1->longs)-get(B1->longs) < 0){
							l = l + BASE;
							carry = 1;
						} 
						else{ 
							carry = 0;
						} 
						prepend(S->longs, l);		
						movePrev(B1->longs);
						movePrev(A1->longs);
					} 
					if(get(B1->longs) != -1){ 
						while(get(B1->longs) != -1){
							prepend(S->longs, get(B1->longs) - carry);
							carry = 0;
							movePrev(B1->longs);
						}
					} 
					else if(get(A1->longs) != -1){ 
						while(get(A1->longs) != -1){ 
							prepend(S->longs, get(A1->longs) - carry);
							carry = 0;
							movePrev(A1->longs);
						} 
					} 
				} 
	
			}
		break;
		};
		
		} 
	}	
}

// sum()
// Returns a reference to a new BigInteger object representing A + B. 
BigInteger sum(BigInteger A, BigInteger B){
	BigInteger S = newBigInteger();
	add(S, A, B);
	return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting 
//itscurrentstate: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B){
	if(compare(A,B)==0) {
		D->sign = 0; 
		append(D->longs, 0);
	}
	else if(A->sign == 0 || B->sign == 0){
		if(A->sign == 0 && B->sign == 0){
			D->sign = 0;
			moveBack(A->longs);
			while(get(A->longs) != -1){
				prepend(D->longs, get(A->longs));
				movePrev(A->longs);
			}
		}
		else if(A->sign != 0){
			D->sign = A->sign;
			moveBack(A->longs);
			while(get(A->longs) != -1){
				prepend(D->longs, get(A->longs));
				movePrev(A->longs);
			}
		}
		else if(B->sign != 0){
			negate(B);
			D->sign = B->sign;
			moveBack(B->longs);
			while(get(B->longs) != -1){
				prepend(D->longs, get(B->longs));
				movePrev(B->longs);
			}
		}
	}
	else if(A->sign == B->sign){
		if(A->sign == 1){
			switch (compare(A, B)) {
				case 0: {
					D->sign=0;
					append(D->longs, 0);
					break;
				}

				case 1: {
					D->sign=A->sign;
					moveBack(A->longs);
					moveBack(B->longs);
					int carry = 0;
					long l;
				
					while(get(A->longs) != -1 && get(B->longs) != -1){ 
						l = get(A->longs) - get(B->longs) - carry;
						if(get(A->longs)-get(B->longs) < 0){ 
							l = l + BASE;
							carry = 1;
						} 
						else{ 
							carry = 0;
						} 
						prepend(D->longs, l);		
						movePrev(A->longs);
						movePrev(B->longs);
					}
					if(get(A->longs) != -1){
						while(get(A->longs) != -1){
							prepend(D->longs, get(A->longs) - carry);
							carry = 0;
							movePrev(A->longs);
						}
					}
					else if(get(B->longs) != -1){
						while(get(B->longs) != -1){
							prepend(D->longs, get(B->longs) - carry);
							carry = 0;
							movePrev(B->longs);
						}
					}
					break;
				}

				case -1: {
					D->sign=B->sign * -1;
					moveBack(A->longs);
					moveBack(B->longs);
					int carry = 0;
					long l;
				
					while(get(B->longs) != -1 && get(A->longs) != -1){ //2
						l = get(B->longs) - get(A->longs) - carry;
						if(get(B->longs)-get(A->longs) < 0){ 
							l = l + BASE;
							carry = 1;
						} 
						else{ 
							carry = 0;
						} 
						prepend(D->longs, l);		
						movePrev(A->longs);
						movePrev(B->longs);
					}
					if(get(A->longs) != -1){
						while(get(A->longs) != -1){
							prepend(D->longs, get(A->longs) - carry);
							carry = 0;
							movePrev(A->longs);
						}
					}
					else if(get(B->longs) != -1){
						while(get(B->longs) != -1){
							prepend(D->longs, get(B->longs) - carry);
							carry = 0;
							movePrev(B->longs);
						}
					}
					break;
				}
			} 
		}
		else if(A->sign == -1){
			BigInteger A1 = copy(A);
			negate(A1);
			BigInteger B1 = copy(B);
			negate(B1);
			switch (compare(A1,B1)) {
				case 0: {
					D->sign=0;
					append(D->longs, 0);
					break;
				}
				case 1: {
					D->sign=A->sign;
					moveBack(A->longs);
					moveBack(B->longs);
					int carry = 0;
					long l;
				
					while(get(A->longs) != -1 && get(B->longs) != -1){ 
						l = get(A->longs) - get(B->longs) - carry;
						if(get(A->longs)-get(B->longs) < 0){ 
							l = l + BASE;
							carry = 1;
						} 
						else{ 
							carry = 0;
						} 
						prepend(D->longs, l);		
						movePrev(A->longs);
						movePrev(B->longs);
					}
					if(get(A->longs) != -1){
						while(get(A->longs) != -1){
							prepend(D->longs, get(A->longs) - carry);
							carry = 0;
							movePrev(A->longs);
						}
					}
					else if(get(B->longs) != -1){
						while(get(B->longs) != -1){
							prepend(D->longs, get(B->longs) - carry);
							carry = 0;
							movePrev(B->longs);
						}
					}
					break;
				}

				case -1: {
					D->sign=1;
					moveBack(A->longs);
					moveBack(B->longs);
					int carry = 0;
					long l;
				
					while(get(B->longs) != -1 && get(A->longs) != -1){ 
						l = get(B->longs) - get(A->longs) - carry;
						if(get(B->longs)-get(A->longs) < 0){ 
							l = l + BASE;
							carry = 1;
						} 
						else{ 
							carry = 0;
						} 
						prepend(D->longs, l);		
						movePrev(A->longs);
						movePrev(B->longs);
					}
					if(get(A->longs) != -1){
						while(get(A->longs) != -1){
							prepend(D->longs, get(A->longs) - carry);
							carry = 0;
							movePrev(A->longs);
						}
					}
					else if(get(B->longs) != -1){
						while(get(B->longs) != -1){
							prepend(D->longs, get(B->longs) - carry);
							carry = 0;
							movePrev(B->longs);
						}
					}
					break;
				}
			}	
		}    
	}
	
	else if((A->sign == -1 && B->sign == 1) || (A->sign == 1 && B->sign == -1)){ 
		negate(B);
		if(A->sign == B->sign){ 
			if(A->sign == -1){ 
				D->sign = -1;
			} 
			else{
				D->sign = 1;
			} 
			long carry = 0;
			moveBack(A->longs);
			moveBack(B->longs);
			long l;
			while(get(A->longs) != -1 && get(B->longs) != -1){ 
				l = get(A->longs) + get(B->longs);
				l = l + carry;
				if(l >= BASE){ 
					l = l - BASE;
					carry = 1;
				} 
				else{ 
					carry = 0;
				} 
				prepend(D->longs, l);
				movePrev(A->longs);
				movePrev(B->longs);
			} 
			if(get(A->longs) != -1){ 
				while(get(A->longs) != -1){ 
					prepend(D->longs, get(A->longs) + carry);
					carry = 0;
					movePrev(A->longs);
				} 
			} 
			else if(get(B->longs) != -1){ 
				while(get(B->longs) != -1){ 
					prepend(D->longs, get(B->longs) + carry);
					carry = 0;
					movePrev(B->longs);
				} 
			} 
		} 
	}	
}

// diff()
// Returns a reference to a new BigInteger object representing A - B. 
BigInteger diff(BigInteger A, BigInteger B){
	BigInteger C = newBigInteger();
	subtract(C, A, B);
	return C;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting 
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
	if(A->sign == B->sign){
		P->sign = 1;
	}
	else if((A->sign == 1 && B->sign == -1)|| (A->sign == -1 && B->sign == 1)){
		P->sign = -1;
	}
	else if(A->sign == 0 || B->sign == 0){
		P->sign = 0;
	}
	
	if((A->sign != 0) || (B->sign != 0)){
		moveBack(B->longs);
		int carry = 0;
		long l;
		int counter = 0;
		moveBack(A->longs);
		while(get(A->longs) != -1){
			l = get(A->longs) * get(B->longs) + carry;
			carry = l/BASE;
			l = l % BASE;	
			prepend(P->longs, l);	
			movePrev(A->longs);
		}
		if(carry > 0){
			prepend(P->longs, carry);
		}
		counter = counter + 1;


	//after 1st iteration
		movePrev(B->longs);
		while(get(B->longs) != -1){
			carry = 0;
			moveBack(A->longs);
			moveBack(P->longs);
			for(int i = 0; i<counter; i++){
				if(get(P->longs) != -1) {
					movePrev(P->longs);
				}
			}
			while(get(A->longs) != -1){
				if(get(P->longs) != -1){
					l = get(B->longs) * get(A->longs) + carry + get(P->longs);
				}
				else{
					l = get(B->longs) * get(A->longs) + carry;
				}
				carry = l/BASE;
				l = l % BASE;	
				
				if(get(P->longs) == -1){
					prepend(P->longs, l);
					
				}
				else{
					set(P->longs, l);	
				}
				movePrev(A->longs);
				movePrev(P->longs);
			}
			counter = counter + 1;
			if(carry > 0){
				if(get(P->longs) != -1){
					l = get(P->longs) + carry;
					carry = l/BASE;
					l = l % BASE;
					
					set(P->longs, l);
				}
				else{
					prepend(P->longs, carry);

				}
			}
			movePrev(B->longs);
		}
	}
}


// prod()
// Returns a reference to a new BigInteger object representing A*B 
BigInteger prod(BigInteger A, BigInteger B){
	BigInteger C = newBigInteger();
	multiply(C, A, B);
	return C;
}



// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out. 
void printBigInteger(FILE* out, BigInteger N){
	moveFront(N->longs);
	if(N==NULL){
		fprintf(stderr, "Error: calling printBigInteger() on a NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}

	if(N->sign == 0){
		fprintf(out, "%s", "0");
	}
	else{
		if(N->sign == -1){
			fprintf(out, "%s", "-");
		}
		while((get(N->longs) != -1) && (get(N->longs) == 0)){
			moveNext(N->longs);
		}
		
		if(get(N->longs) != -1){
			fprintf(out, "%ld", get(N->longs));
			moveNext(N->longs);
		}
		
		while(get(N->longs)!= -1){
			fprintf(out, "%0*ld", POWER, get(N->longs));
		    moveNext(N->longs);
		}
	}
	
}