#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 3)
	{
		printf("Usage: sendsig <signal type> <pid>\n");
		exit(1);
	}	
	if(strcmp(argv[1],"-u") == 0)
	{
		if(kill(atoi(argv[2]), SIGUSR1) == -1)
		{
			printf("User defined signal was not sent through\n");
			exit(1);
		}
	}
	if(strcmp(argv[1],"-i") == 0)
	{
		if(kill(atoi(argv[2]), SIGINT) == -1)
		{
			printf("Interrupt signal was not sent through\n");
			exit(1);
		}
	}
}
