/* 
Name: Veena Kotha
CruzID: vkotha
Assignment name: pa3
*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i); 
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%lu ", get(A));
   }
   printf("\n");   
   for(moveBack(B); index(B)>=0; movePrev(B)){ 
      set(B, 444444444444444);
      printf("%lu ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   set(A, 232);
   for(i=0; i<9; i++) moveNext(A); // at index 15
   set(A, 5555555555);
   insertAfter(A, -2);
   set(A, 999999999);
   for(i=0; i<5; i++) movePrev(A); // at index 10

   delete(A);
   deleteBack(B);
   printList(stdout,A);
   printf("\n");
   printf("%u\n", length(A));
   clear(A);
   printf("%u\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}


/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
444444444444444 444444444444444 444444444444444 444444444444444 444444444444444 444444444444444 444444444444444 444444444444444
 444444444444444 444444444444444 444444444444444 444444444444444 444444444444444 444444444444444 444444444444444 444444444444444
  444444444444444 444444444444444 444444444444444 444444444444444
false
false
true
1 2 3 4 5 -1 231 6 7 8 9 11 12 13 14 999999 15 -2 16 17 18 19 20
21
0
*/