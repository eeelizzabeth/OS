#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// max length input string
#define MAXSTR 25

// convert input binary string to a number

int main() {

   // user input string
   char s[MAXSTR+3]; 

   // prompt for input
   printf("> ");

   // read input string; at most MAXSTR+1 chars accepted
   // Note: this is tricky. If we accept only MAXSTR chars,
   // we can't see if user entered more chars and they are
   // being dropped by fgets.
   fgets(s, MAXSTR+3, stdin);

   // check input length; n does not include final carriage return
   int n = strlen(s)-1;  
   if (n > MAXSTR) {
     printf("input cannot be more than %d characters\n", MAXSTR);
     exit(1);
   }

   // convert s from a string in binary, to an int, and output
   
   // YOUR CODE HERE
   // check for no input
   //if (n == 0)
   //{
     //printf("%d\n", n);
     //exit(1);
   //}
   //int size = sizeof(s) / sizeof(s[0]);
   
   int  dec = 0;

   int i;
   for(i=0; i < n; i++)
   {
     //check invalid input
     if(s[i] == '0' || s[i] == '1')
     {
	
	//if(s[i] == '1')
	//{
	  //dec += pow(2,(n-1) - i);
	//} 
     }
     else
     {
	printf("input must contain only zeros and ones\n");	
	exit(1);
     } 
   }
   int j;
   for(j=0; j < n; j++)
   {
     if(s[j] == '1')
     {
	dec += pow(2, (n-1) - j);
	//printf("curr dec: %lf\n", dec);
     }
   }
   printf("%d\n", dec);
   
	
  

}


