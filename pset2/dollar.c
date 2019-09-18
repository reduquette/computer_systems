#include <stdio.h>
#include <stdlib.h>

int main(){
  //variables
  int total = 0;
  int twenties = 0;
  int tens = 0;
  int fives = 0;
  int ones  = 0;

  //get initial value from user
  printf("Enter a dollar amount:");
  scanf("%d", &total);

  //calculate results
  twenties = total / 20;
  total = total - twenties * 20;
  tens = total / 10;
  total = total - tens * 10;
  fives = total / 5;
  ones = total - fives * 5;

  //print results
  printf("$20 bills: %d\n", twenties);
  printf("$10 bills: %d\n", tens);
  printf("$5 bills: %d\n", fives);
  printf("$1 bills: %d\n", ones);
}
