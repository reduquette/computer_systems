#include <stdio.h>
#include <stdlib.h>
#include "intsort.h"

// create a node
IntNode *createNode(int val){
  IntNode *newNode = (IntNode *) malloc(sizeof(IntNode));
  newNode->item = val;
  return newNode;
}

// insert a node into the chain, in sorted order
void insert(IntNode *header, int val){ 
  IntNode *newNode = createNode(val);

/*  
if ((header == NULL) || ((header->item) > val)){
    printf("Insert at beginning\n");
    newNode-> next = header;
    header = newNode;
  }
  else{*/
//header is a node with info 0: val > header always

    IntNode *temp = header;
    while (1){
      if (temp->next == NULL) break;
      if ((*(temp->next)).item >= val) break;
      temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
  //}
}


// print the values stored in the chain of nodes
void printAll(IntNode *header){
//header is 0 value
  IntNode *temp;
  temp = header->next;
  while (temp != NULL){
    printf("%d ", temp->item);
    temp = temp->next;
  }
  printf("\n");
}

void freeAll(IntNode *header){
   if (header == NULL) return;
   freeAll(header->next);
   free(header);
}

int main(void) {
  
  int i = 0;
  IntNode *zero = createNode(0);

  printf("Enter some numbers, ending with -1:");

  while (1){
    if (scanf("%d", &i) != 1) break;
    //printf("%d ", i);
    if (i == -1) break;
    insert(zero, i);
  }
  printAll(zero);
  freeAll(zero);
  
  return 0;
}
