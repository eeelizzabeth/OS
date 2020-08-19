#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expr.h"
#include "string_util.h"

// constructor for variable expression
EXPR *expr_create_var(char *s) {
   EXPR *e = (EXPR *)malloc(sizeof(EXPR));
   e->expr_type = VAR_EXPR;
   e->s = str_dup(s);
   return e;
}

// constructor for num expression
EXPR *expr_create_num(int i) {
   EXPR *e = (EXPR *)malloc(sizeof(EXPR));
   e->expr_type = NUM_EXPR;
   e->i = i;
   return e;
}

// constructor for function call expression
EXPR *expr_create_fcall(char *fname, EXPR *expr) {
   EXPR *e = malloc(sizeof(EXPR));
   e->expr_type = FCALL_EXPR;
   e->s = str_dup(fname);
   e->expr = expr;
   return e;
}

// print this expression
void expr_print(EXPR *expr) {

   if(expr == NULL)
   {
	return;
   } else {
	if(expr->expr_type == FCALL_EXPR)
	{
	  printf("%s(", expr->s);
	  expr_print(expr->expr);
	  printf(")");
	} else if(expr->expr_type == NUM_EXPR)
	{
	  printf("%d", expr->i);
	} else if(expr->expr_type == VAR_EXPR)
	{
	  printf("%s", expr->s);
	} else {
	  return;
	}
   }

}


