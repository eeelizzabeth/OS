#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_BUF 160

int main(int argc, char **argv) {
    int ch;
    char s[MAX_BUF];
    static const char prompt[] = "msh> ";
    char *status;
    FILE *fp;
    if(argc > 1)
    {
      fp = fopen(argv[1], "r");
    }
    while (1) {
	     if(argc > 1) {
	        status = fgets(s, MAX_BUF, fp);
	    }
	    else {
    	  // prompt for input
        if (isatty(fileno(stdin))) {
          printf(prompt);
        }
    	  // read input
    	  status = fgets(s, MAX_BUF-1, stdin);
    	}
    	char *cd = (char*) malloc(3);
    	strncpy(cd, s, 2);

    	// exit if ^d entered
    	if (status == NULL) {
    	    printf("\n");
    	    exit(EXIT_SUCCESS);
    	}

    	// exit if "exit" entered
    	else if (strcmp(s, "exit\n") == 0) {
    	    exit(EXIT_SUCCESS);
    	}

    	// handle case of input that is too long
    	else if (s[strlen(s)-1] != '\n') {
    	    printf("error: input too long\n");
    	    // clear the input buffer
    	    while ((ch = getchar()) != '\n' && ch != EOF);
    	    continue;
    	}

    	else if(strcmp(s, "help\n") == 0) {
    	   printf("enter Linux command, or 'exit' to exit\n");
    	}
    	else if (strcmp(s, "today\n") == 0) {
    	   time_t t = time(NULL);
    	   struct tm tm = *localtime(&t);
    	   printf("%02d/%02d/%d\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
    	}
    	else if(strcmp(cd, "cd") == 0)
    	{
    	   char *tokens[10];
    	   status[strlen(status)-1] = 0;
    	   char *token = strtok(status, " ");
    	   int i = 0;

    	   while(token != NULL) {
    	     tokens[i] = token;
    	     i++;
    	     token = strtok(NULL, " ");
    	   }
    	   tokens[i] = NULL;

    	   if(tokens[1] == NULL ) {
    	     chdir(getenv("HOME"));
    	   }
    	   else {
    	     if(chdir(tokens[1]) == -1) {
    		       printf("msh: %s: %s\n", tokens[0], strerror(errno));
    	     }
    	   }

    	}
    	else {
    	   int rc = fork();
    	   int n = strlen(status);

    	   if (rc < 0) {
    	      fprintf(stderr, "fork failed\n");
    	      exit(1);
    	   } else if (rc == 0) {
    	     char *tokens[n];
    	     status[n-1] = 0;
    	     char *token = strtok(status, " ");
    	     int i = 0;

    	     while (token != NULL) {
    	        tokens[i] = strdup(token);
    	        i++;
    	        token = strtok(NULL, " ");
    	     }
    	     tokens[i] = NULL;

    	     int execute = execvp(tokens[0], tokens);
    	     printf("msh: %s: %s\n", tokens[0], strerror(errno));
    	     exit(1);

    	     } else {
    	       int rc_wait = wait(NULL);
    	     }
        	}
         }
}
