#include "lexer.h"
#include "error.h"
#include "expr.h"
#include "stmt.h"
#include "prog.h"
//
// a predictive parser for a super-minimal programming language
//
// refer to the BNF  

// types of functions used below
void match();
PROG *parse(), *prog();

int lookahead;    // most recent token

// check that current token is t, and read next token
void match(int t) { 
    if (lookahead == t)
	lookahead = lexan();
    else error("syntax error");
} 

// parse a program
PROG *parse() {
   PROG *p;
   lookahead = lexan();
   p = prog();
   match(DONE);
   return p;
}

// one or more statements
PROG *prog() {
   if(lookahead == DONE)
   {
	error("syntax error");
   }
   EXPR *expr() {
	char *id;
	int num;
	switch(lookahead) {
	  case ID:
	     id = lexer_id_val();
	     match(ID);
	     if(lookahead == '(')
	     {
		EXPR *e = expr();
		match(')');
		
		return e;
	     } else {
		EXPR *e = expr_create_var(id);
		return e;
	     }
	  case NUM:
	     num = lexer_num_val();
	     match(NUM);
	     EXPR *e = expr_create_num(num);
	     return e;
	  default:
	     error("syntax error");
	}
   }
   STMT *stmt() {
	char *id;
	int num;
	switch(lookahead) {
	    case ID:
		id = lexer_id_val();
		match(ID);
		if(lookahead == '(')
		{
		   match('(');
		   EXPR *e = expr();
		   match(')');
		   STMT *s = stmt_create_call(id, e);
		   match(';'); 
		   return s;
		}
		else if(lookahead == '=')
		{
		   match('=');
		   EXPR *e = expr();
		   STMT *s = stmt_create_assign(id, e);
		   match(';');
		   return s;
		}
	    
	    default:
		error("syntax error"); 
		
	}
   }


   // YOUR CODE HERE
   
   PROG *prog = NULL;

   while(lookahead != DONE) {
	
	STMT *s = stmt();
	prog = prog_create(s, prog);

   }
   return prog;
  	
 
}

