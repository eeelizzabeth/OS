#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// a simple parser for this BNF grammar:
// A ::= 0 B  
// B ::= 1 A | 2 B | ;

void A(), B();

// input token
char tok[10];

char *lookahead;

// return the next token from standard input as a string,
// or return NULL if there is no more input
char *lexan() {
  int n;
  n = scanf("%s", tok);
  if (n == EOF) {
    return NULL;
  }
  return tok;
}

// print an error message and exit
void error(char* msg) {
  printf("%s\n", msg);
  exit(1);
}

// return if the standard input follows the syntax for A,
// else print an error message and exit
void A() {
  //char *lookahead;

  // YOUR CODE HERE
  // hints:
  //   - read the next token
  lookahead = lexan();
  //   - it's an error if there's no next token, or
  if(lookahead == NULL)
  {
    error("no");
  } else if(strcmp(lookahead, "0") != 0) {
  //     there is a next token but it's not "0"
    error("no");
  }
  else {
  //   - if "0" is the next token, you will need B()
    lookahead = lexan();
    B();
  }
}

// return if the standard input follows the syntax for B,
// else print an error message and exit
void B() {
  //char *lookahead;
  
  //lookahead = lexan();
  if(lookahead == NULL) {
    error("no");
  }
  else if(strcmp(lookahead, "1") == 0)
  {
    //lookahead = lexan();
    A(); 
  }
  else if(strcmp(lookahead, "2") == 0) {
    lookahead = lexan();
    B();
  }
  else if(strcmp(lookahead, ";") == 0) {
  } 
  else {
    error("no");
  }
  

}

int main() {
  A();
  // the input should be one A only
  if (lexan() != NULL) {
    error("no");
  }
  printf("yes\n");
  
}
