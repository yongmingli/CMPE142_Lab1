// CMPE142 Lab1 
// Yongming Li
// 010215699
// March/2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
 
// The array below will hold the arguments: args[0] is the command.
static char* args[512];
pid_t pid;
 
/*
 * EXAMPLE: If you type "cd cdme" in your shell:
 *    args[0] = "cd" and args[1] = "cdme"
*/

static void command(); 
static void split(char* cmd); 
static char* skipwhite(char* s);
 
int main()
{
	static char line[1024];
	printf("****** Welcome to use lym shell by Yongming Li ******\n"); 
	printf("===> lym: Type 'exit' or send EOF to exit.\n");
	printf("===> Enter 'help' to get the user manual of lym.\n\n"); 
	while (1) {
		// Print the command prompt
		printf("lym>>>");
		fflush(NULL);
 
		// Read a command line
		if (!fgets(line, 1024, stdin)) 
			return 0;
 
		char* cmd = line;
		split(cmd);

		if (args[0] != NULL) {
			if (strcmp(args[0], "exit") == 0) {
				printf("Thank You for using lym shell, PEACE OUT~~~.\n"); 
				exit(0);
			}
			else if (strcmp(args[0], "cd") == 0) chdir(args[1]); //cd
			else if (strcmp(args[0], "fuck") == 0) {
				printf("FUCK YOU!!!!!\n"); 
				exit(0);
			}
			else if (strcmp(args[0], "help") == 0) //help: to get user manual
			{
				printf("\n********lym user manual********\n");
				printf("IMPORTANT: This shell program can ONLY execuate ONE command at a time.\n");
				printf("           The input '<' and output '>' does NOT work in lym shell.\n");
				printf("           There is NO error message if you enter a wrong command.\n");
				printf("\n");
				printf("===>Most of the commands work in lym shell, here are some additional information.\n");
				printf("========================\n");
				//cd
				printf("===>For 'cd' command, you can enter more than one layer using '/'.\n");
				printf("    For example: 'cd file1/file2', it will take you to file2 which is within file1.\n"); 
				printf("    Also, if you want to go back, use 'cd ..' command, which will take you back one layer.\n");
				printf("    You can also use '/' with '..', such as 'cd ../..'.\n");
				//more
				//printf("===>For \n");
				printf("\n");
				printf("Please enjoy and explor lym shell program~\n");
				printf("If you spot/encounter any bug/problem, please contact me.\n");
				printf("Thank You.\n");
				printf("More will update......\n");
				printf("Author: Yongming Li\n");
				printf("Version 1.0\n\n");
			}
			else command();
			}
		for (int i = 0; i < 10; ++i) // add wait state
		wait(NULL); 
	}
	return 0;
}
 
static char* skipwhite(char* s)
{
	while (isspace(*s)) ++s;
	return s;
}
 
static void split(char* cmd)
{
	cmd = skipwhite(cmd);
	char* next = strchr(cmd, ' ');
	int i = 0;
 
	while(next != NULL) {
		next[0] = '\0';
		args[i] = cmd;
		++i;
		cmd = skipwhite(next + 1);
		next = strchr(cmd, ' ');
	}
 
	if (cmd[0] != '\0') {
		args[i] = cmd;
		next = strchr(cmd, '\n');
		next[0] = '\0';
		++i; 
	}

	args[i] = NULL;
}

static void command()
{	
	pid = fork();
 
	if (pid == 0) { //child
		if (execvp(args[0], args) == -1) // If child fails
		{
			printf("Command fail !!!"); 
			_exit(EXIT_FAILURE); 
		}	
	}
}