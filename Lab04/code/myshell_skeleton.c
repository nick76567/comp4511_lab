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

	char program_name[2][32] = {0}, option[2][16] = {0};
	int seconds, status;

	sscanf(cmdline, "%s %*s %s %s", program_name[0], program_name[1], option[1]);
	seconds = atoi(option[0]);
	printf("%s %s %s \n", program_name[0], program_name[1], option[1]);
	
	int pfds[2];
	pipe(pfds);	
	pid_t pid = fork();
	if(pid == 0){
		close(1);
		dup(pfds[1]);
		close(pfds[0]);
		execlp(program_name[0], program_name[0], NULL);
		//exit(0);
	}else if(pid > 0){
		close(0);
		dup(pfds[0]);
		close(pfds[1]);
		wait(0);
		execlp(program_name[1], program_name[1], option[1], NULL);
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
