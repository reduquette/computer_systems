#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
//printf("%d \n", argc);
//printf("%s \n", argv[1]);

int num = 0;
int temp = 0;
int index = 0;
int total = 0;
int displaycounter = 0;
int *outs;


if (argc == 1){
num = 10;
}
else{ 
num = atoi(argv[1]);
}

//store values in outs
outs = (int *) malloc(num * sizeof(int));

while(1){
scanf("%d", &temp);
if (temp == -1) break;
*(outs + index) = temp;
if (index == num -1) index = 0;
else index++;
total++;
}

//print outs
if (total >= num){

printf("Here are the last %d numbers:", num);

for (displaycounter = 0; displaycounter < num; displaycounter++){
printf(" %d", *(outs + index));
if (index == num -1) index = 0;
else index++;
}
printf("\n");
}
else{
printf("There are only %d numbers: ", total);
for (displaycounter = 0; displaycounter < total; displaycounter++){
printf(" %d", *(outs + displaycounter));
}
printf("\n");
}
free(outs);
return 0;
}
