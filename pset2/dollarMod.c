#include <stdio.h>
#include <stdlib.h>

void pay_amount(int dollars, int *twenties, int *tens, int*fives, int *ones);

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones){
  *twenties = dollars / 20;
  dollars = dollars - *twenties * 20;
  *tens = dollars / 10;
  dollars = dollars - *tens * 10;
  *fives = dollars / 5;
  *ones = dollars - *fives * 5;
  return;
}

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
  pay_amount(total, &twenties, &tens, &fives, &ones);

  //print results
  printf("$20 bills: %d\n", twenties);
  printf("$10 bills: %d\n", tens);
  printf("$5 bills: %d\n", fives);
  printf("$1 bills: %d\n", ones);
}
