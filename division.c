#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
int counter;
void zero_handler()
{
	printf("Error: a division by 0 operation was attempted.\n");
	printf("Total number of operations completed successfully: %d\n", counter);
	printf("The program will be terminated.\n");
	exit(0);
}
void user_handler()
{
	printf("\nTotal number of operations completed successfully: %d\n", counter);
        printf("The program will be terminated.\n");
        exit(0);
}
int main()
{
	struct sigaction zeroex;
	if(memset (&zeroex, 0, sizeof(zeroex)) == NULL)
	{
		printf("Clearing for sigaction struct failed\n");
                exit(1);
	}		
	zeroex.sa_handler = zero_handler;
	if(sigaction(SIGFPE, &zeroex, NULL) != 0)
	{
		printf("Not able to process SIGFPE\n");
		exit(1);
	}
	
	struct sigaction divcount;
	if(memset (&divcount, 0, sizeof(divcount)) == NULL)
	{
		printf("Clearing for sigaction struct failed\n");
                exit(1);
	}
	divcount.sa_handler = user_handler;
	if(sigaction(SIGINT, &divcount, NULL) != 0)
	{
		printf("Not able to process SIGINT\n");
		exit(1);
	}
	while(1)
	{
		char buffer[100];

		printf("Enter first integer: ");
		if(fgets(buffer, 100, stdin) == NULL)
		{
			printf("Read input error\n");
			exit(1);
		}
		int first = atoi(buffer);
		
		printf("Enter second integer: ");
		if(fgets(buffer, 100, stdin) == NULL)
		{
			printf("Read input error\n");
			exit(1);
		}
		int second = atoi(buffer);
		
		int division = first / second;
		int remainder = first % second;
		printf("%d / %d is %d with a remainder of %d \n", first, second, division, remainder);
		counter++;
	}
}	
