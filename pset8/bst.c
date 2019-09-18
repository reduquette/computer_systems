#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTnode *createNode(void *item){
	BSTnode *newNode = (BSTnode *) malloc(sizeof(BSTnode));
	newNode->item = item;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
   
}



BSTnode *find(BSTnode *n, void *item, int compare(void *, void *)){
  if (n == NULL) { printf("Empty tree. "); return n;}
  if (n->item == NULL){ printf("find called on node without item. "); return n;}

	int res = compare(item, n->item);

	if (res > 0 && n->right != NULL){ // item larger than n
		return find(n->right, item, compare);
	}

	if (res < 0 && n->left != NULL){ // item is smaller than n
		return find(n->left, item, compare);
	}
  return n;
}



void insert(BSTnode *n, void *item, int compare(void *, void *)){
  if (n == NULL){
   return;
  }

  if (n->item == NULL){
    printf("Node has no item.\n");
    return;
  }

	BSTnode *parent = find(n, item, compare);
  
	int res = compare(item, parent->item);
	if (res == 0) return;

	BSTnode *newNode = createNode(item);
	if (res < 0){
    if (parent->left != NULL) printf("EXCEPTION: trying to insert in an occupied location. \n");
		parent->left = newNode;
	}
	else{
    if (parent->right != NULL) printf("EXCEPTION: trying to insert in an occupied location. \n");
		parent->right = newNode;
	}	
}
