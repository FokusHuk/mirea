#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int execution(char *);
char *read_line(void);

int main()
{
	char * command;
	int stat_exe;
	stat_exe = 1;
	if((command = malloc(sizeof(char) * 512)) == NULL)
	{
		printf("memory error in main\n");
		exit(-1);
	}
	while(stat_exe)
	{
		printf(">> ");
		command = read_line();
		stat_exe = execution(command);
	}
	return 0;
}

int execution(char * command)
{
	char * split_commands[20];
	char * split;
	int index;
	index = 0;
	split = strtok(command, " ");
	while(split != NULL)
	{
		split_commands[index] = split;
		index++;
		split = strtok(NULL, " ");
	}
	split_commands[index] = NULL;
	/* ========== */
	
	if(strstr(split_commands[0], "end"))
	return 0;
	else if(strstr(split_commands[0], "cd"))
	{
		chdir(split_commands[1]);
		return 1;
	}
	/* ==========*/
	pid_t pd, wait_pd;
	int ret;
	pd = fork();
	if(pd == 0)
	{
		if(execvp(split_commands[0], split_commands) == -1)
			printf("error in exxecution (pd < 0)\n");	
	}
	else if(pd < 0)
	{
		printf("error in execution => (pd < 0)\n");
	}
	else
	{
		do
		{
			wait_pd = waitpid(pd, &ret, WUNTRACED);
		}while(!WIFEXITED(ret) && !WIFSIGNALED(ret));
	}
	if(pd == wait_pd) {}
	return 1;
}

char *read_line(void)
{
  int position = 0;
  char *buffer = malloc(sizeof(char) * 1024);
  int c;

  if (!buffer) {
    fprintf(stderr, "allocation error\n");
    exit(-1);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;
    }
}
