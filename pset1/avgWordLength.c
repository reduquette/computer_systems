// count.c  Count the number of lines and chars in the input.

#include <stdio.h>
#include <ctype.h>
int main() {
  int lineCount = 0;
  int numLines = 0;
  int numChars = 0;
  int numWords = 0;
  int wordLength = 0;
  double wordSum = 0.0;
  double avgLength = 0.0;

  printf("Enter text.  Use an empty line to stop.\n");
  
  while (1) {
      int ic = getchar();
      if (ic < 0)    //EOF encountered
          break;
      char c = (char) ic;
      if (c == '\n' && lineCount == 0) //Empty line
          break; 
      numChars ++;
      if (c == '\n') {
          numLines ++;
          lineCount = 0;
      }
      else
          lineCount ++;

      if (isspace(c)){ // reading empty space
	if (wordLength != 0){ //end of a word
	  numWords ++;
          wordLength = 0;
	}
      }
      else{ // reading non whitespace character
      	wordLength ++;
  	wordSum ++;
      }
  }

  avgLength = wordSum / numWords;
  printf("Your text has %d lines and %d characters.\n", numLines, numChars);
  printf("Your text has %d words, with an average length of %.2f.\n", numWords, avgLength);
}
