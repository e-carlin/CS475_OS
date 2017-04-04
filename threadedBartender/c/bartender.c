/*
 * bartender.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void* bartender(void* args){

	//Seed random number generator
	srand(time(NULL));

	//Perform barteding tasks
	int i;
	for (i = 0; i<num_threads; i++)
	{
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 */
void waitForCustomer(){ 

	//Show tender is waiting
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");

	//Wait for a customer to enter
	sem_wait(customerHere);
}


/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 */
void makeDrink(){

	//Let in a customer
	sem_post(roomToEnterBar);
	
	//Wait for customer to place order
	sem_wait(orderPlaced);


	//Show tender is making a drink
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");

	//Random wait for making drink time
	msSleep(5, 1000);

	//The order is ready
	sem_post(orderReady);
}


/**
 * Gets payment from the correct customer
 */
void receivePayment(){
	
	//At the register waiting for customer tofinish browsing art and then pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	//Waiting for customer to pay
	sem_wait(paidForDrink);

	//Got the payment from the right customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
	sem_post(paymentReceived);

	//Wait for the customer to leave
	sem_wait(customerGone);	
}
