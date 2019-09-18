#include <stdio.h>
#include <stdlib.h>

//function declarations
int takesNoArgs(char op);
double processOp(double amt, char op, double val);
double processPlus(double amt, double val);
double processMinus(double amt, double val);
double processTimes(double amt, double val);
double processDivide(double amt, double val);
double processPrint(double amt);
static float processClear();

int main(int argc, char **argv){

  double amt = 0.0;
  char op;
  double val;
  char temp;

  printf("CS 2271 Calculator\n");
  
  while (1){
    op = getchar();
    if (op == EOF) break;
    if (op == 'Q') break;
 
    if (takesNoArgs(op)) {
	val = 0.0;
    }
    else {scanf("%lf", &val);}
    
    temp = getchar();
    while (temp != '\n'){
	temp = getchar();
    }
    amt = processOp(amt, op, val);
  }
  printf("Thank you and goodbye!\n");
}

int takesNoArgs(char op) { 
    return ((op == 'C') || (op == '='));
}

double processOp(double amt, char op, double val) {
    if (op == '+')
        return processPlus(amt, val);
    else if (op == '-')
        return processMinus(amt, val);
    else if (op == '*')
        return processTimes(amt, val);
    else if (op == '/')
        return processDivide(amt, val);
    else if (op == '=')
        return processPrint(amt);
    else if (op == 'C')
        return processClear();
    else {
        printf("Bad Operator \n");
        return amt;
    }
}

double processPlus(double amt, double val) {
    return amt + val;
}

double processMinus(double amt, double val) {
    return amt - val;
}

double processTimes(double amt, double val) {
    return amt * val;
}

double processDivide(double amt, double val) {
    return amt / val;
}

double processPrint(double amt) {
    printf("%f \n", amt);
    return amt;
}

static float processClear() {
    return 0;
}
