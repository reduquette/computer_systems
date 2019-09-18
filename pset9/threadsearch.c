#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


#define THREAD_NUM 100
#define TEXT_LEN 1000000

//Global Variables
char *pattern;
char text[TEXT_LEN];

int done = 0;
int result = -1;

pthread_mutex_t lock;
pthread_mutex_t locktwo;

int patlen;
int textlen;
int next = 0;

//Function Declarations
void *threadfunc();
int searchPosition(int i);

//Start of Program

int main(int argc, char *argv[]) {
  // Step 1: Extract the pattern string from the command line.   
  pattern = argv[1];
  patlen = strlen(pattern);

  // Step 2: Create and populate the text string.
  textlen = TEXT_LEN; // will be overridden by the actual length
  int count = 0;
  while (count < TEXT_LEN) {
      int status = scanf("%c", &text[count]);
      count++;
      if (status == EOF) {
         textlen = count;
         break;
      }
  }

  //Step 3a: Create the necessary number of threads
  
  pthread_t tid[THREAD_NUM];

  pthread_mutex_init(&lock, NULL);
  pthread_mutex_init(&locktwo, NULL);
  
  
  int numthreads = 0;
  
  /*for(numthreads = 0; numthreads <THREAD_NUM; numthreads++){
    pthread_create(&tid[numthreads], NULL, threadfunc, NULL);
  }*/

  while(!done){
    if (numthreads < THREAD_NUM){
      pthread_create(&tid[numthreads], NULL, threadfunc, NULL);
      numthreads++;
    }
   
  }

  //Step 3b: Close threads
  int i;
  for (i=0; i<numthreads; i++)
      pthread_join(tid[i], NULL);  
  
  
  // Step 4: Determine the result and print it
   if (result == -1)
       printf("Pattern not found\n");
   else
       printf("Pattern begins at character %d\n", result);
}

void *threadfunc(){
  int res = -1;
  int index = -1;

  while(!done){
    //Pick a location that has not been chosen by any other thread, and mark it as chosen.  (If all possible locations have been already chosen, then quit.)
    //so that two threads do not pick the same location, this is a critical section and is locked. 	
    pthread_mutex_lock(&lock);
    if (next > (textlen)){
      done = 1;
      pthread_mutex_unlock(&lock); 
      break;
    }
    index = next;
    next++;
    pthread_mutex_unlock(&lock); 

       
    //check index
    res = searchPosition(index); //1 if yes, 0 no

    //since this changes a global variable, this is a critical section 
    pthread_mutex_lock(&lock);
    if (res){
      result = index;
      done = 1;
    }
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}


int searchPosition(int i) {
   int j;
   for (j=0;j<strlen(pattern); j++) 
       if (text[i+j] != pattern[j])
          return 0;
   return 1;
}
				
