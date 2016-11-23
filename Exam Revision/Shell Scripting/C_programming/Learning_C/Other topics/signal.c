/*
	Name: Matthew Ta
	Date: 24/11/2015
	Description: Experimenting with signal handling
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <assert.h>

#define MAX_NUM 100
#define SIG_NUM 50

#define TRUE 1
#define FALSE 0

void signalHandler(int signalV); // function to deal with signals

int main(void)
{
	int i = 0, x;

	srand(time(NULL)); // randomize seed
	signal(SIGINT, signalHandler); // initialize the signal handler
	
	for (i = 0; i < MAX_NUM; i++){
		x = rand() % MAX_NUM;
		if (x == SIG_NUM){
			raise(SIGINT);
		}

		printf("%d ", i);
		if (i % 10 == 0){ printf("\n"); }
	}

	printf("\n");

	return EXIT_SUCCESS;
}

void signalHandler(int signalV)
{
	int cont = FALSE;
	printf("\nReceived intterupt signal: %d\n", signalV);
	printf("Do you wish to continue? ");
	scanf("%d", &cont);
		
	if (cont == TRUE){
		signal(SIGINT, signalHandler); // re-initialise the signal handler
	}

	else{
		exit(EXIT_SUCCESS);
	}
}
