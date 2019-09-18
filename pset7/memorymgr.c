#include <stdio.h>
#include <stdlib.h>
#include "memorymgr.h"
int *fr; 
int *last;

//helper functions
int mult(int size){
  int x = size;
  if (size % 8 != 0) x = (size / 8)*8 + 8;
  return x;
}

//Note: firstBlock, lastBlock, isAllocated, and nextBlock all assume *p is the HEADER of the block, not a pointer to the payload 

int *firstBlock(){         // return a pointer to the first block on the heap
  return fr;
}

int *lastBlock(){          // return a pointer to the sentinel block
  return last;
}

int isAllocated(int* p){
  int res = 0;
  if ((*p % 2) !=0){
    res = 1;
  }
  return res;
}

int *nextBlock(int *p){    // return a pointer to the block that follows p
  int * next;
  int increment;
  if (isAllocated(p)){
    if (*p % 4 == 3){
	increment = (*p - 3) / 4;
    }
    increment = (*p -1) / 4;
  }
  else{
    increment = *p /4 ;
  }
  next = p + increment;
  return next;
}


//main functions

void  initmemory(int size){  // initialize a simulated heap
  //create heap of desired size
  int actualsize, *res;
  actualsize = mult(size + 4) + 8;
  res = malloc(actualsize);

  //create pointers
  fr = res + 1; //sets fr to payload of first available block, is 1 bc type int
  *fr = (actualsize - 8);
  last = res + (actualsize - 4) /4;
  *last = 1;
}


void *myalloc(int length){  // allocate a block of length (or more) bytes
  int *temp, valnext;
  int actual = mult(length + 4);

  temp = firstBlock();
  while ((isAllocated(temp)) ||(*temp < actual) ){
    if (*temp == 1) return NULL;
    temp = nextBlock(temp);
  }
  valnext = *temp - actual;
  *temp = actual + 1;
  if (*nextBlock(temp) != 1) *(nextBlock(temp)) = valnext;
  return temp + 1;
}

void  myfree(void *ptr){     // free an allocated block
  int *header = ptr - 4;
  if (*header % 8 == 0) {
    printf("This block is already free. \n");
    return;
  }
  if (*header == 1){
    printf("This is the sentinel block \n");
    return;
  }
  *header = *header - 1;
}

void  coalesce(){            // go through the heap, coalescing unallocated blocks
  int *temp, *next;
  temp = firstBlock();
  while (*temp != 1){// not the sentinel block
    if (!isAllocated(temp)){
      next = nextBlock(temp);
      while(!isAllocated(next)){
        *temp = *temp + *next;
        next = nextBlock(temp);
      }
    }
    temp = nextBlock(temp);
  }

}


void  printallocation(){  // print info about the simulated heap, for debugging purposes
  int *temp, counter = 0;
  temp = firstBlock();
  while (*temp != 1){
    if (isAllocated(temp)){
      printf("Block %d: size %d \t allocated \n", counter, (*temp -1));
    }
    else{
      printf("Block %d: size %d \t unallocated \n", counter, *temp);
    }
    counter++;
    temp = nextBlock(temp);
  }
  printf("\n");
}
