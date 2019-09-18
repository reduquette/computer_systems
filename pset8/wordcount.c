#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"


struct wordcount{
	char wordcount[80];
	int count;
};
typedef struct wordcount WordCount;


WordCount * createWord(char content[]){
	WordCount *newWord = (WordCount *) malloc(sizeof(WordCount));
	strcpy(newWord->wordcount, content);
  newWord->count = 1;
  return newWord;
}


int cmpCount(void * a, void * b){
  WordCount *x = (WordCount *) a;
  WordCount *y = (WordCount *) b;
  //compares a and b based on count 
  if (x->count == y->count) return 0;
  if (x->count <= y->count) return -1;
  return 1;
}


int cmpWord(void *a, void *b){
  //compares a and b based on value of the word
  WordCount *x = (WordCount *) a;
  WordCount *y = (WordCount *) b;
  return strcmp(x->wordcount, y->wordcount);
}


void inc(BSTnode *root, WordCount *x){
  BSTnode *loc = find(root, x, cmpWord);
  (((WordCount *) loc->item)->count)++;
}


void inorder(BSTnode *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        WordCount * x = (WordCount *) root->item;
        printf(" %s %d ", x->wordcount, x->count); 
        inorder(root->right); 
    } 
} 



BSTnode *findMax(BSTnode *root){
	int res, res2;

	//if has no children, return root
	if ((root->left == NULL) && (root->right == NULL)){
		return root;
	}

	//find max of children
	BSTnode *maxChild = NULL;

	if (root->left == NULL) maxChild = findMax(root->right);
	else if (root->right == NULL) maxChild = findMax(root->left);
	else{ //both children not null
		BSTnode *rightMax = findMax(root->right);
		BSTnode *leftMax = findMax(root->left);
		res = cmpCount(rightMax->item, leftMax->item);
		if (res >0) //right greater than left
			maxChild = rightMax;
		else //left ge right
			maxChild = leftMax;
	}

	//compare to max of children and return greatest one. 
	res2 = cmpCount(maxChild->item, root->item);
	if (res2 >0) return maxChild;
	else return root;
}


int inTree(BSTnode *root, WordCount *item){
  BSTnode *location = find(root, item, cmpWord); 
  WordCount *x =location->item;
  return (cmpWord(item, location->item) == 0);
}

void addWord(BSTnode * root, WordCount *item){
  
  if (inTree(root, item)){
      inc(root, item);
  }
  else{
      insert(root, item, cmpWord);      
  }
  return;
}

int main(void){
   char temp[80];
	WordCount *tester = NULL, *result = NULL;

  BSTnode *root = NULL, *max = NULL;
  scanf("%s", temp);
  root = createNode(createWord(temp));

  
	while (scanf("%s", temp) == 1){
    tester = createWord(temp);
    addWord(root, tester);
  }

  //inorder(root);
  max = findMax(root);
	result = (WordCount *) (max->item);
	printf("The most frequent word is '%s', which occurs %d times.\n", result->wordcount, result->count);

	return 0;
}
