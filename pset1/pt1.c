#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
int rowOne, rowTwo, rowThree, rowFour;
int colOne, colTwo, colThree, colFour;
int diagLeft, diagRight;

printf("Enter the numbers from 1 to 16 in any order.");
scanf( "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p);
printf("%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n", a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);

rowOne = a + b + c + d;
rowTwo = e + f + g + h;
rowThree = i + j + k + l;
rowFour = m + n + o + p;

colOne = a + e + i + m;
colTwo = b + f + j + n;
colThree = c + g + k + o;
colFour = d + h + l + p;

diagLeft = a + f + k + p;
diagRight = m + j + g + d;

printf("Row sums: %d %d %d %d \n", rowOne, rowTwo, rowThree, rowFour);
printf("Column sums: %d %d %d %d \n", colOne, colTwo, colThree, colFour);
printf("Diagonal sums: %d %d \n", diagLeft, diagRight);

return 0;
}
