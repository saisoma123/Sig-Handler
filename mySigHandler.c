#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
int seconds = 4;
int usercount;
void alarm_handler()
{
	time_t curtime;
	if(time(&curtime) == (time_t)-1)
	{
		printf("Time function error");
		exit(0);
	}
	char *date = ctime(&curtime); 
	if(date == NULL)
	{
		printf("Date function error");
		exit(0);
	}
	printf("PID: %d CURRENT: %s", getpid(), date);
	alarm(seconds);
}
void user_handler()
{
	usercount++;
	printf("SIGUSR1 handled and counted!\n");
	
}
void user_count()
{
        printf("\n");
	printf("SIGINT handled.\n");
	if(usercount == 1)
        {
		printf("SIGUSR1 was handled %d time. Exiting now.\n", usercount);
        }
        else
        {
                printf("SIGUSR1 was handled %d times. Exiting now.\n", usercount);
        }
	exit(0);
}
int main()
{
	alarm(seconds);

	struct sigaction act;
	if(memset (&act, 0, sizeof(act)) == NULL)
	{
		printf("Clearing for sigaction struct failed\n");
		exit(1);
	}
	act.sa_handler = alarm_handler;
	if(sigaction(SIGALRM, &act, NULL) != 0)
	{
		printf("Not able to process SIGALRM\n");
		exit(1);
	}
	
	

	struct sigaction useract;
	if(memset (&useract, 0, sizeof(useract)) == NULL)
	{
		printf("Clearing for sigaction struct failed\n");
                exit(1);
	}
	useract.sa_handler = user_handler;
	if(sigaction(SIGUSR1, &useract, NULL) != 0)
	{
		printf("Not able to process SIGUSR1\n");
                exit(1);
	}
	
	struct sigaction ucount;
	if(memset (&ucount, 0, sizeof(ucount)) == NULL)
	{
		printf("Clearing for sigaction struct failed\n");
                exit(1);
	}
	ucount.sa_handler = user_count;
	if(sigaction(SIGINT, &ucount, NULL) != 0)
	{
		printf("Not able to process SIGINT\n");
                exit(1);
	}

	printf("PID and time print every 4 seconds.\n");
	printf("Type Ctrl-C to end the program.\n");
	
	while (1)
	{

	}
}
