/*
 * customer.c
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
#include "customer.h"

/**
 * This is what the thread will call.
 * Do not touch.
 */
void* customer(void* args){

	//Seed random number generator
	srand(time(NULL));

	//Do customer tasks
	unsigned int *custID = (unsigned int*) args;
	custTravelToBar(*custID);
	custArriveAtBar(*custID);
	custPlaceOrder();
	custBrowseArt();
	custAtRegister();
	custLeaveBar();
	return NULL;
}


/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 */
void custTravelToBar(unsigned int custID){

	printf("Cust %u\t\t\t\t\t\t\t\t\t\t\t|\n", custID);

	//Random sleep time for traveling to the bar
	struct timespec slptm;
	long randSleep = rand() % 4980; //Random num between 0 and 4980
	slptm.tv_sec = 0;
	slptm.tv_nsec = (20 + randSleep) * 1000000; //Sleep for between 20ms and 5000ms
	nanosleep(&slptm, NULL);

	sem_post(customerHere);
}


/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 */
void custArriveAtBar(unsigned int custID){

	printf("\t\tCust %u\t\t\t\t\t\t\t\t\t|\n", custID);

	//Wait for space in the bar
	sem_wait(roomToEnterBar);

	//Customer has been let in so let everyone know bartender is serving them 
	nowServing = custID;
}


/**
 * The customer in the bar places an order
 */
void custPlaceOrder(){

	printf("\t\t\t\tCust %u\t\t\t\t\t\t\t|\n", nowServing);
	sem_post(orderPlaced);
}


/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 */
void custBrowseArt(){
 
	printf("\t\t\t\t\t\tCust %u\t\t\t\t\t|\n", nowServing);

	//Random wait for browsing art time
	struct timespec slptm;
	long randSleep = rand() % 3997; //Random num between 0 and 3997
	slptm.tv_sec = 0;
	slptm.tv_nsec = (3 + randSleep) * 1000000; //Sleep for between 5ms and 1000ms
	nanosleep(&slptm, NULL);

}


/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 *
 */
void custAtRegister(){

	//Wait at the register for the bartender to finish mixing the drink
	printf("\t\t\t\t\t\t\t\tCust %u\t\t\t|\n", nowServing);
	sem_wait(orderReady);

	//Pay the partender
	sem_post(paidForDrink);
}


/**
 * The customer in the bar leaves.
 */
void custLeaveBar(){

	//Wait for bartender to receive payment
	sem_wait(paymentReceived);

	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", nowServing);
	sem_post(customerGone);
}
