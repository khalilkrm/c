#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255

char strTmp[BUFFER_SIZE]; 

char *strrev(char *str) {
      char *p1, *p2;
      strcpy(strTmp,str);
 
      if (! strTmp || ! *str) return strTmp;
      for (p1 = strTmp, p2 = strTmp + strlen(str) - 1; p2 > p1; ++p1, --p2) {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return strTmp;
} 

int main (void)
{	
	char toReverse[BUFFER_SIZE];
	
	printf("Enter a string to be reversed : ");
	scanf("%255[^\n]%*c", toReverse);
	
	printf("Reverse '%s' is '%s'\n", toReverse, strrev(toReverse));
	
	return EXIT_SUCCESS;
}
