#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *readaline(int max);

int main(int argc, char **argv){
	char *line;
	int num = 0;
  int i = 0, j= 0, total = 0, N = 0;
	
	//set number of lines to display
	if (argc > 1)
		sscanf(argv[1], "%d", &num);
	else 
		num  = 10;

  char **final = (char **) malloc( sizeof(char *) * num);

	//get the last num lines	

  while((line =readaline(80)) != NULL){
    total++;
    final[j] = line;
    if (j == num - 1){ j = 0;}
    else {j++;}
  }

  //print the array
  if (total < num){
      printf("There are only %d lines: \n", total);
      j = 0;
      N = total;
    }
  else{
      printf("The last %d lines are: \n", num);
      N = num;
  }

  for(i = 0; i<N; i++){
    printf("%s\n",final[j]);
    if (j == num - 1){ j = 0;}
    else {j++;}
  }
  for(i = 0; i < num; i++){
    free(final[i]);
  }
	free(final);
  }

char *readaline(int max){
  int length = 0;
	char *res = (char *) malloc(sizeof(char)*max);
	if (fgets(res, max, stdin) == NULL){
		free(res);
    return NULL;
	}
  length = strlen(res);
  if(res[length-1]=='\n') res[length-1] = 0;
  return res;	
  } 
