#include "memorymgr.h"
#include <stdio.h>

void *stackBottom() {
/*
	Finds and returns address for bottom of the stack. 
*/
	unsigned long bottom;
    FILE *statfp = fopen("/proc/self/stat", "r");
    fscanf(statfp,
           "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*u %*u %*u %*u %*u %*u %*d %*d "
           "%*d %*d %*d %*d %*u %*u %*d "
           "%*u %*u %*u %lu", &bottom);
    fclose(statfp);
	return (void *) bottom;
}



int onHeap(int *p){
/*
	Checks if p is a pointer to a location on the heap (i.e. between the first header and sentinel block). 
*/
  int *first, *last;
  first = firstBlock();
  last = lastBlock(); 
  if (p > first){
    if (p < last){
      return 1;
     }  
  }
  return 0;
}

int *findBlock(int *p){
  /*
	Traverse through the heap to find the block containing p. 
	Returns header of that block.  
  */
  int * temp = firstBlock();
  while (1){
    if (nextBlock(temp) > p) return temp;
    temp = nextBlock(temp);
  }
}

int isMarked(int *ptr){
/*
	Checks the the block indicated by ptr is marked already. 
	Assumes ptr is a pointer to the header of a block. 
*/
  if (*ptr % 4 == 3) return 1;
  return 0;
}

void markBlock(int *ptr){ 
/*
	Designates the block ptr points to as marked. 
	Assumes ptr is a pointer to the header of a block. 
	Assumes the block is allocated. 
*/
  if (isMarked(ptr)) printf("This block is already marked.\n");
  else *ptr = *ptr + 2;
}


void mark(void *p){
  if (!onHeap(p)) return;
  int * b = findBlock(p);
  int i, j;
  if (isAllocated(b)){
    if (isMarked(b)) return;
    markBlock(b);
    //if (*b % 4 == 3) return;
    //*b = *b + 2;
    j = (*b - 3) / 4;
    for (i = 0; i < j ; i++){
	mark(p + i);
    }
    }
}


void printunmarked(){ 
/*
	Iterates through the heap, printing each block and whether it's marked. 
	Similar to printallocation().
	Used for debugging. 
*/
  int *temp, counter = 0;
  temp = firstBlock();
  while (*temp != 1){
    if (counter > 500) break;
    if (isMarked(temp)){
      printf("Block %d: size %d \t marked \n", counter, (*temp -1));
    }
    else{
      printf("Block %d: size %d \t unmarked \n", counter, *temp);
    }
    counter++;
    temp = nextBlock(temp);
  }
  printf("\n");

}

void freeUnmarked(){
/*
	Iterates through the heap, freeing all unmarked blocks. 
	Assumes heap is already fully marked!
*/
  int *temp;
  temp = firstBlock(); 
  
  while (*temp != 1){
    if (!isMarked(temp)){
      if (isAllocated(temp)) myfree(temp + 1); //myfree assumes it receives a pointer to the payload of the block-- temp is the header
    }
    temp = nextBlock(temp);
  }
}

void gc(){
  int **max = (int **) stackBottom(); // the address of the bottom of the stack
  int* dummy;
  int **p = &dummy; // the address of the top of the stack
  int *header;


  while(p<max){
    mark(*p);
    p++;
  }

  //deallocate inaccessible blocks
  freeUnmarked();
  //printallocation();
  //tidy up
  coalesce();
}

