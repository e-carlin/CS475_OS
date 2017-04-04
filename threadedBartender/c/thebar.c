/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"


void printBanner();
void init();
void cleanup();


/**
 * Main function
 */
int main(int argc, char** argv)
{
	printBanner();
	init();		//initialize semaphores

	//Fire off customer threads
	if(argv[1] == NULL){
		printf("Number of customers must be given\n");
		exit(1);
	}

	//Create array for customer threads
	num_threads = atoi(argv[1]);
	pthread_t *customerThreads = (pthread_t*) malloc(sizeof(pthread_t) * num_threads);
	//Create an array for their id args
	int *threadIDs = (int *) malloc(sizeof(int) * num_threads);
	

	int i;
	for(i=0; i<num_threads; i++){
		//TODO: the arg for customer is wrong
		threadIDs[i] = i;
		pthread_create(&customerThreads[i], NULL, customer, &threadIDs[i]);

	}


	//Fire off bartender thread
	pthread_t *bartenderThread = (pthread_t*) malloc(sizeof(pthread_t) * 1);
	pthread_create(&bartenderThread[0], NULL, bartender, NULL);

	//Wait for all threads to finish
	//Wait for customer threads
	for (i=0; i<num_threads; i++){
	    pthread_join(customerThreads[i], NULL);
	}
	//Wait for bartender thread
	pthread_join(bartenderThread[0], NULL);

	free(customerThreads);
	cleanup();	//cleanup and destroy semaphores
	return 0;
}


/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner() {
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("------------------------------------------------------------\n");
}


/**
 * Create and initialize semaphores
 */
void init()
{
	//Unlink old semaphores
	sem_unlink("/customerHere");
	sem_unlink("/roomToEnterBar");
	sem_unlink("/orderPlaced");
	sem_unlink("/orderReady");
	sem_unlink("/doneBrowsingArt");
	// sem_unlink("/");

	//Create semaphores
	customerHere = sem_open("/customerHere", O_CREAT, 0600, 0);
	roomToEnterBar = sem_open("/roomToEnterBar", O_CREAT, 0600, 0);
	orderPlaced = sem_open("/orderPlaced", O_CREAT, 0600, 0);
	orderReady = sem_open("/orderReady", O_CREAT, 0600, 0);
	doneBrowsingArt = sem_open("/doneBrowsingArt", O_CREAT, 0600, 0);
	// = sem_open("/", O_CREAT, 0600, 0);
}


/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{	
	sem_close(customerHere);
	sem_close(roomToEnterBar);
	sem_close(orderPlaced);
	sem_close(orderReady);
	sem_close(doneBrowsingArt);
	// sem_close();

	sem_unlink("/customerHere");
	sem_unlink("/roomToEnterBar");
	sem_unlink("/orderPlaced");
	sem_unlink("/orderReady");
	sem_unlink("/doneBrowsingArt");
	// sem_unlink("/");
}
