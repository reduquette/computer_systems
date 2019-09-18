#include <stdio.h>

int readline(int *pattern, int max){
//read a line of characters from the keyboard.
//The second argument to the function is the maximum number of characters to read.
//If a line has more characters than that, the function should ignore the rest of the characters
//on the line. The function returns the number of characters read.
//Note that the array should not contain the '\n' from the end of the line,
// nor should it include a terminator character such as '\0'.
  int i = 0;
  char c;
  for (i = 0; i < max; i++){
      c = getchar();
      if (c < 0) {
        break;
      }
      //if (c == 10 || c == 0){
      if (c == '\n' || c == '\0'){
	      break;
      }
      *(pattern + i) = c;
   }
   while (c != '\n'  && c != '\0' ){
      c = getchar();
   }
   return i;
}

int *findmatch(int *pattern, int *text, int patternlen, int textlen){
   int *returnPtr = NULL;
   int i = 0;
   for(i = 0; i < (textlen - patternlen + 1); i++){
      if (ismatch(pattern, text, patternlen, i)){ //it's a match!
	 returnPtr = text + i;
	 break;
      }
   }
   return returnPtr;
}

int ismatch(int *pattern, int *text, int patternlen, int pos){
   int notallqs = 0;
   int j = 0;
   for(j; j < patternlen; j++){
      if ((*(pattern + j) != *(text + pos + j))  && (*(pattern + j) != 63)){
         return 0;
      }
      if (*(text + pos + j) != '?'){
         notallqs++;
      }
   }
   if (notallqs == 0){
      return 0;
   }
   return 1;
}



void printmessage(int *position, int *text, int patternlen, int textlen){
//If a match was not found, then a "no match" message is printed.
//If a match is found, then the function prints the position in the text where the match begins,
//and prints the remaining text characters that appear after the match ends.
   int *iter = NULL;
   int *end = text + textlen;
   if (position == NULL){
      printf("No match.\n");
   }
   else{
      printf("The pattern was found at char %i.", position - text);
      printf(" The remaining text characters are: \n");
      iter = position + patternlen ;
      while (iter < end){
	 putchar(*(iter));
	 iter++;
      }
      printf("\n");
      //for(iter = position; iter < end; iter = iter + 1){
      //   putchar(*(iter));
      //}
   }
}


int main() {
   int text[40], pattern[40], *position;
   int textlen, patternlen;
   int i = 0;

   printf("Enter text: ");
   textlen = readline(text, 40);
   printf("Enter pattern: ");
   patternlen = readline(pattern, 40);

   position = findmatch(pattern, text, patternlen, textlen);
   printmessage(position, text, patternlen, textlen);
}
