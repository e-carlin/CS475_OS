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
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void* bartender(void* args){

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

	//TODO: Random wait

	sem_post(orderReady);
}


/**
 * Gets payment from the correct customer
 */
void receivePayment(){
	
	//at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	sem_wait(doneBrowsingArt);

	//got the payment from the right customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");

	//Let in another customer
}
