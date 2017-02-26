#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMDLINE_LEN 256

/* function prototypes go here... */

void show_prompt();
int get_cmd_line(char *cmdline);
void process_cmd(char *cmdline);


/* The main function implementation */
int main()
{
	char cmdline[MAX_CMDLINE_LEN];
	
	while (1) 
	{
		show_prompt();
		if ( get_cmd_line(cmdline) == -1 )
			continue; /* empty line handling */
		
		process_cmd(cmdline);
	}
	return 0;
}


void process_cmd(char *cmdline)
{
	// printf("%s\n", cmdline);
	if(strcmp(cmdline, "exit") == 0){
		printf("myshell is terminated with pid %d\n", getpid());
		exit(0);
	}

	char buffer[4];
	int seconds, status;
	sscanf(cmdline, "%*s %s", buffer);
	seconds = atoi(buffer);

	pid_t pid = fork();
	if(pid == 0){
		printf("child pid %d is started\n", getpid());
		sleep(seconds);
		printf("child pid %d is terminated with status %d\n", getpid(), status);
		exit(0);
	}else if(pid > 0){
		wait(&status);
	}

}


void show_prompt() 
{
	printf("myshell> ");
}

int get_cmd_line(char *cmdline) 
{
    int i;
    int n;
    if (!fgets(cmdline, MAX_CMDLINE_LEN, stdin))
        return -1;
    // Ignore the newline character
    n = strlen(cmdline);
    cmdline[--n] = '\0';
    i = 0;
    while (i < n && cmdline[i] == ' ')
    {
        ++i;
    }
    if (i == n)
    {
        // Empty command
        return -1;
    }
    return 0;
}
