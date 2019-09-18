#include <stdio.h>
#include <string.h>

void pushValStack(int stack[], int *top, int value);
int popValStack (int stack[], int *top);
void pushOpStack(char *stack[], int *top, char *value);
char *popOpStack(char *stack[], int *top);
void printValStack(int stack[], int *top);
void printOpStack(char *stack[], int *top);

int main(int argc, char **argv) {

  int values[50];
  char *operands[50];
  int topvals = -1, topops = -1, i = 0;
  int val, val1, val2, res;
  char *token, *op;


  for (i = 1; i < argc; i++){
    token = argv[i];
    
    if (*token == '[' || *token == '+' || *token == 'x'){
      pushOpStack(operands, &topops, token);
    }
    else if (*token == ']'){
      //while ((op = popOpStack(operands, &topops)) != "["){
      while(1){
      op = popOpStack(operands, &topops);
      if (*op == '[') break;

      val1 = popValStack(values, &topvals);
      val2 = popValStack(values, &topvals);

      if (*op == 'x'){
        res = (val1) * (val2);
        pushValStack(values, &topvals, res);
      }
      if (*op == '+'){
        res = val1 + val2;
        pushValStack(values, &topvals, res);
      }
      }
    }
    else{
      sscanf(token, "%d", &val);
      pushValStack(values, &topvals, val);
    }

  }
  
   while (topops>=0){
    op = popOpStack(operands, &topops);
    if (*op != '['){ 
      val1 = popValStack(values, &topvals);
      val2 = popValStack(values, &topvals);
      //printf("The current operation is: %d %s %d\n", val2, op, val1);
      if (*op == 'x'){
      res = (val1) * (val2);
      //printf("Result is %d\n", res);
      pushValStack(values, &topvals, res);
      }
      if (*op == '+'){
        res = val1 + val2;
        //printf("Result is %d\n", res);
        pushValStack(values, &topvals, res);
      }
    }
  }
  res = popValStack(values, &topvals);
  printf("%d\n", res);
  return 0;
}

//FUNCTIONS

void pushValStack(int stack[], int *top, int value){
  if (*top >= 49){
    printf("Stack is over flow");
  }
  stack[*top + 1] = value;
  *top = *top + 1;
}

int popValStack (int stack[], int *top){
  int temp = 0;
  if (*top < 0){
    printf("Stack is under flow");
  }
  temp = stack[*top];
  stack[*top] = 0;
  *top = *top -1;
  return temp;
}


void pushOpStack(char *stack[], int *top, char *value){
  if (*top >= 49){
    printf("Stack is over flow");
  }
  (*top)++; //should increment the value in top
  stack[*top] = value;
}

char *popOpStack(char *stack[], int *top){
  char *temp;
  if (*top < 0){
    printf("The stack is under flow");
    return NULL;
  }
  temp = stack[*top];
  stack[*top] = NULL;
  (*top)--;
  return temp;
}

void printValStack(int stack[], int *top){
  int i = 0;
  for(i = 0; i < (*top + 1); i++){
    printf("%d\n", stack[i]);
  }
}

void printOpStack(char *stack[], int *top){
  int i = 0;
  for(i = 0; i < (*top + 1); i++){
    printf("%s\n", stack[i]);
  }
}