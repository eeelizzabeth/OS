#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 120

int main() {

   char input[MAX+3];
   bool exit = true;
   bool done = true;
   int t = 0;
   while(exit)
   {	
	done = true;
	printf("msh> ");
	if(fgets(input, MAX+3, stdin) == NULL)
	{
	   printf("\n");	
	   return 0;
	}
	t = strlen(input);

	if(t-1 > MAX)
	{
	  while(!strchr(input, '\n'))
	  {
	    if(fgets(input,(sizeof input), stdin) == NULL )
	    {
		break;	
	    }
	  }
	  printf("error: input too long\n");
	  done = false;
	}
	
	
	input[t-1] = 0;
	
	if(strcmp(input, "exit") == 0)
	{
	   return 0;
	}
	if(done)
	{
	   printf("%s\n", input);
	}	
   }

   return 0;
}

